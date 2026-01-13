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

public class DmTranVersionStoreDataType
{
    readonly long? _transactionSequenceNum;
    readonly long? _versionSequenceNum;
    readonly short? _databaseId;
    readonly long? _rowsetId;
    readonly byte? _status;
    readonly short? _minLengthInBytes;
    readonly short? _recordLengthFirstPartInBytes;
    readonly byte[]? _recordImageFirstPart;
    readonly short? _recordLengthSecondPartInBytes;
    readonly byte[]? _recordImageSecondPart;

    public DmTranVersionStoreDataType( )
    {
    }

    public DmTranVersionStoreDataType(long? transactionSequenceNum,
        long? versionSequenceNum,
        short? databaseId,
        long? rowsetId,
        byte? status,
        short? minLengthInBytes,
        short? recordLengthFirstPartInBytes,
        byte[]? recordImageFirstPart,
        short? recordLengthSecondPartInBytes,
        byte[]? recordImageSecondPart)
    {
        _transactionSequenceNum = transactionSequenceNum;
        _versionSequenceNum = versionSequenceNum;
        _databaseId = databaseId;
        _rowsetId = rowsetId;
        _status = status;
        _minLengthInBytes = minLengthInBytes;
        _recordLengthFirstPartInBytes = recordLengthFirstPartInBytes;
        _recordImageFirstPart = recordImageFirstPart;
        _recordLengthSecondPartInBytes = recordLengthSecondPartInBytes;
        _recordImageSecondPart = recordImageSecondPart;
    }

    public long? TransactionSequenceNum => _transactionSequenceNum;
    public long? VersionSequenceNum => _versionSequenceNum;
    public short? DatabaseId => _databaseId;
    public long? RowsetId => _rowsetId;
    public byte? Status => _status;
    public short? MinLengthInBytes => _minLengthInBytes;
    public short? RecordLengthFirstPartInBytes => _recordLengthFirstPartInBytes;
    public byte[]? RecordImageFirstPart => _recordImageFirstPart;
    public short? RecordLengthSecondPartInBytes => _recordLengthSecondPartInBytes;
    public byte[]? RecordImageSecondPart => _recordImageSecondPart;
}
