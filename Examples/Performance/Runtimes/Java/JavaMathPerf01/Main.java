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


import java.util.function.DoubleFunction;

import javax.lang.model.util.ElementScanner6;

public class Main 
{
    static void RunTest( long outerIterationCount, DoubleFunction<Double> func, double baseValue, double increment, int stackDepth )
    {
        StackTraceElement[] stacktrace = Thread.currentThread().getStackTrace();
        StackTraceElement e = stacktrace[stackDepth];
        String testName = e.getMethodName();

        long InnerIterationCount = 1_000_000_000;

        for (int j = 0; j < outerIterationCount; j++)
        {
            double argumentValue = baseValue;
            double accumulated = 0.0;
            long startTime = System.currentTimeMillis();

            for (long i = 0; i < InnerIterationCount; i++)
            {
                accumulated += func.apply(argumentValue);
                argumentValue += increment;
            }

            long endTime = System.currentTimeMillis();
            var duration = (endTime - startTime)/1000.0;
            System.out.println(testName + ": Duration="+duration+", Accumulated="+accumulated);
        }
    }

    static void RunTest( long outerIterationCount, DoubleFunction<Double> func, double baseValue, double increment )
    {
        RunTest(outerIterationCount,func,baseValue, increment,3);
    }
    static void RunTest( long outerIterationCount, DoubleFunction<Double> func, double baseValue )
    {
        RunTest(outerIterationCount,func,baseValue, 0.000001,3);
    }
    static void RunTest( long outerIterationCount, DoubleFunction<Double> func )
    {
        RunTest(outerIterationCount,func,Math.PI, 0.000001,3);
    }

    static void OverheadTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> x );
    }

    static void IsNaNTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> Double.isNaN(x)?1.0:0.0 );
    }
    static void IsInfTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> Double.isInfinite(x)?1.0:0.0 );
    }
    static void AbsTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> Math.abs(x) );
    }
    static void SignBitTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> Math.signum(x) < 0.0?1.0:0.0  );
    }
    static void MinTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> Math.min(x,x) );
    }
    static void MaxTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> Math.max(x,x) );
    }
    static void CeilTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> Math.ceil(x) );
    }
    static void FloorTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> Math.floor(x) );
    }
    static void TruncTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> x >= 0? (double)Math.round(x-0.5):(double)Math.round(x+0.5) );
    }
    static void RoundTest( long outerIterationCount )
    {
        RunTest(outerIterationCount, x -> (double)Math.round(x) );
    }

    static double Clamp(double value, double minValue, double maxValue)
    {
        if(value < minValue)
        {
            return minValue;
        }
        else if (value > maxValue)
        {
            return maxValue;
        }
        else
        {
            return value;
        }
    }

    static void ClampTest( long outerIterationCount )
    {
        double baseValue = Math.PI; 
        double increment = 0.000001;
        long InnerIterationCount = 1_000_000_000;

        for (int j = 0; j < outerIterationCount; j++)
        {
            double argumentMin = Math.PI/2;
            double argumentValue = baseValue;
            double argumentMax = 2 * Math.PI;
            double accumulated = 0.0;
            long startTime = System.currentTimeMillis();

            for (long i = 0; i < InnerIterationCount; i++)
            {
                accumulated += Clamp(argumentValue,argumentMin,argumentMax);
                argumentValue += increment;
                argumentMin += increment;
                argumentMax += increment;
            }

            long endTime = System.currentTimeMillis();
            var duration = (endTime - startTime)/1000.0;
            System.out.println("ClampTest: Duration="+duration+", Accumulated="+accumulated);
        }
    }

    static double Lerp(double a, double b, double t)
    {
        return a + (t * (b - a));
    }

    static void LerpTest( long outerIterationCount )
    {
        double increment = 0.000001;
        long InnerIterationCount = 1_000_000_000;

        for (int j = 0; j < outerIterationCount; j++)
        {
            double argumentMin = Math.PI/2;
            double argumentMax = 2 * Math.PI;
            double accumulated = 0.0;
            long startTime = System.currentTimeMillis();

            for (long i = 0; i < InnerIterationCount; i++)
            {
                accumulated += Lerp(argumentMin,argumentMax, 0.5 );
                argumentMin += increment;
                argumentMax += increment;
            }

            long endTime = System.currentTimeMillis();
            var duration = (endTime - startTime)/1000.0;
            System.out.println("LerpTest: Duration="+duration+", Accumulated="+accumulated);
        }
    }

    static void ScaleByNTest( long outerIterationCount )
    {
        long ValueIterationCount = 10_000_000;
        long ExpIterationCount = 100;

        double increment = 0.000001;
        double baseValue = 2 * Math.PI;

        for ( int k = 0; k < outerIterationCount; k++ )
        {
            double accumulated = 0.0;
            long startTime = System.currentTimeMillis();
            double value = baseValue;

            for ( long i = 0; i < ValueIterationCount; i++ )
            {
                for ( int j = 0; j < ExpIterationCount; ++j )
                {
                    accumulated += Math.scalb( value, j + 1 );
                }
                value += increment;
            }

            long endTime = System.currentTimeMillis();
            var duration = (endTime - startTime)/1000.0;
            System.out.println("ScaleByNTest: Duration="+duration+", Accumulated="+accumulated);
        }
    }

    static void CopySignTest(long outerIterationCount)
    {
        RunTest(outerIterationCount, (x) -> Math.copySign(x,-1.0));
    }

    static void SinTest(long outerIterationCount)
    {
        RunTest(outerIterationCount, (x) -> Math.sin(x));
    }
    static void ASinTest(long outerIterationCount)
    {
        RunTest(outerIterationCount, (x) -> Math.asin(x), 0.9 / 1000000000.0, 1.0 / 1000000000.0);
    }
    static void CosTest(long outerIterationCount)
    {
        RunTest(outerIterationCount, (x) -> Math.cos(x));
    }
    static void ACosTest(long outerIterationCount)
    {
        RunTest(outerIterationCount, (x) -> Math.acos(x), 0.9 / 1000000000.0, 1.0 / 1000000000.0);
    }
    static void TanTest(long outerIterationCount)
    {
        RunTest(outerIterationCount, (x) -> Math.tan(x));
    }
    static void ATanTest(long outerIterationCount)
    {
        RunTest(outerIterationCount, (x) -> Math.atan(x), 0.9 / 1000000000.0, 1.0 / 1000000000.0);
    }
    static void ATan2Test(long outerIterationCount)
    {
        RunTest(outerIterationCount, (x) -> Math.atan2(x,x), 0.9 / 1000000000.0, 1.0 / 1000000000.0);
    }


    public static void main(String[] args) 
    {
        long outerIterationCount = 1;
        OverheadTest(outerIterationCount);
        IsNaNTest(outerIterationCount);
        IsInfTest(outerIterationCount);
        AbsTest(outerIterationCount);
        SignBitTest(outerIterationCount);
        MinTest(outerIterationCount);
        MaxTest(outerIterationCount);
        CeilTest(outerIterationCount);
        FloorTest(outerIterationCount);
        TruncTest(outerIterationCount);
        RoundTest(outerIterationCount);
        ClampTest(outerIterationCount);
        LerpTest(outerIterationCount);
        ScaleByNTest(outerIterationCount);
        CopySignTest(outerIterationCount);
        SinTest(outerIterationCount);
        ASinTest(outerIterationCount);
        CosTest(outerIterationCount);
        ACosTest(outerIterationCount);
        TanTest(outerIterationCount);
        ATanTest(outerIterationCount);
        ATan2Test(outerIterationCount);
    }
}