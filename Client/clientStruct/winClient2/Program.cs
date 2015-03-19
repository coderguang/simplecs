using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Net.NetworkInformation;
namespace winClient2
{
    class Program
    {
        private static byte[] result = new byte[1024];
        static void Main(string[] args)
        {
            IPAddress ip = IPAddress.Parse("182.254.233.115");
            Random rd=new Random();
            int mPort = 9201;
            Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
//                clientSocket.Connect(new IPEndPoint(ip, mPort)); //配置服务器IP与端口
                clientSocket.Connect(new IPEndPoint(ip,9201)); //配置服务器IP与端口
                Console.WriteLine("连接服务器成功");
            }
            catch
            {
                Console.WriteLine("连接服务器失败，请按回车键退出！");
                //return;
            }

            int counts = 0;
            int MAXTIME = 320000;
            while (counts < MAXTIME)
            {
                Thread.Sleep(2000);
                try
                {
                    //string sendMessage = " hello guang server ,I come in at  " + DateTime.Now + "  with times:" + counts;
                    clientSocket.Send(Encoding.ASCII.GetBytes(sendMessage));
                    Console.WriteLine("send success at " + counts);
                }
                catch (Exception e)
                {
                    Console.WriteLine("At times " + counts + "  send error!" + e.Message);
                    break;
                    
                }
                try
                {
                    int receiveLength = clientSocket.Receive(result);
                    Console.WriteLine("接收服务器消息：{0}", Encoding.ASCII.GetString(result, 0, receiveLength));
                }
                catch {
                    Console.WriteLine("receive  error!");
                    break;
                }
                counts++;
            }
            Console.ReadKey();
        }
        
    }
}
