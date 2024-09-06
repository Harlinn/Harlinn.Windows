using System;
using System.IO;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Common.Core.Net.Tests
{

    [TestClass]
    public class BinaryReadWriterExtensionsTest
    {
        [TestMethod]
        public void TestSizeMethod()
        {
            var expected = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteSize(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value = reader.ReadSize();
            Assert.AreEqual(expected, value);
        }

        [TestMethod]
        public void TestNullableBooleanMethod()
        {
            bool? expected1 = null;
            bool? expected2 = true;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableBoolean();
            var value2 = reader.ReadNullableBoolean();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableSByteMethod()
        {
            sbyte? expected1 = null;
            sbyte? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableSByte();
            var value2 = reader.ReadNullableSByte();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableByteMethod()
        {
            byte? expected1 = null;
            byte? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableByte();
            var value2 = reader.ReadNullableByte();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableInt16Method()
        {
            short? expected1 = null;
            short? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableInt16();
            var value2 = reader.ReadNullableInt16();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableUInt16Method()
        {
            ushort? expected1 = null;
            ushort? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableUInt16();
            var value2 = reader.ReadNullableUInt16();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableInt32Method()
        {
            int? expected1 = null;
            int? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableInt32();
            var value2 = reader.ReadNullableInt32();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableUInt32Method()
        {
            uint? expected1 = null;
            uint? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableUInt32();
            var value2 = reader.ReadNullableUInt32();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableInt64Method()
        {
            long? expected1 = null;
            long? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableInt64();
            var value2 = reader.ReadNullableInt64();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableUInt64Method()
        {
            ulong? expected1 = null;
            ulong? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableUInt64();
            var value2 = reader.ReadNullableUInt64();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        public enum TestEnum
        {
            First,
            Second,
            Third,
            Fourth
        }

        [TestMethod]
        public void TestNullableEnumMethod()
        {
            TestEnum? expected1 = null;
            TestEnum? expected2 = TestEnum.Second;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableEnum<TestEnum>();
            var value2 = reader.ReadNullableEnum<TestEnum>();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestEnumMethod()
        {
            TestEnum expected1 = TestEnum.First;
            TestEnum expected2 = TestEnum.Second;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadEnum<TestEnum>();
            var value2 = reader.ReadEnum<TestEnum>();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }


        [TestMethod]
        public void TestNullableSingleMethod()
        {
            float? expected1 = null;
            float? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableSingle();
            var value2 = reader.ReadNullableSingle();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableDoubleMethod()
        {
            double? expected1 = null;
            double? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableDouble();
            var value2 = reader.ReadNullableDouble();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableCurrencyMethod()
        {
            Currency? expected1 = null;
            Currency? expected2 = new Currency(1);
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableCurrency();
            var value2 = reader.ReadNullableCurrency();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestCurrencyMethod()
        {
            Currency expected1 = new Currency(-1);
            Currency expected2 = new Currency(1);
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadCurrency();
            var value2 = reader.ReadCurrency();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableDecimalMethod()
        {
            decimal? expected1 = null;
            decimal? expected2 = 1;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableDecimal();
            var value2 = reader.ReadNullableDecimal();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableDateTimeMethod()
        {
            DateTime? expected1 = null;
            DateTime? expected2 = DateTime.UtcNow;
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableDateTime();
            var value2 = reader.ReadNullableDateTime();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableTimeSpanMethod()
        {
            TimeSpan? expected1 = null;
            TimeSpan? expected2 = TimeSpan.FromSeconds(1);
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableTimeSpan();
            var value2 = reader.ReadNullableTimeSpan();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestNullableGuidMethod()
        {
            Guid? expected1 = null;
            Guid? expected2 = Guid.NewGuid();
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadNullableGuid();
            var value2 = reader.ReadNullableGuid();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestGuidMethod()
        {
            Guid expected1 = Guid.NewGuid();
            Guid expected2 = Guid.NewGuid();
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.Write(expected1);
            writer.Write(expected2);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var value1 = reader.ReadGuid();
            var value2 = reader.ReadGuid();
            Assert.AreEqual(expected1, value1);
            Assert.AreEqual(expected2, value2);
        }

        [TestMethod]
        public void TestBooleanArrayMethod()
        {
            var expected = new bool[] { true, false, true };
            
            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadBooleanArray();

            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestSByteArrayMethod()
        {
            var expected = new sbyte[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadSByteArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestByteArrayMethod()
        {
            var expected = new byte[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadByteArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestInt16ArrayMethod()
        {
            var expected = new short[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadInt16Array();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestUInt16ArrayMethod()
        {
            var expected = new ushort[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadUInt16Array();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestInt32ArrayMethod()
        {
            var expected = new int[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadInt32Array();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestUInt32ArrayMethod()
        {
            var expected = new uint[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadUInt32Array();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestInt64ArrayMethod()
        {
            var expected = new long[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadInt64Array();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestUInt64ArrayMethod()
        {
            var expected = new ulong[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadUInt64Array();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestSingleArrayMethod()
        {
            var expected = new float[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadSingleArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestDoubleArrayMethod()
        {
            var expected = new double[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadDoubleArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestDecimalArrayMethod()
        {
            var expected = new decimal[] { 2, 4, 6 };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadDecimalArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestCurrencyArrayMethod()
        {
            var expected = new Currency[] { new Currency(2), new Currency(4), new Currency(6) };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadCurrencyArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestDateTimeArrayMethod()
        {
            var expected = new DateTime[] { new DateTime(2,DateTimeKind.Utc), new DateTime(4, DateTimeKind.Utc), new DateTime(6, DateTimeKind.Utc) };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadDateTimeArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestTimeSpanArrayMethod()
        {
            var expected = new TimeSpan[] { new TimeSpan(2), new TimeSpan(4), new TimeSpan(6) };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadTimeSpanArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestGuidArrayMethod()
        {
            var expected = new Guid[] { Guid.NewGuid(), Guid.NewGuid(), Guid.NewGuid() };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadGuidArray();
            AssertEx.AreEqual(expected, values);
        }

        [TestMethod]
        public void TestStringArrayMethod()
        {
            var expected = new string[] { Guid.NewGuid().ToString(), Guid.NewGuid().ToString(), Guid.NewGuid().ToString() };

            var stream = new MemoryStream();
            var writer = new BinaryWriter(stream);
            writer.WriteArray(expected);
            writer.Flush();
            stream.Position = 0;
            var reader = new BinaryReader(stream);
            var values = reader.ReadStringArray();
            AssertEx.AreEqual(expected, values);
        }


    }
}