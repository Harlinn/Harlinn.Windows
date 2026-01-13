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
using System;
using System.Diagnostics;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Common.Core.Net.Tests
{
    [TestClass]
    public class CurrencyTest
    {
        [TestMethod]
        public void TestCtorMethod1()
        {
            Currency currency = default;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 0);
        }


        [TestMethod]
        public void TestCtorMethod2()
        {
            Currency currency = new Currency(Convert.ToInt64(1));

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 10000);
        }

        [TestMethod]
        public void TestCtorMethod3()
        {
            Currency currency = new Currency(Convert.ToSingle(1));

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 10000);
        }

        [TestMethod]
        public void TestCtorMethod5()
        {
            Currency currency = new Currency(Convert.ToDouble(1));

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 10000);
        }
        [TestMethod]
        public void TestCtorMethod6()
        {
            Currency currency = new Currency(Convert.ToDecimal(1));

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 10000);
        }


        [TestMethod]
        public void TestAddMethod1()
        {
            Currency currency = new Currency(1) + new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestAddMethod2()
        {
            Currency currency = 1 + new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestAddMethod3()
        {
            Currency currency = new Currency(1) + 1;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestAddMethod4()
        {
            Currency currency = 1.0f + new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestAddMethod5()
        {
            Currency currency = new Currency(1) + 1.0f;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestAddMethod6()
        {
            Currency currency = 1.0 + new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestAddMethod7()
        {
            Currency currency = new Currency(1) + 1.0;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestAddMethod8()
        {
            Currency currency = 1.0m + new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestAddMethod9()
        {
            Currency currency = new Currency(1) + 1.0m;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }


        [TestMethod]
        public void TestSubMethod1()
        {
            Currency currency = new Currency(3) - new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod2()
        {
            Currency currency = 3 - new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod3()
        {
            Currency currency = new Currency(3) - 1;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod4()
        {
            Currency currency = 3.0f - new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod5()
        {
            Currency currency = new Currency(3) - 1.0f;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod6()
        {
            Currency currency = 3.0 - new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod7()
        {
            Currency currency = new Currency(3) - 1.0;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod8()
        {
            Currency currency = 3.0 - new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod9()
        {
            Currency currency = new Currency(3) - 1.0;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod10()
        {
            Currency currency = 3.0m - new Currency(1);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestSubMethod11()
        {
            Currency currency = new Currency(3) - 1.0m;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestMultiplyMethod1()
        {
            Currency currency = 2 * new Currency(2);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 40000);
        }

        [TestMethod]
        public void TestMultiplyMethod2()
        {
            Currency currency = new Currency(2) * 2;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 40000);
        }

        [TestMethod]
        public void TestMultiplyMethod3()
        {
            Currency currency = 2.0f * new Currency(2);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 40000);
        }

        [TestMethod]
        public void TestMultiplyMethod4()
        {
            Currency currency = new Currency(2) * 2.0f;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 40000);
        }

        [TestMethod]
        public void TestMultiplyMethod5()
        {
            Currency currency = 2.0 * new Currency(2);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 40000);
        }

        [TestMethod]
        public void TestMultiplyMethod6()
        {
            Currency currency = new Currency(2) * 2.0;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 40000);
        }

        [TestMethod]
        public void TestMultiplyMethod7()
        {
            Currency currency = 2.0m * new Currency(2);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 40000);
        }

        [TestMethod]
        public void TestMultiplyMethod8()
        {
            Currency currency = new Currency(2) * 2.0m;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 40000);
        }

        [TestMethod]
        public void TestDivisionMethod1()
        {
            Currency currency = 4 / new Currency(2);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestDivisionMethod2()
        {
            Currency currency = new Currency(4) / 2;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestDivisionMethod3()
        {
            Currency currency = 4.0f / new Currency(2);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestDivisionMethod4()
        {
            Currency currency = new Currency(4) / 2.0f;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestDivisionMethod5()
        {
            Currency currency = 4.0 / new Currency(2);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestDivisionMethod6()
        {
            Currency currency = new Currency(4) / 2.0;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestDivisionMethod7()
        {
            Currency currency = 4.0m / new Currency(2);

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }

        [TestMethod]
        public void TestDivisionMethod8()
        {
            Currency currency = new Currency(4) / 2.0m;

            var scaled = currency.ToScaled();

            Assert.AreEqual(scaled, 20000);
        }


        [TestMethod]
        public void TestPerformanceMethod1()
        {
            
            decimal decimalValue = 1m;
            decimal decimalFactor = 1.001m;
            Stopwatch stopwatch1 = Stopwatch.StartNew();
            for ( int i = 0; i < 1000000; i++)
            {
                decimalValue += 2m;
                decimalValue -= 1m;
            }
            stopwatch1.Stop();

            var totalSeconds1 = stopwatch1.Elapsed.TotalSeconds;

            Currency currencyValue = new Currency(1);
            Stopwatch stopwatch2 = Stopwatch.StartNew();
            for (int i = 0; i < 1000000; i++)
            {
                currencyValue += 2;
                currencyValue -= 1;
            }
            stopwatch2.Stop();
            var totalSeconds2 = stopwatch2.Elapsed.TotalSeconds;

            Assert.IsTrue(totalSeconds1 > totalSeconds2);
        }


    }
}