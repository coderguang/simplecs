using UnityEngine;
using System.Collections;
using Assets.Script.Temp;

public class UpdateParty : MonoBehaviour {


    /*
     * 服务器每次新加入一个成员就推一个列表过来，内容为用户ID
     * 这里根据用户ID，从PersonName.cs里面找到名字，先用Label的形式展示
     * 
     * **/

    //蓝色方的五个成员显示位置
    private UILabel b_1;
    private UILabel b_2;
    private UILabel b_3;
    private UILabel b_4;
    private UILabel b_5;

    private UILabel r_1;
    private UILabel r_2;
    private UILabel r_3;
    private UILabel r_4;
    private UILabel r_5;

    private UILabel Join_Label;//每次更新阵营，清除Join_Label中的阵营切换提示
    public static bool tipFlag=false;//当切换阵营收到错误proto的时候，用于更新Join_Label

    public static bool flag = false;

    //是个槽的对应用户ID值
    public static int b_1ID;
    public static int b_2ID;
    public static int b_3ID;
    public static int b_4ID;
    public static int b_5ID;

    public static int r_1ID;
    public static int r_2ID;
    public static int r_3ID;
    public static int r_4ID;
    public static int r_5ID;


    void OnGUI() {
        //更新用户列表
        if (flag) {
            //蓝方阵营
            b_1.text ="[FF0000]"+ PersonName.GetName(b_1ID)+"[-]";
            b_2.text ="[0000FF]"+PersonName.GetName(b_2ID)+"[-]";
            b_3.text ="[00FFFF]"+PersonName.GetName(b_3ID)+"[-]";
            b_4.text ="[4A766E]"+PersonName.GetName(b_4ID)+"[-]";
            b_5.text ="[6B8E23]"+PersonName.GetName(b_5ID)+"[-]";

            //红方阵营
            r_1.text = "[FF0000]" + PersonName.GetName(r_1ID)+"[-]";
            r_2.text = "[0000FF]" + PersonName.GetName(r_2ID)+"[-]";
            r_3.text = "[00FFFF]" + PersonName.GetName(r_3ID)+"[-]";
            r_4.text = "[4A766E]" + PersonName.GetName(r_4ID)+"[-]";
            r_5.text = "[6B8E23]" + PersonName.GetName(r_5ID)+"[-]";

            Join_Label.text = "";

            flag = false;                
        }

        if (tipFlag) {
            Join_Label.text = "[ff0000]该阵营已满人，切换失败！[-]";
            tipFlag = false;
        }
    
        
    
    
    
    
    
    
    
    }





	// Use this for initialization
	void Start () {
        b_1 = GameObject.Find("UI Root/Window/PartyNow/BlueParty/b_1").GetComponent<UILabel>();
        b_2 = GameObject.Find("UI Root/Window/PartyNow/BlueParty/b_2").GetComponent<UILabel>();
        b_3 = GameObject.Find("UI Root/Window/PartyNow/BlueParty/b_3").GetComponent<UILabel>();
        b_4 = GameObject.Find("UI Root/Window/PartyNow/BlueParty/b_4").GetComponent<UILabel>();
        b_5 = GameObject.Find("UI Root/Window/PartyNow/BlueParty/b_5").GetComponent<UILabel>();

        r_1 = GameObject.Find("UI Root/Window/PartyNow/RedParty/r_1").GetComponent<UILabel>();
        r_2 = GameObject.Find("UI Root/Window/PartyNow/RedParty/r_2").GetComponent<UILabel>();
        r_3 = GameObject.Find("UI Root/Window/PartyNow/RedParty/r_3").GetComponent<UILabel>();
        r_4 = GameObject.Find("UI Root/Window/PartyNow/RedParty/r_4").GetComponent<UILabel>();
        r_5 = GameObject.Find("UI Root/Window/PartyNow/RedParty/r_5").GetComponent<UILabel>();

        Join_Label = GameObject.Find("UI Root/Window/Party/Join_Label").GetComponent<UILabel>();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
