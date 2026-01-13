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
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Common.Core.Net.Data
{
    public enum DeleteTimeseriesRangeType : byte
    {
        Unknown = 0,
        Clear,
        From,
        Until,
        Over
    };

    [DataContract]
    public class DeleteTimeseriesRangeData<TKind> where TKind : struct, Enum
    {
        [DataMember(EmitDefaultValue = false)]
        readonly DeleteTimeseriesRangeType _rangeType;
        [DataMember(EmitDefaultValue = false)]
        Guid _timeseriesId;
        [DataMember(EmitDefaultValue = false)]
        TKind _timeseriesType = default;

        protected DeleteTimeseriesRangeData(DeleteTimeseriesRangeType rangeType)
        {
            _rangeType = rangeType;
        }
        public DeleteTimeseriesRangeData(DeleteTimeseriesRangeType rangeType, Guid id, TKind timeseriesType)
        {
            _rangeType = rangeType;
            _timeseriesId = id;
            _timeseriesType = timeseriesType;
        }


        public DeleteTimeseriesRangeType RangeType => _rangeType;

        public Guid TimeseriesId { get => _timeseriesId; set => _timeseriesId = value; }
        public TKind TimeseriesType { get => _timeseriesType; set => _timeseriesType = value; }

        public virtual void WriteTo(BinaryWriter writer)
        {
            writer.Write((byte)_rangeType);
            writer.Write(_timeseriesId);
            writer.Write(_timeseriesType);
        }

        public static DeleteTimeseriesRangeType ReadRangeType(BinaryReader reader)
        {
            var result = (DeleteTimeseriesRangeType)reader.ReadByte();
            return result;
        }

        public virtual void ReadFrom(BinaryReader reader)
        {
            _timeseriesId = reader.ReadGuid();
            _timeseriesType = reader.ReadEnum<TKind>();
        }
    }

    [DataContract]
    public class DeleteClearTimeseriesRangeData<TKind> : DeleteTimeseriesRangeData<TKind> where TKind : struct, Enum
    {

        public DeleteClearTimeseriesRangeData()
            : base(DeleteTimeseriesRangeType.Clear)
        { }
        public DeleteClearTimeseriesRangeData(Guid id, TKind timeseriesType)
            : base(DeleteTimeseriesRangeType.Clear, id, timeseriesType)
        {
        }

    }

    [DataContract]
    public class DeleteFromTimeseriesRangeData<TKind> : DeleteTimeseriesRangeData<TKind> where TKind : struct, Enum
    {
        [DataMember(EmitDefaultValue = false)]
        DateTime _from;

        public DeleteFromTimeseriesRangeData()
            : base(DeleteTimeseriesRangeType.Clear)
        { }
        public DeleteFromTimeseriesRangeData(Guid id, TKind timeseriesType)
            : base(DeleteTimeseriesRangeType.From, id, timeseriesType)
        {
        }

        public DeleteFromTimeseriesRangeData(Guid id, TKind timeseriesType, DateTime from)
            : base(DeleteTimeseriesRangeType.From, id, timeseriesType)
        {
            _from = from;
        }

        public DateTime From { get => _from; set => _from = value; }

        public override void WriteTo(BinaryWriter writer)
        {
            base.WriteTo(writer);
            writer.Write(_from);
        }
        public override void ReadFrom(BinaryReader reader)
        {
            base.ReadFrom(reader);
            _from = reader.ReadDateTime();
        }

    }

    public class DeleteUntilTimeseriesRangeData<TKind> : DeleteTimeseriesRangeData<TKind> where TKind : struct, Enum
    {
        [DataMember(EmitDefaultValue = false)]
        DateTime _until;

        public DeleteUntilTimeseriesRangeData()
            : base(DeleteTimeseriesRangeType.Until)
        { }
        public DeleteUntilTimeseriesRangeData(Guid id, TKind timeseriesType)
            : base(DeleteTimeseriesRangeType.Until, id, timeseriesType)
        {
        }

        public DeleteUntilTimeseriesRangeData(Guid id, TKind timeseriesType, DateTime until)
            : base(DeleteTimeseriesRangeType.Until, id, timeseriesType)
        {
            _until = until;
        }

        public DateTime Until { get => _until; set => _until = value; }

        public override void WriteTo(BinaryWriter writer)
        {
            base.WriteTo(writer);
            writer.Write(_until);
        }
        public override void ReadFrom(BinaryReader reader)
        {
            base.ReadFrom(reader);
            _until = reader.ReadDateTime();
        }

    }

    [DataContract]
    public class DeleteOverTimeseriesRangeData<TKind> : DeleteTimeseriesRangeData<TKind> where TKind : struct, Enum
    {
        [DataMember(EmitDefaultValue = false)]
        DateTime _start;
        [DataMember(EmitDefaultValue = false)]
        DateTime _end;

        public DeleteOverTimeseriesRangeData()
            : base(DeleteTimeseriesRangeType.Over)
        { }
        public DeleteOverTimeseriesRangeData(Guid id, TKind timeseriesType, DateTime start, DateTime end)
            : base(DeleteTimeseriesRangeType.Over, id, timeseriesType)
        {
            _start = start;
            _end = end;
        }

        public DateTime Start { get => _start; set => _start = value; }
        public DateTime End { get => _end; set => _end = value; }

        public override void WriteTo(BinaryWriter writer)
        {
            base.WriteTo(writer);
            writer.Write(_start);
            writer.Write(_end);
        }
        public override void ReadFrom(BinaryReader reader)
        {
            base.ReadFrom(reader);
            _start = reader.ReadDateTime();
            _end = reader.ReadDateTime();
        }
    }

    public class DeleteTimeseriesRangeFactory<TKind> where TKind : struct, Enum
    {
        public static DeleteTimeseriesRangeData<TKind> Create(DeleteTimeseriesRangeType rangeType)
        {
            DeleteTimeseriesRangeData<TKind> result = null;
            switch (rangeType)
            {
                case DeleteTimeseriesRangeType.Clear:
                {
                    result = new DeleteClearTimeseriesRangeData<TKind>();
                }
                break;
                case DeleteTimeseriesRangeType.From:
                {
                    result = new DeleteFromTimeseriesRangeData<TKind>();
                }
                break;
                case DeleteTimeseriesRangeType.Until:
                {
                    result = new DeleteUntilTimeseriesRangeData<TKind>();
                }
                break;
                case DeleteTimeseriesRangeType.Over:
                {
                    result = new DeleteOverTimeseriesRangeData<TKind>();
                }
                break;
            }
            return result;
        }

        public static DeleteTimeseriesRangeData<TKind> ReadFrom(BinaryReader reader)
        {
            var rangeType = DeleteTimeseriesRangeData<TKind>.ReadRangeType(reader);
            var result = Create(rangeType);
            result.ReadFrom(reader);
            return result;
        }

    }




}
