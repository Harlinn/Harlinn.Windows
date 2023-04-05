using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Harlinn.Common.Net.IO
{
    public class BinaryWriter : System.IO.BinaryWriter
    {
        protected BinaryWriter()
        {
        }
        public BinaryWriter(Stream output) 
            : base(output)
        {
        }

        public BinaryWriter(Stream output, Encoding encoding) 
            : base(output, encoding)
        {
        }

        public BinaryWriter(Stream output, Encoding encoding, bool leaveOpen) 
            : base(output, encoding, leaveOpen)
        {
        }

        public void Write(System.DateTime value)
        {
            if (value.Kind != DateTimeKind.Utc)
            {
                long ticks = value.ToUniversalTime().Ticks;
                Write(ticks);
            }
            else
            {
                long ticks = value.Ticks;
                Write(ticks);
            }
        }

        public void Write(System.TimeSpan value)
        {
            long ticks = value.Ticks;
            Write(ticks);
        }


        public void Write(System.Guid guid)
        {
            byte[] bytes = guid.ToByteArray();
            base.Write(bytes, 0, 16);
        }

        public void WriteArray(ICollection<bool> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                byte b = (byte)(value ? 1 : 0);
                base.Write(b);
            }
        }

        public void WriteArray(bool[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                byte b = (byte)(values[i] ? 1 : 0);
                base.Write(b);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<sbyte> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(sbyte[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }


        public void WriteArray(System.Collections.Generic.ICollection<byte> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(byte[] values)
        {
            int size = values.Length;
            base.Write(size);
            base.Write(values);
        }

        public void WriteArray(System.Collections.Generic.ICollection<short> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(short[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<ushort> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(ushort[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<int> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(int[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<uint> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(uint[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<long> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(long[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<ulong> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(ulong[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<float> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(float[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<double> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(double[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<DateTime> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                long v = value.ToUniversalTime().Ticks;
                base.Write(v);
            }
        }

        public void WriteArray(DateTime[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<TimeSpan> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                long v = value.Ticks;
                base.Write(v);
            }
        }

        public void WriteArray(TimeSpan[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                Write(values[i]);
            }
        }

        public void WriteArray(System.Collections.Generic.ICollection<string> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                base.Write(value);
            }
        }

        public void WriteArray(string[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                base.Write(values[i]);
            }
        }


        public void WriteArray(System.Collections.Generic.ICollection<Guid> values)
        {
            int size = values.Count;
            base.Write(size);
            foreach (var value in values)
            {
                Write(value);
            }
        }

        public void WriteArray(Guid[] values)
        {
            int size = values.Length;
            base.Write(size);
            for (int i = 0; i < size; ++i)
            {
                Write(values[i]);
            }
        }

    }
}
