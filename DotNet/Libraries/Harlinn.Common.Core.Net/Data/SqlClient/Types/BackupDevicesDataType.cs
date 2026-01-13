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

public class BackupDevicesDataType
{
    readonly string _name = string.Empty;
    readonly byte? _type;
    readonly string? _typeDesc;
    readonly string? _physicalName;

    public BackupDevicesDataType( )
    {
    }

    public BackupDevicesDataType(string name,
        byte? type,
        string? typeDesc,
        string? physicalName)
    {
        _name = name;
        _type = type;
        _typeDesc = typeDesc;
        _physicalName = physicalName;
    }

    public string Name => _name;
    public byte? Type => _type;
    public string? TypeDesc => _typeDesc;
    public string? PhysicalName => _physicalName;
}
