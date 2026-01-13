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

public class DmFtsOutstandingBatchesDataType
{
    readonly int _databaseId = 0;
    readonly int _catalogId = 0;
    readonly int _tableId = 0;
    readonly int _batchId = 0;
    readonly byte[] _memoryAddress = Array.Empty<byte>();
    readonly byte[] _crawlMemoryAddress = Array.Empty<byte>();
    readonly byte[] _memregionMemoryAddress = Array.Empty<byte>();
    readonly int _hrBatch = 0;
    readonly bool _isRetryBatch = false;
    readonly int _retryHints = 0;
    readonly string? _retryHintsDescription;
    readonly long _docFailed = 0;
    readonly byte[] _batchTimestamp = Array.Empty<byte>();

    public DmFtsOutstandingBatchesDataType( )
    {
    }

    public DmFtsOutstandingBatchesDataType(int databaseId,
        int catalogId,
        int tableId,
        int batchId,
        byte[] memoryAddress,
        byte[] crawlMemoryAddress,
        byte[] memregionMemoryAddress,
        int hrBatch,
        bool isRetryBatch,
        int retryHints,
        string? retryHintsDescription,
        long docFailed,
        byte[] batchTimestamp)
    {
        _databaseId = databaseId;
        _catalogId = catalogId;
        _tableId = tableId;
        _batchId = batchId;
        _memoryAddress = memoryAddress;
        _crawlMemoryAddress = crawlMemoryAddress;
        _memregionMemoryAddress = memregionMemoryAddress;
        _hrBatch = hrBatch;
        _isRetryBatch = isRetryBatch;
        _retryHints = retryHints;
        _retryHintsDescription = retryHintsDescription;
        _docFailed = docFailed;
        _batchTimestamp = batchTimestamp;
    }

    public int DatabaseId => _databaseId;
    public int CatalogId => _catalogId;
    public int TableId => _tableId;
    public int BatchId => _batchId;
    public byte[] MemoryAddress => _memoryAddress;
    public byte[] CrawlMemoryAddress => _crawlMemoryAddress;
    public byte[] MemregionMemoryAddress => _memregionMemoryAddress;
    public int HrBatch => _hrBatch;
    public bool IsRetryBatch => _isRetryBatch;
    public int RetryHints => _retryHints;
    public string? RetryHintsDescription => _retryHintsDescription;
    public long DocFailed => _docFailed;
    public byte[] BatchTimestamp => _batchTimestamp;
}
