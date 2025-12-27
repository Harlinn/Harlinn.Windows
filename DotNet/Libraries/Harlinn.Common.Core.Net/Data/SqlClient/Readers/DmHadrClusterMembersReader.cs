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

public class DmHadrClusterMembersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_cluster_members]";
    public const string TableName = "dm_hadr_cluster_members";
    public const string ShortName = "dhcm";
    public const string Sql = """
        SELECT
          dhcm.[member_name],
          dhcm.[member_type],
          dhcm.[member_type_desc],
          dhcm.[member_state],
          dhcm.[member_state_desc],
          dhcm.[number_of_quorum_votes]
        FROM
          [sys].[dm_hadr_cluster_members] dhcm
        """;

    public const int MEMBERNAME_FIELD_ID = 0;
    public const int MEMBERTYPE_FIELD_ID = 1;
    public const int MEMBERTYPEDESC_FIELD_ID = 2;
    public const int MEMBERSTATE_FIELD_ID = 3;
    public const int MEMBERSTATEDESC_FIELD_ID = 4;
    public const int NUMBEROFQUORUMVOTES_FIELD_ID = 5;


    public DmHadrClusterMembersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrClusterMembersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrClusterMembersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string MemberName
    {
        get
        {
            return base.GetString(MEMBERNAME_FIELD_ID);
        }
    }

    public byte MemberType
    {
        get
        {
            return base.GetByte(MEMBERTYPE_FIELD_ID);
        }
    }

    public string MemberTypeDesc
    {
        get
        {
            return base.GetString(MEMBERTYPEDESC_FIELD_ID);
        }
    }

    public byte MemberState
    {
        get
        {
            return base.GetByte(MEMBERSTATE_FIELD_ID);
        }
    }

    public string MemberStateDesc
    {
        get
        {
            return base.GetString(MEMBERSTATEDESC_FIELD_ID);
        }
    }

    public int? NumberOfQuorumVotes
    {
        get
        {
            return base.GetNullableInt32(NUMBEROFQUORUMVOTES_FIELD_ID);
        }
    }


    public Types.DmHadrClusterMembersDataType ToDataObject()
    {
        return new Types.DmHadrClusterMembersDataType(MemberName,
            MemberType,
            MemberTypeDesc,
            MemberState,
            MemberStateDesc,
            NumberOfQuorumVotes);
    }

    public List<Types.DmHadrClusterMembersDataType> ToList()
    {
        var list = new List<Types.DmHadrClusterMembersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
