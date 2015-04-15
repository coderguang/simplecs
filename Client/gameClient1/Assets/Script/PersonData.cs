using UnityEngine;
using System.Collections;

public class PersonData : MonoBehaviour {
    //角色属性，挂载在GobalOb对象上

    public static int m_ID=0;
    public static string m_Name=null;
    public static string m_LastTime=null;//上次登录时间
    public static string m_LastIP=null;//上次登录IP
    public static int m_HP=0;
    public static int m_Eat=0;//恢复生命值
    public static int m_Kill=0;//击杀人数
    public static int m_Assist=0;//助攻
    public static int m_Harm=0;//造成伤害
    public static int m_BeHarm=0;//承受伤害
    public static int m_GunNum=0;//子弹剩余数
    public static int m_NullGun=0;//空弹率
    public static int m_KDA=0;	
}
