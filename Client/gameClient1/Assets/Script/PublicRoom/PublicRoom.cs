using UnityEngine;
using System.Collections;
using Assets.Script.Proto;
using Assets.Script;

public class PublicRoom : MonoBehaviour {
 //用于设置公共房间的内容及接收开始或者退出游戏指令

    private UILabel user_name;
    private UILabel time;
    private UILabel ip;

    private UILabel Reject_Label;//非sg无法开启游戏

    public static bool publicRoomFlag = false;
    public static string nameStr;
    public static string timeStr;
    
    public static string ipStr;
    private static PublicRoom _instance;

    void Start() {
        user_name = GameObject.Find("UI Root/Window/Right/name").GetComponent<UILabel>();
        time = GameObject.Find("UI Root/Window/Right/time").GetComponent<UILabel>();
        ip = GameObject.Find("UI Root/Window/Right/ip").GetComponent<UILabel>();
        Reject_Label = GameObject.Find("UI Root/Window/Left/startBtn/Reject_Label").GetComponent<UILabel>();
    }


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
    /**
     * 只有sg具有开启游戏的权利
     * 
     * **/
    public void StartGame() {
        /**
        if (1000 != PersonData.m_ID)
            Reject_Label.text = "[ff0000]只有账号sg具有开启游戏权限[-]";
        else {
            GameStart_tocs temp = new GameStart_tocs();
            Connection.GetInstance().Send(temp);
        }
            **/
        GameStart_tocs temp = new GameStart_tocs();
        Connection.GetInstance().Send(temp);
    }

    public void ExitGame() {
        Application.Quit();
    }

}
