using UnityEngine;
using System.Collections;
using Assets.Script.Proto;
using Assets.Script;

public class JoinRed : MonoBehaviour {

    //挂载在UI Root/Window/Party/joinBlue/JoinRedBtn 对象上

    /**
     * 首先在本地判断，当前阵营，如果和要加入的阵营一致，在下方聊天框提示
     * 否则发送party_change_tos
     * 
     * 改用一个label显示，因为往textList中直接add没反应
     * 
     * **/
    //private UITextList textList;

    private UILabel Join_Label;
    private bool flag = false;

	// Use this for initialization
	void Start () {
        Join_Label = GameObject.Find("UI Root/Window/Party/Join_Label").GetComponent<UILabel>();
	}


    void OnGUI()
    {
        if (flag)
        {
            Join_Label.text = "[ff0000]你已在该阵营，切换失败！[-]";
            flag = false;
        }

    }

    void OnClick() {
        //先判断自身阵营是否和要加入的阵营一致
        if (PartyType.RED == PersonData.m_Party)
        {
            flag = true;
        }
        else
        {
            Party_change_tocs temp = new Party_change_tocs();
            MConnection.GetInstance().Send(temp);     

        }
    
    }
	
	// Update is called once per frame
	void Update () {
	
	}
}
