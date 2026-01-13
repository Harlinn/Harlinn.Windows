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

public class SyscacheobjectsDataType
{
    readonly int _bucketid = 0;
    readonly string _cacheobjtype = string.Empty;
    readonly string _objtype = string.Empty;
    readonly int? _objid;
    readonly short? _dbid;
    readonly short? _dbidexec;
    readonly short? _uid;
    readonly int _refcounts = 0;
    readonly int _usecounts = 0;
    readonly int? _pagesused;
    readonly int? _setopts;
    readonly short? _langid;
    readonly short? _dateformat;
    readonly int? _status;
    readonly long? _lasttime;
    readonly long? _maxexectime;
    readonly long? _avgexectime;
    readonly long? _lastreads;
    readonly long? _lastwrites;
    readonly int? _sqlbytes;
    readonly string? _sql;

    public SyscacheobjectsDataType( )
    {
    }

    public SyscacheobjectsDataType(int bucketid,
        string cacheobjtype,
        string objtype,
        int? objid,
        short? dbid,
        short? dbidexec,
        short? uid,
        int refcounts,
        int usecounts,
        int? pagesused,
        int? setopts,
        short? langid,
        short? dateformat,
        int? status,
        long? lasttime,
        long? maxexectime,
        long? avgexectime,
        long? lastreads,
        long? lastwrites,
        int? sqlbytes,
        string? sql)
    {
        _bucketid = bucketid;
        _cacheobjtype = cacheobjtype;
        _objtype = objtype;
        _objid = objid;
        _dbid = dbid;
        _dbidexec = dbidexec;
        _uid = uid;
        _refcounts = refcounts;
        _usecounts = usecounts;
        _pagesused = pagesused;
        _setopts = setopts;
        _langid = langid;
        _dateformat = dateformat;
        _status = status;
        _lasttime = lasttime;
        _maxexectime = maxexectime;
        _avgexectime = avgexectime;
        _lastreads = lastreads;
        _lastwrites = lastwrites;
        _sqlbytes = sqlbytes;
        _sql = sql;
    }

    public int Bucketid => _bucketid;
    public string Cacheobjtype => _cacheobjtype;
    public string Objtype => _objtype;
    public int? Objid => _objid;
    public short? Dbid => _dbid;
    public short? Dbidexec => _dbidexec;
    public short? Uid => _uid;
    public int Refcounts => _refcounts;
    public int Usecounts => _usecounts;
    public int? Pagesused => _pagesused;
    public int? Setopts => _setopts;
    public short? Langid => _langid;
    public short? Dateformat => _dateformat;
    public int? Status => _status;
    public long? Lasttime => _lasttime;
    public long? Maxexectime => _maxexectime;
    public long? Avgexectime => _avgexectime;
    public long? Lastreads => _lastreads;
    public long? Lastwrites => _lastwrites;
    public int? Sqlbytes => _sqlbytes;
    public string? Sql => _sql;
}
