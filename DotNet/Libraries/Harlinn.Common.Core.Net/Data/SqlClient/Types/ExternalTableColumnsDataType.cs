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

public class ExternalTableColumnsDataType
{
    readonly int _objectId = 0;
    readonly int _columnId = 0;
    readonly int? _partitionColumnOrdinal;
    readonly int? _hashColumnOrdinal;

    public ExternalTableColumnsDataType( )
    {
    }

    public ExternalTableColumnsDataType(int objectId,
        int columnId,
        int? partitionColumnOrdinal,
        int? hashColumnOrdinal)
    {
        _objectId = objectId;
        _columnId = columnId;
        _partitionColumnOrdinal = partitionColumnOrdinal;
        _hashColumnOrdinal = hashColumnOrdinal;
    }

    public int ObjectId => _objectId;
    public int ColumnId => _columnId;
    public int? PartitionColumnOrdinal => _partitionColumnOrdinal;
    public int? HashColumnOrdinal => _hashColumnOrdinal;
}
