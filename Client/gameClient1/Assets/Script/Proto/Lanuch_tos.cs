using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{

    /*C#只支持公有继承，因此前面没有修饰符*/
    [Serializable]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = ProtoID.PackSize)]
    class Lanuch_tos:Message
    {
        //长度根据服务端的数据库决定
        [MarshalAs(UnmanagedType.ByValArray,SizeConst=8)]
        public char []account;
        int acclen;
        [MarshalAs(UnmanagedType.ByValArray,SizeConst=16)]
        public char []passwd;
        int paslen;

        public Lanuch_tos(string acc,string pass) {
            this.id = ProtoID.LanuchID;
            this.error_code = 0;
            this.account = acc.PadRight(8, '\0').ToCharArray();
            this.passwd =  pass.PadRight(16, '\0').ToCharArray();
            acclen = acc.Length;
            paslen = pass.Length;
        }
    }
}
