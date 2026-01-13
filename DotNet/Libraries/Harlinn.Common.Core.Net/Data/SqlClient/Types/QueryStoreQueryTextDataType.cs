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

public class QueryStoreQueryTextDataType
{
    readonly long _queryTextId = 0;
    readonly string? _querySqlText;
    readonly byte[]? _statementSqlHandle;
    readonly bool _isPartOfEncryptedModule = false;
    readonly bool _hasRestrictedText = false;

    public QueryStoreQueryTextDataType( )
    {
    }

    public QueryStoreQueryTextDataType(long queryTextId,
        string? querySqlText,
        byte[]? statementSqlHandle,
        bool isPartOfEncryptedModule,
        bool hasRestrictedText)
    {
        _queryTextId = queryTextId;
        _querySqlText = querySqlText;
        _statementSqlHandle = statementSqlHandle;
        _isPartOfEncryptedModule = isPartOfEncryptedModule;
        _hasRestrictedText = hasRestrictedText;
    }

    public long QueryTextId => _queryTextId;
    public string? QuerySqlText => _querySqlText;
    public byte[]? StatementSqlHandle => _statementSqlHandle;
    public bool IsPartOfEncryptedModule => _isPartOfEncryptedModule;
    public bool HasRestrictedText => _hasRestrictedText;
}
