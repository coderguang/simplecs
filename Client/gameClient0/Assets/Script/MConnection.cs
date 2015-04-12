using Assets.Script.Proto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using UnityEngine;

namespace Assets.Script
{
    /**
     * 客户端的网络模块，包括socket的发起，协议的收发
     * 
     * 同时是事件模型的核心，所有关于协议触发的事件均在这里产生
     * 为了降低难度，不使用事件模型
     * */
    class MConnection
    {
        //声明事件委托
        //public delegate void DoAction(object sender, EventArgs e);

        private static MConnection _instance=null;
        private static string ipAddr = "182.254.233.115";
        private static int port = 9201;
        private static Socket msocket=null;
        private static Thread thread;


       
        private MConnection() {
            Init();
        }
        //在Init中建立socket tcp连接
        private void Init() {
            IPAddress ip = IPAddress.Parse(ipAddr);
            msocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            //尝试连接
            try
            {
                /*http://www.xuanyusong.com/archives/1948*/
                //异步建立TCP
                IPEndPoint ipEndPoint=new IPEndPoint(ip,port);
                //msocket.Connect(new IPEndPoint(ip, port));
                //建立成功后会调用connectCallBack方法
                IAsyncResult result = msocket.BeginConnect(ipEndPoint, new AsyncCallback(connectCallBack), msocket);

                //超时检测
                bool success = result.AsyncWaitHandle.WaitOne(10000, true);
                if (success)
                {
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.LanuchLog, "连接服务器成功..");

                    //开启线程接收数据
                    /**先调好协议，传输时不会出现bug(协议数据的后面会有莫名的字符)再说**/
                    /**仅在调试下才会出现该bug，build之后该bug消失**/
                    thread = new Thread(new ThreadStart(Receive));
                    thread.IsBackground = true;
                    thread.Start();
                     
                }
                else { 
                    //关闭socket
                    if (msocket != null && msocket.Connected) {
                        msocket.Shutdown(SocketShutdown.Both);
                        msocket.Close();
                    }
                    msocket = null;
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.LanuchLog, "连接服务器超时..");
                }
            }
            catch {
                MLogger.Log(Log.MLogLevel.ERROR, Log.MLogType.LanuchLog, "出现异常，连接服务器失败..");
            }
        }

        public void connectCallBack(IAsyncResult asyncConnect) {
            MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "建立异步连接成功");
        }
        

        //发送协议
        
        public  static int Send(Message_tos mproto){

            if (!msocket.Connected)
            {
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "网络未连接...");
                    return -2;
            }

            byte[] buffer = MTransform.StructToBytes(mproto);
            try
            {
                //使用异步来send协议
                //msocket.Send(buffer);
                IAsyncResult asySend = msocket.BeginSend(buffer, 0, buffer.Length, SocketFlags.None, new AsyncCallback(sendCallback), msocket);
                //超时监控
                bool success = asySend.AsyncWaitHandle.WaitOne(5000, true);
                if(success)
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, mproto.GetType().ToString() + " proto send success!protoID="+mproto.GetID());
                else
                   MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, mproto.GetType().ToString() + " proto send timeout! protoID=" + mproto.GetID());
                return 0;
            }
            catch {
                MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, mproto.GetType().ToString() + " proto send failed! protoID="+mproto.GetID());
                return -1;
            }
        }

        //send callback
        private static void sendCallback(IAsyncResult ar)
        {
            //发送返回不做任何事情
            //throw new NotImplementedException();
        }

        //客户端将在后台线程中执行该函数，直到协议过来，进行相应的内容
        public static void Receive(){
           
            while (true)
            {
                //如果和服务器断开了连接，就跳出循环
                if (!msocket.Connected) {
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "已经和服务器断开连接.....");
                    msocket.Close();
                    break;
                }

                try
                {
                    //首先获取协议的ID
                    byte[] id = new byte[4];
                    //Receive是阻塞的，知道数据过来才会继续执行
                    int rid = msocket.Receive(id);
                    if (rid <= 0)
                    {
                        MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "收到错误的包...，客户端主动断开连接....");
                        msocket.Close();
                        break;
                    }

                    int idNum = System.BitConverter.ToInt32(id, 0);
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "get the proto  " + idNum);
                    //获取后面的内容

                  
                    //下面是一个基于事件驱动的模型
                    //该类为
                    switch (idNum) {
                           
                        case protoID.LanuchResultID://获取登录结果
                            {
                                LanuchResult_toc temp = new LanuchResult_toc();
                                byte[] buffer = new byte[Marshal.SizeOf(temp)];
                                //buffer = new byte[128];
                                int recvLength = msocket.Receive(buffer);

                                //MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "获取登录结果协议,长度:"+recvLength);
                                //由这里测试发现是客户端从byte转struct的时候出了问题
                                //char []c=Encoding.ASCII.GetChars(buffer);
                                Type type = typeof(LanuchResult_toc);
                                LanuchResult_toc pr = (LanuchResult_toc)MTransform.BytesToStruct(buffer, type);
                                string n = new string(pr.name);
                                string time = new string(pr.lastLanuch);
                                string lip = new string(pr.lastIP);
                                if (0 == pr.error_code)
                                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.LanuchLog, "name=" + n + "  ip=" + lip + "  time=" + time + "  setting=" + pr.setting);
                            }
                            break;
                        case protoID.ErrID: //获取错误ID
                            {
                                byte[] code = new byte[4];
                                int recvLength = msocket.Receive(code);//获取错误码
                                int codeNum = System.BitConverter.ToInt32(code, 0);
                                MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.GameLog, "err_code=" + codeNum);
                                switch (codeNum) {
                                    case ErrCode.ACCOUNT_ERR_PASSWD: {
                                        /**Unity中,你仅能从主线程中访问Unity的组件,对象和Unity系统调用.任何企图访问这些项目的第二个线程都将失败并引发错误.这是一个要重视的一个限制.**/
                                        //LanuchGame.GetInstance().ShowStatus(ErrCode.ACCOUNT_ERR_PASSWD);
                                        (new LanuchGame()).ShowStatus(ErrCode.ACCOUNT_ERR_PASSWD);
                                    }
                                        break;
                                    case ErrCode.ACCOUNT_HAD_LANUCH: {
                                        //LanuchGame.GetInstance().ShowStatus(ErrCode.ACCOUNT_HAD_LANUCH);
                                        (new LanuchGame()).ShowStatus(ErrCode.ACCOUNT_HAD_LANUCH);
                                    }
                                        break;
                                     
                                
                                
                                
                                }

                            
                            
                            }
                            break;
                    
                    
                    }




                }
                catch (Exception e)
                {
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "get the proto exceptions " + e.Message);
                    break;
                }

            }
            
            //销毁线程
            thread.Abort();
        
        }




        public static MConnection GetInstance() {
            if (null == _instance)
                _instance = new MConnection();
            return _instance;
        
        }
        

    }
}
