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
    public UILabel b_1;
    public UILabel b_2;
    public UILabel b_3;
    public UILabel b_4;
    public UILabel b_5;

    public UILabel r_1;
    public UILabel r_2;
    public UILabel r_3;
    public UILabel r_4;
    public UILabel r_5;

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

            flag = false;                
        }
    
    
        
    
    
    
    
    
    
    
    }





	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
