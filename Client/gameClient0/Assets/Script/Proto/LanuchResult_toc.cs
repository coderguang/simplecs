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
         [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
         public char[] name;
         [MarshalAs(UnmanagedType.ByValArray, SizeConst = 30)]
         public char[] lastLanuch;
         [MarshalAs(UnmanagedType.ByValArray, SizeConst = 15)]
         public char[] lastIP;
         public int setting;
         public LanuchResult_toc(string n, string ltime, string lip, int set) {
             this.name=n.PadRight(10, '\0').ToCharArray();
             this.lastLanuch = ltime.PadRight(30, '\0').ToCharArray();
             this.lastIP = lip.PadRight(15, '\0').ToCharArray();
             this.setting = set;
         }
         public LanuchResult_toc() { 
         
         }


    }
}
