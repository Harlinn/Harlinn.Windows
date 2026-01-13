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

public class ColumnMasterKeysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[column_master_keys]";
    public const string TableName = "column_master_keys";
    public const string ShortName = "cmk";
    public const string Sql = """
        SELECT
          cmk.[Name],
          cmk.[column_master_key_id],
          cmk.[create_date],
          cmk.[modify_date],
          cmk.[key_store_provider_name],
          cmk.[key_path],
          cmk.[allow_enclave_computations],
          cmk.[Signature]
        FROM
          [sys].[column_master_keys] cmk
        """;

    public const int NAME_FIELD_ID = 0;
    public const int COLUMNMASTERKEYID_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int MODIFYDATE_FIELD_ID = 3;
    public const int KEYSTOREPROVIDERNAME_FIELD_ID = 4;
    public const int KEYPATH_FIELD_ID = 5;
    public const int ALLOWENCLAVECOMPUTATIONS_FIELD_ID = 6;
    public const int SIGNATURE_FIELD_ID = 7;


    public ColumnMasterKeysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ColumnMasterKeysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ColumnMasterKeysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int ColumnMasterKeyId
    {
        get
        {
            return base.GetInt32(COLUMNMASTERKEYID_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public string? KeyStoreProviderName
    {
        get
        {
            return base.GetNullableString(KEYSTOREPROVIDERNAME_FIELD_ID);
        }
    }

    public string? KeyPath
    {
        get
        {
            return base.GetNullableString(KEYPATH_FIELD_ID);
        }
    }

    public int AllowEnclaveComputations
    {
        get
        {
            return base.GetInt32(ALLOWENCLAVECOMPUTATIONS_FIELD_ID);
        }
    }

    public byte[]? Signature
    {
        get
        {
            return base.GetNullableBinary(SIGNATURE_FIELD_ID);
        }
    }


    public Types.ColumnMasterKeysDataType ToDataObject()
    {
        return new Types.ColumnMasterKeysDataType(Name,
            ColumnMasterKeyId,
            CreateDate,
            ModifyDate,
            KeyStoreProviderName,
            KeyPath,
            AllowEnclaveComputations,
            Signature);
    }

    public List<Types.ColumnMasterKeysDataType> ToList()
    {
        var list = new List<Types.ColumnMasterKeysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
