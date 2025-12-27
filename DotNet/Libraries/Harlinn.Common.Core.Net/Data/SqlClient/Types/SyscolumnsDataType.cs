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

public class SyscolumnsDataType
{
    readonly string? _name;
    readonly int _id = 0;
    readonly byte _xtype = 0;
    readonly byte? _typestat;
    readonly short? _xusertype;
    readonly short _length = 0;
    readonly byte _xprec = 0;
    readonly byte _xscale = 0;
    readonly short? _colid;
    readonly short? _xoffset;
    readonly byte? _bitpos;
    readonly byte? _reserved;
    readonly short? _colstat;
    readonly int _cdefault = 0;
    readonly int _domain = 0;
    readonly short? _number;
    readonly short? _colorder;
    readonly byte[]? _autoval;
    readonly short? _offset;
    readonly int? _collationid;
    readonly int? _language;
    readonly byte? _status;
    readonly byte _type = 0;
    readonly short? _usertype;
    readonly string? _printfmt;
    readonly short? _prec;
    readonly int? _scale;
    readonly int? _iscomputed;
    readonly int? _isoutparam;
    readonly int? _isnullable;
    readonly string? _collation;
    readonly byte[]? _tdscollation;

    public SyscolumnsDataType( )
    {
    }

    public SyscolumnsDataType(string? name,
        int id,
        byte xtype,
        byte? typestat,
        short? xusertype,
        short length,
        byte xprec,
        byte xscale,
        short? colid,
        short? xoffset,
        byte? bitpos,
        byte? reserved,
        short? colstat,
        int cdefault,
        int domain,
        short? number,
        short? colorder,
        byte[]? autoval,
        short? offset,
        int? collationid,
        int? language,
        byte? status,
        byte type,
        short? usertype,
        string? printfmt,
        short? prec,
        int? scale,
        int? iscomputed,
        int? isoutparam,
        int? isnullable,
        string? collation,
        byte[]? tdscollation)
    {
        _name = name;
        _id = id;
        _xtype = xtype;
        _typestat = typestat;
        _xusertype = xusertype;
        _length = length;
        _xprec = xprec;
        _xscale = xscale;
        _colid = colid;
        _xoffset = xoffset;
        _bitpos = bitpos;
        _reserved = reserved;
        _colstat = colstat;
        _cdefault = cdefault;
        _domain = domain;
        _number = number;
        _colorder = colorder;
        _autoval = autoval;
        _offset = offset;
        _collationid = collationid;
        _language = language;
        _status = status;
        _type = type;
        _usertype = usertype;
        _printfmt = printfmt;
        _prec = prec;
        _scale = scale;
        _iscomputed = iscomputed;
        _isoutparam = isoutparam;
        _isnullable = isnullable;
        _collation = collation;
        _tdscollation = tdscollation;
    }

    public string? Name => _name;
    public int Id => _id;
    public byte Xtype => _xtype;
    public byte? Typestat => _typestat;
    public short? Xusertype => _xusertype;
    public short Length => _length;
    public byte Xprec => _xprec;
    public byte Xscale => _xscale;
    public short? Colid => _colid;
    public short? Xoffset => _xoffset;
    public byte? Bitpos => _bitpos;
    public byte? Reserved => _reserved;
    public short? Colstat => _colstat;
    public int Cdefault => _cdefault;
    public int Domain => _domain;
    public short? Number => _number;
    public short? Colorder => _colorder;
    public byte[]? Autoval => _autoval;
    public short? Offset => _offset;
    public int? Collationid => _collationid;
    public int? Language => _language;
    public byte? Status => _status;
    public byte Type => _type;
    public short? Usertype => _usertype;
    public string? Printfmt => _printfmt;
    public short? Prec => _prec;
    public int? Scale => _scale;
    public int? Iscomputed => _iscomputed;
    public int? Isoutparam => _isoutparam;
    public int? Isnullable => _isnullable;
    public string? Collation => _collation;
    public byte[]? Tdscollation => _tdscollation;
}
