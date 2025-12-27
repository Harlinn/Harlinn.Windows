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

public class DmXeMapValuesDataType
{
    readonly string _name = string.Empty;
    readonly Guid _objectPackageGuid;
    readonly int _mapKey = 0;
    readonly string _mapValue = string.Empty;

    public DmXeMapValuesDataType( )
    {
    }

    public DmXeMapValuesDataType(string name,
        Guid objectPackageGuid,
        int mapKey,
        string mapValue)
    {
        _name = name;
        _objectPackageGuid = objectPackageGuid;
        _mapKey = mapKey;
        _mapValue = mapValue;
    }

    public string Name => _name;
    public Guid ObjectPackageGuid => _objectPackageGuid;
    public int MapKey => _mapKey;
    public string MapValue => _mapValue;
}
