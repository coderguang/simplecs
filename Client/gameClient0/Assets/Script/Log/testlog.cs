using UnityEngine;
using System.Collections;
using Assets.Script.Log;

public class testlog : MonoBehaviour {

	// Use this for initialization
	void Start () {
        MLogger.GetInstance();
	}
	
	// Update is called once per frame
	void Update () {
        //MLogger.Log(MLogLevel.WARN,MLogType.LanuchLog,  "hello,boy");
	}
}
