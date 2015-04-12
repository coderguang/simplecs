using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Assets.Script.Time;
using Assets.Script.Log;
using Assets.Script.Proto;

namespace Assets.Script
{
    //游戏初始化工厂，用于在主线程中初始化某些必要的对象,公用的对象
    class MFactory
    {
        private static MFactory _instance=null;
        private MFactory() { 
            Init();
        }
        public static MFactory GetInstance() {
            if (null == _instance)
                _instance = new MFactory();
            return _instance;
        }

        //在这里初始化        
        private void Init(){           

            MTimer.GetInstance();
            MLogger.GetInstance();
            MConnection.GetInstance();
            
           


        }


    }
}
