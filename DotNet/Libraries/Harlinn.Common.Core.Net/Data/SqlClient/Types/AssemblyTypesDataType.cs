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

public class AssemblyTypesDataType
{
    readonly string _name = string.Empty;
    readonly byte _systemTypeId = 0;
    readonly int _userTypeId = 0;
    readonly int _schemaId = 0;
    readonly int? _principalId;
    readonly short _maxLength = 0;
    readonly byte _precision = 0;
    readonly byte _scale = 0;
    readonly string? _collationName;
    readonly bool? _isNullable;
    readonly bool _isUserDefined = false;
    readonly bool _isAssemblyType = false;
    readonly int _defaultObjectId = 0;
    readonly int _ruleObjectId = 0;
    readonly int _assemblyId = 0;
    readonly string? _assemblyClass;
    readonly bool? _isBinaryOrdered;
    readonly bool? _isFixedLength;
    readonly string? _progId;
    readonly string? _assemblyQualifiedName;
    readonly bool _isTableType = false;

    public AssemblyTypesDataType( )
    {
    }

    public AssemblyTypesDataType(string name,
        byte systemTypeId,
        int userTypeId,
        int schemaId,
        int? principalId,
        short maxLength,
        byte precision,
        byte scale,
        string? collationName,
        bool? isNullable,
        bool isUserDefined,
        bool isAssemblyType,
        int defaultObjectId,
        int ruleObjectId,
        int assemblyId,
        string? assemblyClass,
        bool? isBinaryOrdered,
        bool? isFixedLength,
        string? progId,
        string? assemblyQualifiedName,
        bool isTableType)
    {
        _name = name;
        _systemTypeId = systemTypeId;
        _userTypeId = userTypeId;
        _schemaId = schemaId;
        _principalId = principalId;
        _maxLength = maxLength;
        _precision = precision;
        _scale = scale;
        _collationName = collationName;
        _isNullable = isNullable;
        _isUserDefined = isUserDefined;
        _isAssemblyType = isAssemblyType;
        _defaultObjectId = defaultObjectId;
        _ruleObjectId = ruleObjectId;
        _assemblyId = assemblyId;
        _assemblyClass = assemblyClass;
        _isBinaryOrdered = isBinaryOrdered;
        _isFixedLength = isFixedLength;
        _progId = progId;
        _assemblyQualifiedName = assemblyQualifiedName;
        _isTableType = isTableType;
    }

    public string Name => _name;
    public byte SystemTypeId => _systemTypeId;
    public int UserTypeId => _userTypeId;
    public int SchemaId => _schemaId;
    public int? PrincipalId => _principalId;
    public short MaxLength => _maxLength;
    public byte Precision => _precision;
    public byte Scale => _scale;
    public string? CollationName => _collationName;
    public bool? IsNullable => _isNullable;
    public bool IsUserDefined => _isUserDefined;
    public bool IsAssemblyType => _isAssemblyType;
    public int DefaultObjectId => _defaultObjectId;
    public int RuleObjectId => _ruleObjectId;
    public int AssemblyId => _assemblyId;
    public string? AssemblyClass => _assemblyClass;
    public bool? IsBinaryOrdered => _isBinaryOrdered;
    public bool? IsFixedLength => _isFixedLength;
    public string? ProgId => _progId;
    public string? AssemblyQualifiedName => _assemblyQualifiedName;
    public bool IsTableType => _isTableType;
}
