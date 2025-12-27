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

public class ServerMemoryOptimizedHybridBufferPoolConfigurationReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_memory_optimized_hybrid_buffer_pool_configuration]";
    public const string TableName = "server_memory_optimized_hybrid_buffer_pool_configuration";
    public const string ShortName = "smohbpc";
    public const string Sql = """
        SELECT
          smohbpc.[is_configured],
          smohbpc.[is_enabled]
        FROM
          [sys].[server_memory_optimized_hybrid_buffer_pool_configuration] smohbpc
        """;

    public const int ISCONFIGURED_FIELD_ID = 0;
    public const int ISENABLED_FIELD_ID = 1;


    public ServerMemoryOptimizedHybridBufferPoolConfigurationReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerMemoryOptimizedHybridBufferPoolConfigurationReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerMemoryOptimizedHybridBufferPoolConfigurationReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public object? IsConfigured
    {
        get
        {
            return base.GetNullableValue(ISCONFIGURED_FIELD_ID);
        }
    }

    public object? IsEnabled
    {
        get
        {
            return base.GetNullableValue(ISENABLED_FIELD_ID);
        }
    }


    public Types.ServerMemoryOptimizedHybridBufferPoolConfigurationDataType ToDataObject()
    {
        return new Types.ServerMemoryOptimizedHybridBufferPoolConfigurationDataType(IsConfigured,
            IsEnabled);
    }

    public List<Types.ServerMemoryOptimizedHybridBufferPoolConfigurationDataType> ToList()
    {
        var list = new List<Types.ServerMemoryOptimizedHybridBufferPoolConfigurationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
