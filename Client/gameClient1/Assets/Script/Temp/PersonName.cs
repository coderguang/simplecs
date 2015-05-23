using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Script.Temp
{
    /**
     *  因为从协议中获取name时会有bug
     *  角色名的获取暂时从这里获得
     *  从服务器的一个映射到这里,根据id找名字
     * */
    class PersonName
    {
        public static string SG = "sg";
        public static string SG1 = "sg1";
        public static string SG2 = "sg2";
        public static string SG3 = "sg3";
        public static string SG4 = "sg4";
        public static string SG5 = "sg5";
        public static string SG6 = "sg6";
        public static string SG7 = "sg7";
        public static string SG8 = "sg8";
        public static string SG9 = "sg9";

        public static string GetName(int id) {
            switch (id) { 
                case 1000:
                    return SG;
                    //break;
                case 1001:
                    return SG1;
                    //break;
                case 1002:
                    return SG2;
                    //break;
                case 1003:
                    return SG3;
                    //break;
                case 1004:
                    return SG4;
                    //break;
                case 1005:
                    return SG5;
                    //break;
                case 1006:
                    return SG6;
                    //break;
                case 1007:
                    return SG7;
                    //break;
                case 1008:
                    return SG8;
                    //break;
                case 1009:
                    return SG9;
                    //break;
                default:
                    return "";
                    //break;            
            
            }  
        }


    }
}
