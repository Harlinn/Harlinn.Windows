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

public class MemoryOptimizedTablesInternalAttributesDataType
{
    readonly int? _objectId;
    readonly int _xtpObjectId = 0;
    readonly int? _type;
    readonly string _typeDesc = string.Empty;
    readonly int _minorId = 0;

    public MemoryOptimizedTablesInternalAttributesDataType( )
    {
    }

    public MemoryOptimizedTablesInternalAttributesDataType(int? objectId,
        int xtpObjectId,
        int? type,
        string typeDesc,
        int minorId)
    {
        _objectId = objectId;
        _xtpObjectId = xtpObjectId;
        _type = type;
        _typeDesc = typeDesc;
        _minorId = minorId;
    }

    public int? ObjectId => _objectId;
    public int XtpObjectId => _xtpObjectId;
    public int? Type => _type;
    public string TypeDesc => _typeDesc;
    public int MinorId => _minorId;
}
