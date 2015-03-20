using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;//for StructLayoutAttribute
namespace winClient2
{
    [Serializable]
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)]
    public struct Test
    {
        public int id;
        public int first;
        public int second;
        public int error;
        //字符串
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 512)]
        public char[] msg;
        
        public Test(int one, int two,  int err,string str)
        {
            this.id = 1000;
            this.first = one;
            this.second = two;
            //this.msg =str.ToCharArray();
            this.msg = str.PadRight(512, '\0').ToCharArray();
            this.error = err;
        }
    }
    [Serializable]
    [StructLayoutAttribute(LayoutKind.Sequential,CharSet=CharSet.Unicode,Pack=1)]
    public struct  Test2 {
        public int id;
        public int first;
        public int second;
        public Test2(int one, int two) {
            this.id = 1001;
            this.first = one;
            this.second = two;
        }

    }
    class Program
    { 
        static void Main(string[] args)
        {
            IPAddress ip = IPAddress.Parse("182.254.233.115");
            Random rd=new Random();
            int mPort = 9201;
            Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        
            try
            {  
                clientSocket.Connect(new IPEndPoint(ip, mPort)); //配置服务器IP与端口
                Console.WriteLine("连接服务器成功");
            }
            catch
            {
                Console.WriteLine("连接服务器失败，请按回车键退出！");
                Console.ReadKey();
                return;
            }

            Test tst=new Test(11,18,456,"hello,this is guang client,你好啊");
            string stt=new string(tst.msg);
            char[] ttt = stt.ToCharArray();
            Console.WriteLine("first={0},second={1},msg={2},err={3}", tst.first, tst.second, tst.msg,tst.error);
            Console.WriteLine(tst.msg);
            int counts = 0;
            int MAXTIME = 2;
            byte[] msg = Transform.StructToBytes(tst);
            while (counts < MAXTIME)
            {
                Thread.Sleep(2000);
                try
                {
                    //string sendMessage = " hello guang server ,I come in at  " + DateTime.Now + "  with times:" + counts;
                    clientSocket.Send(msg);
                    Console.WriteLine("send success at " + counts);
                }
                catch (Exception e)
                {
                    Console.WriteLine("At times " + counts + "  send error!" + e.Message);
                    break;
                    
                }
             
              
                try
                {
                    Console.WriteLine("wait for receive");
                    byte[] id = new byte[4];
                    int rid=clientSocket.Receive(id);
                    int ids = System.BitConverter.ToInt32(id, 0);
                    Console.WriteLine("rid={0},id={1}", rid,ids);

                    byte[] result=new byte[2048];
                    int receiveLength = clientSocket.Receive(result); 
                    Type type=typeof(Test);
                    Test rr = (Test)Transform.BytesToStruct(result,type);
                    string ss = new string(rr.msg);
                   Console.WriteLine("接收服务器消息：result.first={0},result.second={1},msg={2},err={3},id={4}",rr.first,rr.second,rr.msg.ToString() ,rr.error,rr.id);
                   Console.WriteLine("接收服务器消息：result.first={0},result.second={1},msg={2}",rr.first,rr.second,ss);
                    
                }
                catch(Exception e){
                    Console.WriteLine("接收失败!,{0}",e.Message);
                    break;
                }
                
                counts++;
            }
            Console.ReadKey();
        }
        
    }
}
