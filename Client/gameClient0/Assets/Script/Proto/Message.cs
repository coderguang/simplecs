using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;//for StructLayoutAttribute

namespace Assets.Script.Proto
{
    /**
     * 所有协议的基类
     * 应包含以下特性
     * [Serializable],[StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)]
     * 为了方便，决定使用ANSI作为字符集，以后如果还有时间再做Unicode字符集，协议bug暂时关闭
     * */

    [Serializable]
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    class Message
    {
        public int id;
        public int GetID() {
            return id;
        }

    }
}
