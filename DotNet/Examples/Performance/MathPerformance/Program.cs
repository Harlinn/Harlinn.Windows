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
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using Harlinn.Common.Core.Net;

namespace MathPerformance
{

    class IteratorEnumerator : IEnumerator<long>
    {
        long current_;
        long maxValue_;

        public IteratorEnumerator(long maxValue)
        {
            current_ = -1;
            maxValue_ = maxValue;
        }
        public long Current
        {
            get
            {
                return current_;
            }
        }
        object IEnumerator.Current
        {
            get
            {
                return current_;
            }
        }
        public void Dispose()
        {
            
        }

        public bool MoveNext()
        {
            current_++;
            return current_ < maxValue_;
        }

        public void Reset()
        {
            current_ = -1;
        }
    }

    class Iterator : IEnumerable<long>
    {
        long maxValue_;

        public Iterator(long maxValue)
        {
            maxValue_ = maxValue;
        }

        public IEnumerator<long> GetEnumerator()
        {
            return new IteratorEnumerator(maxValue_);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new IteratorEnumerator(maxValue_);
        }
    }


    class Program
    {

        static IEnumerable<long> Iterations2(long count)
        {
            for (long i = 0; i < count; i++)
            {
                yield return i;
            }
            yield break;
        }
        static IEnumerable<long> Iterations3(long count)
        {
            return new Iterator(count);
        }


        static void RunTest(long outerIterationCount, Func<double,double> func, 
            double baseValue = Math.PI, double increment = 0.000001, [CallerMemberName] string caller = "")
        {
            const long InnerIterationCount = 1_000_000_000;

            for (int j = 0; j < outerIterationCount; j++)
            {
                double argumentValue = baseValue;
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                for (long i = 0; i < InnerIterationCount; i++)
                {
                    accumulated += func(argumentValue);
                    argumentValue += increment;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("{0}: Iterations={1}, Duration={2}, Accumulated={3}", caller, InnerIterationCount, duration, accumulated);
            }
        }

        static void RunTest(long outerIterationCount, Func<double, double, double> func,
            double baseValue1 = Math.PI, double increment1 = 0.000001, double baseValue2 = Math.PI, double increment2 = 0.000001, [CallerMemberName] string caller = "")
        {
            const long InnerIterationCount = 1_000_000_000;

            for (int j = 0; j < outerIterationCount; j++)
            {
                double argumentValue1 = baseValue1;
                double argumentValue2 = baseValue2;
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                for (long i = 0; i < InnerIterationCount; i++)
                {
                    accumulated += func(argumentValue1, argumentValue2);
                    argumentValue1 += increment1;
                    argumentValue2 += increment2;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("{0}: Iterations={1}, Duration={2}, Accumulated={3}", caller, InnerIterationCount, duration, accumulated);
            }
        }

        static void RunTest2(long outerIterationCount, Func<double, double> func,
            double baseValue = Math.PI, double increment = 0.000001, [CallerMemberName] string caller = "")
        {
            const long InnerIterationCount = 1_000_000_000;

            for (int j = 0; j < outerIterationCount; j++)
            {
                double argumentValue = baseValue;
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                foreach (long i in Iterations2(InnerIterationCount))
                {
                    accumulated += func(argumentValue);
                    argumentValue += increment;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("{0}: Iterations={1}, Duration={2}, Accumulated={3}", caller, InnerIterationCount, duration, accumulated);
            }
        }

        static void RunTest3(long outerIterationCount, Func<double, double> func,
            double baseValue = Math.PI, double increment = 0.000001, [CallerMemberName] string caller = "")
        {
            const long InnerIterationCount = 1_000_000_000;

            for (int j = 0; j < outerIterationCount; j++)
            {
                double argumentValue = baseValue;
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                foreach (long i in Iterations3(InnerIterationCount))
                {
                    accumulated += func(argumentValue);
                    argumentValue += increment;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("{0}: Iterations={1}, Duration={2}, Accumulated={3}", caller, InnerIterationCount, duration, accumulated);
            }
        }


        static void OverheadTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => x);
        }
        static void OverheadTest2(long outerIterationCount)
        {
            RunTest2(outerIterationCount, (x) => x);
        }
        static void OverheadTest3(long outerIterationCount)
        {
            RunTest3(outerIterationCount, (x) => x);
        }

        static void IsNaNTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return double.IsNaN(x) ? 1 : 0; });
        }

