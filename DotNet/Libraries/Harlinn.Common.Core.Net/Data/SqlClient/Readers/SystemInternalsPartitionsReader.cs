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

public class SystemInternalsPartitionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[system_internals_partitions]";
    public const string TableName = "system_internals_partitions";
    public const string ShortName = "sip";
    public const string Sql = """
        SELECT
          sip.[partition_id],
          sip.[object_id],
          sip.[index_id],
          sip.[partition_number],
          sip.[Rows],
          sip.[filestream_filegroup_id],
          sip.[is_orphaned],
          sip.[dropped_lob_column_state],
          sip.[is_unique],
          sip.[is_replicated],
          sip.[is_logged_for_replication],
          sip.[is_sereplicated],
          sip.[max_null_bit_used],
          sip.[max_leaf_length],
          sip.[min_leaf_length],
          sip.[max_internal_length],
          sip.[min_internal_length],
          sip.[allows_nullable_keys],
          sip.[allow_row_locks],
          sip.[allow_page_locks],
          sip.[is_data_row_format],
          sip.[is_not_versioned],
          sip.[filestream_guid],
          sip.[Ownertype],
          sip.[is_columnstore],
          sip.[optimize_for_sequential_key]
        FROM
          [sys].[system_internals_partitions] sip
        """;

    public const int PARTITIONID_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int PARTITIONNUMBER_FIELD_ID = 3;
    public const int ROWS_FIELD_ID = 4;
    public const int FILESTREAMFILEGROUPID_FIELD_ID = 5;
    public const int ISORPHANED_FIELD_ID = 6;
    public const int DROPPEDLOBCOLUMNSTATE_FIELD_ID = 7;
    public const int ISUNIQUE_FIELD_ID = 8;
    public const int ISREPLICATED_FIELD_ID = 9;
    public const int ISLOGGEDFORREPLICATION_FIELD_ID = 10;
    public const int ISSEREPLICATED_FIELD_ID = 11;
    public const int MAXNULLBITUSED_FIELD_ID = 12;
    public const int MAXLEAFLENGTH_FIELD_ID = 13;
    public const int MINLEAFLENGTH_FIELD_ID = 14;
    public const int MAXINTERNALLENGTH_FIELD_ID = 15;
    public const int MININTERNALLENGTH_FIELD_ID = 16;
    public const int ALLOWSNULLABLEKEYS_FIELD_ID = 17;
    public const int ALLOWROWLOCKS_FIELD_ID = 18;
    public const int ALLOWPAGELOCKS_FIELD_ID = 19;
    public const int ISDATAROWFORMAT_FIELD_ID = 20;
    public const int ISNOTVERSIONED_FIELD_ID = 21;
    public const int FILESTREAMGUID_FIELD_ID = 22;
    public const int OWNERTYPE_FIELD_ID = 23;
    public const int ISCOLUMNSTORE_FIELD_ID = 24;
    public const int OPTIMIZEFORSEQUENTIALKEY_FIELD_ID = 25;


    public SystemInternalsPartitionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SystemInternalsPartitionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SystemInternalsPartitionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public int PartitionNumber
    {
        get
        {
            return base.GetInt32(PARTITIONNUMBER_FIELD_ID);
        }
    }

    public long Rows
    {
        get
        {
            return base.GetInt64(ROWS_FIELD_ID);
        }
    }

    public short FilestreamFilegroupId
    {
        get
        {
            return base.GetInt16(FILESTREAMFILEGROUPID_FIELD_ID);
        }
    }

    public bool? IsOrphaned
    {
        get
        {
            return base.GetNullableBoolean(ISORPHANED_FIELD_ID);
        }
    }

    public byte? DroppedLobColumnState
    {
        get
        {
            return base.GetNullableByte(DROPPEDLOBCOLUMNSTATE_FIELD_ID);
        }
    }

    public bool? IsUnique
    {
        get
        {
            return base.GetNullableBoolean(ISUNIQUE_FIELD_ID);
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

    public bool IsSereplicated
    {
        get
        {
            return base.GetBoolean(ISSEREPLICATED_FIELD_ID);
        }
    }

    public short MaxNullBitUsed
    {
        get
        {
            return base.GetInt16(MAXNULLBITUSED_FIELD_ID);
        }
    }

    public int MaxLeafLength
    {
        get
        {
            return base.GetInt32(MAXLEAFLENGTH_FIELD_ID);
        }
    }

    public short MinLeafLength
    {
        get
        {
            return base.GetInt16(MINLEAFLENGTH_FIELD_ID);
        }
    }

    public short MaxInternalLength
    {
        get
        {
            return base.GetInt16(MAXINTERNALLENGTH_FIELD_ID);
        }
    }

    public short MinInternalLength
    {
        get
        {
            return base.GetInt16(MININTERNALLENGTH_FIELD_ID);
        }
    }

    public bool? AllowsNullableKeys
    {
        get
        {
            return base.GetNullableBoolean(ALLOWSNULLABLEKEYS_FIELD_ID);
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

    public bool? IsDataRowFormat
    {
        get
        {
            return base.GetNullableBoolean(ISDATAROWFORMAT_FIELD_ID);
        }
    }

    public bool? IsNotVersioned
    {
        get
        {
            return base.GetNullableBoolean(ISNOTVERSIONED_FIELD_ID);
        }
    }

    public Guid? FilestreamGuid
    {
        get
        {
            return base.GetNullableGuid(FILESTREAMGUID_FIELD_ID);
        }
    }

    public byte Ownertype
    {
        get
        {
            return base.GetByte(OWNERTYPE_FIELD_ID);
        }
    }

    public bool? IsColumnstore
    {
        get
        {
            return base.GetNullableBoolean(ISCOLUMNSTORE_FIELD_ID);
        }
    }

    public bool? OptimizeForSequentialKey
    {
        get
        {
            return base.GetNullableBoolean(OPTIMIZEFORSEQUENTIALKEY_FIELD_ID);
        }
    }


    public Types.SystemInternalsPartition ToDataObject()
    {
        return new Types.SystemInternalsPartition(PartitionId,
            ObjectId,
            IndexId,
            PartitionNumber,
            Rows,
            FilestreamFilegroupId,
            IsOrphaned,
            DroppedLobColumnState,
            IsUnique,
            IsReplicated,
            IsLoggedForReplication,
            IsSereplicated,
            MaxNullBitUsed,
            MaxLeafLength,
            MinLeafLength,
            MaxInternalLength,
            MinInternalLength,
            AllowsNullableKeys,
            AllowRowLocks,
            AllowPageLocks,
            IsDataRowFormat,
            IsNotVersioned,
            FilestreamGuid,
            Ownertype,
            IsColumnstore,
            OptimizeForSequentialKey);
    }

    public List<Types.SystemInternalsPartition> ToList()
    {
        var list = new List<Types.SystemInternalsPartition>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
