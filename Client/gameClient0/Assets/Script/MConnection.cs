using Assets.Script.Proto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;

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

        private static int status=1;//当前网络--》服务器的状态   0:已连接   1:未连接

       
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
                msocket.Connect(new IPEndPoint(ip, port));
                MLogger.Log(Log.MLogLevel.INFO, Log.MLogType.LanuchLog, "连接服务器成功..");
                status = 0;
            }
            catch {
                MLogger.Log(Log.MLogLevel.ERROR, Log.MLogType.LanuchLog, "连接服务器失败..");
                status = 1;
            }
        }

        //发送协议
        
        public  static int Send(Message mproto){

            if (0 != status)
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

        public static MConnection GetInstance() {
            if (null == _instance)
                _instance = new MConnection();
            return _instance;
        
        }
        

    }
}
