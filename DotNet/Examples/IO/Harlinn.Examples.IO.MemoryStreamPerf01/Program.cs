using System;
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
