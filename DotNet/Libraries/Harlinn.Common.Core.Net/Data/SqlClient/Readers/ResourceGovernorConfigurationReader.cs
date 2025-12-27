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

public class ResourceGovernorConfigurationReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[resource_governor_configuration]";
    public const string TableName = "resource_governor_configuration";
    public const string ShortName = "rgc";
    public const string Sql = """
        SELECT
          rgc.[classifier_function_id],
          rgc.[is_enabled],
          rgc.[max_outstanding_io_per_volume]
        FROM
          [sys].[resource_governor_configuration] rgc
        """;

    public const int CLASSIFIERFUNCTIONID_FIELD_ID = 0;
    public const int ISENABLED_FIELD_ID = 1;
    public const int MAXOUTSTANDINGIOPERVOLUME_FIELD_ID = 2;


    public ResourceGovernorConfigurationReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorConfigurationReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorConfigurationReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool IsEnabled
    {
        get
        {
            return base.GetBoolean(ISENABLED_FIELD_ID);
        }
    }

    public int MaxOutstandingIoPerVolume
    {
        get
        {
            return base.GetInt32(MAXOUTSTANDINGIOPERVOLUME_FIELD_ID);
        }
    }


    public Types.ResourceGovernorConfigurationDataType ToDataObject()
    {
        return new Types.ResourceGovernorConfigurationDataType(ClassifierFunctionId,
            IsEnabled,
            MaxOutstandingIoPerVolume);
    }

    public List<Types.ResourceGovernorConfigurationDataType> ToList()
    {
        var list = new List<Types.ResourceGovernorConfigurationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
