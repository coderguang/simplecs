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
     * 
     * toc为服务器发到客户端的协议，该协议具有id，但客户端在读取的时候最开始先读取id,因此toc开头的类结构将没有id这个属性
     * tos为客户端发到服务器的协议，该协议具有id，并且将被填充为具体的值，因此，tos开头的类结构具有id
     * */

    [Serializable]
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    class Message_toc
    {

    }
}
