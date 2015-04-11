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
     * */
    class MConnection
    {
        private static MConnection _instance=null;
        private static string ipAddr = "182.254.233.115";
        private static int port = 9201;
        private static Socket msocket=null;
        private static Thread thread;

        private static int status=1;//当前网络--》服务器的状态   0:已连接   1:未连接
        private static bool statusFlag=false; //用来标记是否已打印网络未连接log

       
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
                    status = 0;
                    //开启线程接收数据
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
                    status = 1;
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.LanuchLog, "连接服务器超时..");
                }
            }
            catch {
                MLogger.Log(Log.MLogLevel.ERROR, Log.MLogType.LanuchLog, "出现异常，连接服务器失败..");
                status = 1;
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
                msocket.Send(buffer);
                MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, mproto.GetType().ToString() + " proto send success!protoID="+mproto.GetID());
                return 0;
            }
            catch {
                MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, mproto.GetType().ToString() + " proto send failed! protoID="+mproto.GetID());
                return -1;
            }
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
                        MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "收到错误的包...，");
                        MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "客户端主动断开连接....");
                        msocket.Close();
                        break;
                    }

                    int idNum = System.BitConverter.ToInt32(id, 0);
                    MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.ProtoLog, "get the proto  " + idNum);
                    //获取后面的内容

                    byte[] buffer;
                    int recvLength = 0;
                    switch (idNum) { 
                        case protoID.pLanuchResult: 
                            LanuchResult_toc temp=new LanuchResult_toc();
                            buffer = new byte[Marshal.SizeOf(temp)];
                            //buffer = new byte[128];
                            recvLength = msocket.Receive(buffer);
                            //由这里测试发现是客户端从byte转struct的时候出了问题
                            //char []c=Encoding.ASCII.GetChars(buffer);
                            Type type = typeof(LanuchResult_toc);
                            LanuchResult_toc pr= (LanuchResult_toc)MTransform.BytesToStruct(buffer, type);
                            

                            string n=new string(pr.name);
                            string time = new string(pr.lastLanuch);
                            string lip = new string(pr.lastIP);
                            if(0==pr.error_code)
                                MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.LanuchLog,"name="+n+"  ip=" + lip + "  time=" +time + "  setting=" + pr.setting);
                            else
                                MLogger.Log(Log.MLogLevel.DEBUG, Log.MLogType.LanuchLog, "LanuchResult error_code not ==0");
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
