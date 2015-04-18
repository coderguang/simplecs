using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{
    /**
     * 服务器保存有该用户的阵营
     * 只需要告诉服务器要变阵营即可，无需其他额外参数
     * 
     * 服务器也通过这个告诉本地，阵营改变，改变PersonData.m_Party
     * **/

    [Serializable]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = ProtoID.PackSize)]
    class Party_change_tocs:Message
    {
        public Party_change_tocs() {
            this.id = ProtoID.PartyChangeID;
            this.error_code = 0;
        }

    }
}
