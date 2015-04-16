using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{

    /**
     * 更新房间用户列表
     * 
     * */
    [Serializable]
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = protoID.PackSize)]
    class Party_toc:Message
    {
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

    }
}
