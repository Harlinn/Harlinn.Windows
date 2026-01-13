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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class SysserversReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysservers]";
    public const string TableName = "sysservers";
    public const string ShortName = "s6";
    public const string Sql = """
        SELECT
          s6.[Srvid],
          s6.[Srvstatus],
          s6.[Srvname],
          s6.[Srvproduct],
          s6.[Providername],
          s6.[Datasource],
          s6.[Location],
          s6.[Providerstring],
          s6.[Schemadate],
          s6.[Topologyx],
          s6.[Topologyy],
          s6.[Catalog],
          s6.[Srvcollation],
          s6.[Connecttimeout],
          s6.[Querytimeout],
          s6.[Srvnetname],
          s6.[Isremote],
          s6.[Rpc],
          s6.[Pub],
          s6.[Sub],
          s6.[Dist],
          s6.[Dpub],
          s6.[Rpcout],
          s6.[Dataaccess],
          s6.[Collationcompatible],
          s6.[System],
          s6.[Useremotecollation],
          s6.[Lazyschemavalidation],
          s6.[Collation],
          s6.[Nonsqlsub]
        FROM
          [sys].[sysservers] s6
        """;

    public const int SRVID_FIELD_ID = 0;
    public const int SRVSTATUS_FIELD_ID = 1;
    public const int SRVNAME_FIELD_ID = 2;
    public const int SRVPRODUCT_FIELD_ID = 3;
    public const int PROVIDERNAME_FIELD_ID = 4;
    public const int DATASOURCE_FIELD_ID = 5;
    public const int LOCATION_FIELD_ID = 6;
    public const int PROVIDERSTRING_FIELD_ID = 7;
    public const int SCHEMADATE_FIELD_ID = 8;
    public const int TOPOLOGYX_FIELD_ID = 9;
    public const int TOPOLOGYY_FIELD_ID = 10;
    public const int CATALOG_FIELD_ID = 11;
    public const int SRVCOLLATION_FIELD_ID = 12;
    public const int CONNECTTIMEOUT_FIELD_ID = 13;
    public const int QUERYTIMEOUT_FIELD_ID = 14;
    public const int SRVNETNAME_FIELD_ID = 15;
    public const int ISREMOTE_FIELD_ID = 16;
    public const int RPC_FIELD_ID = 17;
    public const int PUB_FIELD_ID = 18;
    public const int SUB_FIELD_ID = 19;
    public const int DIST_FIELD_ID = 20;
    public const int DPUB_FIELD_ID = 21;
    public const int RPCOUT_FIELD_ID = 22;
    public const int DATAACCESS_FIELD_ID = 23;
    public const int COLLATIONCOMPATIBLE_FIELD_ID = 24;
    public const int SYSTEM_FIELD_ID = 25;
    public const int USEREMOTECOLLATION_FIELD_ID = 26;
    public const int LAZYSCHEMAVALIDATION_FIELD_ID = 27;
    public const int COLLATION_FIELD_ID = 28;
    public const int NONSQLSUB_FIELD_ID = 29;


    public SysserversReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysserversReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysserversReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? Srvid
    {
        get
        {
            return base.GetNullableInt16(SRVID_FIELD_ID);
        }
    }

    public short? Srvstatus
    {
        get
        {
            return base.GetNullableInt16(SRVSTATUS_FIELD_ID);
        }
    }

    public string Srvname
    {
        get
        {
            return base.GetString(SRVNAME_FIELD_ID);
        }
    }

    public string Srvproduct
    {
        get
        {
            return base.GetString(SRVPRODUCT_FIELD_ID);
        }
    }

    public string Providername
    {
        get
        {
            return base.GetString(PROVIDERNAME_FIELD_ID);
        }
    }

    public string? Datasource
    {
        get
        {
            return base.GetNullableString(DATASOURCE_FIELD_ID);
        }
    }

    public string? Location
    {
        get
        {
            return base.GetNullableString(LOCATION_FIELD_ID);
        }
    }

    public string? Providerstring
    {
        get
        {
            return base.GetNullableString(PROVIDERSTRING_FIELD_ID);
        }
    }

    public DateTime Schemadate
    {
        get
        {
            return base.GetDateTime(SCHEMADATE_FIELD_ID);
        }
    }

    public int? Topologyx
    {
        get
        {
            return base.GetNullableInt32(TOPOLOGYX_FIELD_ID);
        }
    }

    public int? Topologyy
    {
        get
        {
            return base.GetNullableInt32(TOPOLOGYY_FIELD_ID);
        }
    }

    public string? Catalog
    {
        get
        {
            return base.GetNullableString(CATALOG_FIELD_ID);
        }
    }

    public string? Srvcollation
    {
        get
        {
            return base.GetNullableString(SRVCOLLATION_FIELD_ID);
        }
    }

    public int? Connecttimeout
    {
        get
        {
            return base.GetNullableInt32(CONNECTTIMEOUT_FIELD_ID);
        }
    }

    public int? Querytimeout
    {
        get
        {
            return base.GetNullableInt32(QUERYTIMEOUT_FIELD_ID);
        }
    }

    public string? Srvnetname
    {
        get
        {
            return base.GetNullableString(SRVNETNAME_FIELD_ID);
        }
    }

    public bool? Isremote
    {
        get
        {
            return base.GetNullableBoolean(ISREMOTE_FIELD_ID);
        }
    }

    public bool Rpc
    {
        get
        {
            return base.GetBoolean(RPC_FIELD_ID);
        }
    }

    public bool Pub
    {
        get
        {
            return base.GetBoolean(PUB_FIELD_ID);
        }
    }

    public bool? Sub
    {
        get
        {
            return base.GetNullableBoolean(SUB_FIELD_ID);
        }
    }

    public bool? Dist
    {
        get
        {
            return base.GetNullableBoolean(DIST_FIELD_ID);
        }
    }

    public bool? Dpub
    {
        get
        {
            return base.GetNullableBoolean(DPUB_FIELD_ID);
        }
    }

    public bool Rpcout
    {
        get
        {
            return base.GetBoolean(RPCOUT_FIELD_ID);
        }
    }

    public bool Dataaccess
    {
        get
        {
            return base.GetBoolean(DATAACCESS_FIELD_ID);
        }
    }

    public bool Collationcompatible
    {
        get
        {
            return base.GetBoolean(COLLATIONCOMPATIBLE_FIELD_ID);
        }
    }

    public bool System
    {
        get
        {
            return base.GetBoolean(SYSTEM_FIELD_ID);
        }
    }

    public bool Useremotecollation
    {
        get
        {
            return base.GetBoolean(USEREMOTECOLLATION_FIELD_ID);
        }
    }

    public bool Lazyschemavalidation
    {
        get
        {
            return base.GetBoolean(LAZYSCHEMAVALIDATION_FIELD_ID);
        }
    }

    public string? Collation
    {
        get
        {
            return base.GetNullableString(COLLATION_FIELD_ID);
        }
    }

    public bool? Nonsqlsub
    {
        get
        {
            return base.GetNullableBoolean(NONSQLSUB_FIELD_ID);
        }
    }


    public Types.SysserversDataType ToDataObject()
    {
        return new Types.SysserversDataType(Srvid,
            Srvstatus,
            Srvname,
            Srvproduct,
            Providername,
            Datasource,
            Location,
            Providerstring,
            Schemadate,
            Topologyx,
            Topologyy,
            Catalog,
            Srvcollation,
            Connecttimeout,
            Querytimeout,
            Srvnetname,
            Isremote,
            Rpc,
            Pub,
            Sub,
            Dist,
            Dpub,
            Rpcout,
            Dataaccess,
            Collationcompatible,
            System,
            Useremotecollation,
            Lazyschemavalidation,
            Collation,
            Nonsqlsub);
    }

    public List<Types.SysserversDataType> ToList()
    {
        var list = new List<Types.SysserversDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
