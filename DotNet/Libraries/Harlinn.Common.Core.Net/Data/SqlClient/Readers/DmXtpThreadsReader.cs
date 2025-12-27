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

public class DmXtpThreadsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xtp_threads]";
    public const string TableName = "dm_xtp_threads";
    public const string ShortName = "dxt";
    public const string Sql = """
        SELECT
          dxt.[thread_address],
          dxt.[thread_type],
          dxt.[thread_type_desc],
          dxt.[retired_row_count],
          dxt.[retired_transaction_count]
        FROM
          [sys].[dm_xtp_threads] dxt
        """;

    public const int THREADADDRESS_FIELD_ID = 0;
    public const int THREADTYPE_FIELD_ID = 1;
    public const int THREADTYPEDESC_FIELD_ID = 2;
    public const int RETIREDROWCOUNT_FIELD_ID = 3;
    public const int RETIREDTRANSACTIONCOUNT_FIELD_ID = 4;


    public DmXtpThreadsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXtpThreadsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXtpThreadsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] ThreadAddress
    {
        get
        {
            return base.GetBinary(THREADADDRESS_FIELD_ID);
        }
    }

    public int ThreadType
    {
        get
        {
            return base.GetInt32(THREADTYPE_FIELD_ID);
        }
    }

    public string ThreadTypeDesc
    {
        get
        {
            return base.GetString(THREADTYPEDESC_FIELD_ID);
        }
    }

    public int RetiredRowCount
    {
        get
        {
            return base.GetInt32(RETIREDROWCOUNT_FIELD_ID);
        }
    }

    public int RetiredTransactionCount
    {
        get
        {
            return base.GetInt32(RETIREDTRANSACTIONCOUNT_FIELD_ID);
        }
    }


    public Types.DmXtpThreadsDataType ToDataObject()
    {
        return new Types.DmXtpThreadsDataType(ThreadAddress,
            ThreadType,
            ThreadTypeDesc,
            RetiredRowCount,
            RetiredTransactionCount);
    }

    public List<Types.DmXtpThreadsDataType> ToList()
    {
        var list = new List<Types.DmXtpThreadsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
