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

public class SysdatabasesDataType
{
    readonly string? _name;
    readonly short? _dbid;
    readonly byte[]? _sid;
    readonly short? _mode;
    readonly int? _status;
    readonly int? _status2;
    readonly DateTime _crdate;
    readonly DateTime? _reserved;
    readonly int? _category;
    readonly byte _cmptlevel = 0;
    readonly string? _filename;
    readonly short? _version;

    public SysdatabasesDataType( )
    {
    }

    public SysdatabasesDataType(string? name,
        short? dbid,
        byte[]? sid,
        short? mode,
        int? status,
        int? status2,
        DateTime crdate,
        DateTime? reserved,
        int? category,
        byte cmptlevel,
        string? filename,
        short? version)
    {
        _name = name;
        _dbid = dbid;
        _sid = sid;
        _mode = mode;
        _status = status;
        _status2 = status2;
        _crdate = crdate;
        _reserved = reserved;
        _category = category;
        _cmptlevel = cmptlevel;
        _filename = filename;
        _version = version;
    }

    public string? Name => _name;
    public short? Dbid => _dbid;
    public byte[]? Sid => _sid;
    public short? Mode => _mode;
    public int? Status => _status;
    public int? Status2 => _status2;
    public DateTime Crdate => _crdate;
    public DateTime? Reserved => _reserved;
    public int? Category => _category;
    public byte Cmptlevel => _cmptlevel;
    public string? Filename => _filename;
    public short? Version => _version;
}
