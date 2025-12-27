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

public class SysfilesDataType
{
    readonly short? _fileid;
    readonly short? _groupid;
    readonly int _size = 0;
    readonly int _maxsize = 0;
    readonly int _growth = 0;
    readonly int? _status;
    readonly int? _perf;
    readonly string _name = string.Empty;
    readonly string? _filename;

    public SysfilesDataType( )
    {
    }

    public SysfilesDataType(short? fileid,
        short? groupid,
        int size,
        int maxsize,
        int growth,
        int? status,
        int? perf,
        string name,
        string? filename)
    {
        _fileid = fileid;
        _groupid = groupid;
        _size = size;
        _maxsize = maxsize;
        _growth = growth;
        _status = status;
        _perf = perf;
        _name = name;
        _filename = filename;
    }

    public short? Fileid => _fileid;
    public short? Groupid => _groupid;
    public int Size => _size;
    public int Maxsize => _maxsize;
    public int Growth => _growth;
    public int? Status => _status;
    public int? Perf => _perf;
    public string Name => _name;
    public string? Filename => _filename;
}
