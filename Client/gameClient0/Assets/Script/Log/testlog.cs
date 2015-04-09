using UnityEngine;
using System.Collections;

public class testlog : MonoBehaviour {

	// Use this for initialization
	void Start () {
        MLogger.GetInstance();
	}
	
	// Update is called once per frame
	void Update () {
        MLogger.Log("hello");
        MLogger.Log("ok");
        //Logger.Destroy();
	    
	}
}
