using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Script.Time
{
    class MTimer
    {
        private static MTimer _instance;
        private MTimer() {
        }
        public static MTimer GetInstance() {
            if (null == _instance)
                _instance = new MTimer();
            return _instance;
        }

        public static string GetTime() {
            return DateTime.Now.ToString();
        }

        public static int GetSec() {
            return DateTime.Now.Second;
        }




    }
}
