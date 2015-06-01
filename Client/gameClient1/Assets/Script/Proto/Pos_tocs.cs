
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Assets.Script.Proto
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = ProtoID.PackSize)]
    class Pos_tocs:Message
    {
        public int x;
        public int y;
        public int z;

        public Pos_tocs(int xx, int yy, int zz) {
            this.id = ProtoID.PosID;
            x = xx;
            y = yy;
            z = zz;
        }
    }
}
