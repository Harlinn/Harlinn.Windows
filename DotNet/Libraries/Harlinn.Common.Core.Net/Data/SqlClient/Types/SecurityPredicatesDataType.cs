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

public class SecurityPredicatesDataType
{
    readonly int _objectId = 0;
    readonly int _securityPredicateId = 0;
    readonly int _targetObjectId = 0;
    readonly string? _predicateDefinition;
    readonly int? _predicateType;
    readonly string? _predicateTypeDesc;
    readonly int? _operation;
    readonly string? _operationDesc;

    public SecurityPredicatesDataType( )
    {
    }

    public SecurityPredicatesDataType(int objectId,
        int securityPredicateId,
        int targetObjectId,
        string? predicateDefinition,
        int? predicateType,
        string? predicateTypeDesc,
        int? operation,
        string? operationDesc)
    {
        _objectId = objectId;
        _securityPredicateId = securityPredicateId;
        _targetObjectId = targetObjectId;
        _predicateDefinition = predicateDefinition;
        _predicateType = predicateType;
        _predicateTypeDesc = predicateTypeDesc;
        _operation = operation;
        _operationDesc = operationDesc;
    }

    public int ObjectId => _objectId;
    public int SecurityPredicateId => _securityPredicateId;
    public int TargetObjectId => _targetObjectId;
    public string? PredicateDefinition => _predicateDefinition;
    public int? PredicateType => _predicateType;
    public string? PredicateTypeDesc => _predicateTypeDesc;
    public int? Operation => _operation;
    public string? OperationDesc => _operationDesc;
}
