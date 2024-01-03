#=
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
=#


using Dates
using InteractiveUtils

function RunTest(outerIterationCount, testName ,func1, baseValue = pi, increment = 0.000001)
    for j = 1 : outerIterationCount
        argumentValue::Float64 = baseValue
        innerIterationCount = 1000000000
        accumulated::Float64 = 0.0
        startTime = now()
        for i = 1 : innerIterationCount
            accumulated += func1(argumentValue);
            argumentValue += increment
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount,
                    " iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end

function RunTestF(outerIterationCount, testName ,func1, baseValue = pi, increment = 0.000001)
    for j = 1 : outerIterationCount
        argumentValue::Float32 = baseValue
        innerIterationCount = 1000000000
        accumulated::Float32 = 0.0
        startTime = now()
        for i = 1 : innerIterationCount
            accumulated += func1(argumentValue);
            argumentValue += increment
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount,
                    " iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end


function RunTestWithTwoArguments(outerIterationCount, testName ,func1, baseValue1 = pi, increment1 = 0.000001, baseValue2 = baseValue1, increment2 = increment1 )
    for j = 1 : outerIterationCount
        argumentValue1::Float64 = baseValue1
        argumentValue2::Float64 = baseValue2
        innerIterationCount = 1000000000
        accumulated::Float64 = 0.0
        startTime = now()
        for i = 1 : innerIterationCount
            accumulated += func1(argumentValue1,argumentValue2);
            argumentValue1 += increment1
            argumentValue2 += increment2
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount,
                    " iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end



function RunTestReturningTwoValues(outerIterationCount, testName ,func1, baseValue = pi, increment = 0.000001)
    for j = 1 : outerIterationCount
        argumentValue::Float64 = baseValue
        innerIterationCount = 1000000000
        accumulated1::Float64 = 0.0
        accumulated2::Float64 = 0.0
        startTime = now()
        for i = 1 : innerIterationCount
            result = func1(argumentValue);
            accumulated1 += result[1]
            accumulated2 += result[2]
            argumentValue += increment
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount," iterations, Duration: ",duration," Accumulated 1: ",accumulated1," Accumulated 2: ",accumulated2)
    end
end


function RunVectorTest(outerIterationCount, testName ,func1, baseValue::Vector{Float64}, increment::Vector{Float64})
    for j = 1 : outerIterationCount
        argumentValue::Vector{Float64} = baseValue
        innerIterationCount = 1000000000
        accumulated::Vector{Float64} = zeros(length(baseValue))
        startTime = now()
        for i = 1 : innerIterationCount
            accumulated += func1(argumentValue);
            argumentValue += increment
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount,
                    " iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end



function OverheadTest(outerIterationCount = 1)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> x)
end

function RunAddDouble4ATest(outerIterationCount = 1)
    testName = stacktrace()[1].func
    baseValue::Vector{Float64} = ones(4);
    increment::Vector{Float64} = [0.000001, 0.000002, 0.000003, 0.000004]
    RunVectorTest(outerIterationCount, testName, x -> x, baseValue, increment)
end



function IsNaNTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> isnan(x))
end
function IsInfTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> isinf(x))
end

function AbsTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> abs(x))
end

function SignBitTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> signbit(x))
end

function FRExpTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTestReturningTwoValues(outerIterationCount, testName, x -> frexp(x))
end

function ModFTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTestReturningTwoValues(outerIterationCount, testName, x -> modf(x))
end

function MinTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> min(x,x))
end

function MaxTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> max(x,x))
end

function FloorTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> floor(x))
end

function CeilTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> ceil(x))
end

function TruncTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> trunc(x))
end

function RoundTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> round(x))
end

function ClampTest(outerIterationCount)
    testName = stacktrace()[1].func
    baseMin = pi/2
    baseValue = pi
    baseMax = 2*pi
    increment = 0.000001
    for j = 1 : outerIterationCount
        argumentValue::Float64 = baseValue
        argumentMin::Float64 = baseMin
        argumentMax::Float64 = baseMax
        innerIterationCount = 1000000000
        accumulated::Float64 = 0.0
        startTime = now()
        for i = 1 : innerIterationCount
            accumulated += clamp(argumentValue,argumentMin,argumentMax);
            argumentValue += increment
            argumentMin += increment
            argumentMax += increment
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount," iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end

function lerp(a,b,t)
    return a + ( t * ( b - a ) )
end

function LerpTest(outerIterationCount)
    testName = stacktrace()[1].func
    baseMin = pi/2
    baseMax = 2*pi
    baseValue = pi
    increment = 0.000001
    for j = 1 : outerIterationCount
        argumentMin::Float64 = baseMin
        argumentMax::Float64 = baseMax
        innerIterationCount = 1000000000
        accumulated::Float64 = 0.0
        startTime = now()
        for i = 1 : innerIterationCount
            accumulated += lerp(argumentMin,argumentMax,0.5);
            argumentMin += increment
            argumentMax += increment
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount," iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end

function CopySignTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> copysign(x,-1.0))
end

