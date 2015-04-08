using UnityEngine;
using System.Collections;

public class testlog : MonoBehaviour {

	// Use this for initialization
	void Start () {
        Logger.GetInstance();
	}
	
	// Update is called once per frame
	void Update () {
        Logger.Log("hello");
        Logger.Log("ok");
	    
	}
}
