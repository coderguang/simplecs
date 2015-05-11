using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Script.Log
{
    /**
     * Log的类型
     * 
     */
    public enum GameLogLevel : int { 
        FATAL,
        ERROR,
        WARN,
        INFO,
        DEBUG
    };
    public enum GameLogType : int { 
        Conect,
        LanuchLog,  //the log happen when lanuch
        RegitLog,   
        RoomLog,    
        GameLog,    //in gameing
        ResultLog,    //complete the game
        ProtoLog    //proto log
    }
}
