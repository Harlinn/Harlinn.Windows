using System;
using System.Diagnostics;
using Harlinn.Common.Net.Sync;

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
