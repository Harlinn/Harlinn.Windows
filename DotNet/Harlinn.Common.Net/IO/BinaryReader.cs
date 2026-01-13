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
﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Common.Net.IO
{
    public class BinaryReader : System.IO.BinaryReader
    {
        public BinaryReader(Stream input) 
            : base(input)
        {
        }

        public BinaryReader(Stream input, Encoding encoding) 
            : base(input, encoding)
        {
        }

        public BinaryReader(Stream input, Encoding encoding, bool leaveOpen) 
            : base(input, encoding, leaveOpen)
        {
        }

        public System.DateTime ReadDateTime()
        {
            var tmp = ReadInt64();
            var result = new DateTime(tmp, DateTimeKind.Utc);
            return result;
        }

        public System.TimeSpan ReadTimeSpan()
        {
            var tmp = ReadInt64();
            var result = new TimeSpan(tmp);
            return result;
        }


        public System.Guid ReadGuid()
        {
            var bytes = base.ReadBytes(16);
            var result = new System.Guid(bytes);
            return result;
        }


        public int ReadSize()
        {
            var result = this.ReadInt32();
            return result;
        }

        public bool[] ReadBooleanArray()
        {
            var size = ReadSize();
            bool[] result = new bool[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadBoolean();
                }
            }
            return result;
        }

        public List<bool> ReadBooleanList()
        {
            var size = ReadSize();
            List<bool> result = new List<bool>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadBoolean());
                }
            }
            return result;
        }

        public sbyte[] ReadSByteArray()
        {
            var size = ReadSize();
            var result = new sbyte[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadSByte();
                }
            }
            return result;
        }

        public List<sbyte> ReadSByteList()
        {
            var size = ReadSize();
            var result = new List<sbyte>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadSByte());
                }
            }
            return result;
        }

        public byte[] ReadByteArray()
        {
            var size = ReadSize();
            var result = new byte[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadByte();
                }
            }
            return result;
        }

        public List<byte> ReadByteList()
        {
            var size = ReadSize();
            var result = new List<byte>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadByte());
                }
            }
            return result;
        }

        public short[] ReadInt16Array()
        {
            var size = ReadSize();
            var result = new short[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadInt16();
                }
            }
            return result;
        }

        public List<short> ReadInt16List()
        {
            var size = ReadSize();
            var result = new List<short>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadInt16());
                }
            }
            return result;
        }

        public ushort[] ReadUInt16Array()
        {
            var size = ReadSize();
            var result = new ushort[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadUInt16();
                }
            }
            return result;
        }

        public List<ushort> ReadUInt16List()
        {
            var size = ReadSize();
            var result = new List<ushort>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadUInt16());
                }
            }
            return result;
        }

        public int[] ReadInt32Array()
        {
            var size = ReadSize();
            var result = new int[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadInt32();
                }
            }
            return result;
        }

        public List<int> ReadInt32List()
        {
            var size = ReadSize();
            var result = new List<int>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadInt32());
                }
            }
            return result;
        }

        public uint[] ReadUInt32Array()
        {
            var size = ReadSize();
            var result = new uint[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadUInt32();
                }
            }
            return result;
        }

        public List<uint> ReadUInt32List()
        {
            var size = ReadSize();
            var result = new List<uint>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadUInt32());
                }
            }
            return result;
        }

        public long[] ReadInt64Array()
        {
            var size = ReadSize();
            var result = new long[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadInt64();
                }
            }
            return result;
        }

        public List<long> ReadInt64List()
        {
            var size = ReadSize();
            var result = new List<long>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadInt64());
                }
            }
            return result;
        }

        public ulong[] ReadUInt64Array()
        {
            var size = ReadSize();
            var result = new ulong[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadUInt64();
                }
            }
            return result;
        }

        public List<ulong> ReadUInt64List()
        {
            var size = ReadSize();
            var result = new List<ulong>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadUInt64());
                }
            }
            return result;
        }


        public float[] ReadSingleArray()
        {
            var size = ReadSize();
            var result = new float[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadSingle();
                }
            }
            return result;
        }

        public List<float> ReadSingleList()
        {
            var size = ReadSize();
            var result = new List<float>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadSingle());
                }
            }
            return result;
        }

        public double[] ReadDoubleArray()
        {
            var size = ReadSize();
            var result = new double[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = ReadDouble();
                }
            }
            return result;
        }

        public List<double> ReadDoubleList()
        {
            var size = ReadSize();
            var result = new List<double>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadDouble());
                }
            }
            return result;
        }

        public DateTime[] ReadDateTimeArray()
        {
            var size = ReadSize();
            var result = new DateTime[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = this.ReadDateTime();
                }
            }
            return result;
        }

        public List<DateTime> ReadDateTimeList()
        {
            var size = ReadSize();
            var result = new List<DateTime>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadDateTime());
                }
            }
            return result;
        }


        public TimeSpan[] ReadTimeSpanArray()
        {
            var size = ReadSize();
            var result = new TimeSpan[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = this.ReadTimeSpan();
                }
            }
            return result;
        }

        public List<TimeSpan> ReadTimeSpanList()
        {
            var size = ReadSize();
            var result = new List<TimeSpan>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadTimeSpan());
                }
            }
            return result;
        }

        public string[] ReadStringArray()
        {
            var size = ReadSize();
            var result = new string[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = this.ReadString();
                }
            }
            return result;
        }

        public List<string> ReadStringList()
        {
            var size = ReadSize();
            var result = new List<string>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadString());
                }
            }
            return result;
        }

        public Guid[] ReadGuidArray()
        {
            var size = ReadSize();
            var result = new Guid[size];
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result[i] = this.ReadGuid();
                }
            }
            return result;
        }

        public List<Guid> ReadGuidList()
        {
            var size = ReadSize();
            var result = new List<Guid>(size);
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    result.Add(ReadGuid());
                }
            }
            return result;
        }
    }
}
