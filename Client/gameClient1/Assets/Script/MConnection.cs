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
     * 将所有收到的协议先解包，然后加入到List里面去，然后在主线程update中执行实际的业务逻辑
     * 
     * */
    class MConnection
    {
        
        //public delegate void DoAction(object sender, EventArgs e);

        private static MConnection _instance=null;
        private const string ipAddr = "182.254.233.115";
        private const int port = 9201;
        private Socket msocket=null;
        private Thread thread;

        //所有受到的协议包经过解码之后放到这里，然后主线程中某个一直存在的空对象脚本update里面执行
        public List<Message_toc> package=new List<Message_toc>();

       
        private MConnection() {
            Init();
        }
        public static MConnection GetInstance()
        {
            if (null == _instance)
                _instance = new MConnection();
            return _instance;

        }

        //游戏关闭时要执行该函数
        public void Destroy()
        {
            if (msocket.Connected)
                msocket.Close();
            if (thread.IsAlive)
                thread.Abort();

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
        
        public  int Send(Message_tos mproto){

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
        public void Receive(){
           
            while (true)
            {
                //如果和服务器断开了连接，就跳出循环
                if (!msocket.Connected&&null!=msocket) {
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
                    //进入装包程序，根据ID，将协议内容转换成具体的Message_toc的子类对象，装入到pack list中
                    MPack(idNum);
                }
                catch (Exception e)
                {
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "get the proto exceptions " + e.Message);
                    break;
                }

            }           
        
        }

        //装包程序，根据ID，将协议内容转换成具体的Message_toc的子类对象，装入到pack list中
        //超长版switch来袭，恶心就恶心吧~~~
        protected void MPack(int id) {
            switch (id) {
                case protoID.ErrID://错误toc
                        { 
                            //频繁新建对象会造成很大的内存损耗，以后再解决这个问题
                            Err_toc temp=new Err_toc();//C#貌似直接获取长度会有bug，稳妥点，直接新建一个来确定
                            byte[] buffer = new byte[Marshal.SizeOf(temp)];

                            int recvLength = msocket.Receive(buffer);

                              if (Marshal.SizeOf(temp) == recvLength)//收到正确的包
                                {
                                   Err_toc tp = (Err_toc)MTransform.BytesToStruct(buffer, typeof(Err_toc));
                                   //加入到List中
                                   package.Add(tp);
                                 }
                              else {
                                   MLogger.Log(Log.MLogLevel.ERROR, Log.MLogType.ProtoLog, "接收包错误:" + id + "  长度不一致");
                                }  

                    
                         }
                         break;
                case protoID.LanuchResultID://获取登录结果
                         {
                             LanuchResult_toc temp = new LanuchResult_toc();
                             byte[] buffer = new byte[Marshal.SizeOf(temp)];

                             int recvLength = msocket.Receive(buffer);

                             if (Marshal.SizeOf(temp) == recvLength)//收到正确的包
                             {
                                 LanuchResult_toc tp = (LanuchResult_toc)MTransform.BytesToStruct(buffer, typeof(LanuchResult_toc));
                                 //加入到List中
                                 package.Add(tp);

                                 string name = new string(tp.name);
                                 string time = new string(tp.lastLanuch);
                                 string ip = new string(tp.lastIP);

                                 MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "err_code="+tp.error_code+"name=" + name + " last time=" + time + "  ip=" + ip+"  setting="+tp.setting);

                             }
                             else
                             {
                                 MLogger.Log(Log.MLogLevel.ERROR, Log.MLogType.ProtoLog, "接收包错误:" + id + "  长度不一致");
                             }  
                         
                         
                         
                         }
                         break;
            
            
            
            
            }
            //收到一个即关闭socket，杀死后台线程，避免假死
            Destroy();
        
        }




       


    }
}
