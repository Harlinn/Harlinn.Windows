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

public class DmColumnEncryptionEnclaveReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_column_encryption_enclave]";
    public const string TableName = "dm_column_encryption_enclave";
    public const string ShortName = "dcee";
    public const string Sql = """
        SELECT
          dcee.[current_enclave_session_count],
          dcee.[current_column_encryption_key_count],
          dcee.[current_memory_size_kb],
          dcee.[total_evicted_session_count]
        FROM
          [sys].[dm_column_encryption_enclave] dcee
        """;

    public const int CURRENTENCLAVESESSIONCOUNT_FIELD_ID = 0;
    public const int CURRENTCOLUMNENCRYPTIONKEYCOUNT_FIELD_ID = 1;
    public const int CURRENTMEMORYSIZEKB_FIELD_ID = 2;
    public const int TOTALEVICTEDSESSIONCOUNT_FIELD_ID = 3;


    public DmColumnEncryptionEnclaveReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmColumnEncryptionEnclaveReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmColumnEncryptionEnclaveReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? CurrentEnclaveSessionCount
    {
        get
        {
            return base.GetNullableInt32(CURRENTENCLAVESESSIONCOUNT_FIELD_ID);
        }
    }

    public int? CurrentColumnEncryptionKeyCount
    {
        get
        {
            return base.GetNullableInt32(CURRENTCOLUMNENCRYPTIONKEYCOUNT_FIELD_ID);
        }
    }

    public long? CurrentMemorySizeKb
    {
        get
        {
            return base.GetNullableInt64(CURRENTMEMORYSIZEKB_FIELD_ID);
        }
    }

    public long? TotalEvictedSessionCount
    {
        get
        {
            return base.GetNullableInt64(TOTALEVICTEDSESSIONCOUNT_FIELD_ID);
        }
    }


    public Types.DmColumnEncryptionEnclaveDataType ToDataObject()
    {
        return new Types.DmColumnEncryptionEnclaveDataType(CurrentEnclaveSessionCount,
            CurrentColumnEncryptionKeyCount,
            CurrentMemorySizeKb,
            TotalEvictedSessionCount);
    }

    public List<Types.DmColumnEncryptionEnclaveDataType> ToList()
    {
        var list = new List<Types.DmColumnEncryptionEnclaveDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
