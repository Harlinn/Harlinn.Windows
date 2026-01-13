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

public class DmDbMissingIndexDetailsDataType
{
    readonly int _indexHandle = 0;
    readonly short _databaseId = 0;
    readonly int _objectId = 0;
    readonly string? _equalityColumns;
    readonly string? _inequalityColumns;
    readonly string? _includedColumns;
    readonly string? _statement;

    public DmDbMissingIndexDetailsDataType( )
    {
    }

    public DmDbMissingIndexDetailsDataType(int indexHandle,
        short databaseId,
        int objectId,
        string? equalityColumns,
        string? inequalityColumns,
        string? includedColumns,
        string? statement)
    {
        _indexHandle = indexHandle;
        _databaseId = databaseId;
        _objectId = objectId;
        _equalityColumns = equalityColumns;
        _inequalityColumns = inequalityColumns;
        _includedColumns = includedColumns;
        _statement = statement;
    }

    public int IndexHandle => _indexHandle;
    public short DatabaseId => _databaseId;
    public int ObjectId => _objectId;
    public string? EqualityColumns => _equalityColumns;
    public string? InequalityColumns => _inequalityColumns;
    public string? IncludedColumns => _includedColumns;
    public string? Statement => _statement;
}
