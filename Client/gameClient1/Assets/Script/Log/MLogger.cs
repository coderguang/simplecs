using UnityEngine;
using System.Collections;
using System.IO;
using Assets.Script.Time;
using Assets.Script.Log;
public class MLogger {

    private static string file = "log.txt";
    private static FileStream myFs;
    private static StreamWriter mySw;

    private static MLogger _instance=null;

    //控制log是否被打印
    private const bool fatalFlag = true;
    private const bool errorFlag = true;
    private const bool warnFlag = true;
    private const bool infoFlag = true;
    private const bool debugFlag = false;


    private MLogger() {
        Init();
    
    }

    private void Init() {

        if (!File.Exists(file)){
            myFs = new FileStream(file, FileMode.Create);
        }
        mySw = new StreamWriter(file, true, System.Text.Encoding.GetEncoding("utf-8"));
    }

    public static void Log(MLogLevel level,MLogType type,string msg)
    {
        /*判断该级别的log是否要被打印*/

        mySw.WriteLine(MTimer.GetTime());
        string msgType=null; 
        
        switch(level){
            case MLogLevel.DEBUG:
                if (!debugFlag)
                    return ;
                msgType="Debug  ";
                break;
            case MLogLevel.ERROR:
                if (!errorFlag)
                    return;
                msgType = "Error  ";
                break;
            case MLogLevel.FATAL:
                if (!fatalFlag)
                    return;
                msgType = "Fatal  ";
                break;
            case MLogLevel.INFO:
                if (!infoFlag)
                    return;
                msgType = "Info  ";
                break;
            case MLogLevel.WARN:
                if (!warnFlag)
                    return;
                msgType = "Warn  ";
                break;
        
        
        }
        switch (type) { 
            case MLogType.GameLog:
                msgType += "GameLog:";
                break;
            case MLogType.LanuchLog:
                msgType += "LanuchLog:";
                break;
            case MLogType.RegitLog:
                msgType += "RegitLog:";
                break;
            case MLogType.ResultLog:
                msgType +="ResultLog:";
                break;
            case MLogType.RoomLog:
                msgType +="RoomLog:";
                break;
        }
        /**
        mySw.Write(msgType);
        for (int i = 0; i < msg.Length; i++) { 
            if('\0'!=msg[i])    
                mySw.Write(msg[i]);
        }
        mySw.WriteLine();**/
        mySw.WriteLine(msgType + msg);
        mySw.Flush();
    }
    public static void Destroy() {
        mySw.Close();
        myFs.Close();
    }

    public static MLogger GetInstance() { 
        if(null==_instance)
              _instance=new MLogger();
        return _instance;
    
    }

}
