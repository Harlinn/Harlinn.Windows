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
using System.IO;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Examples.Data.Net
{
    public struct SensorValue : IReadWrite
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
