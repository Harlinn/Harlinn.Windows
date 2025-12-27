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

public class DmTranTopVersionGeneratorsDataType
{
    readonly short? _databaseId;
    readonly long? _rowsetId;
    readonly int? _aggregatedRecordLengthInBytes;

    public DmTranTopVersionGeneratorsDataType( )
    {
    }

    public DmTranTopVersionGeneratorsDataType(short? databaseId,
        long? rowsetId,
        int? aggregatedRecordLengthInBytes)
    {
        _databaseId = databaseId;
        _rowsetId = rowsetId;
        _aggregatedRecordLengthInBytes = aggregatedRecordLengthInBytes;
    }

    public short? DatabaseId => _databaseId;
    public long? RowsetId => _rowsetId;
    public int? AggregatedRecordLengthInBytes => _aggregatedRecordLengthInBytes;
}
