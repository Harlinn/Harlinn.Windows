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

public class SyscursorsDataType
{
    readonly int _cursorHandle = 0;
    readonly string? _cursorName;
    readonly int _status = 0;
    readonly byte _model = 0;
    readonly byte _concurrency = 0;
    readonly byte _scrollable = 0;
    readonly byte _openStatus = 0;
    readonly object? _cursorRows;
    readonly short _fetchStatus = 0;
    readonly short _columnCount = 0;
    readonly object? _rowCount;
    readonly byte _lastOperation = 0;

    public SyscursorsDataType( )
    {
    }

    public SyscursorsDataType(int cursorHandle,
        string? cursorName,
        int status,
        byte model,
        byte concurrency,
        byte scrollable,
        byte openStatus,
        object? cursorRows,
        short fetchStatus,
        short columnCount,
        object? rowCount,
        byte lastOperation)
    {
        _cursorHandle = cursorHandle;
        _cursorName = cursorName;
        _status = status;
        _model = model;
        _concurrency = concurrency;
        _scrollable = scrollable;
        _openStatus = openStatus;
        _cursorRows = cursorRows;
        _fetchStatus = fetchStatus;
        _columnCount = columnCount;
        _rowCount = rowCount;
        _lastOperation = lastOperation;
    }

    public int CursorHandle => _cursorHandle;
    public string? CursorName => _cursorName;
    public int Status => _status;
    public byte Model => _model;
    public byte Concurrency => _concurrency;
    public byte Scrollable => _scrollable;
    public byte OpenStatus => _openStatus;
    public object? CursorRows => _cursorRows;
    public short FetchStatus => _fetchStatus;
    public short ColumnCount => _columnCount;
    public object? RowCount => _rowCount;
    public byte LastOperation => _lastOperation;
}
