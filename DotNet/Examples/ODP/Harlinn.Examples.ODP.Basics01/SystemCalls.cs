/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
﻿using System;
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
