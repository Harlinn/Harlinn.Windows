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

public class DmDbUncontainedEntitiesDataType
{
    readonly int _class = 0;
    readonly string _classDesc = string.Empty;
    readonly int _majorId = 0;
    readonly int? _statementLineNumber;
    readonly int? _statementOffsetBegin;
    readonly int? _statementOffsetEnd;
    readonly string? _statementType;
    readonly string _featureName = string.Empty;
    readonly string _featureTypeName = string.Empty;

    public DmDbUncontainedEntitiesDataType( )
    {
    }

    public DmDbUncontainedEntitiesDataType(int class__,
        string classDesc,
        int majorId,
        int? statementLineNumber,
        int? statementOffsetBegin,
        int? statementOffsetEnd,
        string? statementType,
        string featureName,
        string featureTypeName)
    {
        _class = class__;
        _classDesc = classDesc;
        _majorId = majorId;
        _statementLineNumber = statementLineNumber;
        _statementOffsetBegin = statementOffsetBegin;
        _statementOffsetEnd = statementOffsetEnd;
        _statementType = statementType;
        _featureName = featureName;
        _featureTypeName = featureTypeName;
    }

    public int Class => _class;
    public string ClassDesc => _classDesc;
    public int MajorId => _majorId;
    public int? StatementLineNumber => _statementLineNumber;
    public int? StatementOffsetBegin => _statementOffsetBegin;
    public int? StatementOffsetEnd => _statementOffsetEnd;
    public string? StatementType => _statementType;
    public string FeatureName => _featureName;
    public string FeatureTypeName => _featureTypeName;
}
