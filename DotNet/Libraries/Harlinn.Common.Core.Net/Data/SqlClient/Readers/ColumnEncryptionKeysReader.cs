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

public class ColumnEncryptionKeysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[column_encryption_keys]";
    public const string TableName = "column_encryption_keys";
    public const string ShortName = "cek";
    public const string Sql = """
        SELECT
          cek.[Name],
          cek.[column_encryption_key_id],
          cek.[create_date],
          cek.[modify_date]
        FROM
          [sys].[column_encryption_keys] cek
        """;

    public const int NAME_FIELD_ID = 0;
    public const int COLUMNENCRYPTIONKEYID_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int MODIFYDATE_FIELD_ID = 3;


    public ColumnEncryptionKeysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ColumnEncryptionKeysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ColumnEncryptionKeysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int ColumnEncryptionKeyId
    {
        get
        {
            return base.GetInt32(COLUMNENCRYPTIONKEYID_FIELD_ID);
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


    public Types.ColumnEncryptionKeysDataType ToDataObject()
    {
        return new Types.ColumnEncryptionKeysDataType(Name,
            ColumnEncryptionKeyId,
            CreateDate,
            ModifyDate);
    }

    public List<Types.ColumnEncryptionKeysDataType> ToList()
    {
        var list = new List<Types.ColumnEncryptionKeysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
