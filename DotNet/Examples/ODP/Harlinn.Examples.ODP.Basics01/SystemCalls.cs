using System;
using System.Runtime.InteropServices;

namespace Harlinn.Examples.ODP.Basics01
{
    class SystemCalls
    {
        [DllImport("kernel32.dll")]
        static extern IntPtr GetCurrentThread();

        [DllImport("kernel32.dll")]
        static extern uint GetCurrentThreadId();

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool GetThreadTimes(IntPtr hThread, out long lpCreationTime, out long lpExitTime, out long lpKernelTime, out long lpUserTime);

        public static TimeSpan GetUserTime()
        {
            IntPtr threadHandle = GetCurrentThread();
            long creationTime;
            long exitTime;
            long kernelTime;
            long userTime;
            GetThreadTimes(threadHandle, out creationTime, out exitTime, out kernelTime, out userTime);
            return new TimeSpan(userTime);
        }
    }
}
