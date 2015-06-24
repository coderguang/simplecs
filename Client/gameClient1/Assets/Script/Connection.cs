﻿using Assets.Script.Proto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using UnityEngine;
using System.Diagnostics;

namespace Assets.Script {
    /**
     * 客户端的网络模块，包括socket的发起，协议的收发
     * 将所有收到的协议先解包，然后加入到List里面去，然后在主线程update中执行实际的业务逻辑
     * 
     * */
    class Connection {
        private static Connection _instance = null;
        private const string ipAddr = "182.254.233.115";
        private const int port = 9201;//接收本用户的port
        private const int boardcastPort = 9205;//接收广播的port

        private Socket msocket = null;
        private Socket bsocket = null;//接收广播的socket

        private Thread mthread;
        private Thread bthread;//广播的thread

        //所有受到的协议包经过解码之后放到这里，然后主线程中某个一直存在的空对象脚本update里面执行
        public Queue<Message> package = new Queue<Message>();
        //用于控制队列访问(添加，删除）的锁
        public static object objLock = new object();


        private Connection() {
            Init();
        }
        public static Connection GetInstance() {
            if (null == _instance)
                _instance = new Connection();
            return _instance;

        }

        //游戏关闭时要执行该函数
        //由NullObj脚本对象释放时调用
        //否则编辑器会假死，socket未断开，后台线程似乎也不会关闭
        /**http://blog.sina.com.cn/s/blog_62cff5e00102v3px.html **/
        public void Destroy() {
            if (msocket.Connected)
                msocket.Close();
            if (mthread.IsAlive)
                mthread.Abort();

            if (bsocket.Connected)
                bsocket.Close();
            if (bthread.IsAlive)
                bthread.Abort();


        }
        //在Init中建立普通socket tcp连接
        private void Init() {
            IPAddress ip = IPAddress.Parse(ipAddr);
            msocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            //尝试连接
            try {
                /*http://www.xuanyusong.com/archives/1948*/
                //异步建立TCP
                IPEndPoint ipEndPoint = new IPEndPoint(ip, port);
                //msocket.Connect(new IPEndPoint(ip, port));
                //建立成功后会调用connectCallBack方法
                IAsyncResult result = msocket.BeginConnect(ipEndPoint, new AsyncCallback(mconnectCallBack), msocket);

                //超时检测
                bool success = result.AsyncWaitHandle.WaitOne(10000, true);
                if (success) {
                    GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, "异步普通socket任务开启..");

                    //开启线程接收数据
                    /**先调好协议，传输时不会出现bug(协议数据的后面会有莫名的字符)再说**/
                    /**仅在调试下才会出现该bug，build之后该bug消失**/
                    mthread = new Thread(new ThreadStart(mReceive));
                    mthread.IsBackground = true;
                    mthread.Start();

                } else {
                    //关闭socket
                    if (msocket != null && msocket.Connected) {
                        msocket.Shutdown(SocketShutdown.Both);
                        msocket.Close();
                    }
                    msocket = null;
                    GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.Conect, "连接服务器超时..");
                }
            } catch {
                GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.Conect, "出现异常，连接服务器失败..");
            }


            //检测socket是否处于连接状态
            if (!msocket.Connected) {
                LanuchGame.err_code = ErrCode.NETWORD_ERROR;
                LanuchGame.tipFlag = true;
            }



        }

        //登录正确时，开启接收广播信息的socket，该socket仅负责接收广播消息
        public void BeginBoardcastSocket() {
            IPAddress ip = IPAddress.Parse(ipAddr);
            bsocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            //尝试连接
            try {
                /*http://www.xuanyusong.com/archives/1948*/
                //异步建立TCP
                IPEndPoint ipEndPoint = new IPEndPoint(ip, boardcastPort);
                //msocket.Connect(new IPEndPoint(ip, port));
                //建立成功后会调用connectCallBack方法
                IAsyncResult result = bsocket.BeginConnect(ipEndPoint, new AsyncCallback(mconnectCallBack), bsocket);

                //超时检测
                bool success = result.AsyncWaitHandle.WaitOne(10000, true);
                if (success) {
                    GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, "异步广播socket任务开启..");

                    //开启线程接收数据
                    /**先调好协议，传输时不会出现bug(协议数据的后面会有莫名的字符)再说**/
                    /**仅在调试下才会出现该bug，build之后该bug消失**/
                    bthread = new Thread(new ThreadStart(mReceive));
                    bthread.IsBackground = true;
                    bthread.Start();

                } else {
                    //关闭socket
                    if (bsocket != null && bsocket.Connected) {
                        bsocket.Shutdown(SocketShutdown.Both);
                        bsocket.Close();
                    }
                    bsocket = null;
                    GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.Conect, "广播socket连接服务器超时..");
                }
            } catch {
                GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.Conect, "广播socket出现异常，连接服务器失败..");
            }
        }



        public void mconnectCallBack(IAsyncResult asyncConnect) {
            GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, "建立普通异步连接成功");
        }

        public void bconnectCallBack(IAsyncResult asyncConnect) {
            GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, "建立广播异步连接成功");
        }


        //发送协议

        public int Send(Message mproto) {

            if (!msocket.Connected) {
                GameLog.Log(Log.GameLogLevel.FATAL, Log.GameLogType.Conect, "网络断开...");
                Application.Quit();
            }

            byte[] buffer = MTransform.StructToBytes(mproto);
            try {
                //使用异步来send协议
                //msocket.Send(buffer);
                IAsyncResult asySend = msocket.BeginSend(buffer, 0, buffer.Length, SocketFlags.None, new AsyncCallback(sendCallback), msocket);
                //超时监控
                bool success = asySend.AsyncWaitHandle.WaitOne(5000, true);
                if (success)
                    GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, mproto.GetType().ToString() + " proto send success!protoID=" + mproto.GetID());
                else
                    GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.Conect, mproto.GetType().ToString() + " proto send timeout! protoID=" + mproto.GetID());
                return 0;
            } catch {
                GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.ProtoLog, mproto.GetType().ToString() + " proto send failed! protoID=" + mproto.GetID());
                return -1;
            }
        }

        //send callback
        private static void sendCallback(IAsyncResult ar) {
            //发送返回不做任何事情
            //throw new NotImplementedException();
        }


        //客户端将在后台线程中执行该函数，直到普通协议过来，进行相应的内容
        public void mReceive() {

            while (true) {
                //如果和服务器断开了连接，就跳出循环
                if (!msocket.Connected && null != msocket) {
                    GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.Conect, "普通socket已经和服务器断开连接.....");
                    msocket.Close();
                    break;
                }

                try {
                    //首先获取协议的ID
                    //先获取一整个的包
                    byte[] buffer = new byte[512];
                    //Receive是阻塞的，知道数据过来才会继续执行
                    int rid = msocket.Receive(buffer);
                    if (rid <= 0) {
                        GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, "普通socket收到错误的包...，客户端主动断开连接....");
                        msocket.Close();
                        break;
                    }

                    MPack(ref(buffer));

                } catch (Exception e) {
                    GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, "普通socket get the proto exceptions " + e.Message);
                    break;
                }

            }

        }

        //客户端将在后台线程中执行该函数，直到广播协议过来，进行相应的内容
        public void bReceive() {

            while (true) {
                //如果和服务器断开了连接，就跳出循环
                if (!bsocket.Connected && null != bsocket) {
                    GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.Conect, "广播socket已经和服务器断开连接.....");
                    bsocket.Close();
                    break;
                }

                try {
                    //首先获取协议的ID
                    //先获取一整个的包
                    byte[] buffer = new byte[512];
                    //bReceive是阻塞的，知道数据过来才会继续执行
                    int rid = msocket.Receive(buffer);
                    if (rid <= 0) {
                        GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, "广播socket收到错误的包...，客户端主动断开连接....");
                        bsocket.Close();
                        break;
                    }

                    MPack(ref(buffer));

                } catch (Exception e) {
                    GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.Conect, "广播socket get the proto exceptions " + e.Message);
                    break;
                }

            }

        }



        //无法由更高层次的转为低层次的类别，该函数无用
        private void AddToPack(ref Message msg) {
            lock (objLock) {
                package.Enqueue(msg);
            }

        }


        //装包程序，根据ID，将协议内容转换成具体的Message_toc的子类对象，装入到pack list中
        //超长版switch来袭，恶心就恶心吧~~~

        private const int idSize = 4;


        /**http://xiehuawei.me/blog/2014/11/20/unity-multithread/ **/

        protected void MPack(ref byte[] buffer) {

            byte[] idByte = new byte[idSize];

            if (idSize > buffer.Length)//如果整个包的长度小于4，说明这个包有问题，丢弃
                return;


            for (int i = 0; i < idSize; i++) {
                idByte[i] = buffer[i];
            }

            int id = System.BitConverter.ToInt32(idByte, 0);
            switch (id) {
                case ProtoID.ErrID://错误toc
                    {
                        //频繁新建对象会造成很大的内存损耗，以后再解决这个问题
                        //Err_toc temp = new Err_toc();//C#貌似直接获取长度会有bug，稳妥点，直接新建一个来确定
                        //byte[] buf = new byte[Marshal.SizeOf(temp)];

                        Err_toc temp = (Err_toc)MTransform.BytesToStruct(buffer, typeof(Err_toc));

                        lock (objLock) {
                            package.Enqueue(temp);
                        }
                    }
                    break;
                case ProtoID.LanuchResultID://获取登录结果
                    {
                        //LanuchResult_toc temp = new LanuchResult_toc();
                        //byte[] buf = new byte[Marshal.SizeOf(temp)];


                        // Type type = typeof(LanuchResult_toc);
                        LanuchResult_toc tp = (LanuchResult_toc)MTransform.BytesToStruct(buffer, typeof(LanuchResult_toc));
                        lock (objLock) {
                            //加入到List中
                            package.Enqueue(tp);
                        }
                        string name = new string(tp.name,0,tp.namelen);
                        string time = new string(tp.lastLanuch,0,tp.timelen);
                        string ip = new string(tp.lastIP,0,tp.iplen);

                        GameLog.Log(Log.GameLogLevel.INFO, Log.GameLogType.ProtoLog, "err_code=" + tp.error_code + "  name=" + name + " last time=" + time + "  ip=" + ip + "  setting=" + tp.setting);


                    }
                    break;
                case ProtoID.PartyID://获取房间分组信息
                    {
                        Party_toc temp = (Party_toc)MTransform.BytesToStruct(buffer, typeof(Party_toc));
                        lock (objLock) {
                            //加入到List中
                            package.Enqueue(temp);
                        }

                    }
                    break;
                case ProtoID.ChatID://房间内的聊天信息
                    {
                        Chat_tocs temp = (Chat_tocs)MTransform.BytesToStruct(buffer, typeof(Chat_tocs));
                        lock (objLock) {
                            package.Enqueue(temp);
                        }

                    }
                    break;
                case ProtoID.PartyChangeID://更改分组信息
                    {
                        Party_change_tocs temp = (Party_change_tocs)MTransform.BytesToStruct(buffer, typeof(Party_change_tocs));
                        lock (objLock) {
                            package.Enqueue(temp);
                        }

                    }
                    break;
                case ProtoID.GameStartID://开始游戏信号
                    {
                        GameStart_tocs temp = (GameStart_tocs)MTransform.BytesToStruct(buffer, typeof(GameStart_tocs));
                        lock (objLock) {
                            package.Enqueue(temp);
                        }
                    }
                    break;
                case ProtoID.PosID: {
                    Pos_tocs temp = (Pos_tocs)MTransform.BytesToStruct(buffer, typeof(Pos_tocs));
                        lock (objLock) {
                            package.Enqueue(temp);
                        }
                    }
                    break;



            }
            //收到一个即关闭socket，杀死后台线程，避免假死
            //Destroy();

        }







    }
}
