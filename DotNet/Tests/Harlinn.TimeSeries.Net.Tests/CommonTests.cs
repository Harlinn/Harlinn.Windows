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

using static Harlinn.TimeSeries.Net.Common;

namespace Harlinn.TimeSeries.Net.Tests
{
    [TestClass]
    public sealed class CommonTests
    {
        [TestMethod]
        public void CalculateCapacityTest()
        {
            
            int deltaCapacity = 5;
            int requestedSize0 = 0;
            int requestedSize1 = 1;
            int requestedSize2 = 2;
            int requestedSize5 = 5;
            int requestedSize6 = 6;
            int requestedSize9 = 9;
            int requestedSize10 = 10;
            int requestedSize11 = 11;



            int result0 = CalculateCapacity(requestedSize0, deltaCapacity);
            int result1 = CalculateCapacity(requestedSize1, deltaCapacity);
            int result2 = CalculateCapacity(requestedSize2, deltaCapacity);
            int result5 = CalculateCapacity(requestedSize5, deltaCapacity);
            int result6 = CalculateCapacity(requestedSize6, deltaCapacity);
            int result9 = CalculateCapacity(requestedSize9, deltaCapacity);
            int result10 = CalculateCapacity(requestedSize10, deltaCapacity);
            int result11 = CalculateCapacity(requestedSize11, deltaCapacity);

            Assert.AreEqual(0, result0);
            Assert.AreEqual(5, result1);
            Assert.AreEqual(5, result2);
            Assert.AreEqual(5, result5);
            Assert.AreEqual(10, result6);
            Assert.AreEqual(10, result9);
            Assert.AreEqual(10, result10);
            Assert.AreEqual(15, result11);
        }
    }

}
