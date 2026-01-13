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

public class ServerSqlModulesDataType
{
    readonly int _objectId = 0;
    readonly string? _definition;
    readonly bool? _usesAnsiNulls;
    readonly bool? _usesQuotedIdentifier;
    readonly int? _executeAsPrincipalId;

    public ServerSqlModulesDataType( )
    {
    }

    public ServerSqlModulesDataType(int objectId,
        string? definition,
        bool? usesAnsiNulls,
        bool? usesQuotedIdentifier,
        int? executeAsPrincipalId)
    {
        _objectId = objectId;
        _definition = definition;
        _usesAnsiNulls = usesAnsiNulls;
        _usesQuotedIdentifier = usesQuotedIdentifier;
        _executeAsPrincipalId = executeAsPrincipalId;
    }

    public int ObjectId => _objectId;
    public string? Definition => _definition;
    public bool? UsesAnsiNulls => _usesAnsiNulls;
    public bool? UsesQuotedIdentifier => _usesQuotedIdentifier;
    public int? ExecuteAsPrincipalId => _executeAsPrincipalId;
}
