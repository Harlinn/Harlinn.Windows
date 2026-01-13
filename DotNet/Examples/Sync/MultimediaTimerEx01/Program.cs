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
using System.Threading;
using Harlinn.Common.Core.Net.Sync;


namespace MultimediaTimerEx01
{
    class Program
    {
        static ManualResetEvent _manualResetEvent;
        static DateTime _dueTime;
        static bool _done;
        static void Main(string[] args)
        {
            _manualResetEvent = new ManualResetEvent(false);
            var stopwatch = new Stopwatch();
            stopwatch.Start();
            _dueTime = DateTime.UtcNow + TimeSpan.FromSeconds(2);

            var multimediaTimer = new MultimediaTimer();
            multimediaTimer.Interval = 1;
            multimediaTimer.Resolution = 1;
            multimediaTimer.Elapsed += OnTimer;
            multimediaTimer.Start();
            Console.Out.WriteLine("Waiting");
            _manualResetEvent.WaitOne();
            stopwatch.Stop();
            Console.Out.WriteLine("Done waiting...");
            multimediaTimer.Stop();

            var seconds = stopwatch.Elapsed.TotalSeconds;
            System.Console.WriteLine("Waited for {0} seconds", seconds);

        }

        private static void OnTimer(object sender, EventArgs e)
        {
            if (DateTime.UtcNow > _dueTime && _done == false)
            {
                _done = true;
                _manualResetEvent.Set();
            }
        }
    }
}
