using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;//for StructLayoutAttribute

namespace Assets.Script.Proto
{
    /**
     * 
     * 之前的想法错了~
     * toc,tos其实只是相对而言，client to server 的协议应该命名为tos，反之为toc
     * 但其实client和server的结构应该是一样的！否则内存对齐的时候会很麻烦！！
     * 
     * 
     * 所有协议的基类
     * 应包含以下特性
     * [Serializable],[StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)]
     * 为了方便，决定使用ANSI作为字符集，以后如果还有时间再做Unicode字符集，协议bug暂时关闭
     * */

    [Serializable]
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    class Message
    {
        public int id;
        public int error_code;
        public int GetID() {
            return id;
        }

    }
}