function scalbn(x::Float64, n)
	y::UInt64 = reinterpret(UInt64,x);
	if n > 1023 
		y *= 0x1p1023;
		n -= 1023;
		if n > 1023 
			y *= 0x1p1023;
			n -= 1023;
			if (n > 1023)
				n = 1023;
            end
        end
    elseif n < -1022 
		# make sure final n < -53 to avoid double
		#  rounding in the subnormal range 
		y *= 0x1p-1022 * 0x1p53;
		n += 1022 - 53;
		if (n < -1022) 
			y *= 0x1p-1022 * 0x1p53;
			n += 1022 - 53;
			if n < -1022
				n = -1022;
            end
		end
	end
	u = (0x3ff+n)<<52;
	x = y * reinterpret(Float64, u);
	return x;
end

function ScaleBNTest(outerIterationCount)
    ValueIterationCount::Int64 = 10_000_000;
    ExpIterationCount::Int32 = 100;
    innerIterationCount::Int64 = ValueIterationCount * ExpIterationCount;
    increment = 0.000001;
    baseValue = pi / 2.0;
    for k = 1 : outerIterationCount
        accumulated::Float64 = 0.0
        startTime = now()
        accumulated = 0.0;
        value = baseValue;
        for i= 1 : ValueIterationCount
            for j=1 :ExpIterationCount
                accumulated += scalbn(value,j);
            end 
            value += increment;
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println("ScaleBNTest: Executed ",innerIterationCount," iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end

function SinTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> sin(x),pi/100.0)
end
function ASinTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> asin(x),0.9/1000000000.0, 1.0/1000000000.0)
end

function CosTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> cos(x),pi/100.0)
end
function ACosTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> acos(x),0.9/1000000000.0, 1.0/1000000000.0)
end

function TanTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> tan(x),pi/100.0)
end
function ATanTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> atan(x),0.9/1000000000.0, 1.0/1000000000.0)
end

function ATan2Test(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> atan(x,x),0.9/1000000000.0, 1.0/1000000000.0)
end

function SqrtTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> sqrt(x))
end

function NextUpTest(outerIterationCount)
    testName = stacktrace()[1].func
    for j = 1 : outerIterationCount
        argumentValue::Float64 = 0.0
        innerIterationCount = 1000000000
        accumulated::Float64 = 0.0
        startTime = now()
        for i = 1 : innerIterationCount
            argumentValue = nextfloat(argumentValue);
            accumulated += argumentValue
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount," iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end

function NextDownTest(outerIterationCount)
    testName = stacktrace()[1].func
    for j = 1 : outerIterationCount
        argumentValue::Float64 = 0.0
        innerIterationCount = 1000000000
        accumulated::Float64 = 0.0
        startTime = now()
        for i = 1 : innerIterationCount
            argumentValue = prevfloat(argumentValue);
            accumulated += argumentValue
        end
        endTime = now()
        duration = (endTime - startTime).value/1000.0
        println(testName, ": Executed ",innerIterationCount," iterations, Duration: ",duration," Accumulated: ",accumulated)
    end
end

function FModTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTestWithTwoArguments(outerIterationCount, testName, (x,y) -> rem(x,y), pi, 0.000001, pi/4.0)
end
function ExpTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> exp(x), 0.9, 0.000000001)
end
function HypotTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> hypot(x,x), 0.999, 0.000000001)
end
function HypotTest2(outerIterationCount)
    testName = stacktrace()[1].func
    RunTestF(outerIterationCount, testName, x -> hypot(x,x), 0.999, 0.000000001)
end
function LogTest(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> log(x), 0.9, 0.000000001)
end
function Log2Test(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> log2(x), 0.9, 0.000000001)
end
function Log10Test(outerIterationCount)
    testName = stacktrace()[1].func
    RunTest(outerIterationCount, testName, x -> log10(x), 0.9, 0.000000001)
end



outerIterationCount = 1

OverheadTest(outerIterationCount)
IsNaNTest(outerIterationCount)
IsInfTest(outerIterationCount)
AbsTest(outerIterationCount)
SignBitTest(outerIterationCount)
FRExpTest(outerIterationCount)
ModFTest(outerIterationCount)
MinTest(outerIterationCount)
MaxTest(outerIterationCount)
FloorTest(outerIterationCount)
CeilTest(outerIterationCount)
TruncTest(outerIterationCount)
RoundTest(outerIterationCount)
ClampTest(outerIterationCount)
LerpTest(outerIterationCount)
CopySignTest(outerIterationCount)
ScaleBNTest(outerIterationCount)
SinTest(outerIterationCount)
ASinTest(outerIterationCount)
CosTest(outerIterationCount)
ACosTest(outerIterationCount)
TanTest(outerIterationCount)
ATanTest(outerIterationCount)
ATan2Test(outerIterationCount)
SqrtTest(outerIterationCount)
NextUpTest(outerIterationCount)
NextDownTest(outerIterationCount)

FModTest(outerIterationCount)
ExpTest(outerIterationCount)
HypotTest(outerIterationCount)

RunAddDouble4ATest(outerIterationCount)

HypotTest2(outerIterationCount)

LogTest(outerIterationCount)
Log2Test(outerIterationCount)
Log10Test(outerIterationCount)
