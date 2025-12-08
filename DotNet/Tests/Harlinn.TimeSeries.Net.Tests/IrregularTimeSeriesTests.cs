/*
   Copyright 2024-2025 Espen Harlinn

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

namespace Harlinn.TimeSeries.Net.Tests
{
    [TestClass]
    public sealed class IrregularTimeSeriesTests
    {
        [TestMethod]
        public void ConstructorTest()
        {
            var timeSeries = new IrregularTimeSeries();
            Assert.AreEqual(0, timeSeries.Count);

            timeSeries = new IrregularTimeSeries(new Value[] { new Value(DateTime.Now, 1.0) });
            Assert.AreEqual(1, timeSeries.Count);
        }

        [TestMethod]
        public void AppendTest()
        {
            int count = 1_000_000;
            var timeSeries = new IrregularTimeSeries(count);
            var values = Common.Generate(DateTime.Now, TimeSpan.FromMinutes(1), count);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }
            for (int i = 0; i < count; i++)
            {
                Assert.AreEqual(values[i], timeSeries[i]);
            }
        }

        [TestMethod]
        public void ShuffledAddTest()
        {
            int count = 10_000;
            //int count = 1_000_000;
            var timeSeries = new IrregularTimeSeries(count);
            var values = Common.Generate(DateTime.Now, TimeSpan.FromMinutes(1), count);
            var shuffledValues = (Value[])values.Clone();
            Common.Shuffle(shuffledValues);

            foreach (var value in shuffledValues)
            {
                timeSeries.Add(value);
            }
            for (int i = 0; i < count; i++)
            {
                Assert.AreEqual(values[i], timeSeries[i]);
            }
        }

        [TestMethod]
        public void GetByTimeTest()
        {
            int count = 1_000_000;
            var timeSeries = new IrregularTimeSeries(count);
            var values = Common.Generate(DateTime.Now, TimeSpan.FromMinutes(1), count);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }
            for (int i = 0; i < count; i++)
            {
                var current = timeSeries[i];
                var byTime = timeSeries[current.Time];
                Assert.AreEqual(current, byTime);
            }
        }

        [TestMethod]
        public void GetInterpolatedByTimeTest()
        {
            int count = 1_000_000;
            var timeSeries = new IrregularTimeSeries(count);
            var values = Common.Generate(DateTime.Now, TimeSpan.FromMinutes(1), count);
            var halfMin = TimeSpan.FromMinutes(0.5);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }

            for (int i = 0; i < count - 1; i++)
            {
                var current = timeSeries[i];
                var next = timeSeries[i + 1];
                var expected = (current.Data + next.Data)/ 2.0;
                var byTime = timeSeries[current.Time + halfMin];
                Assert.AreEqual(expected, byTime.Data, 0.001);
            }
        }

        [TestMethod]
        public void ForeachTest()
        {
            int count = 1_000_000;
            var timeSeries = new IrregularTimeSeries(count);
            var values = Common.Generate(DateTime.Now, TimeSpan.FromMinutes(1), count);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }

            int ii = 0;
            foreach (var current in timeSeries)
            {
                var byIndex = timeSeries[ii];
                Assert.AreEqual(current, byIndex);
                ii++;
            }
        }

        public class KC : System.Collections.ObjectModel.KeyedCollection<DateTime, Value>
        {
            public KC()
            {
            }

            protected override DateTime GetKeyForItem(Value item)
            {
                return item.Time;
            }
        }

        [TestMethod]
        public void ForeachListTest()
        {
            int count = 1_000_000;
            var timeSeries = new KC();
            var values = Common.Generate(DateTime.Now, TimeSpan.FromMinutes(1), count);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }

            int ii = 0;
            foreach (var current in timeSeries)
            {
                var byIndex = timeSeries[ii];
                Assert.AreEqual(current, byIndex);
                ii++;
            }
        }


        [TestMethod]
        public void RangeTest()
        {    
            int count = 10_000;
            DateTime startTime = DateTime.Now;
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries(count);
            var values = Common.Generate(startTime, TimeSpan.FromMinutes(1), count);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }

            var range0 = timeSeries.ToRange(new Interval(startTime - ( 3 * halfMin), startTime));
            var rangeCount0 = range0.Count;
            Assert.AreEqual(0, rangeCount0);

            var range1 = timeSeries.ToRange(new Interval(startTime - halfMin, startTime + halfMin));
            var rangeCount1 = range1.Count;
            Assert.AreEqual(1, rangeCount1);

            var rangeLast = timeSeries.ToRange(new Interval(startTime + TimeSpan.FromMinutes(count), startTime + TimeSpan.FromMinutes(count) + halfMin));
            var rangeCountLast = rangeLast.Count;
            Assert.AreEqual(1, rangeCountLast);
            Assert.AreEqual(count, rangeLast.End);

            var rangeAfterLast = timeSeries.ToRange(new Interval(startTime + TimeSpan.FromMinutes(count), startTime + TimeSpan.FromMinutes(count) + halfMin));
            var rangeCountAfterLast = rangeAfterLast.Count;
            Assert.AreEqual(1, rangeCountAfterLast);
            Assert.AreEqual(count - 1, rangeAfterLast.Start);
            Assert.AreEqual(count, rangeAfterLast.End);
        }


        [TestMethod]
        public void RangeTest2()
        {
            int count = 10_000;
            DateTime startTime = DateTime.Now;
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries(count);
            var values = Common.Generate(startTime, TimeSpan.FromMinutes(1), count);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }


            var rangeLast = timeSeries.ToRange(new Interval(startTime + TimeSpan.FromMinutes(count), startTime + TimeSpan.FromMinutes(count) + halfMin));
            var rangeCountLast = rangeLast.Count;
            Assert.AreEqual(1, rangeCountLast);
            Assert.AreEqual(count, rangeLast.End);
        }

        [TestMethod]
        public void FindStartIndexTest1()
        {
            int count = 3;
            DateTime startTime = DateTime.Now;
            TimeSpan minute = TimeSpan.FromMinutes(1);
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries();
            var values = Common.Generate(startTime, minute, count);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }

            var lastTime = startTime + TimeSpan.FromMinutes(count - 1);
            var lastIndex = timeSeries.FindStartIndex(lastTime);

            Assert.AreEqual(2, lastIndex);
        }

        [TestMethod]
        public void FindStartIndexTest2()
        {
            int count = 3;
            DateTime startTime = DateTime.Now;
            TimeSpan minute = TimeSpan.FromMinutes(1);
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries();
            var values = Common.Generate(startTime, minute, count);

            for (int i = 0; i < count; i++)
            {
                timeSeries.Add(values[i]);
            }

            var afterLastTime = startTime + TimeSpan.FromMinutes(count - 1) + new TimeSpan(1L);
            var lastIndex = timeSeries.FindStartIndex(afterLastTime);

            Assert.AreEqual(2, lastIndex);
        }

        [TestMethod]
        public void GetValuesTest1()
        {
            int numberOfGeneratedValues = 3;
            DateTime startTime = DateTime.Now;
            TimeSpan minute = TimeSpan.FromMinutes(1);
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries();
            var values = Common.Generate(startTime, minute, numberOfGeneratedValues);
            timeSeries.Add(values);

            var intervalStart = startTime + halfMin;
            var intervalEnd = intervalStart + minute;
            var interval = new Interval(intervalStart, intervalEnd);
            var retrievedValues = timeSeries.GetValues(interval);

            Assert.HasCount(3, retrievedValues);
            Assert.AreEqual(0.5, retrievedValues[0].Data);
            Assert.AreEqual(intervalStart, retrievedValues[0].Time);
            Assert.AreEqual(1.0, retrievedValues[1].Data);
            Assert.AreEqual(intervalStart + halfMin, retrievedValues[1].Time);
            Assert.AreEqual(1.5, retrievedValues[2].Data);
            Assert.AreEqual(intervalEnd, retrievedValues[2].Time);
        }

        [TestMethod]
        public void GetValuesTest2()
        {
            int numberOfGeneratedValues = 3;
            DateTime startTime = DateTime.Now;
            TimeSpan minute = TimeSpan.FromMinutes(1);
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries();
            var values = Common.Generate(startTime, minute, numberOfGeneratedValues);
            timeSeries.Add(values);

            var intervalStart = startTime - halfMin;
            var intervalEnd = intervalStart + minute;
            var interval = new Interval(intervalStart, intervalEnd);
            var retrievedValues = timeSeries.GetValues(interval);

            Assert.HasCount(2, retrievedValues);
            Assert.AreEqual(0.0, retrievedValues[0].Data);
            Assert.AreEqual(startTime, retrievedValues[0].Time);
            Assert.AreEqual(0.5, retrievedValues[1].Data);
            Assert.AreEqual(intervalEnd, retrievedValues[1].Time);
        }


        [TestMethod]
        public void GetValuesTest3()
        {
            int numberOfGeneratedValues = 3;
            DateTime startTime = DateTime.Now;
            TimeSpan minute = TimeSpan.FromMinutes(1);
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries();
            var values = Common.Generate(startTime, minute, numberOfGeneratedValues);
            timeSeries.Add(values);

            var intervalStart = startTime - halfMin;
            var intervalEnd = intervalStart + (3 * minute);
            var interval = new Interval(intervalStart, intervalEnd);
            var retrievedValues = timeSeries.GetValues(interval);

            Assert.HasCount(3, retrievedValues);
            Assert.AreEqual(0.0, retrievedValues[0].Data);
            Assert.AreEqual(startTime, retrievedValues[0].Time);
            Assert.AreEqual(1.0, retrievedValues[1].Data);
            Assert.AreEqual(startTime + minute, retrievedValues[1].Time);
            Assert.AreEqual(2.0, retrievedValues[2].Data);
            Assert.AreEqual(startTime + (2 * minute), retrievedValues[2].Time);
        }

        [TestMethod]
        public void GetValuesTest4()
        {
            int numberOfGeneratedValues = 3;
            DateTime startTime = DateTime.Now;
            TimeSpan minute = TimeSpan.FromMinutes(1);
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries();
            var values = Common.Generate(startTime, minute, numberOfGeneratedValues);
            timeSeries.Add(values);

            var intervalStart = values[values.Length - 1].Time;
            var intervalEnd = intervalStart + halfMin;
            var interval = new Interval(intervalStart, intervalEnd);
            var retrievedValues = timeSeries.GetValues(interval);

            Assert.HasCount(1, retrievedValues);
            Assert.AreEqual(2.0, retrievedValues[0].Data);
            Assert.AreEqual(intervalStart, retrievedValues[0].Time);
        }

        [TestMethod]
        public void GetValuesTest5()
        {
            int numberOfGeneratedValues = 5;
            DateTime startTime = DateTime.Now;
            TimeSpan minute = TimeSpan.FromMinutes(1);
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries();
            var values = Common.Generate(startTime, minute, numberOfGeneratedValues);
            timeSeries.Add(values);

            var intervalStart = startTime + halfMin;
            var intervalEnd = values[values.Length - 1].Time - halfMin;
            var interval = new Interval(intervalStart, intervalEnd);
            var retrievedValues = timeSeries.GetValues(interval);

            Assert.HasCount(5, retrievedValues);
            Assert.AreEqual(0.5, retrievedValues[0].Data);
            Assert.AreEqual(intervalStart, retrievedValues[0].Time);
            Assert.AreEqual(1.0, retrievedValues[1].Data);
            Assert.AreEqual(startTime + minute, retrievedValues[1].Time);
            Assert.AreEqual(2.0, retrievedValues[2].Data);
            Assert.AreEqual(startTime + (2 * minute), retrievedValues[2].Time);
            Assert.AreEqual(3.0, retrievedValues[3].Data);
            Assert.AreEqual(startTime + (3 * minute), retrievedValues[3].Time);
            Assert.AreEqual(3.5, retrievedValues[4].Data);
            Assert.AreEqual(intervalEnd, retrievedValues[4].Time);
        }

        [TestMethod]
        public void GetValuesTest6()
        {
            int numberOfGeneratedValues = 3;
            DateTime startTime = DateTime.Now;
            TimeSpan minute = TimeSpan.FromMinutes(1);
            TimeSpan halfMin = TimeSpan.FromMinutes(0.5);
            var timeSeries = new IrregularTimeSeries(true);
            var values = Common.Generate(startTime, minute, numberOfGeneratedValues);
            timeSeries.Add(values);

            var intervalStart = startTime + halfMin;
            var intervalEnd = intervalStart + minute;
            var interval = new Interval(intervalStart, intervalEnd);
            var retrievedValues = timeSeries.GetValues(interval);

            Assert.HasCount(2, retrievedValues);
            Assert.AreEqual(0.0, retrievedValues[0].Data);
            Assert.AreEqual(intervalStart, retrievedValues[0].Time);
            Assert.AreEqual(1.0, retrievedValues[1].Data);
            Assert.AreEqual(startTime + minute, retrievedValues[1].Time);
        }



    }

}
