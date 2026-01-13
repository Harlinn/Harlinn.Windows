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

public class DmOsMemoryBrokerClerksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_broker_clerks]";
    public const string TableName = "dm_os_memory_broker_clerks";
    public const string ShortName = "dombc";
    public const string Sql = """
        SELECT
          dombc.[clerk_name],
          dombc.[total_kb],
          dombc.[simulated_kb],
          dombc.[simulation_benefit],
          dombc.[internal_benefit],
          dombc.[external_benefit],
          dombc.[value_of_memory],
          dombc.[periodic_freed_kb],
          dombc.[internal_freed_kb]
        FROM
          [sys].[dm_os_memory_broker_clerks] dombc
        """;

    public const int CLERKNAME_FIELD_ID = 0;
    public const int TOTALKB_FIELD_ID = 1;
    public const int SIMULATEDKB_FIELD_ID = 2;
    public const int SIMULATIONBENEFIT_FIELD_ID = 3;
    public const int INTERNALBENEFIT_FIELD_ID = 4;
    public const int EXTERNALBENEFIT_FIELD_ID = 5;
    public const int VALUEOFMEMORY_FIELD_ID = 6;
    public const int PERIODICFREEDKB_FIELD_ID = 7;
    public const int INTERNALFREEDKB_FIELD_ID = 8;


    public DmOsMemoryBrokerClerksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryBrokerClerksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryBrokerClerksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string ClerkName
    {
        get
        {
            return base.GetString(CLERKNAME_FIELD_ID);
        }
    }

    public long TotalKb
    {
        get
        {
            return base.GetInt64(TOTALKB_FIELD_ID);
        }
    }

    public long SimulatedKb
    {
        get
        {
            return base.GetInt64(SIMULATEDKB_FIELD_ID);
        }
    }

    public double SimulationBenefit
    {
        get
        {
            return base.GetDouble(SIMULATIONBENEFIT_FIELD_ID);
        }
    }

    public double InternalBenefit
    {
        get
        {
            return base.GetDouble(INTERNALBENEFIT_FIELD_ID);
        }
    }

    public double ExternalBenefit
    {
        get
        {
            return base.GetDouble(EXTERNALBENEFIT_FIELD_ID);
        }
    }

    public double ValueOfMemory
    {
        get
        {
            return base.GetDouble(VALUEOFMEMORY_FIELD_ID);
        }
    }

    public long PeriodicFreedKb
    {
        get
        {
            return base.GetInt64(PERIODICFREEDKB_FIELD_ID);
        }
    }

    public long InternalFreedKb
    {
        get
        {
            return base.GetInt64(INTERNALFREEDKB_FIELD_ID);
        }
    }


    public Types.DmOsMemoryBrokerClerksDataType ToDataObject()
    {
        return new Types.DmOsMemoryBrokerClerksDataType(ClerkName,
            TotalKb,
            SimulatedKb,
            SimulationBenefit,
            InternalBenefit,
            ExternalBenefit,
            ValueOfMemory,
            PeriodicFreedKb,
            InternalFreedKb);
    }

    public List<Types.DmOsMemoryBrokerClerksDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryBrokerClerksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
