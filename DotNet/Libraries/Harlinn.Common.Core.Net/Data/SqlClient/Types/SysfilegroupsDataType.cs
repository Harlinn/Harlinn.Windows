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

public class SysfilegroupsDataType
{
    readonly short? _groupid;
    readonly short? _allocpolicy;
    readonly int? _status;
    readonly string _groupname = string.Empty;

    public SysfilegroupsDataType( )
    {
    }

    public SysfilegroupsDataType(short? groupid,
        short? allocpolicy,
        int? status,
        string groupname)
    {
        _groupid = groupid;
        _allocpolicy = allocpolicy;
        _status = status;
        _groupname = groupname;
    }

    public short? Groupid => _groupid;
    public short? Allocpolicy => _allocpolicy;
    public int? Status => _status;
    public string Groupname => _groupname;
}
