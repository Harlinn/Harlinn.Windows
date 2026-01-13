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

public class MasterFilesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[master_files]";
    public const string TableName = "master_files";
    public const string ShortName = "mf";
    public const string Sql = """
        SELECT
          mf.[database_id],
          mf.[file_id],
          mf.[file_guid],
          mf.[Type],
          mf.[type_desc],
          mf.[data_space_id],
          mf.[Name],
          mf.[physical_name],
          mf.[State],
          mf.[state_desc],
          mf.[Size],
          mf.[max_size],
          mf.[Growth],
          mf.[is_media_read_only],
          mf.[is_read_only],
          mf.[is_sparse],
          mf.[is_percent_growth],
          mf.[is_name_reserved],
          mf.[is_persistent_log_buffer],
          mf.[create_lsn],
          mf.[drop_lsn],
          mf.[read_only_lsn],
          mf.[read_write_lsn],
          mf.[differential_base_lsn],
          mf.[differential_base_guid],
          mf.[differential_base_time],
          mf.[redo_start_lsn],
          mf.[redo_start_fork_guid],
          mf.[redo_target_lsn],
          mf.[redo_target_fork_guid],
          mf.[backup_lsn],
          mf.[credential_id]
        FROM
          [sys].[master_files] mf
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int FILEID_FIELD_ID = 1;
    public const int FILEGUID_FIELD_ID = 2;
    public const int TYPE_FIELD_ID = 3;
    public const int TYPEDESC_FIELD_ID = 4;
    public const int DATASPACEID_FIELD_ID = 5;
    public const int NAME_FIELD_ID = 6;
    public const int PHYSICALNAME_FIELD_ID = 7;
    public const int STATE_FIELD_ID = 8;
    public const int STATEDESC_FIELD_ID = 9;
    public const int SIZE_FIELD_ID = 10;
    public const int MAXSIZE_FIELD_ID = 11;
    public const int GROWTH_FIELD_ID = 12;
    public const int ISMEDIAREADONLY_FIELD_ID = 13;
    public const int ISREADONLY_FIELD_ID = 14;
    public const int ISSPARSE_FIELD_ID = 15;
    public const int ISPERCENTGROWTH_FIELD_ID = 16;
    public const int ISNAMERESERVED_FIELD_ID = 17;
    public const int ISPERSISTENTLOGBUFFER_FIELD_ID = 18;
    public const int CREATELSN_FIELD_ID = 19;
    public const int DROPLSN_FIELD_ID = 20;
    public const int READONLYLSN_FIELD_ID = 21;
    public const int READWRITELSN_FIELD_ID = 22;
    public const int DIFFERENTIALBASELSN_FIELD_ID = 23;
    public const int DIFFERENTIALBASEGUID_FIELD_ID = 24;
    public const int DIFFERENTIALBASETIME_FIELD_ID = 25;
    public const int REDOSTARTLSN_FIELD_ID = 26;
    public const int REDOSTARTFORKGUID_FIELD_ID = 27;
    public const int REDOTARGETLSN_FIELD_ID = 28;
    public const int REDOTARGETFORKGUID_FIELD_ID = 29;
    public const int BACKUPLSN_FIELD_ID = 30;
    public const int CREDENTIALID_FIELD_ID = 31;


    public MasterFilesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public MasterFilesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public MasterFilesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public int FileId
    {
        get
        {
            return base.GetInt32(FILEID_FIELD_ID);
        }
    }

    public Guid? FileGuid
    {
        get
        {
            return base.GetNullableGuid(FILEGUID_FIELD_ID);
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

    public int DataSpaceId
    {
        get
        {
            return base.GetInt32(DATASPACEID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string PhysicalName
    {
        get
        {
            return base.GetString(PHYSICALNAME_FIELD_ID);
        }
    }

    public byte? State
    {
        get
        {
            return base.GetNullableByte(STATE_FIELD_ID);
        }
    }

    public string? StateDesc
    {
        get
        {
            return base.GetNullableString(STATEDESC_FIELD_ID);
        }
    }

    public int Size
    {
        get
        {
            return base.GetInt32(SIZE_FIELD_ID);
        }
    }

    public int MaxSize
    {
        get
        {
            return base.GetInt32(MAXSIZE_FIELD_ID);
        }
    }

    public int Growth
    {
        get
        {
            return base.GetInt32(GROWTH_FIELD_ID);
        }
    }

    public bool IsMediaReadOnly
    {
        get
        {
            return base.GetBoolean(ISMEDIAREADONLY_FIELD_ID);
        }
    }

    public bool IsReadOnly
    {
        get
        {
            return base.GetBoolean(ISREADONLY_FIELD_ID);
        }
    }

    public bool IsSparse
    {
        get
        {
            return base.GetBoolean(ISSPARSE_FIELD_ID);
        }
    }

    public bool IsPercentGrowth
    {
        get
        {
            return base.GetBoolean(ISPERCENTGROWTH_FIELD_ID);
        }
    }

    public bool IsNameReserved
    {
        get
        {
            return base.GetBoolean(ISNAMERESERVED_FIELD_ID);
        }
    }

    public bool IsPersistentLogBuffer
    {
        get
        {
            return base.GetBoolean(ISPERSISTENTLOGBUFFER_FIELD_ID);
        }
    }

    public decimal? CreateLsn
    {
        get
        {
            return base.GetNullableDecimal(CREATELSN_FIELD_ID);
        }
    }

    public decimal? DropLsn
    {
        get
        {
            return base.GetNullableDecimal(DROPLSN_FIELD_ID);
        }
    }

    public decimal? ReadOnlyLsn
    {
        get
        {
            return base.GetNullableDecimal(READONLYLSN_FIELD_ID);
        }
    }

    public decimal? ReadWriteLsn
    {
        get
        {
            return base.GetNullableDecimal(READWRITELSN_FIELD_ID);
        }
    }

    public decimal? DifferentialBaseLsn
    {
        get
        {
            return base.GetNullableDecimal(DIFFERENTIALBASELSN_FIELD_ID);
        }
    }

    public Guid? DifferentialBaseGuid
    {
        get
        {
            return base.GetNullableGuid(DIFFERENTIALBASEGUID_FIELD_ID);
        }
    }

    public DateTime? DifferentialBaseTime
    {
        get
        {
            return base.GetNullableDateTime(DIFFERENTIALBASETIME_FIELD_ID);
        }
    }

    public decimal? RedoStartLsn
    {
        get
        {
            return base.GetNullableDecimal(REDOSTARTLSN_FIELD_ID);
        }
    }

    public Guid? RedoStartForkGuid
    {
        get
        {
            return base.GetNullableGuid(REDOSTARTFORKGUID_FIELD_ID);
        }
    }

    public decimal? RedoTargetLsn
    {
        get
        {
            return base.GetNullableDecimal(REDOTARGETLSN_FIELD_ID);
        }
    }

    public Guid? RedoTargetForkGuid
    {
        get
        {
            return base.GetNullableGuid(REDOTARGETFORKGUID_FIELD_ID);
        }
    }

    public decimal? BackupLsn
    {
        get
        {
            return base.GetNullableDecimal(BACKUPLSN_FIELD_ID);
        }
    }

    public int? CredentialId
    {
        get
        {
            return base.GetNullableInt32(CREDENTIALID_FIELD_ID);
        }
    }


    public Types.MasterFilesDataType ToDataObject()
    {
        return new Types.MasterFilesDataType(DatabaseId,
            FileId,
            FileGuid,
            Type,
            TypeDesc,
            DataSpaceId,
            Name,
            PhysicalName,
            State,
            StateDesc,
            Size,
            MaxSize,
            Growth,
            IsMediaReadOnly,
            IsReadOnly,
            IsSparse,
            IsPercentGrowth,
            IsNameReserved,
            IsPersistentLogBuffer,
            CreateLsn,
            DropLsn,
            ReadOnlyLsn,
            ReadWriteLsn,
            DifferentialBaseLsn,
            DifferentialBaseGuid,
            DifferentialBaseTime,
            RedoStartLsn,
            RedoStartForkGuid,
            RedoTargetLsn,
            RedoTargetForkGuid,
            BackupLsn,
            CredentialId);
    }

    public List<Types.MasterFilesDataType> ToList()
    {
        var list = new List<Types.MasterFilesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
