using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{
    //发往服务器时，通知服务器开启游戏
    //本地收到时，进入游戏
    [Serializable]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = ProtoID.PackSize)]
    class GameStart_tocs : Message
    {
        //只有收到的协议才会有r1-b5的值，发到服务器的是没有的
        public int r1;
        public int r2;
        public int r3;
        public int r4;
        public int r5;


        public int b1;
        public int b2;
        public int b3;
        public int b4;
        public int b5;


        public GameStart_tocs()
        {
            this.id = ProtoID.GameStart;
            this.error_code = 0;

        }
    }
}
