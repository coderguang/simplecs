using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{
    [Serializable]
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = protoID.PackSize)]


    class Chat_tocs:Message
    {
        public int user_id;//发起聊天的id
        public int type;//消息类型  公共，阵营
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public char[] msg;

        public Chat_tocs(int id, PartyType t, string ms) {
            this.id = protoID.ChatID;
            this.error_code = 0;
            this.user_id = id;
            this.type = (int)t;
            this.msg =ms.PadRight(32, '\0').ToCharArray();        
        }
        
    }
}
