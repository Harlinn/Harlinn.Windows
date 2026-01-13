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

public class DmHadrClusterReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_cluster]";
    public const string TableName = "dm_hadr_cluster";
    public const string ShortName = "dhc";
    public const string Sql = """
        SELECT
          dhc.[cluster_name],
          dhc.[quorum_type],
          dhc.[quorum_type_desc],
          dhc.[quorum_state],
          dhc.[quorum_state_desc]
        FROM
          [sys].[dm_hadr_cluster] dhc
        """;

    public const int CLUSTERNAME_FIELD_ID = 0;
    public const int QUORUMTYPE_FIELD_ID = 1;
    public const int QUORUMTYPEDESC_FIELD_ID = 2;
    public const int QUORUMSTATE_FIELD_ID = 3;
    public const int QUORUMSTATEDESC_FIELD_ID = 4;


    public DmHadrClusterReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrClusterReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrClusterReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string ClusterName
    {
        get
        {
            return base.GetString(CLUSTERNAME_FIELD_ID);
        }
    }

    public byte QuorumType
    {
        get
        {
            return base.GetByte(QUORUMTYPE_FIELD_ID);
        }
    }

    public string QuorumTypeDesc
    {
        get
        {
            return base.GetString(QUORUMTYPEDESC_FIELD_ID);
        }
    }

    public byte QuorumState
    {
        get
        {
            return base.GetByte(QUORUMSTATE_FIELD_ID);
        }
    }

    public string QuorumStateDesc
    {
        get
        {
            return base.GetString(QUORUMSTATEDESC_FIELD_ID);
        }
    }


    public Types.DmHadrClusterDataType ToDataObject()
    {
        return new Types.DmHadrClusterDataType(ClusterName,
            QuorumType,
            QuorumTypeDesc,
            QuorumState,
            QuorumStateDesc);
    }

    public List<Types.DmHadrClusterDataType> ToList()
    {
        var list = new List<Types.DmHadrClusterDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
