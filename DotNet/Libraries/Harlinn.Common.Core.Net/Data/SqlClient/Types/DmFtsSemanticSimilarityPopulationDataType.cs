/*
   Copyright 2024-2025 Espen Harlinn

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

public class DmFtsSemanticSimilarityPopulationDataType
{
    readonly int _databaseId = 0;
    readonly int _catalogId = 0;
    readonly int _tableId = 0;
    readonly long _documentCount = 0;
    readonly long _documentProcessedCount = 0;
    readonly int _completionType = 0;
    readonly string? _completionTypeDescription;
    readonly int _workerCount = 0;
    readonly int _status = 0;
    readonly string? _statusDescription;
    readonly DateTime _startTime;
    readonly byte[] _incrementalTimestamp = Array.Empty<byte>();

    public DmFtsSemanticSimilarityPopulationDataType( )
    {
    }

    public DmFtsSemanticSimilarityPopulationDataType(int databaseId,
        int catalogId,
        int tableId,
        long documentCount,
        long documentProcessedCount,
        int completionType,
        string? completionTypeDescription,
        int workerCount,
        int status,
        string? statusDescription,
        DateTime startTime,
        byte[] incrementalTimestamp)
    {
        _databaseId = databaseId;
        _catalogId = catalogId;
        _tableId = tableId;
        _documentCount = documentCount;
        _documentProcessedCount = documentProcessedCount;
        _completionType = completionType;
        _completionTypeDescription = completionTypeDescription;
        _workerCount = workerCount;
        _status = status;
        _statusDescription = statusDescription;
        _startTime = startTime;
        _incrementalTimestamp = incrementalTimestamp;
    }

    public int DatabaseId => _databaseId;
    public int CatalogId => _catalogId;
    public int TableId => _tableId;
    public long DocumentCount => _documentCount;
    public long DocumentProcessedCount => _documentProcessedCount;
    public int CompletionType => _completionType;
    public string? CompletionTypeDescription => _completionTypeDescription;
    public int WorkerCount => _workerCount;
    public int Status => _status;
    public string? StatusDescription => _statusDescription;
    public DateTime StartTime => _startTime;
    public byte[] IncrementalTimestamp => _incrementalTimestamp;
}
