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

public class DmHadrNameIdMapReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_name_id_map]";
    public const string TableName = "dm_hadr_name_id_map";
    public const string ShortName = "dhnim";
    public const string Sql = """
        SELECT
          dhnim.[ag_name],
          dhnim.[ag_id],
          dhnim.[ag_resource_id],
          dhnim.[ag_group_id]
        FROM
          [sys].[dm_hadr_name_id_map] dhnim
        """;

    public const int AGNAME_FIELD_ID = 0;
    public const int AGID_FIELD_ID = 1;
    public const int AGRESOURCEID_FIELD_ID = 2;
    public const int AGGROUPID_FIELD_ID = 3;


    public DmHadrNameIdMapReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrNameIdMapReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrNameIdMapReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string AgName
    {
        get
        {
            return base.GetString(AGNAME_FIELD_ID);
        }
    }

    public Guid AgId
    {
        get
        {
            return base.GetGuid(AGID_FIELD_ID);
        }
    }

    public string AgResourceId
    {
        get
        {
            return base.GetString(AGRESOURCEID_FIELD_ID);
        }
    }

    public string AgGroupId
    {
        get
        {
            return base.GetString(AGGROUPID_FIELD_ID);
        }
    }


    public Types.DmHadrNameIdMapDataType ToDataObject()
    {
        return new Types.DmHadrNameIdMapDataType(AgName,
            AgId,
            AgResourceId,
            AgGroupId);
    }

    public List<Types.DmHadrNameIdMapDataType> ToList()
    {
        var list = new List<Types.DmHadrNameIdMapDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
