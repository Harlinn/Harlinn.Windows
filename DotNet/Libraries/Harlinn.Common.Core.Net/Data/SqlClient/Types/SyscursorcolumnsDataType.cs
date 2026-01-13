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

public class SyscursorcolumnsDataType
{
    readonly int _cursorHandle = 0;
    readonly string? _columnName;
    readonly int _ordinalPosition = 0;
    readonly int _columnCharacteristicsFlags = 0;
    readonly int _columnSize = 0;
    readonly int _dataTypeSql = 0;
    readonly byte _columnPrecision = 0;
    readonly byte _columnScale = 0;
    readonly int _orderPosition = 0;
    readonly string? _orderDirection;
    readonly short _hiddenColumn = 0;
    readonly int _columnid = 0;
    readonly int _objectid = 0;
    readonly int _dbid = 0;
    readonly string? _dbname;

    public SyscursorcolumnsDataType( )
    {
    }

    public SyscursorcolumnsDataType(int cursorHandle,
        string? columnName,
        int ordinalPosition,
        int columnCharacteristicsFlags,
        int columnSize,
        int dataTypeSql,
        byte columnPrecision,
        byte columnScale,
        int orderPosition,
        string? orderDirection,
        short hiddenColumn,
        int columnid,
        int objectid,
        int dbid,
        string? dbname)
    {
        _cursorHandle = cursorHandle;
        _columnName = columnName;
        _ordinalPosition = ordinalPosition;
        _columnCharacteristicsFlags = columnCharacteristicsFlags;
        _columnSize = columnSize;
        _dataTypeSql = dataTypeSql;
        _columnPrecision = columnPrecision;
        _columnScale = columnScale;
        _orderPosition = orderPosition;
        _orderDirection = orderDirection;
        _hiddenColumn = hiddenColumn;
        _columnid = columnid;
        _objectid = objectid;
        _dbid = dbid;
        _dbname = dbname;
    }

    public int CursorHandle => _cursorHandle;
    public string? ColumnName => _columnName;
    public int OrdinalPosition => _ordinalPosition;
    public int ColumnCharacteristicsFlags => _columnCharacteristicsFlags;
    public int ColumnSize => _columnSize;
    public int DataTypeSql => _dataTypeSql;
    public byte ColumnPrecision => _columnPrecision;
    public byte ColumnScale => _columnScale;
    public int OrderPosition => _orderPosition;
    public string? OrderDirection => _orderDirection;
    public short HiddenColumn => _hiddenColumn;
    public int Columnid => _columnid;
    public int Objectid => _objectid;
    public int Dbid => _dbid;
    public string? Dbname => _dbname;
}
