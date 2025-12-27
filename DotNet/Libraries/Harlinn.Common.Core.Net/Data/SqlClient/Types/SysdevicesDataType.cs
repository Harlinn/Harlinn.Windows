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

public class SysdevicesDataType
{
    readonly string _name = string.Empty;
    readonly int? _size;
    readonly int? _low;
    readonly int? _high;
    readonly short? _status;
    readonly short? _cntrltype;
    readonly string? _phyname;

    public SysdevicesDataType( )
    {
    }

    public SysdevicesDataType(string name,
        int? size,
        int? low,
        int? high,
        short? status,
        short? cntrltype,
        string? phyname)
    {
        _name = name;
        _size = size;
        _low = low;
        _high = high;
        _status = status;
        _cntrltype = cntrltype;
        _phyname = phyname;
    }

    public string Name => _name;
    public int? Size => _size;
    public int? Low => _low;
    public int? High => _high;
    public short? Status => _status;
    public short? Cntrltype => _cntrltype;
    public string? Phyname => _phyname;
}
