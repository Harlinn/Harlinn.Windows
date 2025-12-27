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

public class DmDbXtpCheckpointFilesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_checkpoint_files]";
    public const string TableName = "dm_db_xtp_checkpoint_files";
    public const string ShortName = "ddxcf";
    public const string Sql = """
        SELECT
          ddxcf.[container_id],
          ddxcf.[container_guid],
          ddxcf.[checkpoint_file_id],
          ddxcf.[relative_file_path],
          ddxcf.[file_type],
          ddxcf.[file_type_desc],
          ddxcf.[internal_storage_slot],
          ddxcf.[checkpoint_pair_file_id],
          ddxcf.[file_size_in_bytes],
          ddxcf.[file_size_used_in_bytes],
          ddxcf.[logical_row_count],
          ddxcf.[State],
          ddxcf.[state_desc],
          ddxcf.[lower_bound_tsn],
          ddxcf.[upper_bound_tsn],
          ddxcf.[begin_checkpoint_id],
          ddxcf.[end_checkpoint_id],
          ddxcf.[last_updated_checkpoint_id],
          ddxcf.[encryption_status],
          ddxcf.[encryption_status_desc]
        FROM
          [sys].[dm_db_xtp_checkpoint_files] ddxcf
        """;

    public const int CONTAINERID_FIELD_ID = 0;
    public const int CONTAINERGUID_FIELD_ID = 1;
    public const int CHECKPOINTFILEID_FIELD_ID = 2;
    public const int RELATIVEFILEPATH_FIELD_ID = 3;
    public const int FILETYPE_FIELD_ID = 4;
    public const int FILETYPEDESC_FIELD_ID = 5;
    public const int INTERNALSTORAGESLOT_FIELD_ID = 6;
    public const int CHECKPOINTPAIRFILEID_FIELD_ID = 7;
    public const int FILESIZEINBYTES_FIELD_ID = 8;
    public const int FILESIZEUSEDINBYTES_FIELD_ID = 9;
    public const int LOGICALROWCOUNT_FIELD_ID = 10;
    public const int STATE_FIELD_ID = 11;
    public const int STATEDESC_FIELD_ID = 12;
    public const int LOWERBOUNDTSN_FIELD_ID = 13;
    public const int UPPERBOUNDTSN_FIELD_ID = 14;
    public const int BEGINCHECKPOINTID_FIELD_ID = 15;
    public const int ENDCHECKPOINTID_FIELD_ID = 16;
    public const int LASTUPDATEDCHECKPOINTID_FIELD_ID = 17;
    public const int ENCRYPTIONSTATUS_FIELD_ID = 18;
    public const int ENCRYPTIONSTATUSDESC_FIELD_ID = 19;


    public DmDbXtpCheckpointFilesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpCheckpointFilesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpCheckpointFilesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ContainerId
    {
        get
        {
            return base.GetInt32(CONTAINERID_FIELD_ID);
        }
    }

    public Guid ContainerGuid
    {
        get
        {
            return base.GetGuid(CONTAINERGUID_FIELD_ID);
        }
    }

    public Guid CheckpointFileId
    {
        get
        {
            return base.GetGuid(CHECKPOINTFILEID_FIELD_ID);
        }
    }

    public string RelativeFilePath
    {
        get
        {
            return base.GetString(RELATIVEFILEPATH_FIELD_ID);
        }
    }

    public short FileType
    {
        get
        {
            return base.GetInt16(FILETYPE_FIELD_ID);
        }
    }

    public string FileTypeDesc
    {
        get
        {
            return base.GetString(FILETYPEDESC_FIELD_ID);
        }
    }

    public int? InternalStorageSlot
    {
        get
        {
            return base.GetNullableInt32(INTERNALSTORAGESLOT_FIELD_ID);
        }
    }

    public Guid? CheckpointPairFileId
    {
        get
        {
            return base.GetNullableGuid(CHECKPOINTPAIRFILEID_FIELD_ID);
        }
    }

    public long FileSizeInBytes
    {
        get
        {
            return base.GetInt64(FILESIZEINBYTES_FIELD_ID);
        }
    }

    public long? FileSizeUsedInBytes
    {
        get
        {
            return base.GetNullableInt64(FILESIZEUSEDINBYTES_FIELD_ID);
        }
    }

    public long? LogicalRowCount
    {
        get
        {
            return base.GetNullableInt64(LOGICALROWCOUNT_FIELD_ID);
        }
    }

    public short State
    {
        get
        {
            return base.GetInt16(STATE_FIELD_ID);
        }
    }

    public string StateDesc
    {
        get
        {
            return base.GetString(STATEDESC_FIELD_ID);
        }
    }

    public long? LowerBoundTsn
    {
        get
        {
            return base.GetNullableInt64(LOWERBOUNDTSN_FIELD_ID);
        }
    }

    public long? UpperBoundTsn
    {
        get
        {
            return base.GetNullableInt64(UPPERBOUNDTSN_FIELD_ID);
        }
    }

    public long? BeginCheckpointId
    {
        get
        {
            return base.GetNullableInt64(BEGINCHECKPOINTID_FIELD_ID);
        }
    }

    public long? EndCheckpointId
    {
        get
        {
            return base.GetNullableInt64(ENDCHECKPOINTID_FIELD_ID);
        }
    }

    public long? LastUpdatedCheckpointId
    {
        get
        {
            return base.GetNullableInt64(LASTUPDATEDCHECKPOINTID_FIELD_ID);
        }
    }

    public short? EncryptionStatus
    {
        get
        {
            return base.GetNullableInt16(ENCRYPTIONSTATUS_FIELD_ID);
        }
    }

    public string? EncryptionStatusDesc
    {
        get
        {
            return base.GetNullableString(ENCRYPTIONSTATUSDESC_FIELD_ID);
        }
    }


    public Types.DmDbXtpCheckpointFilesDataType ToDataObject()
    {
        return new Types.DmDbXtpCheckpointFilesDataType(ContainerId,
            ContainerGuid,
            CheckpointFileId,
            RelativeFilePath,
            FileType,
            FileTypeDesc,
            InternalStorageSlot,
            CheckpointPairFileId,
            FileSizeInBytes,
            FileSizeUsedInBytes,
            LogicalRowCount,
            State,
            StateDesc,
            LowerBoundTsn,
            UpperBoundTsn,
            BeginCheckpointId,
            EndCheckpointId,
            LastUpdatedCheckpointId,
            EncryptionStatus,
            EncryptionStatusDesc);
    }

    public List<Types.DmDbXtpCheckpointFilesDataType> ToList()
    {
        var list = new List<Types.DmDbXtpCheckpointFilesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
