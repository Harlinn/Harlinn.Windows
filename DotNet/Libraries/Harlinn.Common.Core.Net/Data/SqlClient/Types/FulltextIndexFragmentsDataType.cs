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

public class FulltextIndexFragmentsDataType
{
    readonly int _tableId = 0;
    readonly int _fragmentId = 0;
    readonly int _fragmentObjectId = 0;
    readonly byte[] _timestamp = Array.Empty<byte>();
    readonly int _status = 0;
    readonly long _dataSize = 0;
    readonly long _rowCount = 0;

    public FulltextIndexFragmentsDataType( )
    {
    }

    public FulltextIndexFragmentsDataType(int tableId,
        int fragmentId,
        int fragmentObjectId,
        byte[] timestamp,
        int status,
        long dataSize,
        long rowCount)
    {
        _tableId = tableId;
        _fragmentId = fragmentId;
        _fragmentObjectId = fragmentObjectId;
        _timestamp = timestamp;
        _status = status;
        _dataSize = dataSize;
        _rowCount = rowCount;
    }

    public int TableId => _tableId;
    public int FragmentId => _fragmentId;
    public int FragmentObjectId => _fragmentObjectId;
    public byte[] Timestamp => _timestamp;
    public int Status => _status;
    public long DataSize => _dataSize;
    public long RowCount => _rowCount;
}
