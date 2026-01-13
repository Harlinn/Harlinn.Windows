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

public class SysloginsDataType
{
    readonly byte[]? _sid;
    readonly short? _status;
    readonly DateTime _createdate;
    readonly DateTime _updatedate;
    readonly DateTime _accdate;
    readonly int? _totcpu;
    readonly int? _totio;
    readonly int? _spacelimit;
    readonly int? _timelimit;
    readonly int? _resultlimit;
    readonly string _name = string.Empty;
    readonly string? _dbname;
    readonly string? _password;
    readonly string? _language;
    readonly int? _denylogin;
    readonly int? _hasaccess;
    readonly int? _isntname;
    readonly int? _isntgroup;
    readonly int? _isntuser;
    readonly int? _sysadmin;
    readonly int? _securityadmin;
    readonly int? _serveradmin;
    readonly int? _setupadmin;
    readonly int? _processadmin;
    readonly int? _diskadmin;
    readonly int? _dbcreator;
    readonly int? _bulkadmin;
    readonly string _loginname = string.Empty;

    public SysloginsDataType( )
    {
    }

    public SysloginsDataType(byte[]? sid,
        short? status,
        DateTime createdate,
        DateTime updatedate,
        DateTime accdate,
        int? totcpu,
        int? totio,
        int? spacelimit,
        int? timelimit,
        int? resultlimit,
        string name,
        string? dbname,
        string? password,
        string? language,
        int? denylogin,
        int? hasaccess,
        int? isntname,
        int? isntgroup,
        int? isntuser,
        int? sysadmin,
        int? securityadmin,
        int? serveradmin,
        int? setupadmin,
        int? processadmin,
        int? diskadmin,
        int? dbcreator,
        int? bulkadmin,
        string loginname)
    {
        _sid = sid;
        _status = status;
        _createdate = createdate;
        _updatedate = updatedate;
        _accdate = accdate;
        _totcpu = totcpu;
        _totio = totio;
        _spacelimit = spacelimit;
        _timelimit = timelimit;
        _resultlimit = resultlimit;
        _name = name;
        _dbname = dbname;
        _password = password;
        _language = language;
        _denylogin = denylogin;
        _hasaccess = hasaccess;
        _isntname = isntname;
        _isntgroup = isntgroup;
        _isntuser = isntuser;
        _sysadmin = sysadmin;
        _securityadmin = securityadmin;
        _serveradmin = serveradmin;
        _setupadmin = setupadmin;
        _processadmin = processadmin;
        _diskadmin = diskadmin;
        _dbcreator = dbcreator;
        _bulkadmin = bulkadmin;
        _loginname = loginname;
    }

    public byte[]? Sid => _sid;
    public short? Status => _status;
    public DateTime Createdate => _createdate;
    public DateTime Updatedate => _updatedate;
    public DateTime Accdate => _accdate;
    public int? Totcpu => _totcpu;
    public int? Totio => _totio;
    public int? Spacelimit => _spacelimit;
    public int? Timelimit => _timelimit;
    public int? Resultlimit => _resultlimit;
    public string Name => _name;
    public string? Dbname => _dbname;
    public string? Password => _password;
    public string? Language => _language;
    public int? Denylogin => _denylogin;
    public int? Hasaccess => _hasaccess;
    public int? Isntname => _isntname;
    public int? Isntgroup => _isntgroup;
    public int? Isntuser => _isntuser;
    public int? Sysadmin => _sysadmin;
    public int? Securityadmin => _securityadmin;
    public int? Serveradmin => _serveradmin;
    public int? Setupadmin => _setupadmin;
    public int? Processadmin => _processadmin;
    public int? Diskadmin => _diskadmin;
    public int? Dbcreator => _dbcreator;
    public int? Bulkadmin => _bulkadmin;
    public string Loginname => _loginname;
}