        static void IsInfTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return double.IsInfinity(x) ? 1 : 0; });
        }

        static void AbsTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Abs(x); });
        }

        static void SignBitTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Sign(x) < 0 ? 1.0 : 0.0; });
        }


        static double frexp(double x, out int e)
        {
            ulong yi = (ulong)BitConverter.DoubleToInt64Bits(x);
            ulong ee = yi >> 52 & 0x7ff;

            if (ee == 0)
            {
                if (x != 0.0)
                {
                    unchecked
                    {
                        x = frexp(x * BitConverter.Int64BitsToDouble((long)0xfffffffffffff800), out e);
                    }
                    e -= 64;
                }
                else
                {
                    e = 0;
                }
                return x;
            }
            else if (ee == 0x7ff)
            {
                e = -1;
                return x;
            }

            e = (int)ee - 0x3fe;
            yi &= 0x800fffffffffffff;
            yi |= 0x3fe0000000000000;
            return BitConverter.Int64BitsToDouble((long)yi);
        }

        static void FRExpTest(long outerIterationCount)
        {
            double baseValue = Math.PI;
            double increment = 0.000001;
            string testName = "FRExpTest";
            const long InnerIterationCount = 1_000_000_000;

            for (int j = 0; j < outerIterationCount; j++)
            {
                double argumentValue = baseValue;
                double accumulated1 = 0.0;
                double accumulated2 = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                for (long i = 0; i < InnerIterationCount; i++)
                {
                    int n;
                    accumulated1 += frexp(argumentValue, out n);
                    accumulated2 += Convert.ToDouble(n);
                    argumentValue += increment;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("{0}: Iterations={1}, Duration={2}, Accumulated 1={3}, Accumulated 2={3}", testName, InnerIterationCount, duration, accumulated1, accumulated2);
            }
        }

        static double modf(double x, out double intPart)
        {
            intPart = Math.Truncate(x);
            return x - intPart;
        }

        static void ModFTest(long outerIterationCount)
        {
            double baseValue = Math.PI;
            double increment = 0.000001;
            string testName = "ModFTest";
            const long InnerIterationCount = 1_000_000_000;

            for (int j = 0; j < outerIterationCount; j++)
            {
                double argumentValue = baseValue;
                double accumulated1 = 0.0;
                double accumulated2 = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                for (long i = 0; i < InnerIterationCount; i++)
                {
                    double n;
                    accumulated1 += modf(argumentValue, out n);
                    accumulated2 += n;
                    argumentValue += increment;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("{0}: Iterations={1}, Duration={2}, Accumulated 1={3}, Accumulated 2={3}", testName, InnerIterationCount, duration, accumulated1, accumulated2);
            }
        }



        static void MinTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Min(x,x); });
        }
        static void MaxTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Max(x, x); });
        }

        static void CeilTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Ceiling(x); });
        }
        static void FloorTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Floor(x); });
        }
        static void TruncTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Truncate(x); });
        }
        static void RoundTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Round(x); });
        }

        static void ClampTest(long outerIterationCount )
        {
            const long InnerIterationCount = 1_000_000_000;
            double increment = 0.000001;
            double baseMin = Math.PI / 2;
            double baseValue = Math.PI;
            double baseMax = 2 * Math.PI;


            for (int j = 0; j < outerIterationCount; j++)
            {
                double argumentValue = baseValue;
                double argumentMin = baseMin;
                double argumentMax = baseMax;
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                for (long i = 0; i < InnerIterationCount; i++)
                {
                    accumulated += Math.Clamp(argumentValue, argumentMin, argumentMax);
                    argumentValue += increment;
                    argumentMin += increment;
                    argumentMax += increment;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("ClampTest: Iterations={0}, Duration={1}, Accumulated={2}", InnerIterationCount, duration, accumulated);
            }
        }

        static double Lerp(double a, double b, double t)
        {
            return a + (t * (b - a));
        }
        static void LerpTest(long outerIterationCount)
        {
            const long InnerIterationCount = 1_000_000_000;
            double increment = 0.000001;
            double baseMin = Math.PI / 2;
            double baseMax = 2 * Math.PI;


            for (int j = 0; j < outerIterationCount; j++)
            {
                double argumentMin = baseMin;
                double argumentMax = baseMax;
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                for (long i = 0; i < InnerIterationCount; i++)
                {
                    accumulated += Lerp(argumentMin, argumentMax, 0.5);
                    argumentMin += increment;
                    argumentMax += increment;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("LerpTest: Iterations={0}, Duration={1}, Accumulated={2}", InnerIterationCount, duration, accumulated);
            }
        }




        static void ScaleByNTest( long outerIterationCount )
        {
            long ValueIterationCount = 10_000_000;
            long ExpIterationCount = 100;
            long InnerIterationCount = ValueIterationCount * ExpIterationCount;

            double increment = 0.000001;
            double baseValue = Math.PI / 2.0;

            for ( int k = 0; k < outerIterationCount; k++ )
            {
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch( );
                stopwatch.Start( );
                double value = baseValue;

                for ( long i = 0; i < ValueIterationCount; i++ )
                {
                    for ( int j = 0; j < ExpIterationCount; ++j )
                    {
                        accumulated += Math.ScaleB( value, j + 1 );
                    }
                    value += increment;
                }

                stopwatch.Stop( );
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("ScaleByNTest: Iterations={0}, Duration={1}, Accumulated={2}", InnerIterationCount, duration, accumulated);
            }
        }

        static void CopySignTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.CopySign(x,-1.0); });
        }

        static void SinTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Sin(x); });
        }
        static void ASinTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Asin(x); }, 0.9 / 1000000000.0, 1.0 / 1000000000.0);
        }
        static void CosTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Cos(x); });
        }
        static void ACosTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Acos(x); }, 0.9 / 1000000000.0, 1.0 / 1000000000.0);
        }
        static void TanTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Tan(x); });
        }
        static void ATanTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Atan(x); }, 0.9 / 1000000000.0, 1.0 / 1000000000.0);
        }
        static void ATan2Test(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Atan2(x, x); }, 0.9 / 1000000000.0, 1.0 / 1000000000.0);
        }

        static void SqrtTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Sqrt(x); });
        }

        static void NextUpTest(long outerIterationCount)
        {
            const long InnerIterationCount = 1_000_000_000;
            double baseValue = 0.0;

            for (int j = 0; j < outerIterationCount; j++)
            {
                double argument = baseValue;
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                for (long i = 0; i < InnerIterationCount; i++)
                {
                    argument = Math.BitIncrement(argument);
                    accumulated += argument;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("NextUpTest: Iterations={0}, Duration={1}, Accumulated={2}", InnerIterationCount, duration, accumulated);
            }
        }
        static void NextDownTest(long outerIterationCount)
        {
            const long InnerIterationCount = 1_000_000_000;
            double baseValue = 0.0;

            for (int j = 0; j < outerIterationCount; j++)
            {
                double argument = baseValue;
                double accumulated = 0.0;
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                for (long i = 0; i < InnerIterationCount; i++)
                {
                    argument = Math.BitDecrement(argument);
                    accumulated += argument;
                }

                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                Console.Out.WriteLine("NextDownTest: Iterations={0}, Duration={1}, Accumulated={2}", InnerIterationCount, duration, accumulated);
            }
        }

        static void FModTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x,y) => { return x%y; }, Math.PI, 0.000001, Math.PI / 4.0, 0.000001);
        }
        static void ExpTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Exp(x); }, 0.9, 0.000000001);
        }
        static void HypotTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x,y) => { return Math.Sqrt(x*x+y*y); }, 0.999, 0.000000001, 0.999, 0.000000001);
        }

        static void LogTest(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Log(x); }, 0.9, 0.000000001);
        }
        static void Log2Test(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Log2(x); }, 0.9, 0.000000001);
        }
        static void Log10Test(long outerIterationCount)
        {
            RunTest(outerIterationCount, (x) => { return Math.Log10(x); }, 0.9, 0.000000001);
        }



        static void Main(string[] args)
        {
            const long OuterIterationCount = 1;
            OverheadTest(OuterIterationCount);
            OverheadTest2(OuterIterationCount);
            OverheadTest3(OuterIterationCount);
            IsNaNTest(OuterIterationCount);
            IsInfTest(OuterIterationCount);
            AbsTest(OuterIterationCount);
            SignBitTest(OuterIterationCount);
            FRExpTest(OuterIterationCount);
            ModFTest(OuterIterationCount);
            MinTest(OuterIterationCount);
            MaxTest(OuterIterationCount);
            CeilTest(OuterIterationCount);
            FloorTest(OuterIterationCount);
            TruncTest(OuterIterationCount);
            RoundTest(OuterIterationCount);
            ClampTest(OuterIterationCount);
            LerpTest(OuterIterationCount);
            CopySignTest(OuterIterationCount);
            ScaleByNTest(OuterIterationCount);
            SinTest(OuterIterationCount);
            ASinTest(OuterIterationCount);
            CosTest(OuterIterationCount);
            ACosTest(OuterIterationCount);
            TanTest(OuterIterationCount);
            ATanTest(OuterIterationCount);
            ATan2Test(OuterIterationCount);
            SqrtTest(OuterIterationCount);
            NextUpTest(OuterIterationCount);
            NextDownTest(OuterIterationCount);
            FModTest(OuterIterationCount);
            ExpTest(OuterIterationCount);
            HypotTest(OuterIterationCount);
            LogTest(OuterIterationCount);
            Log2Test(OuterIterationCount);
            Log10Test(OuterIterationCount);


            Console.WriteLine();
            Console.WriteLine("Done!");
        }
    }
}
