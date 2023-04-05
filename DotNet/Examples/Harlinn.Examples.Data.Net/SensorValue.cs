using System;
using Harlinn.Common.Net.IO;

namespace Harlinn.Examples.Data.Net
{
    public struct SensorValue : Common.Net.IReadWrite
    {
        Guid _sensor;
        DateTime _timestamp;
        long _flags;
        double _value;

        public SensorValue(Guid sensor, DateTime timestamp, double value)
        {
            _sensor = sensor;
            _timestamp = timestamp;
            _flags = 0;
            _value = value;
        }

        public SensorValue(Guid sensor, DateTime timestamp, long flags, double value)
        {
            _sensor = sensor;
            _timestamp = timestamp;
            _flags = flags;
            _value = value;
        }

        public Guid Sensor { get => _sensor; set => _sensor = value; }
        public DateTime Timestamp { get => _timestamp; set => _timestamp = value; }
        public long Flags { get => _flags; set => _flags = value; }
        public double Value { get => _value; set => _value = value; }

        public void Read(BinaryReader reader)
        {
            _sensor = reader.ReadGuid();
            _timestamp = reader.ReadDateTime();
            _flags = reader.ReadInt64();
            _value = reader.ReadDouble();
        }

        public void Write(BinaryWriter writer)
        {
            writer.Write(_sensor);
            writer.Write(_timestamp);
            writer.Write(_flags);
            writer.Write(_value);
        }
    }

}
