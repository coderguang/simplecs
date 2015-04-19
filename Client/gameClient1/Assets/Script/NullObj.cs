using UnityEngine;
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
                    case ProtoID.ErrID://错误情况
                        {
                            if (ErrCode.ACCOUNT_ERR_PASSWD == msg.error_code||ErrCode.ACCOUNT_HAD_LANUCH==msg.error_code||ErrCode.SERVER_FULL==msg.error_code||ErrCode.SERVER_IN_GAME==msg.error_code) {
                                //LanuchGame.GetInstance().err_code=msg.error_code;
                                //LanuchGame.GetInstance().tipFlag = true;
                                LanuchGame.err_code = msg.error_code;
                                LanuchGame.tipFlag = true;
                            }
                            else if (ErrCode.PARTY_IS_FULL == msg.error_code || ErrCode.PARTY_NO_CHANGE == msg.error_code) {
                                UpdateParty.tipFlag = true;//中心显示阵营切换失败
                            }                        
                        
                        }
                        break;
                    case ProtoID.LanuchResultID: //登录正确
                        {                                                         
                            LanuchResult_toc temp=(LanuchResult_toc)msg;
                            /**
                            PublicRoom.GetInstance();
                            PublicRoom.nameStr = new string(temp.name);
                            PublicRoom.timeStr = new string(temp.lastLanuch);
                            PublicRoom.ipStr = new string(temp.lastIP);
                             **/
                            //PersonData.m_Name=new string(temp.name);
                            PersonData.m_ID = temp.account_id;
                            PersonData.m_Name = PersonName.GetName(temp.account_id);
                            PersonData.m_LastTime = new string(temp.lastLanuch);
                            PersonData.m_LastIP= new string(temp.lastIP);
                            PublicRoom.publicRoomFlag = true;

                            PersonData.m_Party= temp.party; //标记当前阵营 ,用于判断阵容变化
                            Application.LoadLevel("PublicRoom");
                        }
                        break;
                    case ProtoID.PartyID://更新分组信息
                        {
                            Party_toc temp = (Party_toc)msg;

                            
                            UpdateParty.b_1ID = temp.b1;
                            UpdateParty.b_2ID = temp.b2;
                            UpdateParty.b_3ID = temp.b3;
                            UpdateParty.b_4ID = temp.b4;
                            UpdateParty.b_5ID = temp.b5;

                            UpdateParty.r_1ID = temp.r1;
                            UpdateParty.r_2ID = temp.r2;
                            UpdateParty.r_3ID = temp.r3;
                            UpdateParty.r_4ID = temp.r4;
                            UpdateParty.r_5ID = temp.r5;

                            /**
                            UpdateParty.b_1ID = temp.blue[0];
                            UpdateParty.b_2ID = temp.blue[1];
                            UpdateParty.b_3ID = temp.blue[2];
                            UpdateParty.b_4ID = temp.blue[3];
                            UpdateParty.b_5ID = temp.blue[4];

                            UpdateParty.r_1ID = temp.red[0];
                            UpdateParty.r_2ID = temp.red[1];
                            UpdateParty.r_3ID = temp.red[2];
                            UpdateParty.r_4ID = temp.red[3];
                            UpdateParty.r_5ID = temp.red[4];
                             * */
                            UpdateParty.flag = true;

                            //Debug.Log("更新分组");

                        }
                        break;
                    case ProtoID.ChatID://房间聊天信息
                        {
                            Chat_tocs temp = (Chat_tocs)msg;

                            string str = new string(temp.msg);
                            Send_Btn.str = str;
                            //Debug.Log("收到消息:" + str);
                           // Debug.Log("收到消息:");
                            Send_Btn.uid = temp.user_id;
                            //Send_Btn.str = new string(temp.msg);
                            Send_Btn.flag = true;
                        }
                        break;
                    case ProtoID.PartyChangeID://阵营改变
                        { 
                            //直接改变阵营即可
                            if (PartyType.BLUE == PersonData.m_Party)
                                PersonData.m_Party = PartyType.RED;
                            else
                                PersonData.m_Party = PartyType.BLUE;

                            //Debug.Log("自身阵营改变、当前阵营：" + PersonData.m_Party);
                        
                        }
                        break;
                    case ProtoID.GameStart://开始游戏
                        {
                            Debug.Log("开始游戏");
                            Application.LoadLevel("GameMap"); 
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
