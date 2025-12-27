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

public class SyscursortablesDataType
{
    readonly int _cursorHandle = 0;
    readonly string? _tableOwner;
    readonly string? _tableName;
    readonly short _optimizerHint = 0;
    readonly short _lockType = 0;
    readonly string? _serverName;
    readonly int _objectid = 0;
    readonly int _dbid = 0;
    readonly string? _dbname;

    public SyscursortablesDataType( )
    {
    }

    public SyscursortablesDataType(int cursorHandle,
        string? tableOwner,
        string? tableName,
        short optimizerHint,
        short lockType,
        string? serverName,
        int objectid,
        int dbid,
        string? dbname)
    {
        _cursorHandle = cursorHandle;
        _tableOwner = tableOwner;
        _tableName = tableName;
        _optimizerHint = optimizerHint;
        _lockType = lockType;
        _serverName = serverName;
        _objectid = objectid;
        _dbid = dbid;
        _dbname = dbname;
    }

    public int CursorHandle => _cursorHandle;
    public string? TableOwner => _tableOwner;
    public string? TableName => _tableName;
    public short OptimizerHint => _optimizerHint;
    public short LockType => _lockType;
    public string? ServerName => _serverName;
    public int Objectid => _objectid;
    public int Dbid => _dbid;
    public string? Dbname => _dbname;
}
