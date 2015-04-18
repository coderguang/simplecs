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
    class GameStart_tocs:Message
    {
        public GameStart_tocs() {
            this.id = ProtoID.GameStart;
            this.error_code = 0;
        }


    }
}
