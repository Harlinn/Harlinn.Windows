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

public class PartitionParametersDataType
{
    readonly int _functionId = 0;
    readonly int _parameterId = 0;
    readonly byte _systemTypeId = 0;
    readonly short _maxLength = 0;
    readonly byte _precision = 0;
    readonly byte _scale = 0;
    readonly string? _collationName;
    readonly int _userTypeId = 0;

    public PartitionParametersDataType( )
    {
    }

    public PartitionParametersDataType(int functionId,
        int parameterId,
        byte systemTypeId,
        short maxLength,
        byte precision,
        byte scale,
        string? collationName,
        int userTypeId)
    {
        _functionId = functionId;
        _parameterId = parameterId;
        _systemTypeId = systemTypeId;
        _maxLength = maxLength;
        _precision = precision;
        _scale = scale;
        _collationName = collationName;
        _userTypeId = userTypeId;
    }

    public int FunctionId => _functionId;
    public int ParameterId => _parameterId;
    public byte SystemTypeId => _systemTypeId;
    public short MaxLength => _maxLength;
    public byte Precision => _precision;
    public byte Scale => _scale;
    public string? CollationName => _collationName;
    public int UserTypeId => _userTypeId;
}
