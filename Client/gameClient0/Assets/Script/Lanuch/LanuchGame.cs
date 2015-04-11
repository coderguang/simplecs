using UnityEngine;
using System.Collections;
using Assets.Script.Log;
using Assets.Script.Proto;
using Assets.Script.Time;
using Assets.Script;
/**
 * 该脚本用于获取登录界面的账号及密码信息
 * 点击提交按钮之后，将发送账号密码等信息的proto到服务器
 * 
 * 
 * */
public class LanuchGame : MonoBehaviour {
    //通过拖动指定下面两个的值
    //UIIput的validation指定为  Alphanumeric(字符及数字)
    public UIInput user;
    public UIInput passwd;

   
    //点击登录按钮将调用该函数
    public void Login() {      
        string username = user.value;
        string passwdstr = passwd.value;
        MLogger.Log(MLogLevel.INFO, MLogType.LanuchLog, "尝试登录,账号:" + username + "  密码:" + passwdstr);
        Lanuch_tos pmsg = new Lanuch_tos(username, passwdstr);
        MConnection.Send(pmsg);
       
        
    }

	// Use this for initialization
	void Start () {
        MTimer.GetInstance();
        MLogger.GetInstance();
        MConnection.GetInstance();
        /**
        Lanuch_tos pmsg1= new Lanuch_tos("sg1", "sg1passwd");
        MConnection.Send(pmsg1);

        Lanuch_tos pmsg2 = new Lanuch_tos("sg2", "sg2passwd");
        MConnection.Send(pmsg2);

        Lanuch_tos pmsg3 = new Lanuch_tos("sg3", "sg3passwd");
        MConnection.Send(pmsg3);

        Lanuch_tos pmsg4 = new Lanuch_tos("sg4", "sg4passwd");
        MConnection.Send(pmsg4);

        Lanuch_tos pmsg5 = new Lanuch_tos("sg5", "sg5passwd");
        MConnection.Send(pmsg5);
         * **/
	}
	
	// Update is called once per frame
	void Update () {
	}


}
