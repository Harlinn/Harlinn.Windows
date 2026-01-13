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

public class DmDbXtpTransactionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_transactions]";
    public const string TableName = "dm_db_xtp_transactions";
    public const string ShortName = "ddxt";
    public const string Sql = """
        SELECT
          ddxt.[node_id],
          ddxt.[xtp_transaction_id],
          ddxt.[transaction_id],
          ddxt.[session_id],
          ddxt.[begin_tsn],
          ddxt.[end_tsn],
          ddxt.[State],
          ddxt.[state_desc],
          ddxt.[Result],
          ddxt.[result_desc],
          ddxt.[xtp_parent_transaction_node_id],
          ddxt.[xtp_parent_transaction_id],
          ddxt.[last_error],
          ddxt.[is_speculative],
          ddxt.[is_prepared],
          ddxt.[is_delayed_durability],
          ddxt.[memory_address],
          ddxt.[database_address],
          ddxt.[thread_id],
          ddxt.[read_set_row_count],
          ddxt.[write_set_row_count],
          ddxt.[scan_set_count],
          ddxt.[savepoint_garbage_count],
          ddxt.[log_bytes_required],
          ddxt.[count_of_allocations],
          ddxt.[allocated_bytes],
          ddxt.[reserved_bytes],
          ddxt.[commit_dependency_count],
          ddxt.[commit_dependency_total_attempt_count],
          ddxt.[scan_area],
          ddxt.[scan_area_desc],
          ddxt.[scan_location],
          ddxt.[dependent_1_address],
          ddxt.[dependent_2_address],
          ddxt.[dependent_3_address],
          ddxt.[dependent_4_address],
          ddxt.[dependent_5_address],
          ddxt.[dependent_6_address],
          ddxt.[dependent_7_address],
          ddxt.[dependent_8_address]
        FROM
          [sys].[dm_db_xtp_transactions] ddxt
        """;

    public const int NODEID_FIELD_ID = 0;
    public const int XTPTRANSACTIONID_FIELD_ID = 1;
    public const int TRANSACTIONID_FIELD_ID = 2;
    public const int SESSIONID_FIELD_ID = 3;
    public const int BEGINTSN_FIELD_ID = 4;
    public const int ENDTSN_FIELD_ID = 5;
    public const int STATE_FIELD_ID = 6;
    public const int STATEDESC_FIELD_ID = 7;
    public const int RESULT_FIELD_ID = 8;
    public const int RESULTDESC_FIELD_ID = 9;
    public const int XTPPARENTTRANSACTIONNODEID_FIELD_ID = 10;
    public const int XTPPARENTTRANSACTIONID_FIELD_ID = 11;
    public const int LASTERROR_FIELD_ID = 12;
    public const int ISSPECULATIVE_FIELD_ID = 13;
    public const int ISPREPARED_FIELD_ID = 14;
    public const int ISDELAYEDDURABILITY_FIELD_ID = 15;
    public const int MEMORYADDRESS_FIELD_ID = 16;
    public const int DATABASEADDRESS_FIELD_ID = 17;
    public const int THREADID_FIELD_ID = 18;
    public const int READSETROWCOUNT_FIELD_ID = 19;
    public const int WRITESETROWCOUNT_FIELD_ID = 20;
    public const int SCANSETCOUNT_FIELD_ID = 21;
    public const int SAVEPOINTGARBAGECOUNT_FIELD_ID = 22;
    public const int LOGBYTESREQUIRED_FIELD_ID = 23;
    public const int COUNTOFALLOCATIONS_FIELD_ID = 24;
    public const int ALLOCATEDBYTES_FIELD_ID = 25;
    public const int RESERVEDBYTES_FIELD_ID = 26;
    public const int COMMITDEPENDENCYCOUNT_FIELD_ID = 27;
    public const int COMMITDEPENDENCYTOTALATTEMPTCOUNT_FIELD_ID = 28;
    public const int SCANAREA_FIELD_ID = 29;
    public const int SCANAREADESC_FIELD_ID = 30;
    public const int SCANLOCATION_FIELD_ID = 31;
    public const int DEPENDENT1ADDRESS_FIELD_ID = 32;
    public const int DEPENDENT2ADDRESS_FIELD_ID = 33;
    public const int DEPENDENT3ADDRESS_FIELD_ID = 34;
    public const int DEPENDENT4ADDRESS_FIELD_ID = 35;
    public const int DEPENDENT5ADDRESS_FIELD_ID = 36;
    public const int DEPENDENT6ADDRESS_FIELD_ID = 37;
    public const int DEPENDENT7ADDRESS_FIELD_ID = 38;
    public const int DEPENDENT8ADDRESS_FIELD_ID = 39;


    public DmDbXtpTransactionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpTransactionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpTransactionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short NodeId
    {
        get
        {
            return base.GetInt16(NODEID_FIELD_ID);
        }
    }

    public long XtpTransactionId
    {
        get
        {
            return base.GetInt64(XTPTRANSACTIONID_FIELD_ID);
        }
    }

    public long TransactionId
    {
        get
        {
            return base.GetInt64(TRANSACTIONID_FIELD_ID);
        }
    }

    public short SessionId
    {
        get
        {
            return base.GetInt16(SESSIONID_FIELD_ID);
        }
    }

    public long BeginTsn
    {
        get
        {
            return base.GetInt64(BEGINTSN_FIELD_ID);
        }
    }

    public long EndTsn
    {
        get
        {
            return base.GetInt64(ENDTSN_FIELD_ID);
        }
    }

    public int State
    {
        get
        {
            return base.GetInt32(STATE_FIELD_ID);
        }
    }

    public string StateDesc
    {
        get
        {
            return base.GetString(STATEDESC_FIELD_ID);
        }
    }

    public int Result
    {
        get
        {
            return base.GetInt32(RESULT_FIELD_ID);
        }
    }

    public string ResultDesc
    {
        get
        {
            return base.GetString(RESULTDESC_FIELD_ID);
        }
    }

    public short XtpParentTransactionNodeId
    {
        get
        {
            return base.GetInt16(XTPPARENTTRANSACTIONNODEID_FIELD_ID);
        }
    }

    public long XtpParentTransactionId
    {
        get
        {
            return base.GetInt64(XTPPARENTTRANSACTIONID_FIELD_ID);
        }
    }

    public int LastError
    {
        get
        {
            return base.GetInt32(LASTERROR_FIELD_ID);
        }
    }

    public bool IsSpeculative
    {
        get
        {
            return base.GetBoolean(ISSPECULATIVE_FIELD_ID);
        }
    }

    public bool IsPrepared
    {
        get
        {
            return base.GetBoolean(ISPREPARED_FIELD_ID);
        }
    }

    public bool IsDelayedDurability
    {
        get
        {
            return base.GetBoolean(ISDELAYEDDURABILITY_FIELD_ID);
        }
    }

    public byte[] MemoryAddress
    {
        get
        {
            return base.GetBinary(MEMORYADDRESS_FIELD_ID);
        }
    }

    public byte[] DatabaseAddress
    {
        get
        {
            return base.GetBinary(DATABASEADDRESS_FIELD_ID);
        }
    }

    public int ThreadId
    {
        get
        {
            return base.GetInt32(THREADID_FIELD_ID);
        }
    }

    public int ReadSetRowCount
    {
        get
        {
            return base.GetInt32(READSETROWCOUNT_FIELD_ID);
        }
    }

    public int WriteSetRowCount
    {
        get
        {
            return base.GetInt32(WRITESETROWCOUNT_FIELD_ID);
        }
    }

    public int ScanSetCount
    {
        get
        {
            return base.GetInt32(SCANSETCOUNT_FIELD_ID);
        }
    }

    public int SavepointGarbageCount
    {
        get
        {
            return base.GetInt32(SAVEPOINTGARBAGECOUNT_FIELD_ID);
        }
    }

    public long LogBytesRequired
    {
        get
        {
            return base.GetInt64(LOGBYTESREQUIRED_FIELD_ID);
        }
    }

    public int CountOfAllocations
    {
        get
        {
            return base.GetInt32(COUNTOFALLOCATIONS_FIELD_ID);
        }
    }

    public int AllocatedBytes
    {
        get
        {
            return base.GetInt32(ALLOCATEDBYTES_FIELD_ID);
        }
    }

    public int ReservedBytes
    {
        get
        {
            return base.GetInt32(RESERVEDBYTES_FIELD_ID);
        }
    }

    public int CommitDependencyCount
    {
        get
        {
            return base.GetInt32(COMMITDEPENDENCYCOUNT_FIELD_ID);
        }
    }

    public int CommitDependencyTotalAttemptCount
    {
        get
        {
            return base.GetInt32(COMMITDEPENDENCYTOTALATTEMPTCOUNT_FIELD_ID);
        }
    }

    public int ScanArea
    {
        get
        {
            return base.GetInt32(SCANAREA_FIELD_ID);
        }
    }

    public string ScanAreaDesc
    {
        get
        {
            return base.GetString(SCANAREADESC_FIELD_ID);
        }
    }

    public int ScanLocation
    {
        get
        {
            return base.GetInt32(SCANLOCATION_FIELD_ID);
        }
    }

    public byte[] Dependent1Address
    {
        get
        {
            return base.GetBinary(DEPENDENT1ADDRESS_FIELD_ID);
        }
    }

    public byte[] Dependent2Address
    {
        get
        {
            return base.GetBinary(DEPENDENT2ADDRESS_FIELD_ID);
        }
    }

    public byte[] Dependent3Address
    {
        get
        {
            return base.GetBinary(DEPENDENT3ADDRESS_FIELD_ID);
        }
    }

    public byte[] Dependent4Address
    {
        get
        {
            return base.GetBinary(DEPENDENT4ADDRESS_FIELD_ID);
        }
    }

    public byte[] Dependent5Address
    {
        get
        {
            return base.GetBinary(DEPENDENT5ADDRESS_FIELD_ID);
        }
    }

    public byte[] Dependent6Address
    {
        get
        {
            return base.GetBinary(DEPENDENT6ADDRESS_FIELD_ID);
        }
    }

    public byte[] Dependent7Address
    {
        get
        {
            return base.GetBinary(DEPENDENT7ADDRESS_FIELD_ID);
        }
    }

    public byte[] Dependent8Address
    {
        get
        {
            return base.GetBinary(DEPENDENT8ADDRESS_FIELD_ID);
        }
    }


    public Types.DmDbXtpTransactionsDataType ToDataObject()
    {
        return new Types.DmDbXtpTransactionsDataType(NodeId,
            XtpTransactionId,
            TransactionId,
            SessionId,
            BeginTsn,
            EndTsn,
            State,
            StateDesc,
            Result,
            ResultDesc,
            XtpParentTransactionNodeId,
            XtpParentTransactionId,
            LastError,
            IsSpeculative,
            IsPrepared,
            IsDelayedDurability,
            MemoryAddress,
            DatabaseAddress,
            ThreadId,
            ReadSetRowCount,
            WriteSetRowCount,
            ScanSetCount,
            SavepointGarbageCount,
            LogBytesRequired,
            CountOfAllocations,
            AllocatedBytes,
            ReservedBytes,
            CommitDependencyCount,
            CommitDependencyTotalAttemptCount,
            ScanArea,
            ScanAreaDesc,
            ScanLocation,
            Dependent1Address,
            Dependent2Address,
            Dependent3Address,
            Dependent4Address,
            Dependent5Address,
            Dependent6Address,
            Dependent7Address,
            Dependent8Address);
    }

    public List<Types.DmDbXtpTransactionsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpTransactionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
