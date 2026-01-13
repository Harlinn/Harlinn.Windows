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

public class NumberedProcedureParametersDataType
{
    readonly int _objectId = 0;
    readonly short _procedureNumber = 0;
    readonly string? _name;
    readonly int _parameterId = 0;
    readonly byte _systemTypeId = 0;
    readonly int _userTypeId = 0;
    readonly short _maxLength = 0;
    readonly byte _precision = 0;
    readonly byte _scale = 0;
    readonly bool _isOutput = false;
    readonly bool _isCursorRef = false;

    public NumberedProcedureParametersDataType( )
    {
    }

    public NumberedProcedureParametersDataType(int objectId,
        short procedureNumber,
        string? name,
        int parameterId,
        byte systemTypeId,
        int userTypeId,
        short maxLength,
        byte precision,
        byte scale,
        bool isOutput,
        bool isCursorRef)
    {
        _objectId = objectId;
        _procedureNumber = procedureNumber;
        _name = name;
        _parameterId = parameterId;
        _systemTypeId = systemTypeId;
        _userTypeId = userTypeId;
        _maxLength = maxLength;
        _precision = precision;
        _scale = scale;
        _isOutput = isOutput;
        _isCursorRef = isCursorRef;
    }

    public int ObjectId => _objectId;
    public short ProcedureNumber => _procedureNumber;
    public string? Name => _name;
    public int ParameterId => _parameterId;
    public byte SystemTypeId => _systemTypeId;
    public int UserTypeId => _userTypeId;
    public short MaxLength => _maxLength;
    public byte Precision => _precision;
    public byte Scale => _scale;
    public bool IsOutput => _isOutput;
    public bool IsCursorRef => _isCursorRef;
}
