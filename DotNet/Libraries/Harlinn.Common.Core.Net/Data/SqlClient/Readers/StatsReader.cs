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

public class StatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[stats]";
    public const string TableName = "stats";
    public const string ShortName = "s4";
    public const string Sql = """
        SELECT
          s4.[object_id],
          s4.[Name],
          s4.[stats_id],
          s4.[auto_created],
          s4.[user_created],
          s4.[no_recompute],
          s4.[has_filter],
          s4.[filter_definition],
          s4.[is_temporary],
          s4.[is_incremental],
          s4.[has_persisted_sample],
          s4.[stats_generation_method],
          s4.[stats_generation_method_desc]
        FROM
          [sys].[stats] s4
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int STATSID_FIELD_ID = 2;
    public const int AUTOCREATED_FIELD_ID = 3;
    public const int USERCREATED_FIELD_ID = 4;
    public const int NORECOMPUTE_FIELD_ID = 5;
    public const int HASFILTER_FIELD_ID = 6;
    public const int FILTERDEFINITION_FIELD_ID = 7;
    public const int ISTEMPORARY_FIELD_ID = 8;
    public const int ISINCREMENTAL_FIELD_ID = 9;
    public const int HASPERSISTEDSAMPLE_FIELD_ID = 10;
    public const int STATSGENERATIONMETHOD_FIELD_ID = 11;
    public const int STATSGENERATIONMETHODDESC_FIELD_ID = 12;


    public StatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public StatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public StatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public int StatsId
    {
        get
        {
            return base.GetInt32(STATSID_FIELD_ID);
        }
    }

    public bool? AutoCreated
    {
        get
        {
            return base.GetNullableBoolean(AUTOCREATED_FIELD_ID);
        }
    }

    public bool? UserCreated
    {
        get
        {
            return base.GetNullableBoolean(USERCREATED_FIELD_ID);
        }
    }

    public bool? NoRecompute
    {
        get
        {
            return base.GetNullableBoolean(NORECOMPUTE_FIELD_ID);
        }
    }

    public bool? HasFilter
    {
        get
        {
            return base.GetNullableBoolean(HASFILTER_FIELD_ID);
        }
    }

    public string? FilterDefinition
    {
        get
        {
            return base.GetNullableString(FILTERDEFINITION_FIELD_ID);
        }
    }

    public bool? IsTemporary
    {
        get
        {
            return base.GetNullableBoolean(ISTEMPORARY_FIELD_ID);
        }
    }

    public bool? IsIncremental
    {
        get
        {
            return base.GetNullableBoolean(ISINCREMENTAL_FIELD_ID);
        }
    }

    public bool? HasPersistedSample
    {
        get
        {
            return base.GetNullableBoolean(HASPERSISTEDSAMPLE_FIELD_ID);
        }
    }

    public int StatsGenerationMethod
    {
        get
        {
            return base.GetInt32(STATSGENERATIONMETHOD_FIELD_ID);
        }
    }

    public string StatsGenerationMethodDesc
    {
        get
        {
            return base.GetString(STATSGENERATIONMETHODDESC_FIELD_ID);
        }
    }


    public Types.StatsDataType ToDataObject()
    {
        return new Types.StatsDataType(ObjectId,
            Name,
            StatsId,
            AutoCreated,
            UserCreated,
            NoRecompute,
            HasFilter,
            FilterDefinition,
            IsTemporary,
            IsIncremental,
            HasPersistedSample,
            StatsGenerationMethod,
            StatsGenerationMethodDesc);
    }

    public List<Types.StatsDataType> ToList()
    {
        var list = new List<Types.StatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
