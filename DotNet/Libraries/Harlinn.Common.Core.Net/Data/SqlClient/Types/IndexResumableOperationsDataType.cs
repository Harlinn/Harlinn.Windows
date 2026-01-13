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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class IndexResumableOperationsDataType
{
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly string _name = string.Empty;
    readonly string? _sqlText;
    readonly short _lastMaxDopUsed = 0;
    readonly int? _partitionNumber;
    readonly byte _state = 0;
    readonly string? _stateDesc;
    readonly DateTime _startTime;
    readonly DateTime? _lastPauseTime;
    readonly int _totalExecutionTime = 0;
    readonly double _percentComplete = 0.0;
    readonly long _pageCount = 0;

    public IndexResumableOperationsDataType( )
    {
    }

    public IndexResumableOperationsDataType(int objectId,
        int indexId,
        string name,
        string? sqlText,
        short lastMaxDopUsed,
        int? partitionNumber,
        byte state,
        string? stateDesc,
        DateTime startTime,
        DateTime? lastPauseTime,
        int totalExecutionTime,
        double percentComplete,
        long pageCount)
    {
        _objectId = objectId;
        _indexId = indexId;
        _name = name;
        _sqlText = sqlText;
        _lastMaxDopUsed = lastMaxDopUsed;
        _partitionNumber = partitionNumber;
        _state = state;
        _stateDesc = stateDesc;
        _startTime = startTime;
        _lastPauseTime = lastPauseTime;
        _totalExecutionTime = totalExecutionTime;
        _percentComplete = percentComplete;
        _pageCount = pageCount;
    }

    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public string Name => _name;
    public string? SqlText => _sqlText;
    public short LastMaxDopUsed => _lastMaxDopUsed;
    public int? PartitionNumber => _partitionNumber;
    public byte State => _state;
    public string? StateDesc => _stateDesc;
    public DateTime StartTime => _startTime;
    public DateTime? LastPauseTime => _lastPauseTime;
    public int TotalExecutionTime => _totalExecutionTime;
    public double PercentComplete => _percentComplete;
    public long PageCount => _pageCount;
}
