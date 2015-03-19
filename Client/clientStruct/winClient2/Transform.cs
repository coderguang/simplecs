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
            return bytes;        
        }
    }
}
