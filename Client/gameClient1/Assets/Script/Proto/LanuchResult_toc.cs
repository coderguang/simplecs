using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    class LanuchResult_toc:Message_toc
    { 
        public int setting;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public char[] name;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public char[] lastIP;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public char[] lastLanuch;
              


    }
}
