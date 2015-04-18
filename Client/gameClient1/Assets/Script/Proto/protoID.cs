using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Script.Proto
{
    static class ProtoID
    {

        public const int PackSize = 1; //统一控制协议的对齐方式

       public const int LanuchID= 1000;
       public const int LanuchResultID = 1001;

       public const int PartyID = 1500;//房间用户列表

       public const int PartyChangeID = 1600;//用户阵营改变

       public const int ChatID = 1800;//房间内的聊天信息

       public const int GameStart = 1900;//开启游戏，仅sg具有该权限，本地与服务器都检测是否具有权限

       public const int ErrID = 3999;//错误协议
    }
}