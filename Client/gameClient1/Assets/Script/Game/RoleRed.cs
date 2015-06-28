
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Script.Game {
    public class RoleRed:MonoBehaviour {
        private int roleID;
        private GameObject born;//重生点
        private GameObject role;
        private GameObject weapon;
        private GameObject bullet;
        public RoleRed(int id, GameObject pos) {
            roleID = id;
            born = pos;
            Init();
        }
        private void Init() {
            GameObject itSelfPrefab = Resources.Load("Prefab/Person/otherSoldier") as GameObject;
            role = Instantiate(itSelfPrefab, born.transform.position, born.transform.rotation) as GameObject;
            weapon = GameObject.Find("m4a1flags");
            bullet = Resources.Load("Prefab/Weapon/Bullet") as GameObject;
        }

        public void Fire() {
            Instantiate(bullet, weapon.transform.position, weapon.transform.rotation);
        }
        public void SetPos(Vector3 pos) {
            role.transform.position = pos;
        }

        public Vector3 GetPos() {
            return role.transform.position;
        }

        public void ReBorn() {
            role.transform.position = born.transform.position;
        }
    }
}
