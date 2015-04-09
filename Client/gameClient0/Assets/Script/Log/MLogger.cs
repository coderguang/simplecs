using UnityEngine;
using System.Collections;
using System.IO;
using Assets.Script.Time;
public class MLogger {

    private static string file = "log.txt";
    private static FileStream myFs;
    private static StreamWriter mySw;

    private static MLogger _instance=null;

    private MLogger() {
        Init();
    
    }

    private void Init() {

        if (!File.Exists(file)){
            myFs = new FileStream(file, FileMode.Create);
        }
        mySw = new StreamWriter(file, true, System.Text.Encoding.GetEncoding("utf-8"));
        mySw.WriteLine("hello,this is client log");
        System.Console.WriteLine("write ok");
    }

    public static void Log(string msg)
    {
        mySw.WriteLine(MTimer.GetTime());
        mySw.WriteLine(msg);
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
