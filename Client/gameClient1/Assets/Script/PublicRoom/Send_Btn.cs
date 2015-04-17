using UnityEngine;
using System.Collections;
using Assets.Script.Proto;
using Assets.Script;
using Assets.Script.Temp;

public class Send_Btn : MonoBehaviour {

    public UITextList textList;

    
    public static bool flag = false;

    public static string str = null;

    public static int uid = 0;

    void OnGUI() {
        if (flag) {
            textList.Add("[00ff00]"+PersonName.GetName(uid)+":[-][000000]"+str+"[-]");
            flag = false;
        }
    
    }

    // Use this for initialization  
    void Start()
    {

    }

    // Update is called once per frame  
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            this.OnClick();
        }
    }

    void OnClick()
    {
        GameObject input_Label = GameObject.Find("Input_Label");
        //string text_str = "[00ff00]"+"Some say:[-] " + "[ff0000]"+input_Label.GetComponent<UILabel>().text+"[-]";
        string str = input_Label.GetComponent<UILabel>().text;
        
        Chat_tocs temp = new Chat_tocs(PersonData.m_ID, PartyType.ALL, str);
        MConnection.GetInstance().Send(temp);
        
        //textList.Add(text_str);
    }  
}
