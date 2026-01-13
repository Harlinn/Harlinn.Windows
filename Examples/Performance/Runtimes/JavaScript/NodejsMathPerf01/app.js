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


function RunTest(outerIterationCount, func1, baseValue = Math.PI, increment = 0.000001)
{
    var testName = RunTest.caller.name;
    for (var i = 0; i < outerIterationCount; i++)
    {
        var argumentValue = baseValue;
        var innerIterationCount = 1000000000;
        var accumulated = 0.0;
        console.time(testName);
        for (var j = 0; j < innerIterationCount; j++)
        {
            accumulated += func1(argumentValue);
            argumentValue += increment;
        }
        console.timeEnd(testName);
        console.log("\tAccumulated", accumulated)
    }
}

function OverheadTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => x);
}

function IsNaNTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => isNaN(x));
}

function IsInfTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => (isFinite(x) === false) && (isNaN(x) === false) );
}

function AbsTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.abs(x) );
}

function MinTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.min(x,x));
}
function MaxTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.max(x, x));
}
function FloorTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.floor(x));
}
function CeilTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.ceil(x));
}
function TruncTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.trunc(x));
}
function RoundTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.round(x));
}

function Clamp(x, minValue, maxValue)
{
    if (x < minValue)
    {
        return minValue;
    }
    else if (x > maxValue)
    {
        return maxValue;
    }
    return x;
}

function ClampTest(outerIterationCount)
{
    var baseMin = Math.PI/2;
    var baseValue = Math.PI;
    var baseMax = 2 * Math.PI;
    var increment = 0.000001;
    for (var i = 0; i < outerIterationCount; i++)
    {
        var argumentValue = baseValue;
        var argumentMin = baseMin;
        var argumentMax = baseMax;
        var innerIterationCount = 1000000000;
        var accumulated = 0.0;
        console.time("ClampTest");
        for (var j = 0; j < innerIterationCount; j++)
        {
            accumulated += Clamp(argumentValue, argumentMin, argumentMax);
            argumentValue += increment;
            argumentMin += increment;
            argumentMax += increment;
        }
        console.timeEnd("ClampTest");
        console.log("\tAccumulated", accumulated);
    }
}

function Lerp(a, b, t)
{
    return a + (t * (b - a));
}

function LerpTest(outerIterationCount)
{
    var baseMin = Math.PI / 2;
    var baseMax = 2 * Math.PI;
    var increment = 0.000001;
    for (var i = 0; i < outerIterationCount; i++)
    {
        var argumentMin = baseMin;
        var argumentMax = baseMax;
        var innerIterationCount = 1000000000;
        var accumulated = 0.0;
        console.time("LerpTest");
        for (var j = 0; j < innerIterationCount; j++)
        {
            accumulated += Lerp(argumentMin, argumentMax, 0.5);
            argumentMin += increment;
            argumentMax += increment;
        }
        console.timeEnd("LerpTest");
        console.log("\tAccumulated", accumulated);
    }
}

const CopySign = (x, y) => Math.sign(x) === Math.sign(y) ? x : -x;

function CopySignTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => CopySign(x,-1.0));
}

const CopySign2 = (x, y) => CopySign(x, y);
function CopySign2Test(outerIterationCount)
{
    RunTest(outerIterationCount, x => CopySign2(x, -1.0));
}

function CopySign3(x, y)
{
    return Math.sign(x) === Math.sign(y) ? x : -x;
}

function CopySign3Test(outerIterationCount)
{
    RunTest(outerIterationCount, x => CopySign3(x, -1.0));
}

function CopySign4(x, y)
{
    return Math.sign(y) >= 0 ? x : -x;
}

function CopySign4Test(outerIterationCount)
{
    RunTest(outerIterationCount, x => CopySign4(x, -1.0));
}

const CopySign5 = (x, y) => Math.sign(y) >= 0 ? x : -x;

function CopySign5Test(outerIterationCount)
{
    RunTest(outerIterationCount, x => CopySign5(x, -1.0));
}

function SinTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.sin(x), Math.PI / 100.0);
}
function ASinTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.asin(x),0.9 / 1000000000.0, 1.0 / 1000000000.0);
}

function CosTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.cos(x), Math.PI / 100.0);
}
function ACosTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.acos(x), 0.9 / 1000000000.0, 1.0 / 1000000000.0);
}

function TanTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.tan(x), Math.PI / 100.0);
}
function ATanTest(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.atan(x), 0.9 / 1000000000.0, 1.0 / 1000000000.0);
}

function ATan2Test(outerIterationCount)
{
    RunTest(outerIterationCount, x => Math.atan2(x,x), 0.9 / 1000000000.0, 1.0 / 1000000000.0);
}



var outerIterationCount = 1;
OverheadTest(outerIterationCount);

IsNaNTest(outerIterationCount);
IsInfTest(outerIterationCount);
AbsTest(outerIterationCount);
MinTest(outerIterationCount);
MaxTest(outerIterationCount);
FloorTest(outerIterationCount);
CeilTest(outerIterationCount);
TruncTest(outerIterationCount);
RoundTest(outerIterationCount);
ClampTest(outerIterationCount);
LerpTest(outerIterationCount);
CopySignTest(outerIterationCount);
SinTest(outerIterationCount);
ASinTest(outerIterationCount);
CosTest(outerIterationCount);
ACosTest(outerIterationCount);
TanTest(outerIterationCount);
ATanTest(outerIterationCount);
ATan2Test(outerIterationCount);

CopySign2Test(outerIterationCount);
CopySign3Test(outerIterationCount);
CopySign4Test(outerIterationCount);
CopySign5Test(outerIterationCount);

console.log('Done!');
