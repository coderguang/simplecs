using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace winClient2
{
    class Transform
    {
        public static byte[] StructToBytes(object obj) {
            //得到结构体的大小
            int size = Marshal.SizeOf(obj);

            //创建byte []数组存放数据
            byte[] bytes = new byte[size];
           //分配结构体大小的内存空间
            IntPtr objPtr = Marshal.AllocHGlobal(size);
           //拷贝结构体到分配好的内存空间
           Marshal.StructureToPtr(obj, objPtr, false);
           Marshal.Copy(objPtr, bytes, 0, size);
           //释放内存空间
           Marshal.FreeHGlobal(objPtr);
            
            Console.WriteLine("bytes[]={0}", bytes.Length);
            return bytes;        
        }

        public static object BytesToStruct(byte[] bytes,Type type) {
            int size = Marshal.SizeOf(type);
            //如果bytes数组的长度小于结构体的大小
            if (size > bytes.Length) {
                return null;
            }

            IntPtr objPtr = Marshal.AllocHGlobal(size);
            Marshal.Copy(bytes, 0, objPtr, size);

            //将数据转换为目标结构体
            object obj = Marshal.PtrToStructure(objPtr,type);

            Marshal.FreeHGlobal(objPtr);

            return obj;  
        }
        public static object BytesToStruct2(byte[] bytes, Type type)
        {
            object obj = new object();
            int size = Marshal.SizeOf(type);

            IntPtr objPtr = Marshal.AllocHGlobal(size);
            try
            {
                Marshal.Copy(bytes, 0, objPtr, size);
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Console.WriteLine(ex.Message);

            }
            catch (ArgumentNullException ex) {
                Console.WriteLine(ex.Message);
            }
            //将数据转换为目标结构体
            obj = (object)Marshal.PtrToStructure(objPtr, type);

            Marshal.FreeHGlobal(objPtr);

            return obj;
        }

    }
}
