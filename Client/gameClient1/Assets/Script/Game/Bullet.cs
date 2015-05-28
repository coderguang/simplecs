using UnityEngine;
using System.Collections;
using Assets.Script.Log;

public class Bullet : MonoBehaviour {

    public float damage = 10.0f;
    public float speed = 100.0f;
    public float DestroyTime = 1.0f;
    private Vector3 velocity;

	// Use this for initialization
	void Start () {
        velocity = transform.forward * speed;
        Destroy(gameObject, DestroyTime);
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    void FixedUpdate()
    {
        transform.position += velocity * Time.deltaTime;
    }

    
    void OnTriggerEnter(Collider other) {
        if (other.gameObject.name == "otherSoldier(Clone)")
        {
            GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "打死人了enter");
        }
        else
        {
            GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "bum===" + other.gameObject.name);
        }
    }

    void OnTriggerStay(Collider other)
    {
        if (other.gameObject.name == "otherSoldier(Clone)")
        {
            GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "打死人了stay");
        }      
    }


    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.name == "otherSoldier(Clone)")
        {
            GameLog.Log(GameLogLevel.INFO, GameLogType.GameLog, "打死人了exit");
        }
    }


}
