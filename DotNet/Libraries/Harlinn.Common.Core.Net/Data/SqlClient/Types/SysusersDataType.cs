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

public class SysusersDataType
{
    readonly short? _uid;
    readonly short? _status;
    readonly string _name = string.Empty;
    readonly byte[]? _sid;
    readonly byte[]? _roles;
    readonly DateTime _createdate;
    readonly DateTime _updatedate;
    readonly short? _altuid;
    readonly byte[]? _password;
    readonly short? _gid;
    readonly string? _environ;
    readonly int? _hasdbaccess;
    readonly int? _islogin;
    readonly int? _isntname;
    readonly int? _isntgroup;
    readonly int? _isntuser;
    readonly int? _issqluser;
    readonly int? _isaliased;
    readonly int? _issqlrole;
    readonly int? _isapprole;

    public SysusersDataType( )
    {
    }

    public SysusersDataType(short? uid,
        short? status,
        string name,
        byte[]? sid,
        byte[]? roles,
        DateTime createdate,
        DateTime updatedate,
        short? altuid,
        byte[]? password,
        short? gid,
        string? environ,
        int? hasdbaccess,
        int? islogin,
        int? isntname,
        int? isntgroup,
        int? isntuser,
        int? issqluser,
        int? isaliased,
        int? issqlrole,
        int? isapprole)
    {
        _uid = uid;
        _status = status;
        _name = name;
        _sid = sid;
        _roles = roles;
        _createdate = createdate;
        _updatedate = updatedate;
        _altuid = altuid;
        _password = password;
        _gid = gid;
        _environ = environ;
        _hasdbaccess = hasdbaccess;
        _islogin = islogin;
        _isntname = isntname;
        _isntgroup = isntgroup;
        _isntuser = isntuser;
        _issqluser = issqluser;
        _isaliased = isaliased;
        _issqlrole = issqlrole;
        _isapprole = isapprole;
    }

    public short? Uid => _uid;
    public short? Status => _status;
    public string Name => _name;
    public byte[]? Sid => _sid;
    public byte[]? Roles => _roles;
    public DateTime Createdate => _createdate;
    public DateTime Updatedate => _updatedate;
    public short? Altuid => _altuid;
    public byte[]? Password => _password;
    public short? Gid => _gid;
    public string? Environ => _environ;
    public int? Hasdbaccess => _hasdbaccess;
    public int? Islogin => _islogin;
    public int? Isntname => _isntname;
    public int? Isntgroup => _isntgroup;
    public int? Isntuser => _isntuser;
    public int? Issqluser => _issqluser;
    public int? Isaliased => _isaliased;
    public int? Issqlrole => _issqlrole;
    public int? Isapprole => _isapprole;
}
