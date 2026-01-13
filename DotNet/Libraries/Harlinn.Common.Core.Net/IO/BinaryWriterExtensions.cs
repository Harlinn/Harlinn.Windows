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
using System.Diagnostics.CodeAnalysis;
using System.Numerics;

namespace Harlinn.Common.Core.Net.IO
{
    /// <summary>
    /// Useful extensions to the BinaryWriter class.
    /// </summary>
    public static class BinaryWriterExtensions
    {
        public static BinaryWriter WriteSize([DisallowNull] this BinaryWriter self, int value)
        {
            self.Write(value);
            return self;
        }

        public static void Write([DisallowNull] this BinaryWriter self, bool? value)
        {
            self.Write(value.HasValue);
            if (value is bool v)
            {
                self.Write(v);
            }
        }
        public static void Write([DisallowNull] this BinaryWriter self, sbyte? value)
        {
            self.Write(value.HasValue);
            if (value is sbyte v)
            {
                self.Write(v);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, byte? value)
        {
            self.Write(value.HasValue);
            if (value is byte v)
            {
                self.Write(v);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, short? value)
        {
            self.Write(value.HasValue);
            if (value is short v)
            {
                self.Write(v);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, ushort? value)
        {
            self.Write(value.HasValue);
            if (value is ushort v)
            {
                self.Write(v);
            }
        }
        public static void Write([DisallowNull] this BinaryWriter self, int? value)
        {
            self.Write(value.HasValue);
            if (value is int v)
            {
                self.Write(v);
            }
        }
        public static void Write([DisallowNull] this BinaryWriter self, uint? value)
        {
            self.Write(value.HasValue);
            if (value is uint v)
            {
                self.Write(v);
            }
        }
        public static void Write([DisallowNull] this BinaryWriter self, long? value)
        {
            self.Write(value.HasValue);
            if (value is long v)
            {
                self.Write(v);
            }
        }
        public static void Write([DisallowNull] this BinaryWriter self, ulong? value)
        {
            self.Write(value.HasValue);
            if (value is ulong v)
            {
                self.Write(v);
            }
        }

        public static void Write<T>([DisallowNull] this BinaryWriter self, T value) where T : struct, Enum
        {
            var enumType = typeof(T);
            var enumIntegerType = Enum.GetUnderlyingType(enumType);
            if (enumIntegerType == typeof(int))
            {
                self.Write(Convert.ToInt32(value));
            }
            else if (enumIntegerType == typeof(uint))
            {
                self.Write(Convert.ToUInt32(value));
            }
            else if (enumIntegerType == typeof(sbyte))
            {
                self.Write(Convert.ToSByte(value));
            }
            else if (enumIntegerType == typeof(byte))
            {
                self.Write(Convert.ToByte(value));
            }
            else if (enumIntegerType == typeof(short))
            {
                self.Write(Convert.ToInt16(value));
            }
            else if (enumIntegerType == typeof(ushort))
            {
                self.Write(Convert.ToUInt16(value));
            }
            else if (enumIntegerType == typeof(long))
            {
                self.Write(Convert.ToInt64(value));
            }
            else if (enumIntegerType == typeof(ulong))
            {
                self.Write(Convert.ToUInt64(value));
            }
        }

        public static void Write<T>([DisallowNull] this BinaryWriter self, T? value) where T : struct, Enum
        {
            self.Write(value.HasValue);
            if (value is T v)
            {
                self.Write(v);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, float? value)
        {
            self.Write(value.HasValue);
            if (value is float v)
            {
                self.Write(v);
            }
        }
        public static void Write([DisallowNull] this BinaryWriter self, double? value)
        {
            self.Write(value.HasValue);
            if (value is double v)
            {
                self.Write(v);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, Currency value)
        {
            self.Write(value.ToScaled());
        }

        public static void Write([DisallowNull] this BinaryWriter self, Currency? value)
        {
            self.Write(value.HasValue);
            if (value is Currency v)
            {
                self.Write(v);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, decimal? value)
        {
            self.Write(value.HasValue);
            if (value is decimal v)
            {
                self.Write(v);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, DateTime value)
        {
            if(value.Kind != DateTimeKind.Utc)
            {
                var utcValue = value.ToUniversalTime();
                self.Write(utcValue.Ticks);
            }
            else
            {
                self.Write(value.Ticks);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, DateTime? value)
        {
            self.Write(value.HasValue);
            if (value is DateTime v)
            {
                self.Write(v);
            }
        }

        public static void Write([DisallowNull] this BinaryWriter self, TimeSpan value)
        {
            self.Write(value.Ticks);
        }
        public static void Write([DisallowNull] this BinaryWriter self, TimeSpan? value)
        {
            self.Write(value.HasValue);
            if (value is TimeSpan v)
            {
                self.Write(v);
            }
        }
        public static void Write([DisallowNull] this BinaryWriter self, Guid value)
        {
            self.Write(value.ToByteArray());
        }
        public static void Write([DisallowNull] this BinaryWriter self, Guid? value)
        {
            self.Write(value.HasValue);
            if (value is Guid v)
            {
                self.Write(v);
            }
        }


        public static void WriteArray([DisallowNull] this BinaryWriter self, bool[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for(int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, sbyte[]? value) 
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, byte[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if(size > 0)
            {
                self.Write(value);
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, short[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, ushort[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, int[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, uint[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, long[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, ulong[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray<T>([DisallowNull] this BinaryWriter self, T[]? value) where T : struct, System.Enum
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write<T>(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, float[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, double[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, decimal[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, Currency[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, DateTime[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, TimeSpan[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, Guid[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

        public static void WriteArray([DisallowNull] this BinaryWriter self, string[]? value)
        {
            var size = value != null ? value.Length : 0;
            self.WriteSize(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    self.Write(value[i]);
                }
            }
        }

    }
}
