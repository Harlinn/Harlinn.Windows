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

public class SystypesDataType
{
    readonly string _name = string.Empty;
    readonly byte _xtype = 0;
    readonly byte? _status;
    readonly short? _xusertype;
    readonly short _length = 0;
    readonly byte _xprec = 0;
    readonly byte _xscale = 0;
    readonly int _tdefault = 0;
    readonly int _domain = 0;
    readonly short? _uid;
    readonly short? _reserved;
    readonly int? _collationid;
    readonly short? _usertype;
    readonly bool _variable = false;
    readonly bool? _allownulls;
    readonly byte _type = 0;
    readonly string? _printfmt;
    readonly short? _prec;
    readonly byte? _scale;
    readonly string? _collation;

    public SystypesDataType( )
    {
    }

    public SystypesDataType(string name,
        byte xtype,
        byte? status,
        short? xusertype,
        short length,
        byte xprec,
        byte xscale,
        int tdefault,
        int domain,
        short? uid,
        short? reserved,
        int? collationid,
        short? usertype,
        bool variable,
        bool? allownulls,
        byte type,
        string? printfmt,
        short? prec,
        byte? scale,
        string? collation)
    {
        _name = name;
        _xtype = xtype;
        _status = status;
        _xusertype = xusertype;
        _length = length;
        _xprec = xprec;
        _xscale = xscale;
        _tdefault = tdefault;
        _domain = domain;
        _uid = uid;
        _reserved = reserved;
        _collationid = collationid;
        _usertype = usertype;
        _variable = variable;
        _allownulls = allownulls;
        _type = type;
        _printfmt = printfmt;
        _prec = prec;
        _scale = scale;
        _collation = collation;
    }

    public string Name => _name;
    public byte Xtype => _xtype;
    public byte? Status => _status;
    public short? Xusertype => _xusertype;
    public short Length => _length;
    public byte Xprec => _xprec;
    public byte Xscale => _xscale;
    public int Tdefault => _tdefault;
    public int Domain => _domain;
    public short? Uid => _uid;
    public short? Reserved => _reserved;
    public int? Collationid => _collationid;
    public short? Usertype => _usertype;
    public bool Variable => _variable;
    public bool? Allownulls => _allownulls;
    public byte Type => _type;
    public string? Printfmt => _printfmt;
    public short? Prec => _prec;
    public byte? Scale => _scale;
    public string? Collation => _collation;
}
