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

public class SysdependsDataType
{
    readonly int _id = 0;
    readonly int _depid = 0;
    readonly short? _number;
    readonly short? _depnumber;
    readonly short? _status;
    readonly byte _deptype = 0;
    readonly short? _depdbid;
    readonly short? _depsiteid;
    readonly bool _selall = false;
    readonly bool _resultobj = false;
    readonly bool _readobj = false;

    public SysdependsDataType( )
    {
    }

    public SysdependsDataType(int id,
        int depid,
        short? number,
        short? depnumber,
        short? status,
        byte deptype,
        short? depdbid,
        short? depsiteid,
        bool selall,
        bool resultobj,
        bool readobj)
    {
        _id = id;
        _depid = depid;
        _number = number;
        _depnumber = depnumber;
        _status = status;
        _deptype = deptype;
        _depdbid = depdbid;
        _depsiteid = depsiteid;
        _selall = selall;
        _resultobj = resultobj;
        _readobj = readobj;
    }

    public int Id => _id;
    public int Depid => _depid;
    public short? Number => _number;
    public short? Depnumber => _depnumber;
    public short? Status => _status;
    public byte Deptype => _deptype;
    public short? Depdbid => _depdbid;
    public short? Depsiteid => _depsiteid;
    public bool Selall => _selall;
    public bool Resultobj => _resultobj;
    public bool Readobj => _readobj;
}
