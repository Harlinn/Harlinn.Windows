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

public class DmReplArticlesDataType
{
    readonly byte[]? _artcacheDbAddress;
    readonly byte[]? _artcacheTableAddress;
    readonly byte[]? _artcacheSchemaAddress;
    readonly byte[]? _artcacheArticleAddress;
    readonly int? _artid;
    readonly int? _artfilter;
    readonly int? _artobjid;
    readonly int? _artpubid;
    readonly byte? _artstatus;
    readonly byte? _arttype;
    readonly string? _wszartdesttable;
    readonly string? _wszartdesttableowner;
    readonly string? _wszartinscmd;
    readonly int? _cmdtypeins;
    readonly string? _wszartdelcmd;
    readonly int? _cmdtypedel;
    readonly string? _wszartupdcmd;
    readonly int? _cmdtypeupd;
    readonly string? _wszartpartialupdcmd;
    readonly int? _cmdtypepartialupd;
    readonly int? _numcol;
    readonly byte? _artcmdtype;
    readonly string? _artgeninscmd;
    readonly string? _artgendelcmd;
    readonly string? _artgenupdcmd;
    readonly string? _artpartialupdcmd;
    readonly string? _artupdtxtcmd;
    readonly string? _artgenins2cmd;
    readonly string? _artgendel2cmd;
    readonly byte? _finreconcile;
    readonly byte? _fpuballowupdate;
    readonly int? _intpublicationoptions;

    public DmReplArticlesDataType( )
    {
    }

    public DmReplArticlesDataType(byte[]? artcacheDbAddress,
        byte[]? artcacheTableAddress,
        byte[]? artcacheSchemaAddress,
        byte[]? artcacheArticleAddress,
        int? artid,
        int? artfilter,
        int? artobjid,
        int? artpubid,
        byte? artstatus,
        byte? arttype,
        string? wszartdesttable,
        string? wszartdesttableowner,
        string? wszartinscmd,
        int? cmdtypeins,
        string? wszartdelcmd,
        int? cmdtypedel,
        string? wszartupdcmd,
        int? cmdtypeupd,
        string? wszartpartialupdcmd,
        int? cmdtypepartialupd,
        int? numcol,
        byte? artcmdtype,
        string? artgeninscmd,
        string? artgendelcmd,
        string? artgenupdcmd,
        string? artpartialupdcmd,
        string? artupdtxtcmd,
        string? artgenins2cmd,
        string? artgendel2cmd,
        byte? finreconcile,
        byte? fpuballowupdate,
        int? intpublicationoptions)
    {
        _artcacheDbAddress = artcacheDbAddress;
        _artcacheTableAddress = artcacheTableAddress;
        _artcacheSchemaAddress = artcacheSchemaAddress;
        _artcacheArticleAddress = artcacheArticleAddress;
        _artid = artid;
        _artfilter = artfilter;
        _artobjid = artobjid;
        _artpubid = artpubid;
        _artstatus = artstatus;
        _arttype = arttype;
        _wszartdesttable = wszartdesttable;
        _wszartdesttableowner = wszartdesttableowner;
        _wszartinscmd = wszartinscmd;
        _cmdtypeins = cmdtypeins;
        _wszartdelcmd = wszartdelcmd;
        _cmdtypedel = cmdtypedel;
        _wszartupdcmd = wszartupdcmd;
        _cmdtypeupd = cmdtypeupd;
        _wszartpartialupdcmd = wszartpartialupdcmd;
        _cmdtypepartialupd = cmdtypepartialupd;
        _numcol = numcol;
        _artcmdtype = artcmdtype;
        _artgeninscmd = artgeninscmd;
        _artgendelcmd = artgendelcmd;
        _artgenupdcmd = artgenupdcmd;
        _artpartialupdcmd = artpartialupdcmd;
        _artupdtxtcmd = artupdtxtcmd;
        _artgenins2cmd = artgenins2cmd;
        _artgendel2cmd = artgendel2cmd;
        _finreconcile = finreconcile;
        _fpuballowupdate = fpuballowupdate;
        _intpublicationoptions = intpublicationoptions;
    }

    public byte[]? ArtcacheDbAddress => _artcacheDbAddress;
    public byte[]? ArtcacheTableAddress => _artcacheTableAddress;
    public byte[]? ArtcacheSchemaAddress => _artcacheSchemaAddress;
    public byte[]? ArtcacheArticleAddress => _artcacheArticleAddress;
    public int? Artid => _artid;
    public int? Artfilter => _artfilter;
    public int? Artobjid => _artobjid;
    public int? Artpubid => _artpubid;
    public byte? Artstatus => _artstatus;
    public byte? Arttype => _arttype;
    public string? Wszartdesttable => _wszartdesttable;
    public string? Wszartdesttableowner => _wszartdesttableowner;
    public string? Wszartinscmd => _wszartinscmd;
    public int? Cmdtypeins => _cmdtypeins;
    public string? Wszartdelcmd => _wszartdelcmd;
    public int? Cmdtypedel => _cmdtypedel;
    public string? Wszartupdcmd => _wszartupdcmd;
    public int? Cmdtypeupd => _cmdtypeupd;
    public string? Wszartpartialupdcmd => _wszartpartialupdcmd;
    public int? Cmdtypepartialupd => _cmdtypepartialupd;
    public int? Numcol => _numcol;
    public byte? Artcmdtype => _artcmdtype;
    public string? Artgeninscmd => _artgeninscmd;
    public string? Artgendelcmd => _artgendelcmd;
    public string? Artgenupdcmd => _artgenupdcmd;
    public string? Artpartialupdcmd => _artpartialupdcmd;
    public string? Artupdtxtcmd => _artupdtxtcmd;
    public string? Artgenins2cmd => _artgenins2cmd;
    public string? Artgendel2cmd => _artgendel2cmd;
    public byte? Finreconcile => _finreconcile;
    public byte? Fpuballowupdate => _fpuballowupdate;
    public int? Intpublicationoptions => _intpublicationoptions;
}
