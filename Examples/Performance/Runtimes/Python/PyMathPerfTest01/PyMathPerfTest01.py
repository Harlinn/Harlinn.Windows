import datetime;
import math;
import inspect;

def RunTest( outerIterationCount, func1, base = math.pi, increment = 0.000001 ):
    for j in range(outerIterationCount):
        argumentValue = base
        innerIterationCount = 1000000000
        accumulated = 0.0
        
        startTime = datetime.datetime.now();
        for i in range(innerIterationCount):
            accumulated += func1(argumentValue);
            argumentValue += increment
        endTime = datetime.datetime.now();
        duration = endTime - startTime
        seconds = duration.seconds + duration.microseconds/1E6
        
        print(inspect.stack()[1][3], ": accumulated ", accumulated, " in ", seconds, " seconds")

def RunTest2( outerIterationCount, func1, base = math.pi, increment = 0.000001 ):
    for j in range(outerIterationCount):
        argumentValue = base
        innerIterationCount = 1000000000
        accumulated1 = 0.0
        accumulated2 = 0.0
        
        startTime = datetime.datetime.now();
        for i in range(innerIterationCount):
            result = func1(argumentValue);
            accumulated1 += result[0];
            accumulated2 += result[1];
            argumentValue += increment
        endTime = datetime.datetime.now();
        duration = endTime - startTime
        seconds = duration.seconds + duration.microseconds/1E6
        
        print(inspect.stack()[1][3], ": accumulated 1:", accumulated1,": accumulated 2:", accumulated2, " in ", seconds, "seconds")



def OverheadTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:x)

def IsNaNTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.isnan(x))

def IsInfTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.isinf(x))

def AbsTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:abs(x))

def FRExpTest(outerIterationCount):
    RunTest2(outerIterationCount, lambda x:math.frexp(x))

def ModFTest(outerIterationCount):
    RunTest2(outerIterationCount, lambda x:math.modf(x))

def MinTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:min(x,x))

def MaxTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:max(x,x))

def CeilTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.ceil(x))

def FloorTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.floor(x))

def TruncTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.trunc(x))

def RoundTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:round(x))

def clamp(num, min_value, max_value):
   return max(min(num, max_value), min_value)

def ClampTest( outerIterationCount, base = math.pi, increment = 0.000001 ):
    for j in range(outerIterationCount):
        baseMin = math.pi/2
        baseMax = 2 * math.pi
        argumentMin = baseMin
        argumentMax = baseMax
        argumentValue = base
        innerIterationCount = 1000000000
        accumulated = 0.0
        
        startTime = datetime.datetime.now();
        for i in range(innerIterationCount):
            accumulated += clamp(argumentValue,argumentMin,argumentMax);
            argumentValue += increment
            argumentMin += increment
            argumentMax += increment
        endTime = datetime.datetime.now();
        duration = endTime - startTime
        seconds = duration.seconds + duration.microseconds/1E6
        
        print(inspect.stack()[0][3], ": accumulated ", accumulated, " in ", seconds, " seconds")

def lerp(a,b,t):
    return a + ( t * ( b - a ) )


def LerpTest( outerIterationCount, increment = 0.000001 ):
    for j in range(outerIterationCount):
        baseMin = math.pi/2
        baseMax = 2 * math.pi
        argumentMin = baseMin
        argumentMax = baseMax
        innerIterationCount = 1000000000
        accumulated = 0.0
        
        startTime = datetime.datetime.now();
        for i in range(innerIterationCount):
            accumulated += lerp(argumentMin,argumentMax,0.5);
            argumentMin += increment
            argumentMax += increment
        endTime = datetime.datetime.now();
        duration = endTime - startTime
        seconds = duration.seconds + duration.microseconds/1E6
        
        print(inspect.stack()[0][3], ": accumulated ", accumulated, " in ", seconds, " seconds")


def CopySignTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.copysign(x,-1.0))

def SinTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.sin(x),math.pi/100)

def ASinTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.asin(x),0.9/1000000000.0, 1.0/1000000000.0)

def CosTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.cos(x),math.pi/100)

def ACosTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.acos(x),0.9/1000000000.0, 1.0/1000000000.0)

def TanTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.tan(x),math.pi/100)

def ATanTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.atan(x),0.9/1000000000.0, 1.0/1000000000.0)

def ATan2Test(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.atan2(x,x),0.9/1000000000.0, 1.0/1000000000.0)

def SqrtTest(outerIterationCount):
    RunTest(outerIterationCount, lambda x:math.sqrt(x))


outerIterationCount = 1
OverheadTest(outerIterationCount)
IsNaNTest(outerIterationCount)
IsInfTest(outerIterationCount)
AbsTest(outerIterationCount)
FRExpTest(outerIterationCount)
ModFTest(outerIterationCount)
MinTest(outerIterationCount)
MaxTest(outerIterationCount)
CeilTest(outerIterationCount)
FloorTest(outerIterationCount)
TruncTest(outerIterationCount)
RoundTest(outerIterationCount)
ClampTest(outerIterationCount)
LerpTest(outerIterationCount)
CopySignTest(outerIterationCount)
SinTest(outerIterationCount)
CosTest(outerIterationCount)
TanTest(outerIterationCount)
SqrtTest(outerIterationCount)
ASinTest(outerIterationCount)
ACosTest(outerIterationCount)
ATanTest(outerIterationCount)
ATan2Test(outerIterationCount)

