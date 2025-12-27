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

public class DmResourceGovernorConfigurationReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_resource_governor_configuration]";
    public const string TableName = "dm_resource_governor_configuration";
    public const string ShortName = "drgc";
    public const string Sql = """
        SELECT
          drgc.[classifier_function_id],
          drgc.[is_reconfiguration_pending],
          drgc.[max_outstanding_io_per_volume]
        FROM
          [sys].[dm_resource_governor_configuration] drgc
        """;

    public const int CLASSIFIERFUNCTIONID_FIELD_ID = 0;
    public const int ISRECONFIGURATIONPENDING_FIELD_ID = 1;
    public const int MAXOUTSTANDINGIOPERVOLUME_FIELD_ID = 2;


    public DmResourceGovernorConfigurationReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorConfigurationReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorConfigurationReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ClassifierFunctionId
    {
        get
        {
            return base.GetInt32(CLASSIFIERFUNCTIONID_FIELD_ID);
        }
    }

    public byte IsReconfigurationPending
    {
        get
        {
            return base.GetByte(ISRECONFIGURATIONPENDING_FIELD_ID);
        }
    }

    public int MaxOutstandingIoPerVolume
    {
        get
        {
            return base.GetInt32(MAXOUTSTANDINGIOPERVOLUME_FIELD_ID);
        }
    }


    public Types.DmResourceGovernorConfigurationDataType ToDataObject()
    {
        return new Types.DmResourceGovernorConfigurationDataType(ClassifierFunctionId,
            IsReconfigurationPending,
            MaxOutstandingIoPerVolume);
    }

    public List<Types.DmResourceGovernorConfigurationDataType> ToList()
    {
        var list = new List<Types.DmResourceGovernorConfigurationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
