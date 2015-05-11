using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace Assets.Script.Proto
{
    class MTransform
    {
        public static byte[] StructToBytes(Message obj)
        {
            //得到结构体的大小
            int size = Marshal.SizeOf(obj);

            //创建byte []数组存放数据
            byte[] bytes = new byte[size];
            //Array.Clear(bytes, 0, bytes.Length);

            //分配结构体大小的内存空间
            IntPtr objPtr = Marshal.AllocHGlobal(size);
            try
            {
                //拷贝结构体到分配好的内存空间
                Marshal.StructureToPtr(obj, objPtr, false);
                Marshal.Copy(objPtr, bytes, 0, size);

                //char[] c = Encoding.ASCII.GetChars(bytes);
                //Console.WriteLine("bytes[]={0}", bytes.Length);
                return bytes;
            }
            finally { 
               //释放内存空间
                Marshal.FreeHGlobal(objPtr);
            }
        }

        public static object BytesToStruct(byte[] bytes, Type type)
        {
            int size = Marshal.SizeOf(type);
            //char []c=Encoding.ASCII.GetChars(bytes);
            //如果bytes数组的长度小于结构体的大小
            if (size > bytes.Length)
            {
                return null;
            }
            /** 因为tos和toc不再共用一个结构，因此不需要做移位操作
            IntPtr ptr = Marshal.AllocHGlobal(size);
            int offsetPtr = ptr.ToInt32() + 4;//因为最开始Recive的时候，已经接收了4个byte的ID数据，因此，内存指针要后移4位
            //IntPtr objPtr = new IntPtr(offsetPtr);
             * */
            IntPtr objPtr=Marshal.AllocHGlobal(size);
            try
            {
                Marshal.Copy(bytes, 0, objPtr, size);

                //将数据转换为目标结构体
                //问题出在了下面这一行，转换的时候，丢失了某些数据
                //将协议中的int放在前面，即解决数据丢失问题，暂时不清楚是什么问题，可能是某个标识符使其忽略了后面的数字
                object obj = Marshal.PtrToStructure(objPtr, type);
                return obj;
            }
            catch (Exception e){
                GameLog.Log(Log.GameLogLevel.ERROR, Log.GameLogType.ProtoLog, "解析toc出现异常" + type.ToString() + "  " + e.Message);
                return null;
            }
            finally {
                Marshal.FreeHGlobal(objPtr);
            }
        }
      

    }
}
