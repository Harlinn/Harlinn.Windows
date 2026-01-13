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

namespace Harlinn.Examples.IO.MemoryStreamPerf01
{
    class Program
    {
        static void Main(string[] args)
        {
            ulong Iterations = 10000;
            ulong Values = 100000;
            long bytesWritten = 0;

            var stopwatch = new Stopwatch();
            stopwatch.Start();
            for (ulong i = 0; i < Iterations; ++i)
            {
                var stream = new System.IO.MemoryStream();
                ulong value = i + 1;
                var bytes = System.BitConverter.GetBytes(value);
                for (ulong j = 0; j < Values; ++j)
                {
                    stream.Write(bytes,0, bytes.Length);
                }
                bytesWritten += stream.Length;
            }
            stopwatch.Stop();
            var duration = stopwatch.Elapsed.TotalSeconds;
            var bytesPerSecond = ((double)bytesWritten) / duration;

            System.Console.Out.WriteLine("Wrote {0} bytes in {1} seconds, {2} bytes per second\n", bytesWritten, duration, bytesPerSecond);
        }
    }
}
