using UnityEngine;
using System.Collections;
using Assets.Script.Log;
using Assets.Script.Proto;
using Assets.Script;
using Assets.Script.Temp;
using Assets.Script.Time;
using System;
using Assets.Script.Game;

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

//    private GameObject itSelfPrefab;
//    private GameObject itself;

//    private GameObject bullet;

    private RoleBlue myRole;
    private RoleRed otherRole;

//    private GameObject otherManPrefab;
//    private GameObject otherMan;

//    private GameObject ak47flags;//主角枪口（用于发射子弹）
//    private GameObject m4a1flags;//对方枪口

    private int lastTime;
    private int curTime;

    private int lastfire;
    private int curfire;

    // Use this for initialization
    void Start()
    {
        bornB = GameObject.Find("Boat/BlueBorn");
        bornR = GameObject.Find("Boat/RedBorn");

        if (PersonData.m_Party == PartyType.BLUE) {
            myRole = new RoleBlue(PersonData.m_ID, bornB);
            otherRole = new RoleRed(0, bornR);//暂时不根据roleID来确定角色
        } else {
            myRole = new RoleBlue(PersonData.m_ID, bornR);
            otherRole = new RoleRed(0, bornB);//暂时不根据roleID来确定角色
        }


        //itSelfPrefab = Resources.Load("Prefab/Person/itself") as GameObject;
        //bmanPrefab = Resources.Load("Prefab/Person/soldierPrefab") as GameObject;
        //otherManPrefab = Resources.Load("Prefab/Person/otherSoldier") as GameObject;

        //bullet = Resources.Load("Prefab/Weapon/Bullet") as GameObject;

        // bman = Instantiate(bmanPrefab, bornB.transform.position, bornB.transform.rotation) as GameObject;

        //itself = Instantiate(itSelfPrefab, bornB.transform.position, bornB.transform.rotation) as GameObject;

        //otherMan = Instantiate(otherManPrefab, bornR.transform.position, bornR.transform.rotation) as GameObject;

        //ak47flags = GameObject.Find("ak74flags");
        //m4a1flags = GameObject.Find("m4a1flags");

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
            //otherMan.transform.position = pos;
            if (otherRole != null) {
                otherRole.transform.position = pos;
                GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "敌方位置  x=" + pos.x + "  y=" + pos.y + "  z=" + pos.z);
            } else {
                GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "敌方为空");
            }
        }




        

        //Pos_tocs temp = new Pos_tocs((int)x, (int)y, (int)z);

        curTime = MTimer.GetSec();

        if (Math.Abs(curTime - lastTime) > 1)
        {
            lastTime = curTime;

            Vector3 pos = myRole.GetPos();
            Pos_tocs temp = new Pos_tocs((int)pos.x,(int)pos.y,(int)pos.z);
            Connection.GetInstance().Send(temp);
            //GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "x=" + pos.x + "  y=" + pos.y + "  z=" + pos.z);           
            //Instantiate(otherManPrefab, bornR.transform.position, bornR.transform.rotation);
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
            //Instantiate(bullet, ak47flags.transform.position, ak47flags.transform.rotation);
            
            if (Math.Abs(curfire - lastfire) > 0.001)
            {
                lastfire = curfire;
                myRole.Fire();
                //GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "click the mouse");
                //Instantiate(bullet, ak47flags.transform.position, ak47flags.transform.rotation);
            }
        }
    }

}
