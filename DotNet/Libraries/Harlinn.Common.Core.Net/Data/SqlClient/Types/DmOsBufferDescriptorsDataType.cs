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

public class DmOsBufferDescriptorsDataType
{
    readonly int? _databaseId;
    readonly int? _fileId;
    readonly int? _pageId;
    readonly int? _pageLevel;
    readonly long? _allocationUnitId;
    readonly string? _pageType;
    readonly int? _rowCount;
    readonly int? _freeSpaceInBytes;
    readonly bool? _isModified;
    readonly int? _numaNode;
    readonly long? _readMicrosec;
    readonly bool? _isInBpoolExtension;
    readonly int? _errorCode;
    readonly byte[]? _opHistory;

    public DmOsBufferDescriptorsDataType( )
    {
    }

    public DmOsBufferDescriptorsDataType(int? databaseId,
        int? fileId,
        int? pageId,
        int? pageLevel,
        long? allocationUnitId,
        string? pageType,
        int? rowCount,
        int? freeSpaceInBytes,
        bool? isModified,
        int? numaNode,
        long? readMicrosec,
        bool? isInBpoolExtension,
        int? errorCode,
        byte[]? opHistory)
    {
        _databaseId = databaseId;
        _fileId = fileId;
        _pageId = pageId;
        _pageLevel = pageLevel;
        _allocationUnitId = allocationUnitId;
        _pageType = pageType;
        _rowCount = rowCount;
        _freeSpaceInBytes = freeSpaceInBytes;
        _isModified = isModified;
        _numaNode = numaNode;
        _readMicrosec = readMicrosec;
        _isInBpoolExtension = isInBpoolExtension;
        _errorCode = errorCode;
        _opHistory = opHistory;
    }

    public int? DatabaseId => _databaseId;
    public int? FileId => _fileId;
    public int? PageId => _pageId;
    public int? PageLevel => _pageLevel;
    public long? AllocationUnitId => _allocationUnitId;
    public string? PageType => _pageType;
    public int? RowCount => _rowCount;
    public int? FreeSpaceInBytes => _freeSpaceInBytes;
    public bool? IsModified => _isModified;
    public int? NumaNode => _numaNode;
    public long? ReadMicrosec => _readMicrosec;
    public bool? IsInBpoolExtension => _isInBpoolExtension;
    public int? ErrorCode => _errorCode;
    public byte[]? OpHistory => _opHistory;
}
