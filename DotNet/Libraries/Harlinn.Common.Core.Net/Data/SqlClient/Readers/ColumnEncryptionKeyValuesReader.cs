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

public class ColumnEncryptionKeyValuesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[column_encryption_key_values]";
    public const string TableName = "column_encryption_key_values";
    public const string ShortName = "cekv";
    public const string Sql = """
        SELECT
          cekv.[column_encryption_key_id],
          cekv.[column_master_key_id],
          cekv.[encrypted_value],
          cekv.[encryption_algorithm_name]
        FROM
          [sys].[column_encryption_key_values] cekv
        """;

    public const int COLUMNENCRYPTIONKEYID_FIELD_ID = 0;
    public const int COLUMNMASTERKEYID_FIELD_ID = 1;
    public const int ENCRYPTEDVALUE_FIELD_ID = 2;
    public const int ENCRYPTIONALGORITHMNAME_FIELD_ID = 3;


    public ColumnEncryptionKeyValuesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ColumnEncryptionKeyValuesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ColumnEncryptionKeyValuesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ColumnEncryptionKeyId
    {
        get
        {
            return base.GetInt32(COLUMNENCRYPTIONKEYID_FIELD_ID);
        }
    }

    public int ColumnMasterKeyId
    {
        get
        {
            return base.GetInt32(COLUMNMASTERKEYID_FIELD_ID);
        }
    }

    public byte[]? EncryptedValue
    {
        get
        {
            return base.GetNullableBinary(ENCRYPTEDVALUE_FIELD_ID);
        }
    }

    public string? EncryptionAlgorithmName
    {
        get
        {
            return base.GetNullableString(ENCRYPTIONALGORITHMNAME_FIELD_ID);
        }
    }


    public Types.ColumnEncryptionKeyValuesDataType ToDataObject()
    {
        return new Types.ColumnEncryptionKeyValuesDataType(ColumnEncryptionKeyId,
            ColumnMasterKeyId,
            EncryptedValue,
            EncryptionAlgorithmName);
    }

    public List<Types.ColumnEncryptionKeyValuesDataType> ToList()
    {
        var list = new List<Types.ColumnEncryptionKeyValuesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
