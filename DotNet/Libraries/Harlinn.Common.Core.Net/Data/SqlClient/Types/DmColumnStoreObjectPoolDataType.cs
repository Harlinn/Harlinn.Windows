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

public class DmColumnStoreObjectPoolDataType
{
    readonly int _databaseId = 0;
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly int _partitionNumber = 0;
    readonly int? _columnId;
    readonly int _rowGroupId = 0;
    readonly int _objectType = 0;
    readonly string _objectTypeDesc = string.Empty;
    readonly long _accessCount = 0;
    readonly long _memoryUsedInBytes = 0;
    readonly DateTime _objectLoadTime;

    public DmColumnStoreObjectPoolDataType( )
    {
    }

    public DmColumnStoreObjectPoolDataType(int databaseId,
        int objectId,
        int indexId,
        int partitionNumber,
        int? columnId,
        int rowGroupId,
        int objectType,
        string objectTypeDesc,
        long accessCount,
        long memoryUsedInBytes,
        DateTime objectLoadTime)
    {
        _databaseId = databaseId;
        _objectId = objectId;
        _indexId = indexId;
        _partitionNumber = partitionNumber;
        _columnId = columnId;
        _rowGroupId = rowGroupId;
        _objectType = objectType;
        _objectTypeDesc = objectTypeDesc;
        _accessCount = accessCount;
        _memoryUsedInBytes = memoryUsedInBytes;
        _objectLoadTime = objectLoadTime;
    }

    public int DatabaseId => _databaseId;
    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public int PartitionNumber => _partitionNumber;
    public int? ColumnId => _columnId;
    public int RowGroupId => _rowGroupId;
    public int ObjectType => _objectType;
    public string ObjectTypeDesc => _objectTypeDesc;
    public long AccessCount => _accessCount;
    public long MemoryUsedInBytes => _memoryUsedInBytes;
    public DateTime ObjectLoadTime => _objectLoadTime;
}
