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

public class DmAuditClassTypeMapDataType
{
    readonly string? _classType;
    readonly string? _classTypeDesc;
    readonly string? _securableClassDesc;

    public DmAuditClassTypeMapDataType( )
    {
    }

    public DmAuditClassTypeMapDataType(string? classType,
        string? classTypeDesc,
        string? securableClassDesc)
    {
        _classType = classType;
        _classTypeDesc = classTypeDesc;
        _securableClassDesc = securableClassDesc;
    }

    public string? ClassType => _classType;
    public string? ClassTypeDesc => _classTypeDesc;
    public string? SecurableClassDesc => _securableClassDesc;
}
