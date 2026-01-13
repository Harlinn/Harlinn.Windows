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

public class SystemSqlModule
{
    readonly int _objectId = 0;
    readonly string? _definition;
    readonly bool _usesAnsiNulls = false;
    readonly bool _usesQuotedIdentifier = false;
    readonly bool _isSchemaBound = false;
    readonly bool _usesDatabaseCollation = false;
    readonly bool _isRecompiled = false;
    readonly bool _nullOnNullInput = false;
    readonly int? _executeAsPrincipalId;
    readonly bool _usesNativeCompilation = false;
    readonly bool _inlineType = false;
    readonly bool _isInlineable = false;

    public SystemSqlModule( )
    {
    }

    public SystemSqlModule(int objectId,
        string? definition,
        bool usesAnsiNulls,
        bool usesQuotedIdentifier,
        bool isSchemaBound,
        bool usesDatabaseCollation,
        bool isRecompiled,
        bool nullOnNullInput,
        int? executeAsPrincipalId,
        bool usesNativeCompilation,
        bool inlineType,
        bool isInlineable)
    {
        _objectId = objectId;
        _definition = definition;
        _usesAnsiNulls = usesAnsiNulls;
        _usesQuotedIdentifier = usesQuotedIdentifier;
        _isSchemaBound = isSchemaBound;
        _usesDatabaseCollation = usesDatabaseCollation;
        _isRecompiled = isRecompiled;
        _nullOnNullInput = nullOnNullInput;
        _executeAsPrincipalId = executeAsPrincipalId;
        _usesNativeCompilation = usesNativeCompilation;
        _inlineType = inlineType;
        _isInlineable = isInlineable;
    }

    public int ObjectId => _objectId;
    public string? Definition => _definition;
    public bool UsesAnsiNulls => _usesAnsiNulls;
    public bool UsesQuotedIdentifier => _usesQuotedIdentifier;
    public bool IsSchemaBound => _isSchemaBound;
    public bool UsesDatabaseCollation => _usesDatabaseCollation;
    public bool IsRecompiled => _isRecompiled;
    public bool NullOnNullInput => _nullOnNullInput;
    public int? ExecuteAsPrincipalId => _executeAsPrincipalId;
    public bool UsesNativeCompilation => _usesNativeCompilation;
    public bool InlineType => _inlineType;
    public bool IsInlineable => _isInlineable;
}
