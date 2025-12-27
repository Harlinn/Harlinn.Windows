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

public class DmReplSchemasDataType
{
    readonly byte[]? _artcacheSchemaAddress;
    readonly int? _tabid;
    readonly short? _indexid;
    readonly int? _idsch;
    readonly string? _tabschema;
    readonly short? _cctabschema;
    readonly string? _tabname;
    readonly short? _cctabname;
    readonly long? _rowsetidDelete;
    readonly long? _rowsetidInsert;
    readonly int? _numPkCols;
    readonly byte[]? _pcitee;
    readonly int? _reNumtextcols;
    readonly string? _reSchemaLsnBegin;
    readonly string? _reSchemaLsnEnd;
    readonly int? _reNumcols;
    readonly int? _reColid;
    readonly string? _reAwcname;
    readonly short? _reCcname;
    readonly short? _reColattr;
    readonly short? _reMaxlen;
    readonly byte? _rePrec;
    readonly byte? _reScale;
    readonly int? _reCollatid;
    readonly byte? _reXvtype;
    readonly int? _reOffset;
    readonly byte? _reBitpos;
    readonly byte? _reFnullable;
    readonly byte? _reFansitrim;
    readonly int? _reComputed;
    readonly long? _seRowsetid;
    readonly string? _seSchemaLsnBegin;
    readonly string? _seSchemaLsnEnd;
    readonly int? _seNumcols;
    readonly int? _seColid;
    readonly short? _seMaxlen;
    readonly byte? _sePrec;
    readonly byte? _seScale;
    readonly int? _seCollatid;
    readonly byte? _seXvtype;
    readonly int? _seOffset;
    readonly byte? _seBitpos;
    readonly byte? _seFnullable;
    readonly byte? _seFansitrim;
    readonly byte? _seComputed;
    readonly short? _seNullbitinleafrows;

    public DmReplSchemasDataType( )
    {
    }

    public DmReplSchemasDataType(byte[]? artcacheSchemaAddress,
        int? tabid,
        short? indexid,
        int? idsch,
        string? tabschema,
        short? cctabschema,
        string? tabname,
        short? cctabname,
        long? rowsetidDelete,
        long? rowsetidInsert,
        int? numPkCols,
        byte[]? pcitee,
        int? reNumtextcols,
        string? reSchemaLsnBegin,
        string? reSchemaLsnEnd,
        int? reNumcols,
        int? reColid,
        string? reAwcname,
        short? reCcname,
        short? reColattr,
        short? reMaxlen,
        byte? rePrec,
        byte? reScale,
        int? reCollatid,
        byte? reXvtype,
        int? reOffset,
        byte? reBitpos,
        byte? reFnullable,
        byte? reFansitrim,
        int? reComputed,
        long? seRowsetid,
        string? seSchemaLsnBegin,
        string? seSchemaLsnEnd,
        int? seNumcols,
        int? seColid,
        short? seMaxlen,
        byte? sePrec,
        byte? seScale,
        int? seCollatid,
        byte? seXvtype,
        int? seOffset,
        byte? seBitpos,
        byte? seFnullable,
        byte? seFansitrim,
        byte? seComputed,
        short? seNullbitinleafrows)
    {
        _artcacheSchemaAddress = artcacheSchemaAddress;
        _tabid = tabid;
        _indexid = indexid;
        _idsch = idsch;
        _tabschema = tabschema;
        _cctabschema = cctabschema;
        _tabname = tabname;
        _cctabname = cctabname;
        _rowsetidDelete = rowsetidDelete;
        _rowsetidInsert = rowsetidInsert;
        _numPkCols = numPkCols;
        _pcitee = pcitee;
        _reNumtextcols = reNumtextcols;
        _reSchemaLsnBegin = reSchemaLsnBegin;
        _reSchemaLsnEnd = reSchemaLsnEnd;
        _reNumcols = reNumcols;
        _reColid = reColid;
        _reAwcname = reAwcname;
        _reCcname = reCcname;
        _reColattr = reColattr;
        _reMaxlen = reMaxlen;
        _rePrec = rePrec;
        _reScale = reScale;
        _reCollatid = reCollatid;
        _reXvtype = reXvtype;
        _reOffset = reOffset;
        _reBitpos = reBitpos;
        _reFnullable = reFnullable;
        _reFansitrim = reFansitrim;
        _reComputed = reComputed;
        _seRowsetid = seRowsetid;
        _seSchemaLsnBegin = seSchemaLsnBegin;
        _seSchemaLsnEnd = seSchemaLsnEnd;
        _seNumcols = seNumcols;
        _seColid = seColid;
        _seMaxlen = seMaxlen;
        _sePrec = sePrec;
        _seScale = seScale;
        _seCollatid = seCollatid;
        _seXvtype = seXvtype;
        _seOffset = seOffset;
        _seBitpos = seBitpos;
        _seFnullable = seFnullable;
        _seFansitrim = seFansitrim;
        _seComputed = seComputed;
        _seNullbitinleafrows = seNullbitinleafrows;
    }

    public byte[]? ArtcacheSchemaAddress => _artcacheSchemaAddress;
    public int? Tabid => _tabid;
    public short? Indexid => _indexid;
    public int? Idsch => _idsch;
    public string? Tabschema => _tabschema;
    public short? Cctabschema => _cctabschema;
    public string? Tabname => _tabname;
    public short? Cctabname => _cctabname;
    public long? RowsetidDelete => _rowsetidDelete;
    public long? RowsetidInsert => _rowsetidInsert;
    public int? NumPkCols => _numPkCols;
    public byte[]? Pcitee => _pcitee;
    public int? ReNumtextcols => _reNumtextcols;
    public string? ReSchemaLsnBegin => _reSchemaLsnBegin;
    public string? ReSchemaLsnEnd => _reSchemaLsnEnd;
    public int? ReNumcols => _reNumcols;
    public int? ReColid => _reColid;
    public string? ReAwcname => _reAwcname;
    public short? ReCcname => _reCcname;
    public short? ReColattr => _reColattr;
    public short? ReMaxlen => _reMaxlen;
    public byte? RePrec => _rePrec;
    public byte? ReScale => _reScale;
    public int? ReCollatid => _reCollatid;
    public byte? ReXvtype => _reXvtype;
    public int? ReOffset => _reOffset;
    public byte? ReBitpos => _reBitpos;
    public byte? ReFnullable => _reFnullable;
    public byte? ReFansitrim => _reFansitrim;
    public int? ReComputed => _reComputed;
    public long? SeRowsetid => _seRowsetid;
    public string? SeSchemaLsnBegin => _seSchemaLsnBegin;
    public string? SeSchemaLsnEnd => _seSchemaLsnEnd;
    public int? SeNumcols => _seNumcols;
    public int? SeColid => _seColid;
    public short? SeMaxlen => _seMaxlen;
    public byte? SePrec => _sePrec;
    public byte? SeScale => _seScale;
    public int? SeCollatid => _seCollatid;
    public byte? SeXvtype => _seXvtype;
    public int? SeOffset => _seOffset;
    public byte? SeBitpos => _seBitpos;
    public byte? SeFnullable => _seFnullable;
    public byte? SeFansitrim => _seFansitrim;
    public byte? SeComputed => _seComputed;
    public short? SeNullbitinleafrows => _seNullbitinleafrows;
}
