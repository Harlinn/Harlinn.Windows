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

public class InternalPartitionsDataType
{
    readonly long _partitionId = 0;
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly int _partitionNumber = 0;
    readonly long _hobtId = 0;
    readonly byte? _internalObjectType;
    readonly string? _internalObjectTypeDesc;
    readonly int? _rowGroupId;
    readonly long? _rows;
    readonly byte? _dataCompression;
    readonly string? _dataCompressionDesc;

    public InternalPartitionsDataType( )
    {
    }

    public InternalPartitionsDataType(long partitionId,
        int objectId,
        int indexId,
        int partitionNumber,
        long hobtId,
        byte? internalObjectType,
        string? internalObjectTypeDesc,
        int? rowGroupId,
        long? rows,
        byte? dataCompression,
        string? dataCompressionDesc)
    {
        _partitionId = partitionId;
        _objectId = objectId;
        _indexId = indexId;
        _partitionNumber = partitionNumber;
        _hobtId = hobtId;
        _internalObjectType = internalObjectType;
        _internalObjectTypeDesc = internalObjectTypeDesc;
        _rowGroupId = rowGroupId;
        _rows = rows;
        _dataCompression = dataCompression;
        _dataCompressionDesc = dataCompressionDesc;
    }

    public long PartitionId => _partitionId;
    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public int PartitionNumber => _partitionNumber;
    public long HobtId => _hobtId;
    public byte? InternalObjectType => _internalObjectType;
    public string? InternalObjectTypeDesc => _internalObjectTypeDesc;
    public int? RowGroupId => _rowGroupId;
    public long? Rows => _rows;
    public byte? DataCompression => _dataCompression;
    public string? DataCompressionDesc => _dataCompressionDesc;
}
