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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class ServersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[servers]";
    public const string TableName = "servers";
    public const string ShortName = "s5";
    public const string Sql = """
        SELECT
          s5.[server_id],
          s5.[Name],
          s5.[Product],
          s5.[Provider],
          s5.[data_source],
          s5.[Location],
          s5.[provider_string],
          s5.[Catalog],
          s5.[connect_timeout],
          s5.[query_timeout],
          s5.[is_linked],
          s5.[is_remote_login_enabled],
          s5.[is_rpc_out_enabled],
          s5.[is_data_access_enabled],
          s5.[is_collation_compatible],
          s5.[uses_remote_collation],
          s5.[collation_name],
          s5.[lazy_schema_validation],
          s5.[is_system],
          s5.[is_publisher],
          s5.[is_subscriber],
          s5.[is_distributor],
          s5.[is_nonsql_subscriber],
          s5.[is_remote_proc_transaction_promotion_enabled],
          s5.[modify_date],
          s5.[is_rda_server]
        FROM
          [sys].[servers] s5
        """;

    public const int SERVERID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int PRODUCT_FIELD_ID = 2;
    public const int PROVIDER_FIELD_ID = 3;
    public const int DATASOURCE_FIELD_ID = 4;
    public const int LOCATION_FIELD_ID = 5;
    public const int PROVIDERSTRING_FIELD_ID = 6;
    public const int CATALOG_FIELD_ID = 7;
    public const int CONNECTTIMEOUT_FIELD_ID = 8;
    public const int QUERYTIMEOUT_FIELD_ID = 9;
    public const int ISLINKED_FIELD_ID = 10;
    public const int ISREMOTELOGINENABLED_FIELD_ID = 11;
    public const int ISRPCOUTENABLED_FIELD_ID = 12;
    public const int ISDATAACCESSENABLED_FIELD_ID = 13;
    public const int ISCOLLATIONCOMPATIBLE_FIELD_ID = 14;
    public const int USESREMOTECOLLATION_FIELD_ID = 15;
    public const int COLLATIONNAME_FIELD_ID = 16;
    public const int LAZYSCHEMAVALIDATION_FIELD_ID = 17;
    public const int ISSYSTEM_FIELD_ID = 18;
    public const int ISPUBLISHER_FIELD_ID = 19;
    public const int ISSUBSCRIBER_FIELD_ID = 20;
    public const int ISDISTRIBUTOR_FIELD_ID = 21;
    public const int ISNONSQLSUBSCRIBER_FIELD_ID = 22;
    public const int ISREMOTEPROCTRANSACTIONPROMOTIONENABLED_FIELD_ID = 23;
    public const int MODIFYDATE_FIELD_ID = 24;
    public const int ISRDASERVER_FIELD_ID = 25;


    public ServersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ServerId
    {
        get
        {
            return base.GetInt32(SERVERID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string Product
    {
        get
        {
            return base.GetString(PRODUCT_FIELD_ID);
        }
    }

    public string Provider
    {
        get
        {
            return base.GetString(PROVIDER_FIELD_ID);
        }
    }

    public string? DataSource
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

    public string? ProviderString
    {
        get
        {
            return base.GetNullableString(PROVIDERSTRING_FIELD_ID);
        }
    }

    public string? Catalog
    {
        get
        {
            return base.GetNullableString(CATALOG_FIELD_ID);
        }
    }

    public int? ConnectTimeout
    {
        get
        {
            return base.GetNullableInt32(CONNECTTIMEOUT_FIELD_ID);
        }
    }

    public int? QueryTimeout
    {
        get
        {
            return base.GetNullableInt32(QUERYTIMEOUT_FIELD_ID);
        }
    }

    public bool IsLinked
    {
        get
        {
            return base.GetBoolean(ISLINKED_FIELD_ID);
        }
    }

    public bool IsRemoteLoginEnabled
    {
        get
        {
            return base.GetBoolean(ISREMOTELOGINENABLED_FIELD_ID);
        }
    }

    public bool IsRpcOutEnabled
    {
        get
        {
            return base.GetBoolean(ISRPCOUTENABLED_FIELD_ID);
        }
    }

    public bool IsDataAccessEnabled
    {
        get
        {
            return base.GetBoolean(ISDATAACCESSENABLED_FIELD_ID);
        }
    }

    public bool IsCollationCompatible
    {
        get
        {
            return base.GetBoolean(ISCOLLATIONCOMPATIBLE_FIELD_ID);
        }
    }

    public bool UsesRemoteCollation
    {
        get
        {
            return base.GetBoolean(USESREMOTECOLLATION_FIELD_ID);
        }
    }

    public string? CollationName
    {
        get
        {
            return base.GetNullableString(COLLATIONNAME_FIELD_ID);
        }
    }

    public bool LazySchemaValidation
    {
        get
        {
            return base.GetBoolean(LAZYSCHEMAVALIDATION_FIELD_ID);
        }
    }

    public bool IsSystem
    {
        get
        {
            return base.GetBoolean(ISSYSTEM_FIELD_ID);
        }
    }

    public bool IsPublisher
    {
        get
        {
            return base.GetBoolean(ISPUBLISHER_FIELD_ID);
        }
    }

    public bool? IsSubscriber
    {
        get
        {
            return base.GetNullableBoolean(ISSUBSCRIBER_FIELD_ID);
        }
    }

    public bool? IsDistributor
    {
        get
        {
            return base.GetNullableBoolean(ISDISTRIBUTOR_FIELD_ID);
        }
    }

    public bool? IsNonsqlSubscriber
    {
        get
        {
            return base.GetNullableBoolean(ISNONSQLSUBSCRIBER_FIELD_ID);
        }
    }

    public bool? IsRemoteProcTransactionPromotionEnabled
    {
        get
        {
            return base.GetNullableBoolean(ISREMOTEPROCTRANSACTIONPROMOTIONENABLED_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public bool? IsRdaServer
    {
        get
        {
            return base.GetNullableBoolean(ISRDASERVER_FIELD_ID);
        }
    }


    public Types.ServersDataType ToDataObject()
    {
        return new Types.ServersDataType(ServerId,
            Name,
            Product,
            Provider,
            DataSource,
            Location,
            ProviderString,
            Catalog,
            ConnectTimeout,
            QueryTimeout,
            IsLinked,
            IsRemoteLoginEnabled,
            IsRpcOutEnabled,
            IsDataAccessEnabled,
            IsCollationCompatible,
            UsesRemoteCollation,
            CollationName,
            LazySchemaValidation,
            IsSystem,
            IsPublisher,
            IsSubscriber,
            IsDistributor,
            IsNonsqlSubscriber,
            IsRemoteProcTransactionPromotionEnabled,
            ModifyDate,
            IsRdaServer);
    }

    public List<Types.ServersDataType> ToList()
    {
        var list = new List<Types.ServersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
