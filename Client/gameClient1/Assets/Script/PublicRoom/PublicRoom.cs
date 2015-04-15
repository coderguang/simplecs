using UnityEngine;
using System.Collections;

public class PublicRoom : MonoBehaviour {
 //用于设置公共房间的内容及接收开始或者退出游戏指令

    public UILabel user_name;
    public UILabel time;
    public UILabel ip;

    [HideInInspector]
    public static bool publicRoomFlag = false;
    [HideInInspector]
    public static string nameStr;
    [HideInInspector]
    public static string timeStr;
    [HideInInspector]
    public static string ipStr;


    private static PublicRoom _instance;

    private PublicRoom() {    
    
    }

    public static PublicRoom GetInstance() {
        if (null == _instance)
            _instance = new PublicRoom();
        return _instance;
    
    }

    //从全局数据中获取上次登录相关信息
    void OnGUI()
    {
        if (publicRoomFlag)
        {
            //name是个坑，老是获取不正确，先放着这个bug
            user_name.text = "[ff0000]角色名："+PersonData.m_Name+"[-]";
            time.text = "[ff0000]上次登录时间：" + PersonData.m_LastTime+"[-]";
            ip.text = "[ff0000]上次登录IP：" + PersonData.m_LastIP+"[-]";
            publicRoomFlag = false;
           
        }
    }

    public void StartGame() {
        Application.LoadLevel("GameMap");    
    }

    public void ExitGame() {
        Application.Quit();
    }

}
