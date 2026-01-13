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

public class DmClrLoadedAssembliesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_clr_loaded_assemblies]";
    public const string TableName = "dm_clr_loaded_assemblies";
    public const string ShortName = "dcla";
    public const string Sql = """
        SELECT
          dcla.[assembly_id],
          dcla.[appdomain_address],
          dcla.[load_time]
        FROM
          [sys].[dm_clr_loaded_assemblies] dcla
        """;

    public const int ASSEMBLYID_FIELD_ID = 0;
    public const int APPDOMAINADDRESS_FIELD_ID = 1;
    public const int LOADTIME_FIELD_ID = 2;


    public DmClrLoadedAssembliesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmClrLoadedAssembliesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmClrLoadedAssembliesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? AssemblyId
    {
        get
        {
            return base.GetNullableInt32(ASSEMBLYID_FIELD_ID);
        }
    }

    public byte[]? AppdomainAddress
    {
        get
        {
            return base.GetNullableBinary(APPDOMAINADDRESS_FIELD_ID);
        }
    }

    public DateTime? LoadTime
    {
        get
        {
            return base.GetNullableDateTime(LOADTIME_FIELD_ID);
        }
    }


    public Types.DmClrLoadedAssembliesDataType ToDataObject()
    {
        return new Types.DmClrLoadedAssembliesDataType(AssemblyId,
            AppdomainAddress,
            LoadTime);
    }

    public List<Types.DmClrLoadedAssembliesDataType> ToList()
    {
        var list = new List<Types.DmClrLoadedAssembliesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
