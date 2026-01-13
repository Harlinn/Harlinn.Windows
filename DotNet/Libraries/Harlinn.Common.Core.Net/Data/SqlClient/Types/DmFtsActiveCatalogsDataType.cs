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

public class DmFtsActiveCatalogsDataType
{
    readonly int _databaseId = 0;
    readonly int _catalogId = 0;
    readonly byte[] _memoryAddress = Array.Empty<byte>();
    readonly string _name = string.Empty;
    readonly bool _isPaused = false;
    readonly int _status = 0;
    readonly string? _statusDescription;
    readonly int _previousStatus = 0;
    readonly string? _previousStatusDescription;
    readonly int _workerCount = 0;
    readonly int _activeFtsIndexCount = 0;
    readonly int _autoPopulationCount = 0;
    readonly int _manualPopulationCount = 0;
    readonly int _fullIncrementalPopulationCount = 0;
    readonly int _rowCountInThousands = 0;
    readonly bool _isImporting = false;

    public DmFtsActiveCatalogsDataType( )
    {
    }

    public DmFtsActiveCatalogsDataType(int databaseId,
        int catalogId,
        byte[] memoryAddress,
        string name,
        bool isPaused,
        int status,
        string? statusDescription,
        int previousStatus,
        string? previousStatusDescription,
        int workerCount,
        int activeFtsIndexCount,
        int autoPopulationCount,
        int manualPopulationCount,
        int fullIncrementalPopulationCount,
        int rowCountInThousands,
        bool isImporting)
    {
        _databaseId = databaseId;
        _catalogId = catalogId;
        _memoryAddress = memoryAddress;
        _name = name;
        _isPaused = isPaused;
        _status = status;
        _statusDescription = statusDescription;
        _previousStatus = previousStatus;
        _previousStatusDescription = previousStatusDescription;
        _workerCount = workerCount;
        _activeFtsIndexCount = activeFtsIndexCount;
        _autoPopulationCount = autoPopulationCount;
        _manualPopulationCount = manualPopulationCount;
        _fullIncrementalPopulationCount = fullIncrementalPopulationCount;
        _rowCountInThousands = rowCountInThousands;
        _isImporting = isImporting;
    }

    public int DatabaseId => _databaseId;
    public int CatalogId => _catalogId;
    public byte[] MemoryAddress => _memoryAddress;
    public string Name => _name;
    public bool IsPaused => _isPaused;
    public int Status => _status;
    public string? StatusDescription => _statusDescription;
    public int PreviousStatus => _previousStatus;
    public string? PreviousStatusDescription => _previousStatusDescription;
    public int WorkerCount => _workerCount;
    public int ActiveFtsIndexCount => _activeFtsIndexCount;
    public int AutoPopulationCount => _autoPopulationCount;
    public int ManualPopulationCount => _manualPopulationCount;
    public int FullIncrementalPopulationCount => _fullIncrementalPopulationCount;
    public int RowCountInThousands => _rowCountInThousands;
    public bool IsImporting => _isImporting;
}
