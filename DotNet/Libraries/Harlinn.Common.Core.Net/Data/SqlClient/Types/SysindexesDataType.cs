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

public class SysindexesDataType
{
    readonly int _id = 0;
    readonly int? _status;
    readonly byte[]? _first;
    readonly short? _indid;
    readonly byte[]? _root;
    readonly short? _minlen;
    readonly short? _keycnt;
    readonly short? _groupid;
    readonly int? _dpages;
    readonly int? _reserved;
    readonly int? _used;
    readonly long? _rowcnt;
    readonly int? _rowmodctr;
    readonly byte? _reserved3;
    readonly byte? _reserved4;
    readonly short? _xmaxlen;
    readonly short? _maxirow;
    readonly byte? _origfillfactor;
    readonly byte? _statversion;
    readonly int? _reserved2;
    readonly byte[]? _firstiam;
    readonly short? _impid;
    readonly short? _lockflags;
    readonly int? _pgmodctr;
    readonly byte[]? _keys;
    readonly string? _name;
    readonly byte[]? _statblob;
    readonly int? _maxlen;
    readonly int? _rows;

    public SysindexesDataType( )
    {
    }

    public SysindexesDataType(int id,
        int? status,
        byte[]? first,
        short? indid,
        byte[]? root,
        short? minlen,
        short? keycnt,
        short? groupid,
        int? dpages,
        int? reserved,
        int? used,
        long? rowcnt,
        int? rowmodctr,
        byte? reserved3,
        byte? reserved4,
        short? xmaxlen,
        short? maxirow,
        byte? origfillfactor,
        byte? statversion,
        int? reserved2,
        byte[]? firstiam,
        short? impid,
        short? lockflags,
        int? pgmodctr,
        byte[]? keys,
        string? name,
        byte[]? statblob,
        int? maxlen,
        int? rows)
    {
        _id = id;
        _status = status;
        _first = first;
        _indid = indid;
        _root = root;
        _minlen = minlen;
        _keycnt = keycnt;
        _groupid = groupid;
        _dpages = dpages;
        _reserved = reserved;
        _used = used;
        _rowcnt = rowcnt;
        _rowmodctr = rowmodctr;
        _reserved3 = reserved3;
        _reserved4 = reserved4;
        _xmaxlen = xmaxlen;
        _maxirow = maxirow;
        _origfillfactor = origfillfactor;
        _statversion = statversion;
        _reserved2 = reserved2;
        _firstiam = firstiam;
        _impid = impid;
        _lockflags = lockflags;
        _pgmodctr = pgmodctr;
        _keys = keys;
        _name = name;
        _statblob = statblob;
        _maxlen = maxlen;
        _rows = rows;
    }

    public int Id => _id;
    public int? Status => _status;
    public byte[]? First => _first;
    public short? Indid => _indid;
    public byte[]? Root => _root;
    public short? Minlen => _minlen;
    public short? Keycnt => _keycnt;
    public short? Groupid => _groupid;
    public int? Dpages => _dpages;
    public int? Reserved => _reserved;
    public int? Used => _used;
    public long? Rowcnt => _rowcnt;
    public int? Rowmodctr => _rowmodctr;
    public byte? Reserved3 => _reserved3;
    public byte? Reserved4 => _reserved4;
    public short? Xmaxlen => _xmaxlen;
    public short? Maxirow => _maxirow;
    public byte? Origfillfactor => _origfillfactor;
    public byte? Statversion => _statversion;
    public int? Reserved2 => _reserved2;
    public byte[]? Firstiam => _firstiam;
    public short? Impid => _impid;
    public short? Lockflags => _lockflags;
    public int? Pgmodctr => _pgmodctr;
    public byte[]? Keys => _keys;
    public string? Name => _name;
    public byte[]? Statblob => _statblob;
    public int? Maxlen => _maxlen;
    public int? Rows => _rows;
}
