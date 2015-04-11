using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    class LanuchResult_tos:Message_tos
    {
         [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
         public char[] name;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
         public char[] lastIP;
         [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
         public char[] lastLanuch;
        
         public int setting;
         public LanuchResult_tos(string n, string ltime, string lip, int set) {
             this.id = protoID.pLanuchResult;
             this.name=n.PadRight(8, '\0').ToCharArray();
             this.lastLanuch = ltime.PadRight(16, '\0').ToCharArray();
             this.lastIP = lip.PadRight(32, '\0').ToCharArray();
             this.setting = set;
         }
         public LanuchResult_tos() { 
         
         }


    }
}
