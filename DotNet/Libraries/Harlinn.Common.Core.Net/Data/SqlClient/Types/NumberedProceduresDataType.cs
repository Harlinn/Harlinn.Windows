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

public class NumberedProceduresDataType
{
    readonly int _objectId = 0;
    readonly short? _procedureNumber;
    readonly string? _definition;

    public NumberedProceduresDataType( )
    {
    }

    public NumberedProceduresDataType(int objectId,
        short? procedureNumber,
        string? definition)
    {
        _objectId = objectId;
        _procedureNumber = procedureNumber;
        _definition = definition;
    }

    public int ObjectId => _objectId;
    public short? ProcedureNumber => _procedureNumber;
    public string? Definition => _definition;
}
