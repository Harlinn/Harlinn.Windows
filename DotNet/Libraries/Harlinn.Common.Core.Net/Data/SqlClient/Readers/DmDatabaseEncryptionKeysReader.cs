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

public class DmDatabaseEncryptionKeysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_database_encryption_keys]";
    public const string TableName = "dm_database_encryption_keys";
    public const string ShortName = "ddek";
    public const string Sql = """
        SELECT
          ddek.[database_id],
          ddek.[encryption_state],
          ddek.[create_date],
          ddek.[regenerate_date],
          ddek.[modify_date],
          ddek.[set_date],
          ddek.[opened_date],
          ddek.[key_algorithm],
          ddek.[key_length],
          ddek.[encryptor_thumbprint],
          ddek.[encryptor_type],
          ddek.[percent_complete],
          ddek.[encryption_state_desc],
          ddek.[encryption_scan_state],
          ddek.[encryption_scan_state_desc],
          ddek.[encryption_scan_modify_date]
        FROM
          [sys].[dm_database_encryption_keys] ddek
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int ENCRYPTIONSTATE_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int REGENERATEDATE_FIELD_ID = 3;
    public const int MODIFYDATE_FIELD_ID = 4;
    public const int SETDATE_FIELD_ID = 5;
    public const int OPENEDDATE_FIELD_ID = 6;
    public const int KEYALGORITHM_FIELD_ID = 7;
    public const int KEYLENGTH_FIELD_ID = 8;
    public const int ENCRYPTORTHUMBPRINT_FIELD_ID = 9;
    public const int ENCRYPTORTYPE_FIELD_ID = 10;
    public const int PERCENTCOMPLETE_FIELD_ID = 11;
    public const int ENCRYPTIONSTATEDESC_FIELD_ID = 12;
    public const int ENCRYPTIONSCANSTATE_FIELD_ID = 13;
    public const int ENCRYPTIONSCANSTATEDESC_FIELD_ID = 14;
    public const int ENCRYPTIONSCANMODIFYDATE_FIELD_ID = 15;


    public DmDatabaseEncryptionKeysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDatabaseEncryptionKeysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDatabaseEncryptionKeysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public int? EncryptionState
    {
        get
        {
            return base.GetNullableInt32(ENCRYPTIONSTATE_FIELD_ID);
        }
    }

    public DateTime? CreateDate
    {
        get
        {
            return base.GetNullableDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime? RegenerateDate
    {
        get
        {
            return base.GetNullableDateTime(REGENERATEDATE_FIELD_ID);
        }
    }

    public DateTime? ModifyDate
    {
        get
        {
            return base.GetNullableDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public DateTime? SetDate
    {
        get
        {
            return base.GetNullableDateTime(SETDATE_FIELD_ID);
        }
    }

    public DateTime? OpenedDate
    {
        get
        {
            return base.GetNullableDateTime(OPENEDDATE_FIELD_ID);
        }
    }

    public string? KeyAlgorithm
    {
        get
        {
            return base.GetNullableString(KEYALGORITHM_FIELD_ID);
        }
    }

    public int? KeyLength
    {
        get
        {
            return base.GetNullableInt32(KEYLENGTH_FIELD_ID);
        }
    }

    public byte[]? EncryptorThumbprint
    {
        get
        {
            return base.GetNullableBinary(ENCRYPTORTHUMBPRINT_FIELD_ID);
        }
    }

    public string? EncryptorType
    {
        get
        {
            return base.GetNullableString(ENCRYPTORTYPE_FIELD_ID);
        }
    }

    public float? PercentComplete
    {
        get
        {
            return base.GetNullableSingle(PERCENTCOMPLETE_FIELD_ID);
        }
    }

    public string? EncryptionStateDesc
    {
        get
        {
            return base.GetNullableString(ENCRYPTIONSTATEDESC_FIELD_ID);
        }
    }

    public int? EncryptionScanState
    {
        get
        {
            return base.GetNullableInt32(ENCRYPTIONSCANSTATE_FIELD_ID);
        }
    }

    public string? EncryptionScanStateDesc
    {
        get
        {
            return base.GetNullableString(ENCRYPTIONSCANSTATEDESC_FIELD_ID);
        }
    }

    public DateTime? EncryptionScanModifyDate
    {
        get
        {
            return base.GetNullableDateTime(ENCRYPTIONSCANMODIFYDATE_FIELD_ID);
        }
    }


    public Types.DmDatabaseEncryptionKeysDataType ToDataObject()
    {
        return new Types.DmDatabaseEncryptionKeysDataType(DatabaseId,
            EncryptionState,
            CreateDate,
            RegenerateDate,
            ModifyDate,
            SetDate,
            OpenedDate,
            KeyAlgorithm,
            KeyLength,
            EncryptorThumbprint,
            EncryptorType,
            PercentComplete,
            EncryptionStateDesc,
            EncryptionScanState,
            EncryptionScanStateDesc,
            EncryptionScanModifyDate);
    }

    public List<Types.DmDatabaseEncryptionKeysDataType> ToList()
    {
        var list = new List<Types.DmDatabaseEncryptionKeysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
