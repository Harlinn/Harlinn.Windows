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

public class PlanGuidesDataType
{
    readonly int _planGuideId = 0;
    readonly string _name = string.Empty;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly bool _isDisabled = false;
    readonly string? _queryText;
    readonly byte _scopeType = 0;
    readonly string? _scopeTypeDesc;
    readonly int? _scopeObjectId;
    readonly string? _scopeBatch;
    readonly string? _parameters;
    readonly string? _hints;

    public PlanGuidesDataType( )
    {
    }

    public PlanGuidesDataType(int planGuideId,
        string name,
        DateTime createDate,
        DateTime modifyDate,
        bool isDisabled,
        string? queryText,
        byte scopeType,
        string? scopeTypeDesc,
        int? scopeObjectId,
        string? scopeBatch,
        string? parameters,
        string? hints)
    {
        _planGuideId = planGuideId;
        _name = name;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _isDisabled = isDisabled;
        _queryText = queryText;
        _scopeType = scopeType;
        _scopeTypeDesc = scopeTypeDesc;
        _scopeObjectId = scopeObjectId;
        _scopeBatch = scopeBatch;
        _parameters = parameters;
        _hints = hints;
    }

    public int PlanGuideId => _planGuideId;
    public string Name => _name;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public bool IsDisabled => _isDisabled;
    public string? QueryText => _queryText;
    public byte ScopeType => _scopeType;
    public string? ScopeTypeDesc => _scopeTypeDesc;
    public int? ScopeObjectId => _scopeObjectId;
    public string? ScopeBatch => _scopeBatch;
    public string? Parameters => _parameters;
    public string? Hints => _hints;
}
