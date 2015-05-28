using UnityEngine;
using System.Collections;
using Assets.Script.Log;

public class Gameing : MonoBehaviour {


    private GameObject bornB;//蓝方出生点
    private GameObject bornR;//红方出生点

    //private GameObject bmanPrefab;//蓝方人物预设体（可被控制）
    //private GameObject bman;//用户控制的人物,通过实例化预设获得

    private GameObject itSelfPrefab;

    private GameObject itself;

    private GameObject bullet;

    private GameObject bRobotPrefab;
    private GameObject bRobot1;

    private GameObject ak47flags;//主角枪口（用于发射子弹）
    private GameObject m4a1flags;//对方枪口

    private GameObject b1;
    private GameObject b2;


	// Use this for initialization
	void Start () {
        bornB = GameObject.Find("Boat/BlueBorn");
        bornR = GameObject.Find("Boat/RedBorn");

        itSelfPrefab = Resources.Load("Prefab/Person/itself") as GameObject;
        //bmanPrefab = Resources.Load("Prefab/Person/soldierPrefab") as GameObject;
        bRobotPrefab = Resources.Load("Prefab/Person/otherSoldier") as GameObject;

        bullet = Resources.Load("Prefab/Weapon/Bullet") as GameObject;

       // bman = Instantiate(bmanPrefab, bornB.transform.position, bornB.transform.rotation) as GameObject;

        itself = Instantiate(itSelfPrefab, bornB.transform.position, bornB.transform.rotation) as GameObject;

        bRobot1 = Instantiate(bRobotPrefab, bornR.transform.position, bornR.transform.rotation) as GameObject;

        ak47flags = GameObject.Find("ak74flags");
        m4a1flags = GameObject.Find("m4a1flags");




	}
	
	// Update is called once per frame
	void Update () {
        /**
        Transform  tran=itself.GetComponent<Transform>();
        float x=tran.position.x;
        float y=tran.position.y;
        float z=tran.position.z;
	    GameLog.Log(GameLogLevel.INFO,GameLogType.GameLog,"x="+x+"  y="+y+"  z="+z);
        **/
       // Instantiate(bullet, ak47flags.transform.position, ak47flags.transform.rotation);

	}


    /// <summary>
    /// 捕获鼠标左键点击事件
    /// </summary>
    void OnGUI() {
        if (Input.GetMouseButton(0)) {
            GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "click the mouse");
            Instantiate(bullet, ak47flags.transform.position, ak47flags.transform.rotation);
        }
    }

}
