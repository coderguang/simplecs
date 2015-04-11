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
	}
	
	// Update is called once per frame
	void Update () {
	}


}
