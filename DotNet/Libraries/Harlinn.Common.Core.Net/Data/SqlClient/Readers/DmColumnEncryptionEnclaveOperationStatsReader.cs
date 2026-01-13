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

public class DmColumnEncryptionEnclaveOperationStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_column_encryption_enclave_operation_stats]";
    public const string TableName = "dm_column_encryption_enclave_operation_stats";
    public const string ShortName = "dceeos";
    public const string Sql = """
        SELECT
          dceeos.[operation_type],
          dceeos.[total_operation_count]
        FROM
          [sys].[dm_column_encryption_enclave_operation_stats] dceeos
        """;

    public const int OPERATIONTYPE_FIELD_ID = 0;
    public const int TOTALOPERATIONCOUNT_FIELD_ID = 1;


    public DmColumnEncryptionEnclaveOperationStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmColumnEncryptionEnclaveOperationStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmColumnEncryptionEnclaveOperationStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? OperationType
    {
        get
        {
            return base.GetNullableString(OPERATIONTYPE_FIELD_ID);
        }
    }

    public long? TotalOperationCount
    {
        get
        {
            return base.GetNullableInt64(TOTALOPERATIONCOUNT_FIELD_ID);
        }
    }


    public Types.DmColumnEncryptionEnclaveOperationStatsDataType ToDataObject()
    {
        return new Types.DmColumnEncryptionEnclaveOperationStatsDataType(OperationType,
            TotalOperationCount);
    }

    public List<Types.DmColumnEncryptionEnclaveOperationStatsDataType> ToList()
    {
        var list = new List<Types.DmColumnEncryptionEnclaveOperationStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
