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

public class SysobjectsDataType
{
    readonly string _name = string.Empty;
    readonly int _id = 0;
    readonly string _xtype = string.Empty;
    readonly short? _uid;
    readonly short? _info;
    readonly int? _status;
    readonly int? _baseSchemaVer;
    readonly int? _replinfo;
    readonly int _parentObj = 0;
    readonly DateTime _crdate;
    readonly short? _ftcatid;
    readonly int? _schemaVer;
    readonly int? _statsSchemaVer;
    readonly string? _type;
    readonly short? _userstat;
    readonly short? _sysstat;
    readonly short? _indexdel;
    readonly DateTime _refdate;
    readonly int? _version;
    readonly int? _deltrig;
    readonly int? _instrig;
    readonly int? _updtrig;
    readonly int? _seltrig;
    readonly int? _category;
    readonly short? _cache;

    public SysobjectsDataType( )
    {
    }

    public SysobjectsDataType(string name,
        int id,
        string xtype,
        short? uid,
        short? info,
        int? status,
        int? baseSchemaVer,
        int? replinfo,
        int parentObj,
        DateTime crdate,
        short? ftcatid,
        int? schemaVer,
        int? statsSchemaVer,
        string? type,
        short? userstat,
        short? sysstat,
        short? indexdel,
        DateTime refdate,
        int? version,
        int? deltrig,
        int? instrig,
        int? updtrig,
        int? seltrig,
        int? category,
        short? cache)
    {
        _name = name;
        _id = id;
        _xtype = xtype;
        _uid = uid;
        _info = info;
        _status = status;
        _baseSchemaVer = baseSchemaVer;
        _replinfo = replinfo;
        _parentObj = parentObj;
        _crdate = crdate;
        _ftcatid = ftcatid;
        _schemaVer = schemaVer;
        _statsSchemaVer = statsSchemaVer;
        _type = type;
        _userstat = userstat;
        _sysstat = sysstat;
        _indexdel = indexdel;
        _refdate = refdate;
        _version = version;
        _deltrig = deltrig;
        _instrig = instrig;
        _updtrig = updtrig;
        _seltrig = seltrig;
        _category = category;
        _cache = cache;
    }

    public string Name => _name;
    public int Id => _id;
    public string Xtype => _xtype;
    public short? Uid => _uid;
    public short? Info => _info;
    public int? Status => _status;
    public int? BaseSchemaVer => _baseSchemaVer;
    public int? Replinfo => _replinfo;
    public int ParentObj => _parentObj;
    public DateTime Crdate => _crdate;
    public short? Ftcatid => _ftcatid;
    public int? SchemaVer => _schemaVer;
    public int? StatsSchemaVer => _statsSchemaVer;
    public string? Type => _type;
    public short? Userstat => _userstat;
    public short? Sysstat => _sysstat;
    public short? Indexdel => _indexdel;
    public DateTime Refdate => _refdate;
    public int? Version => _version;
    public int? Deltrig => _deltrig;
    public int? Instrig => _instrig;
    public int? Updtrig => _updtrig;
    public int? Seltrig => _seltrig;
    public int? Category => _category;
    public short? Cache => _cache;
}
