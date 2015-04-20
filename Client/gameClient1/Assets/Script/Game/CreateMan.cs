using UnityEngine;
using System.Collections;

public class CreateMan : MonoBehaviour {


    private GameObject bornB;//蓝方出生点
    private GameObject bornR;//红方出生点

    //private GameObject bmanPrefab;//蓝方人物预设体（可被控制）
    //private GameObject bman;//用户控制的人物,通过实例化预设获得

    private GameObject itSelfPrefab;
    private GameObject itself;

    private GameObject bRobotPrefab;
    private GameObject bRobot1;


    private GameObject b1;
    private GameObject b2;


	// Use this for initialization
	void Start () {
        bornB = GameObject.Find("Boat/BlueBorn");
        bornR = GameObject.Find("Boat/RedBorn");

        itSelfPrefab = Resources.Load("Prefab/Person/itself") as GameObject;
        //bmanPrefab = Resources.Load("Prefab/Person/soldierPrefab") as GameObject;
        bRobotPrefab = Resources.Load("Prefab/Person/otherSoldier") as GameObject;        

       // bman = Instantiate(bmanPrefab, bornB.transform.position, bornB.transform.rotation) as GameObject;

        itself = Instantiate(itSelfPrefab, bornB.transform.position, bornB.transform.rotation) as GameObject;

        bRobot1 = Instantiate(bRobotPrefab, bornR.transform.position, bornR.transform.rotation) as GameObject;


	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
