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

public class SystemInternalsPartitionColumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[system_internals_partition_columns]";
    public const string TableName = "system_internals_partition_columns";
    public const string ShortName = "sipc";
    public const string Sql = """
        SELECT
          sipc.[partition_id],
          sipc.[partition_column_id],
          sipc.[modified_count],
          sipc.[max_inrow_length],
          sipc.[is_replicated],
          sipc.[is_logged_for_replication],
          sipc.[is_dropped],
          sipc.[system_type_id],
          sipc.[max_length],
          sipc.[Precision],
          sipc.[Scale],
          sipc.[collation_name],
          sipc.[is_filestream],
          sipc.[key_ordinal],
          sipc.[is_nullable],
          sipc.[is_descending_key],
          sipc.[is_uniqueifier],
          sipc.[leaf_offset],
          sipc.[internal_offset],
          sipc.[leaf_bit_position],
          sipc.[internal_bit_position],
          sipc.[leaf_null_bit],
          sipc.[internal_null_bit],
          sipc.[is_anti_matter],
          sipc.[partition_column_guid],
          sipc.[is_sparse],
          sipc.[has_default],
          sipc.[default_value]
        FROM
          [sys].[system_internals_partition_columns] sipc
        """;

    public const int PARTITIONID_FIELD_ID = 0;
    public const int PARTITIONCOLUMNID_FIELD_ID = 1;
    public const int MODIFIEDCOUNT_FIELD_ID = 2;
    public const int MAXINROWLENGTH_FIELD_ID = 3;
    public const int ISREPLICATED_FIELD_ID = 4;
    public const int ISLOGGEDFORREPLICATION_FIELD_ID = 5;
    public const int ISDROPPED_FIELD_ID = 6;
    public const int SYSTEMTYPEID_FIELD_ID = 7;
    public const int MAXLENGTH_FIELD_ID = 8;
    public const int PRECISION_FIELD_ID = 9;
    public const int SCALE_FIELD_ID = 10;
    public const int COLLATIONNAME_FIELD_ID = 11;
    public const int ISFILESTREAM_FIELD_ID = 12;
    public const int KEYORDINAL_FIELD_ID = 13;
    public const int ISNULLABLE_FIELD_ID = 14;
    public const int ISDESCENDINGKEY_FIELD_ID = 15;
    public const int ISUNIQUEIFIER_FIELD_ID = 16;
    public const int LEAFOFFSET_FIELD_ID = 17;
    public const int INTERNALOFFSET_FIELD_ID = 18;
    public const int LEAFBITPOSITION_FIELD_ID = 19;
    public const int INTERNALBITPOSITION_FIELD_ID = 20;
    public const int LEAFNULLBIT_FIELD_ID = 21;
    public const int INTERNALNULLBIT_FIELD_ID = 22;
    public const int ISANTIMATTER_FIELD_ID = 23;
    public const int PARTITIONCOLUMNGUID_FIELD_ID = 24;
    public const int ISSPARSE_FIELD_ID = 25;
    public const int HASDEFAULT_FIELD_ID = 26;
    public const int DEFAULTVALUE_FIELD_ID = 27;


    public SystemInternalsPartitionColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SystemInternalsPartitionColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SystemInternalsPartitionColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long PartitionId
    {
        get
        {
            return base.GetInt64(PARTITIONID_FIELD_ID);
        }
    }

    public int PartitionColumnId
    {
        get
        {
            return base.GetInt32(PARTITIONCOLUMNID_FIELD_ID);
        }
    }

    public long ModifiedCount
    {
        get
        {
            return base.GetInt64(MODIFIEDCOUNT_FIELD_ID);
        }
    }

    public short? MaxInrowLength
    {
        get
        {
            return base.GetNullableInt16(MAXINROWLENGTH_FIELD_ID);
        }
    }

    public bool? IsReplicated
    {
        get
        {
            return base.GetNullableBoolean(ISREPLICATED_FIELD_ID);
        }
    }

    public bool? IsLoggedForReplication
    {
        get
        {
            return base.GetNullableBoolean(ISLOGGEDFORREPLICATION_FIELD_ID);
        }
    }

    public bool? IsDropped
    {
        get
        {
            return base.GetNullableBoolean(ISDROPPED_FIELD_ID);
        }
    }

    public byte? SystemTypeId
    {
        get
        {
            return base.GetNullableByte(SYSTEMTYPEID_FIELD_ID);
        }
    }

    public short? MaxLength
    {
        get
        {
            return base.GetNullableInt16(MAXLENGTH_FIELD_ID);
        }
    }

    public byte? Precision
    {
        get
        {
            return base.GetNullableByte(PRECISION_FIELD_ID);
        }
    }

    public byte? Scale
    {
        get
        {
            return base.GetNullableByte(SCALE_FIELD_ID);
        }
    }

    public string? CollationName
    {
        get
        {
            return base.GetNullableString(COLLATIONNAME_FIELD_ID);
        }
    }

    public bool? IsFilestream
    {
        get
        {
            return base.GetNullableBoolean(ISFILESTREAM_FIELD_ID);
        }
    }

    public short KeyOrdinal
    {
        get
        {
            return base.GetInt16(KEYORDINAL_FIELD_ID);
        }
    }

    public bool? IsNullable
    {
        get
        {
            return base.GetNullableBoolean(ISNULLABLE_FIELD_ID);
        }
    }

    public bool? IsDescendingKey
    {
        get
        {
            return base.GetNullableBoolean(ISDESCENDINGKEY_FIELD_ID);
        }
    }

    public bool? IsUniqueifier
    {
        get
        {
            return base.GetNullableBoolean(ISUNIQUEIFIER_FIELD_ID);
        }
    }

    public short? LeafOffset
    {
        get
        {
            return base.GetNullableInt16(LEAFOFFSET_FIELD_ID);
        }
    }

    public short? InternalOffset
    {
        get
        {
            return base.GetNullableInt16(INTERNALOFFSET_FIELD_ID);
        }
    }

    public byte? LeafBitPosition
    {
        get
        {
            return base.GetNullableByte(LEAFBITPOSITION_FIELD_ID);
        }
    }

    public byte? InternalBitPosition
    {
        get
        {
            return base.GetNullableByte(INTERNALBITPOSITION_FIELD_ID);
        }
    }

    public short? LeafNullBit
    {
        get
        {
            return base.GetNullableInt16(LEAFNULLBIT_FIELD_ID);
        }
    }

    public short? InternalNullBit
    {
        get
        {
            return base.GetNullableInt16(INTERNALNULLBIT_FIELD_ID);
        }
    }

    public bool? IsAntiMatter
    {
        get
        {
            return base.GetNullableBoolean(ISANTIMATTER_FIELD_ID);
        }
    }

    public Guid? PartitionColumnGuid
    {
        get
        {
            return base.GetNullableGuid(PARTITIONCOLUMNGUID_FIELD_ID);
        }
    }

    public bool? IsSparse
    {
        get
        {
            return base.GetNullableBoolean(ISSPARSE_FIELD_ID);
        }
    }

    public bool HasDefault
    {
        get
        {
            return base.GetBoolean(HASDEFAULT_FIELD_ID);
        }
    }

    public object? DefaultValue
    {
        get
        {
            return base.GetNullableValue(DEFAULTVALUE_FIELD_ID);
        }
    }


    public Types.SystemInternalsPartitionColumn ToDataObject()
    {
        return new Types.SystemInternalsPartitionColumn(PartitionId,
            PartitionColumnId,
            ModifiedCount,
            MaxInrowLength,
            IsReplicated,
            IsLoggedForReplication,
            IsDropped,
            SystemTypeId,
            MaxLength,
            Precision,
            Scale,
            CollationName,
            IsFilestream,
            KeyOrdinal,
            IsNullable,
            IsDescendingKey,
            IsUniqueifier,
            LeafOffset,
            InternalOffset,
            LeafBitPosition,
            InternalBitPosition,
            LeafNullBit,
            InternalNullBit,
            IsAntiMatter,
            PartitionColumnGuid,
            IsSparse,
            HasDefault,
            DefaultValue);
    }

    public List<Types.SystemInternalsPartitionColumn> ToList()
    {
        var list = new List<Types.SystemInternalsPartitionColumn>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
