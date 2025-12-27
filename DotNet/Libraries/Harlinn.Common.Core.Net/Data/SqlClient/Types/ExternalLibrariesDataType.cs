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

public class ExternalLibrariesDataType
{
    readonly int _externalLibraryId = 0;
    readonly string? _name;
    readonly int? _principalId;
    readonly string? _language;
    readonly int _scope = 0;
    readonly string _scopeDesc = string.Empty;

    public ExternalLibrariesDataType( )
    {
    }

    public ExternalLibrariesDataType(int externalLibraryId,
        string? name,
        int? principalId,
        string? language,
        int scope,
        string scopeDesc)
    {
        _externalLibraryId = externalLibraryId;
        _name = name;
        _principalId = principalId;
        _language = language;
        _scope = scope;
        _scopeDesc = scopeDesc;
    }

    public int ExternalLibraryId => _externalLibraryId;
    public string? Name => _name;
    public int? PrincipalId => _principalId;
    public string? Language => _language;
    public int Scope => _scope;
    public string ScopeDesc => _scopeDesc;
}
