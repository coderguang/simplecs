using UnityEngine;
using System.Collections;
using Assets.Script.Log;
using Assets.Script;
using Assets.Script.Proto;

public class testlog : MonoBehaviour {

	// Use this for initialization
	void Start () {
        MLogger.GetInstance();
        MConnection.GetInstance();
        pLanuch p = new pLanuch();
        p.account = "sg1".ToCharArray();
        p.passwd = "sg1passwd".ToCharArray();
        MConnection.Send(p);

	}
	
	// Update is called once per frame
	void Update () {
        //MLogger.Log(MLogLevel.WARN,MLogType.LanuchLog,  "hello,boy");
	}
}
