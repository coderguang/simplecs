﻿using UnityEngine;
using System.Collections;
using Assets.Script;
using Assets.Script.Proto;
using Assets.Script.Log;
using Assets.Script.Temp;
using System;

public class NullObj : MonoBehaviour {

    //该对象的生命周期为整个游戏的生命周期
    //从游戏一开始加载就加载
    //场景变化该对象也不会销毁
    //在update中进行协议包的业务处理
	// Use this for initialization


    private static NullObj _instance=null;

    /**
    private NullObj() { 
        
    }
    private static NullObj GetInstance() {
        if (null == _instance)
            _instance = new NullObj();
        return _instance;    
    }
    **/

    void Awake() {
        if(null==_instance){
            _instance = this;
            //切换场景时，该对象不消失
            DontDestroyOnLoad(transform.gameObject);
        }
    
    }


	void Start () {
        MFactory.GetInstance();
	
	}
	
	// Update is called once per frame
    //在Update中进行业务逻辑处理
	void Update () {

        //如果缓存中有协议
        if (MConnection.GetInstance().package.Count>0) {
            try
            {   Message msg ;
                lock (MConnection.objLock)
                {
                    //获取并删除第一个元素
                   msg = MConnection.GetInstance().package.Dequeue();
                }

                int id = msg.id;
                MLogger.Log(MLogLevel.INFO, MLogType.ProtoLog, "update 处理到协议:" + id);

                //具体的业务逻辑处理
                //超恶心switch
                switch (id) {
                    case protoID.ErrID://错误情况
                        {
                            if (ErrCode.ACCOUNT_ERR_PASSWD == msg.error_code||ErrCode.ACCOUNT_HAD_LANUCH==msg.error_code||ErrCode.SERVER_FULL==msg.error_code) {
                                //LanuchGame.GetInstance().err_code=msg.error_code;
                                //LanuchGame.GetInstance().tipFlag = true;
                                LanuchGame.err_code = msg.error_code;
                                LanuchGame.tipFlag = true;
                                
                            }                        
                        
                        }
                        break;
                    case protoID.LanuchResultID: //登录正确
                        {
                            
                             
                            LanuchResult_toc temp=(LanuchResult_toc)msg;
                            /**
                            PublicRoom.GetInstance();
                            PublicRoom.nameStr = new string(temp.name);
                            PublicRoom.timeStr = new string(temp.lastLanuch);
                            PublicRoom.ipStr = new string(temp.lastIP);
                             **/
                            //PersonData.m_Name=new string(temp.name);
                            PersonData.m_Name = PersonName.GetName(temp.account_id);
                            PersonData.m_LastTime = new string(temp.lastLanuch);
                            PersonData.m_LastIP= new string(temp.lastIP);
                            PublicRoom.publicRoomFlag = true;
                            Application.LoadLevel("PublicRoom");
                        }
                        break;

                
                
                
                }







            }
            catch (Exception e) {
                MLogger.Log(MLogLevel.INFO, MLogType.ProtoLog, "队列无协议:" + e.Message);
            }


        }


	}


    void OnDestroy() {

        MConnection.GetInstance().Destroy();
    }




}
