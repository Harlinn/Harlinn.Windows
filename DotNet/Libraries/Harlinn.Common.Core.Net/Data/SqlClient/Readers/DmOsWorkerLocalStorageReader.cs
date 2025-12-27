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

public class DmOsWorkerLocalStorageReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_worker_local_storage]";
    public const string TableName = "dm_os_worker_local_storage";
    public const string ShortName = "dowls";
    public const string Sql = """
        SELECT
          dowls.[worker_address],
          dowls.[comp_exec_ctxt_address],
          dowls.[ec_address],
          dowls.[broker_address],
          dowls.[task_proxy_address],
          dowls.[msqlxact_address],
          dowls.[sql_prof_address],
          dowls.[stack_checker_address],
          dowls.[host_task_address],
          dowls.[sni_error_address],
          dowls.[queryscan_address],
          dowls.[diag_address],
          dowls.[query_driver_address],
          dowls.[federatedxact_address],
          dowls.[filestream_address],
          dowls.[qe_cc_address],
          dowls.[xtp_address],
          dowls.[gq_address],
          dowls.[extensibility_ctxt_address]
        FROM
          [sys].[dm_os_worker_local_storage] dowls
        """;

    public const int WORKERADDRESS_FIELD_ID = 0;
    public const int COMPEXECCTXTADDRESS_FIELD_ID = 1;
    public const int ECADDRESS_FIELD_ID = 2;
    public const int BROKERADDRESS_FIELD_ID = 3;
    public const int TASKPROXYADDRESS_FIELD_ID = 4;
    public const int MSQLXACTADDRESS_FIELD_ID = 5;
    public const int SQLPROFADDRESS_FIELD_ID = 6;
    public const int STACKCHECKERADDRESS_FIELD_ID = 7;
    public const int HOSTTASKADDRESS_FIELD_ID = 8;
    public const int SNIERRORADDRESS_FIELD_ID = 9;
    public const int QUERYSCANADDRESS_FIELD_ID = 10;
    public const int DIAGADDRESS_FIELD_ID = 11;
    public const int QUERYDRIVERADDRESS_FIELD_ID = 12;
    public const int FEDERATEDXACTADDRESS_FIELD_ID = 13;
    public const int FILESTREAMADDRESS_FIELD_ID = 14;
    public const int QECCADDRESS_FIELD_ID = 15;
    public const int XTPADDRESS_FIELD_ID = 16;
    public const int GQADDRESS_FIELD_ID = 17;
    public const int EXTENSIBILITYCTXTADDRESS_FIELD_ID = 18;


    public DmOsWorkerLocalStorageReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsWorkerLocalStorageReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsWorkerLocalStorageReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] WorkerAddress
    {
        get
        {
            return base.GetBinary(WORKERADDRESS_FIELD_ID);
        }
    }

    public byte[] CompExecCtxtAddress
    {
        get
        {
            return base.GetBinary(COMPEXECCTXTADDRESS_FIELD_ID);
        }
    }

    public byte[] EcAddress
    {
        get
        {
            return base.GetBinary(ECADDRESS_FIELD_ID);
        }
    }

    public byte[] BrokerAddress
    {
        get
        {
            return base.GetBinary(BROKERADDRESS_FIELD_ID);
        }
    }

    public byte[] TaskProxyAddress
    {
        get
        {
            return base.GetBinary(TASKPROXYADDRESS_FIELD_ID);
        }
    }

    public byte[] MsqlxactAddress
    {
        get
        {
            return base.GetBinary(MSQLXACTADDRESS_FIELD_ID);
        }
    }

    public byte[] SqlProfAddress
    {
        get
        {
            return base.GetBinary(SQLPROFADDRESS_FIELD_ID);
        }
    }

    public byte[] StackCheckerAddress
    {
        get
        {
            return base.GetBinary(STACKCHECKERADDRESS_FIELD_ID);
        }
    }

    public byte[] HostTaskAddress
    {
        get
        {
            return base.GetBinary(HOSTTASKADDRESS_FIELD_ID);
        }
    }

    public byte[] SniErrorAddress
    {
        get
        {
            return base.GetBinary(SNIERRORADDRESS_FIELD_ID);
        }
    }

    public byte[] QueryscanAddress
    {
        get
        {
            return base.GetBinary(QUERYSCANADDRESS_FIELD_ID);
        }
    }

    public byte[] DiagAddress
    {
        get
        {
            return base.GetBinary(DIAGADDRESS_FIELD_ID);
        }
    }

    public byte[] QueryDriverAddress
    {
        get
        {
            return base.GetBinary(QUERYDRIVERADDRESS_FIELD_ID);
        }
    }

    public byte[] FederatedxactAddress
    {
        get
        {
            return base.GetBinary(FEDERATEDXACTADDRESS_FIELD_ID);
        }
    }

    public byte[] FilestreamAddress
    {
        get
        {
            return base.GetBinary(FILESTREAMADDRESS_FIELD_ID);
        }
    }

    public byte[] QeCcAddress
    {
        get
        {
            return base.GetBinary(QECCADDRESS_FIELD_ID);
        }
    }

    public byte[] XtpAddress
    {
        get
        {
            return base.GetBinary(XTPADDRESS_FIELD_ID);
        }
    }

    public byte[] GqAddress
    {
        get
        {
            return base.GetBinary(GQADDRESS_FIELD_ID);
        }
    }

    public byte[] ExtensibilityCtxtAddress
    {
        get
        {
            return base.GetBinary(EXTENSIBILITYCTXTADDRESS_FIELD_ID);
        }
    }


    public Types.DmOsWorkerLocalStorageDataType ToDataObject()
    {
        return new Types.DmOsWorkerLocalStorageDataType(WorkerAddress,
            CompExecCtxtAddress,
            EcAddress,
            BrokerAddress,
            TaskProxyAddress,
            MsqlxactAddress,
            SqlProfAddress,
            StackCheckerAddress,
            HostTaskAddress,
            SniErrorAddress,
            QueryscanAddress,
            DiagAddress,
            QueryDriverAddress,
            FederatedxactAddress,
            FilestreamAddress,
            QeCcAddress,
            XtpAddress,
            GqAddress,
            ExtensibilityCtxtAddress);
    }

    public List<Types.DmOsWorkerLocalStorageDataType> ToList()
    {
        var list = new List<Types.DmOsWorkerLocalStorageDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
