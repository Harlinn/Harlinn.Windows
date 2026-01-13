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
using System.Globalization;
using System.Runtime.Serialization;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Common.Core.Net.Data
{


    public class UpdateData<TKind> where TKind : struct, Enum
    {
        Guid _sessionId;
        DateTime _timestamp;
        long _sequenceNumber;
        IList<BaseDataGuid<TKind>> _inserted;
        IList<BaseDataGuid<TKind>> _updated;
        IList<BaseDataGuid<TKind>> _deleted;
        IList<DeleteTimeseriesRangeData<TKind>> _timeseriesDeleted;
        IBaseDataFactory<TKind> _factory;

        public UpdateData(IBaseDataFactory<TKind> factory)
        {
            _inserted = new List<BaseDataGuid<TKind>>();
            _updated = new List<BaseDataGuid<TKind>>();
            _deleted = new List<BaseDataGuid<TKind>>();
            _timeseriesDeleted = new List<DeleteTimeseriesRangeData<TKind>>();
            _factory = factory;
        }

        public UpdateData(IBaseDataFactory<TKind> factory, Guid sessionId, DateTime timestamp, long sequenceNumber, IList<BaseDataGuid<TKind>> inserted, IList<BaseDataGuid<TKind>> updated, IList<BaseDataGuid<TKind>> deleted, IList<DeleteTimeseriesRangeData<TKind>> timeseriesDeleted = null)
        {
            _sessionId = sessionId;
            _timestamp = timestamp;
            _sequenceNumber = sequenceNumber;
            _inserted = inserted ?? new List<BaseDataGuid<TKind>>();
            _updated = updated ?? new List<BaseDataGuid<TKind>>();
            _deleted = deleted ?? new List<BaseDataGuid<TKind>>();
            _timeseriesDeleted = timeseriesDeleted ?? new List<DeleteTimeseriesRangeData<TKind>>();
            _factory = factory;
        }


        public Guid SessionId
        {
            get { return _sessionId; }
            set { _sessionId = value; }
        }

        public DateTime Timestamp { get => _timestamp; set => _timestamp = value; }

        public long SequenceNumber { get => _sequenceNumber; set => _sequenceNumber = value; }
        public IList<BaseDataGuid<TKind>> Inserted { get => _inserted; set => _inserted = value ?? new List<BaseDataGuid<TKind>>(); }
        public IList<BaseDataGuid<TKind>> Updated { get => _updated; set => _updated = value ?? new List<BaseDataGuid<TKind>>(); }

        public IList<BaseDataGuid<TKind>> Deleted { get => _deleted; set => _deleted = value ?? new List<BaseDataGuid<TKind>>(); }

        public IList<DeleteTimeseriesRangeData<TKind>> TimeseriesDeleted { get => _timeseriesDeleted; set => _timeseriesDeleted = value ?? new List<DeleteTimeseriesRangeData<TKind>>(); }

        public void WriteTo(BinaryWriter writer)
        {
            writer.Write(_sessionId);
            writer.Write(_timestamp);
            writer.Write(_sequenceNumber);
            int count = _inserted.Count;
            writer.WriteSize(count);
            for (int i = 0; i < count; i++)
            {
                _inserted[i].WriteTo(writer);
            }
            count = _updated.Count;
            writer.WriteSize(count);
            for (int i = 0; i < count; i++)
            {
                _updated[i].WriteTo(writer);
            }
            count = _deleted.Count;
            writer.WriteSize(count);
            for (int i = 0; i < count; i++)
            {
                _deleted[i].WriteTo(writer);
            }

            count = _timeseriesDeleted.Count;
            writer.WriteSize(count);
            for (int i = 0; i < count; i++)
            {
                _timeseriesDeleted[i].WriteTo(writer);
            }
        }
        public void ReadFrom(BinaryReader source )
        {
            _sessionId = source.ReadGuid();
            _timestamp = source.ReadDateTime();
            _sequenceNumber = source.ReadInt64();
            
            _inserted = _factory.ReadListFrom(source);
            _updated = _factory.ReadListFrom(source);
            _deleted = _factory.ReadListFrom(source);

            var count = source.ReadSize();
            _timeseriesDeleted = new List<DeleteTimeseriesRangeData<TKind>>(count);
            for (int i = 0; i < count; i++)
            {
                var data = DeleteTimeseriesRangeFactory<TKind>.ReadFrom(source);
                _timeseriesDeleted.Add(data);
            }
        }




    }
}
