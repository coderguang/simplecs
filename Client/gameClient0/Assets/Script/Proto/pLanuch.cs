﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{

    /*C#只支持公有继承，因此前面没有修饰符*/
    [Serializable]
    [StructLayout(LayoutKind.Sequential,CharSet=CharSet.Ansi,Pack=1)]
    class pLanuch:Message
    {
        //长度根据服务端的数据库决定
        [MarshalAs(UnmanagedType.ByValArray,SizeConst=8)]
        public char []account;
        [MarshalAs(UnmanagedType.ByValArray,SizeConst=20)]
        public char []passwd;

        public pLanuch() {
            id = protoID.pLanuchID;
        }
    }
}