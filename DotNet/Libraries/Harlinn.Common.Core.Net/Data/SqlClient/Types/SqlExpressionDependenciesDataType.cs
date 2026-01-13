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

public class SqlExpressionDependenciesDataType
{
    readonly int _referencingId = 0;
    readonly int _referencingMinorId = 0;
    readonly byte? _referencingClass;
    readonly string? _referencingClassDesc;
    readonly bool _isSchemaBoundReference = false;
    readonly byte? _referencedClass;
    readonly string? _referencedClassDesc;
    readonly string? _referencedServerName;
    readonly string? _referencedDatabaseName;
    readonly string? _referencedSchemaName;
    readonly string? _referencedEntityName;
    readonly int? _referencedId;
    readonly int _referencedMinorId = 0;
    readonly bool _isCallerDependent = false;
    readonly bool _isAmbiguous = false;

    public SqlExpressionDependenciesDataType( )
    {
    }

    public SqlExpressionDependenciesDataType(int referencingId,
        int referencingMinorId,
        byte? referencingClass,
        string? referencingClassDesc,
        bool isSchemaBoundReference,
        byte? referencedClass,
        string? referencedClassDesc,
        string? referencedServerName,
        string? referencedDatabaseName,
        string? referencedSchemaName,
        string? referencedEntityName,
        int? referencedId,
        int referencedMinorId,
        bool isCallerDependent,
        bool isAmbiguous)
    {
        _referencingId = referencingId;
        _referencingMinorId = referencingMinorId;
        _referencingClass = referencingClass;
        _referencingClassDesc = referencingClassDesc;
        _isSchemaBoundReference = isSchemaBoundReference;
        _referencedClass = referencedClass;
        _referencedClassDesc = referencedClassDesc;
        _referencedServerName = referencedServerName;
        _referencedDatabaseName = referencedDatabaseName;
        _referencedSchemaName = referencedSchemaName;
        _referencedEntityName = referencedEntityName;
        _referencedId = referencedId;
        _referencedMinorId = referencedMinorId;
        _isCallerDependent = isCallerDependent;
        _isAmbiguous = isAmbiguous;
    }

    public int ReferencingId => _referencingId;
    public int ReferencingMinorId => _referencingMinorId;
    public byte? ReferencingClass => _referencingClass;
    public string? ReferencingClassDesc => _referencingClassDesc;
    public bool IsSchemaBoundReference => _isSchemaBoundReference;
    public byte? ReferencedClass => _referencedClass;
    public string? ReferencedClassDesc => _referencedClassDesc;
    public string? ReferencedServerName => _referencedServerName;
    public string? ReferencedDatabaseName => _referencedDatabaseName;
    public string? ReferencedSchemaName => _referencedSchemaName;
    public string? ReferencedEntityName => _referencedEntityName;
    public int? ReferencedId => _referencedId;
    public int ReferencedMinorId => _referencedMinorId;
    public bool IsCallerDependent => _isCallerDependent;
    public bool IsAmbiguous => _isAmbiguous;
}
