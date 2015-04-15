using UnityEngine;
using System.Collections;

public class PublicRoom : MonoBehaviour {
 //用于设置公共房间的内容及接收开始或者退出游戏指令

    public UILabel user_name;
    public UILabel time;
    public UILabel ip;

    [HideInInspector]
    public bool publicRoomFlag = false;

    [HideInInspector]
    public string nameStr;
    [HideInInspector]
    public string timeStr;
    [HideInInspector]
    public string ipStr;


    private static PublicRoom _instance;

    private PublicRoom() {    
    
    }

    public static PublicRoom GetInstance() {
        if (null == _instance)
            _instance = new PublicRoom();
        return _instance;
    
    }

    void OnGUI()
    {
        if (publicRoomFlag)
        {
            user_name.text = nameStr;
            time.text = timeStr;
            ip.text = ipStr;
            publicRoomFlag = false;
           
        }
    }



	void Start () {
	    
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
