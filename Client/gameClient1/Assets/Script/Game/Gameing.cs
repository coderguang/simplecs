using UnityEngine;
using System.Collections;
using Assets.Script.Log;
using Assets.Script.Proto;
using Assets.Script;
using Assets.Script.Temp;
using Assets.Script.Time;
using System;
public class Gameing : MonoBehaviour
{


    public static bool flag = false;
    public static int ax;
    public static int ay;
    public static int az;

    public static bool isDead = false;
    public static bool otherDead = false;

    private GameObject bornB;//蓝方出生点
    private GameObject bornR;//红方出生点

    //private GameObject bmanPrefab;//蓝方人物预设体（可被控制）
    //private GameObject bman;//用户控制的人物,通过实例化预设获得

    private GameObject itSelfPrefab;
    private GameObject itself;

    private GameObject bullet;

    private GameObject otherManPrefab;
    private GameObject otherMan;

    private GameObject ak47flags;//主角枪口（用于发射子弹）
    private GameObject m4a1flags;//对方枪口

    private GameObject b1;
    private GameObject b2;

    private int lastTime;
    private int curTime;

    private int lastfire;
    private int curfire;

    // Use this for initialization
    void Start()
    {
        bornB = GameObject.Find("Boat/BlueBorn");
        bornR = GameObject.Find("Boat/RedBorn");

        itSelfPrefab = Resources.Load("Prefab/Person/itself") as GameObject;
        //bmanPrefab = Resources.Load("Prefab/Person/soldierPrefab") as GameObject;
        otherManPrefab = Resources.Load("Prefab/Person/otherSoldier") as GameObject;

        bullet = Resources.Load("Prefab/Weapon/Bullet") as GameObject;

        // bman = Instantiate(bmanPrefab, bornB.transform.position, bornB.transform.rotation) as GameObject;

        itself = Instantiate(itSelfPrefab, bornB.transform.position, bornB.transform.rotation) as GameObject;

        otherMan = Instantiate(otherManPrefab, bornR.transform.position, bornR.transform.rotation) as GameObject;

        ak47flags = GameObject.Find("ak74flags");
        m4a1flags = GameObject.Find("m4a1flags");

        lastTime = MTimer.GetSec();
        lastfire = MTimer.GetSec();


    }

    // Update is called once per frame
    void Update()
    {

        if (isDead) { 
            
        
        }



        if (flag)
        {
            //改变位置
            flag = false;
            Vector3 pos = new Vector3(ax, ay, az);
            otherMan.transform.position = pos;
        }



        Transform tran = itself.GetComponent<Transform>();
        float x = tran.position.x;
        float y = tran.position.y;
        float z = tran.position.z;


        Pos_tocs temp = new Pos_tocs((int)x, (int)y, (int)z);

        curTime = MTimer.GetSec();

        if (Math.Abs(curTime - lastTime) > 8)
        {
            lastTime = curTime;
            //Connection.GetInstance().Send(temp);
            //GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "x=" + x + "  y=" + y + "  z=" + z);

            Instantiate(otherManPrefab, bornR.transform.position, bornR.transform.rotation);
        }


    }


    /// <summary>
    /// 捕获鼠标左键点击事件
    /// </summary>
    void OnGUI()
    {
        if (Input.GetMouseButton(0))
        {
            curfire = MTimer.GetSec();
            Instantiate(bullet, ak47flags.transform.position, ak47flags.transform.rotation);
            /**
            if (Math.Abs(curfire - lastfire) > 0.001)
            {
                lastfire = curfire;
                //GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "click the mouse");
                Instantiate(bullet, ak47flags.transform.position, ak47flags.transform.rotation);
            }**/
        }
    }

}
