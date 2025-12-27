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

public class HashIndexesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[hash_indexes]";
    public const string TableName = "hash_indexes";
    public const string ShortName = "hi";
    public const string Sql = """
        SELECT
          hi.[object_id],
          hi.[Name],
          hi.[index_id],
          hi.[Type],
          hi.[type_desc],
          hi.[is_unique],
          hi.[data_space_id],
          hi.[ignore_dup_key],
          hi.[is_primary_key],
          hi.[is_unique_constraint],
          hi.[fill_factor],
          hi.[is_padded],
          hi.[is_disabled],
          hi.[is_hypothetical],
          hi.[is_ignored_in_optimization],
          hi.[allow_row_locks],
          hi.[allow_page_locks],
          hi.[has_filter],
          hi.[filter_definition],
          hi.[bucket_count],
          hi.[auto_created]
        FROM
          [sys].[hash_indexes] hi
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int TYPE_FIELD_ID = 3;
    public const int TYPEDESC_FIELD_ID = 4;
    public const int ISUNIQUE_FIELD_ID = 5;
    public const int DATASPACEID_FIELD_ID = 6;
    public const int IGNOREDUPKEY_FIELD_ID = 7;
    public const int ISPRIMARYKEY_FIELD_ID = 8;
    public const int ISUNIQUECONSTRAINT_FIELD_ID = 9;
    public const int FILLFACTOR_FIELD_ID = 10;
    public const int ISPADDED_FIELD_ID = 11;
    public const int ISDISABLED_FIELD_ID = 12;
    public const int ISHYPOTHETICAL_FIELD_ID = 13;
    public const int ISIGNOREDINOPTIMIZATION_FIELD_ID = 14;
    public const int ALLOWROWLOCKS_FIELD_ID = 15;
    public const int ALLOWPAGELOCKS_FIELD_ID = 16;
    public const int HASFILTER_FIELD_ID = 17;
    public const int FILTERDEFINITION_FIELD_ID = 18;
    public const int BUCKETCOUNT_FIELD_ID = 19;
    public const int AUTOCREATED_FIELD_ID = 20;


    public HashIndexesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public HashIndexesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public HashIndexesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public byte Type
    {
        get
        {
            return base.GetByte(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public bool? IsUnique
    {
        get
        {
            return base.GetNullableBoolean(ISUNIQUE_FIELD_ID);
        }
    }

    public int DataSpaceId
    {
        get
        {
            return base.GetInt32(DATASPACEID_FIELD_ID);
        }
    }

    public bool? IgnoreDupKey
    {
        get
        {
            return base.GetNullableBoolean(IGNOREDUPKEY_FIELD_ID);
        }
    }

    public bool? IsPrimaryKey
    {
        get
        {
            return base.GetNullableBoolean(ISPRIMARYKEY_FIELD_ID);
        }
    }

    public bool? IsUniqueConstraint
    {
        get
        {
            return base.GetNullableBoolean(ISUNIQUECONSTRAINT_FIELD_ID);
        }
    }

    public byte FillFactor
    {
        get
        {
            return base.GetByte(FILLFACTOR_FIELD_ID);
        }
    }

    public bool? IsPadded
    {
        get
        {
            return base.GetNullableBoolean(ISPADDED_FIELD_ID);
        }
    }

    public bool? IsDisabled
    {
        get
        {
            return base.GetNullableBoolean(ISDISABLED_FIELD_ID);
        }
    }

    public bool? IsHypothetical
    {
        get
        {
            return base.GetNullableBoolean(ISHYPOTHETICAL_FIELD_ID);
        }
    }

    public bool? IsIgnoredInOptimization
    {
        get
        {
            return base.GetNullableBoolean(ISIGNOREDINOPTIMIZATION_FIELD_ID);
        }
    }

    public bool? AllowRowLocks
    {
        get
        {
            return base.GetNullableBoolean(ALLOWROWLOCKS_FIELD_ID);
        }
    }

    public bool? AllowPageLocks
    {
        get
        {
            return base.GetNullableBoolean(ALLOWPAGELOCKS_FIELD_ID);
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

    public int BucketCount
    {
        get
        {
            return base.GetInt32(BUCKETCOUNT_FIELD_ID);
        }
    }

    public bool? AutoCreated
    {
        get
        {
            return base.GetNullableBoolean(AUTOCREATED_FIELD_ID);
        }
    }


    public Types.HashIndexesDataType ToDataObject()
    {
        return new Types.HashIndexesDataType(ObjectId,
            Name,
            IndexId,
            Type,
            TypeDesc,
            IsUnique,
            DataSpaceId,
            IgnoreDupKey,
            IsPrimaryKey,
            IsUniqueConstraint,
            FillFactor,
            IsPadded,
            IsDisabled,
            IsHypothetical,
            IsIgnoredInOptimization,
            AllowRowLocks,
            AllowPageLocks,
            HasFilter,
            FilterDefinition,
            BucketCount,
            AutoCreated);
    }

    public List<Types.HashIndexesDataType> ToList()
    {
        var list = new List<Types.HashIndexesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
