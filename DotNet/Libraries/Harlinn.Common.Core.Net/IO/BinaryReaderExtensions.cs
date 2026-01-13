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
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.IO;

namespace Harlinn.Common.Core.Net.IO
{
    /// <summary>
    /// Useful extensions to the BinaryReader class.
    /// </summary>
    public static class BinaryReaderExtensions
    {
        public static int ReadSize( [DisallowNull] this BinaryReader self )
        {
            return self.ReadInt32();
        }

        public static bool? ReadNullableBoolean([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadBoolean();
            }
            return default;
        }
        public static sbyte? ReadNullableSByte([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadSByte();
            }
            return default;
        }
        public static byte? ReadNullableByte([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadByte();
            }
            return default;
        }

        public static short? ReadNullableInt16([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadInt16();
            }
            return default;
        }

        public static ushort? ReadNullableUInt16([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadUInt16();
            }
            return default;
        }

        public static int? ReadNullableInt32([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadInt32();
            }
            return default;
        }
        public static uint? ReadNullableUInt32([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadUInt32();
            }
            return default;
        }

        public static long? ReadNullableInt64([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadInt64();
            }
            return default;
        }

        public static ulong? ReadNullableUInt64([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadUInt64();
            }
            return default;
        }

        

        public static T ReadEnum<T>([DisallowNull] this BinaryReader self) where T : struct, System.Enum
        {
            var enumType = typeof(T);
            var enumIntegerType = Enum.GetUnderlyingType(enumType);
            if (enumIntegerType == typeof(int))
            {
                var value = self.ReadInt32();
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(uint))
            {
                var value = self.ReadUInt32();
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(sbyte))
            {
                var value = self.ReadSByte();
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(byte))
            {
                var value = self.ReadByte();
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(short))
            {
                var value = self.ReadInt16();
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(ushort))
            {
                var value = self.ReadUInt16();
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(long))
            {
                var value = self.ReadInt64();
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(ulong))
            {
                var value = self.ReadUInt64();
                return (T)Enum.ToObject(typeof(T), value);
            }
            return default;
        }

        public static T? ReadNullableEnum<T>([DisallowNull] this BinaryReader self) where T : struct, System.Enum
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadEnum<T>();
            }
            return default;
        }


        public static float? ReadNullableSingle([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadSingle();
            }
            return default;
        }

        public static double? ReadNullableDouble([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadDouble();
            }
            return default;
        }

        public static decimal? ReadNullableDecimal([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return self.ReadDecimal();
            }
            return default;
        }

        public static Currency ReadCurrency([DisallowNull] this BinaryReader self)
        {
            return Currency.FromScaled(self.ReadInt64());
        }

        public static Currency? ReadNullableCurrency([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return Currency.FromScaled(self.ReadInt64());
            }
            return default;
        }

        public static DateTime ReadDateTime([DisallowNull] this BinaryReader self)
        {
            return new DateTime(self.ReadInt64(), DateTimeKind.Utc);
        }

        public static DateTime? ReadNullableDateTime([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return new DateTime(self.ReadInt64(),DateTimeKind.Utc);
            }
            return default;
        }

        public static TimeSpan ReadTimeSpan([DisallowNull] this BinaryReader self)
        {
            return new TimeSpan(self.ReadInt64());
        }

        public static TimeSpan? ReadNullableTimeSpan([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return new TimeSpan(self.ReadInt64());
            }
            return default;
        }

        public static Guid ReadGuid([DisallowNull] this BinaryReader self)
        {
            return new Guid( self.ReadBytes(16) );
        }

        public static Guid? ReadNullableGuid([DisallowNull] this BinaryReader self)
        {
            var hasValue = self.ReadBoolean();
            if (hasValue)
            {
                return new Guid(self.ReadBytes(16));
            }
            return default;
        }

        public static bool[] ReadBooleanArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new bool[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadBoolean( );
                }
                return result;
            }
            return Array.Empty<bool>();
        }

        public static sbyte[] ReadSByteArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new sbyte[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadSByte();
                }
                return result;
            }
            return Array.Empty<sbyte>();
        }

        public static byte[] ReadByteArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                return self.ReadBytes(size);
            }
            return Array.Empty<byte>();
        }

        public static short[] ReadInt16Array([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new short[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadInt16();
                }
                return result;
            }
            return Array.Empty<short>();
        }

        public static ushort[] ReadUInt16Array([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new ushort[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadUInt16();
                }
                return result;
            }
            return Array.Empty<ushort>();
        }

        public static int[] ReadInt32Array([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new int[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadInt32();
                }
                return result;
            }
            return Array.Empty<int>();
        }

        public static uint[] ReadUInt32Array([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new uint[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadUInt32();
                }
                return result;
            }
            return Array.Empty<uint>();
        }

        public static long[] ReadInt64Array([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new long[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadInt64();
                }
                return result;
            }
            return Array.Empty<long>();
        }

        public static ulong[] ReadUInt64Array([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new ulong[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadUInt64();
                }
                return result;
            }
            return Array.Empty<ulong>();
        }

        public static T[] ReadEnumArray<T>([DisallowNull] this BinaryReader self) where T : struct, System.Enum
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new T[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadEnum<T>();
                }
                return result;
            }
            return Array.Empty<T>();
        }

        public static float[] ReadSingleArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new float[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadSingle();
                }
                return result;
            }
            return Array.Empty<float>();
        }

        public static double[] ReadDoubleArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new double[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadDouble();
                }
                return result;
            }
            return Array.Empty<double>();
        }

        public static decimal[] ReadDecimalArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new decimal[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadDecimal();
                }
                return result;
            }
            return Array.Empty<decimal>();
        }

        public static Currency[] ReadCurrencyArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new Currency[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadCurrency();
                }
                return result;
            }
            return Array.Empty<Currency>();
        }

        public static DateTime[] ReadDateTimeArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new DateTime[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadDateTime();
                }
                return result;
            }
            return Array.Empty<DateTime>();
        }

        public static TimeSpan[] ReadTimeSpanArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new TimeSpan[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadTimeSpan();
                }
                return result;
            }
            return Array.Empty<TimeSpan>();
        }

        public static Guid[] ReadGuidArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new Guid[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadGuid();
                }
                return result;
            }
            return Array.Empty<Guid>();
        }

        public static string[] ReadStringArray([DisallowNull] this BinaryReader self)
        {
            var size = self.ReadSize();
            if (size > 0)
            {
                var result = new string[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = self.ReadString();
                }
                return result;
            }
            return Array.Empty<string>();
        }


    }
}
