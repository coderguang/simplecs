using UnityEngine;
using System.Collections;
using System.IO;
using Assets.Script.Time;
using Assets.Script.Log;
public class GameLog {    

    private static string file = "log.txt";
    private static FileStream myFs;
    private static StreamWriter mySw;

    private static GameLog _instance=null;

    //控制log是否被打印
    private const bool _Connect = true;
    private const bool _Fatal = true;
    private const bool _Error = true;
    private const bool _Warn = true;
    private const bool _Info = true;
    private const bool _Debug = false;

    private const bool isPrint = true;//打印到Unity




    private GameLog() {
        Init();
    
    }

    private void Init() {

        if (!File.Exists(file)){
            myFs = new FileStream(file, FileMode.Create);
        }
        mySw = new StreamWriter(file, true, System.Text.Encoding.GetEncoding("utf-8"));
    }    

    public static void Log(GameLogLevel level,GameLogType type,string msg)
    {
        /*判断该级别的log是否要被打印*/

        mySw.WriteLine(MTimer.GetTime());
        string msgType=null; 
        
        switch(level){
            case GameLogLevel.DEBUG:
                if (!_Debug)
                    return ;
                msgType="Debug  ";
                break;
            case GameLogLevel.ERROR:
                if (!_Error)
                    return;
                msgType = "Error  ";
                break;
            case GameLogLevel.FATAL:
                if (!_Fatal)
                    return;
                msgType = "Fatal  ";
                break;
            case GameLogLevel.INFO:
                if (!_Info)
                    return;
                msgType = "Info  ";
                break;
            case GameLogLevel.WARN:
                if (!_Warn)
                    return;
                msgType = "Warn  ";
                break;
        
        
        }
        switch (type) { 
            case GameLogType.GameLog:
                msgType += "GameLog:";
                break;
            case GameLogType.LanuchLog:
                msgType += "LanuchLog:";
                break;
            case GameLogType.RegitLog:
                msgType += "RegitLog:";
                break;
            case GameLogType.ResultLog:
                msgType +="ResultLog:";
                break;
            case GameLogType.RoomLog:
                msgType +="RoomLog:";
                break;
        }
        mySw.WriteLine(msgType + msg);
        mySw.Flush();

        if (isPrint) {
            Debug.Log(msgType + msg);
        }

    }
    public static void Destroy() {
        mySw.Close();
        myFs.Close();
    }

    public static GameLog GetInstance() { 
        if(null==_instance)
              _instance=new GameLog();
        return _instance;
    
    }

}
