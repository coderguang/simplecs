using UnityEngine;
using System.Collections;
using Assets.Script.Time;

public class Death : MonoBehaviour {

    private bool isDeath = false;
    public GameObject obj;
	// Use this for initialization
    public GameObject m4a1flags;

    private GameObject bullet;

    private int lastTime;
    private int curTime;

	void Start () {



        m4a1flags = GameObject.Find("m4a1flags");
        bullet = Resources.Load("Prefab/Weapon/Bullet") as GameObject;

        lastTime = MTimer.GetSec();
	}
	
	// Update is called once per frame
	void Update () {
        if (isDeath) {
            isDeath = false;
            //obj.transform.Translate(1,0,1);
            Destroy(obj);
        }

        curTime = MTimer.GetSec();
        if (Mathf.Abs(curTime - lastTime) > 0.005)
        {
            lastTime = curTime;
            Instantiate(bullet, m4a1flags.transform.position, m4a1flags.transform.rotation);

            Transform tran = obj.GetComponent<Transform>();
            float x=tran.position.x+(float)Random.Range(1,3)/100;
            float z = tran.position.z + (float)Random.Range(1, 3) / 100;
            obj.transform.position = new Vector3(x, tran.position.y, z);
        }

	}

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.name == "Bullet(Clone)")
        {
            isDeath = true;
        }
    }

    void OnTriggerStay(Collider other)
    {
        if (other.gameObject.name == "Bullet(Clone)")
        {
            isDeath = true;
        }
    }


    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.name == "Bullet(Clone)")
        {
            isDeath = true;
        }
    }
}
