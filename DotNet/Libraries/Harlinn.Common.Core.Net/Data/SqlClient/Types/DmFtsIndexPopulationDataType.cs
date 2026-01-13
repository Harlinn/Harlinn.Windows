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

public class DmFtsIndexPopulationDataType
{
    readonly int _databaseId = 0;
    readonly int _catalogId = 0;
    readonly int _tableId = 0;
    readonly byte[] _memoryAddress = Array.Empty<byte>();
    readonly int _populationType = 0;
    readonly string? _populationTypeDescription;
    readonly bool _isClusteredIndexScan = false;
    readonly int _rangeCount = 0;
    readonly int _completedRangeCount = 0;
    readonly int _outstandingBatchCount = 0;
    readonly int _status = 0;
    readonly string? _statusDescription;
    readonly int _completionType = 0;
    readonly string? _completionTypeDescription;
    readonly int _workerCount = 0;
    readonly int _queuedPopulationType = 0;
    readonly string? _queuedPopulationTypeDescription;
    readonly DateTime _startTime;
    readonly byte[] _incrementalTimestamp = Array.Empty<byte>();

    public DmFtsIndexPopulationDataType( )
    {
    }

    public DmFtsIndexPopulationDataType(int databaseId,
        int catalogId,
        int tableId,
        byte[] memoryAddress,
        int populationType,
        string? populationTypeDescription,
        bool isClusteredIndexScan,
        int rangeCount,
        int completedRangeCount,
        int outstandingBatchCount,
        int status,
        string? statusDescription,
        int completionType,
        string? completionTypeDescription,
        int workerCount,
        int queuedPopulationType,
        string? queuedPopulationTypeDescription,
        DateTime startTime,
        byte[] incrementalTimestamp)
    {
        _databaseId = databaseId;
        _catalogId = catalogId;
        _tableId = tableId;
        _memoryAddress = memoryAddress;
        _populationType = populationType;
        _populationTypeDescription = populationTypeDescription;
        _isClusteredIndexScan = isClusteredIndexScan;
        _rangeCount = rangeCount;
        _completedRangeCount = completedRangeCount;
        _outstandingBatchCount = outstandingBatchCount;
        _status = status;
        _statusDescription = statusDescription;
        _completionType = completionType;
        _completionTypeDescription = completionTypeDescription;
        _workerCount = workerCount;
        _queuedPopulationType = queuedPopulationType;
        _queuedPopulationTypeDescription = queuedPopulationTypeDescription;
        _startTime = startTime;
        _incrementalTimestamp = incrementalTimestamp;
    }

    public int DatabaseId => _databaseId;
    public int CatalogId => _catalogId;
    public int TableId => _tableId;
    public byte[] MemoryAddress => _memoryAddress;
    public int PopulationType => _populationType;
    public string? PopulationTypeDescription => _populationTypeDescription;
    public bool IsClusteredIndexScan => _isClusteredIndexScan;
    public int RangeCount => _rangeCount;
    public int CompletedRangeCount => _completedRangeCount;
    public int OutstandingBatchCount => _outstandingBatchCount;
    public int Status => _status;
    public string? StatusDescription => _statusDescription;
    public int CompletionType => _completionType;
    public string? CompletionTypeDescription => _completionTypeDescription;
    public int WorkerCount => _workerCount;
    public int QueuedPopulationType => _queuedPopulationType;
    public string? QueuedPopulationTypeDescription => _queuedPopulationTypeDescription;
    public DateTime StartTime => _startTime;
    public byte[] IncrementalTimestamp => _incrementalTimestamp;
}
