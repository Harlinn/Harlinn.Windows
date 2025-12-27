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

public class RemoteDataArchiveDatabasesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[remote_data_archive_databases]";
    public const string TableName = "remote_data_archive_databases";
    public const string ShortName = "rdad";
    public const string Sql = """
        SELECT
          rdad.[remote_database_id],
          rdad.[remote_database_name],
          rdad.[data_source_id],
          rdad.[federated_service_account]
        FROM
          [sys].[remote_data_archive_databases] rdad
        """;

    public const int REMOTEDATABASEID_FIELD_ID = 0;
    public const int REMOTEDATABASENAME_FIELD_ID = 1;
    public const int DATASOURCEID_FIELD_ID = 2;
    public const int FEDERATEDSERVICEACCOUNT_FIELD_ID = 3;


    public RemoteDataArchiveDatabasesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public RemoteDataArchiveDatabasesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public RemoteDataArchiveDatabasesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int RemoteDatabaseId
    {
        get
        {
            return base.GetInt32(REMOTEDATABASEID_FIELD_ID);
        }
    }

    public string RemoteDatabaseName
    {
        get
        {
            return base.GetString(REMOTEDATABASENAME_FIELD_ID);
        }
    }

    public int DataSourceId
    {
        get
        {
            return base.GetInt32(DATASOURCEID_FIELD_ID);
        }
    }

    public bool? FederatedServiceAccount
    {
        get
        {
            return base.GetNullableBoolean(FEDERATEDSERVICEACCOUNT_FIELD_ID);
        }
    }


    public Types.RemoteDataArchiveDatabasesDataType ToDataObject()
    {
        return new Types.RemoteDataArchiveDatabasesDataType(RemoteDatabaseId,
            RemoteDatabaseName,
            DataSourceId,
            FederatedServiceAccount);
    }

    public List<Types.RemoteDataArchiveDatabasesDataType> ToList()
    {
        var list = new List<Types.RemoteDataArchiveDatabasesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
