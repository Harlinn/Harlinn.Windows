using System;
using System.Diagnostics;
using System.Threading;
using Harlinn.Common.Net.Sync;


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
