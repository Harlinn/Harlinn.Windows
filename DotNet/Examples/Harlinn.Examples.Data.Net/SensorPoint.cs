using System;
using System.IO;
using System.Collections.Generic;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Examples.Data.Net
{
    public struct SensorPoint : IReadWrite
    {
        DateTime _timestamp;
        long _flags;
        double _value;

        public SensorPoint(DateTime timestamp, double value)
        {
            _timestamp = timestamp;
            _flags = 0;
            _value = value;
        }

        public SensorPoint(DateTime timestamp, long flags, double value)
        {
            _timestamp = timestamp;
            _flags = flags;
            _value = value;
        }

        public DateTime Timestamp { get => _timestamp; set => _timestamp = value; }
        public long Flags { get => _flags; set => _flags = value; }
        public double Value { get => _value; set => _value = value; }

        public void Read(BinaryReader reader)
        {
            _timestamp = reader.ReadDateTime();
            _flags = reader.ReadInt64();
            _value = reader.ReadDouble();
        }

        public void Write(BinaryWriter writer)
        {
            writer.Write(_timestamp);
            writer.Write(_flags);
            writer.Write(_value);
        }
    }


}
