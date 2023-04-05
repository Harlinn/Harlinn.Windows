using System;
using System.Collections.Generic;

class TimeseriesPoint
{
    DateTime _timestamp;
    ulong _flags;
    double _value;

    public TimeseriesPoint(DateTime timestamp, ulong flags, double value)
    {
        _timestamp = timestamp;
        _flags = flags;
        _value = value;
    }

    public DateTime Timestamp { get => _timestamp; set => _timestamp = value; }
    public ulong Flags { get => _flags; set => _flags = value; }
    public double Value { get => _value; set => _value = value; }
}


namespace DictionaryPerformance
{
    

    class Program
    {
        static void Fill(DateTime fromTimestamp, DateTime toTimestamp, TimeSpan interval, Dictionary<DateTime, TimeseriesPoint> result)
        {
            while (fromTimestamp < toTimestamp)
            {
                result[fromTimestamp] = new TimeseriesPoint(fromTimestamp,0,1.0);
                fromTimestamp += interval;
            }
        }

        static void Run(int iterations)
        {
            DateTime startDateTime = new DateTime(2010,1,1);
            DateTime endDateTime = new DateTime(2015, 1, 1);
            TimeSpan resolution = TimeSpan.FromMinutes(1);
            for (int i = 0; i < iterations; i++)
            {
                var dict = new Dictionary<DateTime, TimeseriesPoint>();
                Fill(startDateTime, endDateTime, resolution, dict);
            }
        }

        static void Main(string[] args)
        {
            var stopwatch = new System.Diagnostics.Stopwatch();
            stopwatch.Start();
            Run(100);
            stopwatch.Stop();
            var duration = stopwatch.Elapsed.TotalSeconds;
            System.Console.WriteLine("Duration {0} seconds", duration);
        }
    }
}
