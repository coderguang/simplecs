using UnityEngine;
using System.Collections;
using Assets.Script.Log;
using Assets.Script.Proto;
using Assets.Script.Time;
using Assets.Script;
/**
 * 该脚本用于获取登录界面的账号及密码信息
 * 点击提交按钮之后，将发送账号密码等信息的proto到服务器
 *  挂载在UI Root/lanuch对象上
 * 
 * */
public class LanuchGame : MonoBehaviour {

    //通过拖动指定下面两个的值

    //UIIput的validation指定为  Alphanumeric(字符及数字)
    private UIInput user;
    private UIInput passwd;
    //用于根据协议的错误码来更新登录状态提示
    private UILabel tip;

    public static int err_code = 0;
    public static bool tipFlag = false;
    
    private static LanuchGame _instance;


    // Use this for initialization
    void Start()
    {
        user = GameObject.Find("UI Root/account").GetComponent<UIInput>();
        passwd = GameObject.Find("UI Root/passwd").GetComponent<UIInput>();
        tip = GameObject.Find("UI Root/lanuch/Tip_Label").GetComponent<UILabel>();

    }


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
                tip.text = "[ff0000]" + "账号或密码不正确,请重新输入" + "[-]";
            else if (ErrCode.ACCOUNT_HAD_LANUCH == err_code)
                tip.text = "[ff0000]" + "该账号已经登录，无法再次登录!" + "[-]";
            else if (ErrCode.NETWORD_ERROR == err_code)
                tip.text = "[ff0000]" + "网络未连接或服务器未开启!" + "[-]";
            else if (ErrCode.SERVER_FULL == err_code)
                tip.text = "[ff0000]" + "服务器已爆满，无法登陆"+"[-]";
            else if(ErrCode.SERVER_IN_GAME==err_code)
                tip.text = "[ff0000]" + "游戏已经开始，无法进入" + "[-]";
            else
                tip.text = "[ff0000]" + "未知错误:" + err_code + "[-]";

            tipFlag = false;
        }
    }

    //点击登录按钮将调用该函数
    public void Login() {
        string username = user.text;
        string passname = passwd.value;
        Lanuch_tos temp=new Lanuch_tos(username,passname);
        GameLog.Log(GameLogLevel.INFO,GameLogType.LanuchLog,"登录 account="+username+"  passwd="+passname);
        Connection.GetInstance().Send(temp);

        
    }

	
	// Update is called once per frame
	void Update () {

	}


}
