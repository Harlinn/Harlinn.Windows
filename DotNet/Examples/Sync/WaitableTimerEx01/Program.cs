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
using System.Diagnostics;
using Harlinn.Common.Core.Net.Sync;

namespace WaitableTimerEx01
{
    class Program
    {
        static void Main(string[] args)
        {
            // Create a manual reset high resolution timer
            var waitableTimer = new WaitableTimer(true,true);
            var stopwatch = new Stopwatch();
            stopwatch.Start();
            TimeSpan waitTime = TimeSpan.FromSeconds(10);
            waitableTimer.SetTimer(waitTime, 0, false);
            waitableTimer.Wait();
            stopwatch.Stop();

            var seconds = stopwatch.Elapsed.TotalSeconds;
            System.Console.WriteLine("Waited for {0} seconds", seconds);


        }
    }
}
