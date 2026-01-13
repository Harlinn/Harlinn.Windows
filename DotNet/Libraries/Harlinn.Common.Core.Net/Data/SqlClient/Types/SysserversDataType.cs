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

public class SysserversDataType
{
    readonly short? _srvid;
    readonly short? _srvstatus;
    readonly string _srvname = string.Empty;
    readonly string _srvproduct = string.Empty;
    readonly string _providername = string.Empty;
    readonly string? _datasource;
    readonly string? _location;
    readonly string? _providerstring;
    readonly DateTime _schemadate;
    readonly int? _topologyx;
    readonly int? _topologyy;
    readonly string? _catalog;
    readonly string? _srvcollation;
    readonly int? _connecttimeout;
    readonly int? _querytimeout;
    readonly string? _srvnetname;
    readonly bool? _isremote;
    readonly bool _rpc = false;
    readonly bool _pub = false;
    readonly bool? _sub;
    readonly bool? _dist;
    readonly bool? _dpub;
    readonly bool _rpcout = false;
    readonly bool _dataaccess = false;
    readonly bool _collationcompatible = false;
    readonly bool _system = false;
    readonly bool _useremotecollation = false;
    readonly bool _lazyschemavalidation = false;
    readonly string? _collation;
    readonly bool? _nonsqlsub;

    public SysserversDataType( )
    {
    }

    public SysserversDataType(short? srvid,
        short? srvstatus,
        string srvname,
        string srvproduct,
        string providername,
        string? datasource,
        string? location,
        string? providerstring,
        DateTime schemadate,
        int? topologyx,
        int? topologyy,
        string? catalog,
        string? srvcollation,
        int? connecttimeout,
        int? querytimeout,
        string? srvnetname,
        bool? isremote,
        bool rpc,
        bool pub,
        bool? sub,
        bool? dist,
        bool? dpub,
        bool rpcout,
        bool dataaccess,
        bool collationcompatible,
        bool system,
        bool useremotecollation,
        bool lazyschemavalidation,
        string? collation,
        bool? nonsqlsub)
    {
        _srvid = srvid;
        _srvstatus = srvstatus;
        _srvname = srvname;
        _srvproduct = srvproduct;
        _providername = providername;
        _datasource = datasource;
        _location = location;
        _providerstring = providerstring;
        _schemadate = schemadate;
        _topologyx = topologyx;
        _topologyy = topologyy;
        _catalog = catalog;
        _srvcollation = srvcollation;
        _connecttimeout = connecttimeout;
        _querytimeout = querytimeout;
        _srvnetname = srvnetname;
        _isremote = isremote;
        _rpc = rpc;
        _pub = pub;
        _sub = sub;
        _dist = dist;
        _dpub = dpub;
        _rpcout = rpcout;
        _dataaccess = dataaccess;
        _collationcompatible = collationcompatible;
        _system = system;
        _useremotecollation = useremotecollation;
        _lazyschemavalidation = lazyschemavalidation;
        _collation = collation;
        _nonsqlsub = nonsqlsub;
    }

    public short? Srvid => _srvid;
    public short? Srvstatus => _srvstatus;
    public string Srvname => _srvname;
    public string Srvproduct => _srvproduct;
    public string Providername => _providername;
    public string? Datasource => _datasource;
    public string? Location => _location;
    public string? Providerstring => _providerstring;
    public DateTime Schemadate => _schemadate;
    public int? Topologyx => _topologyx;
    public int? Topologyy => _topologyy;
    public string? Catalog => _catalog;
    public string? Srvcollation => _srvcollation;
    public int? Connecttimeout => _connecttimeout;
    public int? Querytimeout => _querytimeout;
    public string? Srvnetname => _srvnetname;
    public bool? Isremote => _isremote;
    public bool Rpc => _rpc;
    public bool Pub => _pub;
    public bool? Sub => _sub;
    public bool? Dist => _dist;
    public bool? Dpub => _dpub;
    public bool Rpcout => _rpcout;
    public bool Dataaccess => _dataaccess;
    public bool Collationcompatible => _collationcompatible;
    public bool System => _system;
    public bool Useremotecollation => _useremotecollation;
    public bool Lazyschemavalidation => _lazyschemavalidation;
    public string? Collation => _collation;
    public bool? Nonsqlsub => _nonsqlsub;
}
