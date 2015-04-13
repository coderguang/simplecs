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
    //用于根据协议的错误码来更新登录状态提示
    public UILabel tip;


    public static int err_code = 0;

    public static bool tipFlag = false;
    
    private static LanuchGame _instance;

    //使用单例模式，在协议模式中被调用，不使用事件委托模型
    public static LanuchGame GetInstance() {
        if (null == _instance)
            _instance = new LanuchGame();
        return _instance;    
    }
    

    void OnGUI() {
        if (tipFlag)
        {
            tip.text = "";
            if (ErrCode.ACCOUNT_ERR_PASSWD == err_code)
                tip.text = "密码或密码不正确,请重新输入";
            else if (ErrCode.ACCOUNT_HAD_LANUCH == err_code)
                tip.text = "该账号已经登录，无法再次登录!";
            else
                tip.text = "未知错误:" + err_code;

            tipFlag = false;
        }
    }

    //点击登录按钮将调用该函数
    public void Login() {
        string username = user.value;
        string passname = passwd.value;
        Lanuch_tos temp=new Lanuch_tos(username,passname);
        MConnection.GetInstance().Send(temp);

        
    }

	// Use this for initialization
	void Start () {
      
	}
	
	// Update is called once per frame
	void Update () {
        if (tipFlag) { 
            
        }
	}


}
