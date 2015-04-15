using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Script.Proto
{
    /**
     * 服务器发送的错误代码均在此处
     * 和服务器的Err_toc.h的值一致
     * 
     * 
     * 
     * */
    class ErrCode
    {
        public const int NETWORD_ERROR = 4999;//网络问题或者服务器未开启

        public const int SERVER_FULL = 5888;//服务器已爆满，无法登陆

        public const int ACCOUNT_HADREGIT=6000;//账号已被注册

        public const int ACCOUNT_ERR_IDENTITY = 6100;//重置密码时的验证问题或答案不对

        public const int ACCOUNT_ERR_PASSWD = 6200;//登录时密码不正确

        public const int ACCOUNT_HAD_LANUCH = 6300;//账号已经登录，无法再次登录





    }
}
