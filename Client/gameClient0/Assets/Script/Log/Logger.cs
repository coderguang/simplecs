using UnityEngine;
using System.Collections;
using System.IO;
public class Logger {

    private static string file = "log.txt";
    private static FileStream myFs;
    private static StreamWriter mySw;

    private static Logger _instance=null;

    private Logger() {
        Init();
    
    }

    private void Init() {

      //  if (!File.Exists(file)){
            myFs = new FileStream(file, FileMode.Create);
        //}
        mySw = new StreamWriter(file, true, System.Text.Encoding.GetEncoding("utf-8"));
        mySw.WriteLine("hello,this is client log");
        System.Console.WriteLine("write ok");
    }

    public static void Log(string msg) {
        mySw.WriteLine(msg);
    }

    public void Destroy() {
        mySw.Close();
        myFs.Close();
    }

    public static Logger GetInstance() { 
        if(null==_instance)
              _instance=new Logger();
        return _instance;
    
    }

}
