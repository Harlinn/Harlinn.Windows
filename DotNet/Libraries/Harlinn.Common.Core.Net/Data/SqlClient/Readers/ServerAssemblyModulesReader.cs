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

public class ServerAssemblyModulesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_assembly_modules]";
    public const string TableName = "server_assembly_modules";
    public const string ShortName = "sam";
    public const string Sql = """
        SELECT
          sam.[object_id],
          sam.[assembly_id],
          sam.[assembly_class],
          sam.[assembly_method],
          sam.[execute_as_principal_id]
        FROM
          [sys].[server_assembly_modules] sam
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int ASSEMBLYID_FIELD_ID = 1;
    public const int ASSEMBLYCLASS_FIELD_ID = 2;
    public const int ASSEMBLYMETHOD_FIELD_ID = 3;
    public const int EXECUTEASPRINCIPALID_FIELD_ID = 4;


    public ServerAssemblyModulesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerAssemblyModulesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerAssemblyModulesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int AssemblyId
    {
        get
        {
            return base.GetInt32(ASSEMBLYID_FIELD_ID);
        }
    }

    public string? AssemblyClass
    {
        get
        {
            return base.GetNullableString(ASSEMBLYCLASS_FIELD_ID);
        }
    }

    public string? AssemblyMethod
    {
        get
        {
            return base.GetNullableString(ASSEMBLYMETHOD_FIELD_ID);
        }
    }

    public int? ExecuteAsPrincipalId
    {
        get
        {
            return base.GetNullableInt32(EXECUTEASPRINCIPALID_FIELD_ID);
        }
    }


    public Types.ServerAssemblyModulesDataType ToDataObject()
    {
        return new Types.ServerAssemblyModulesDataType(ObjectId,
            AssemblyId,
            AssemblyClass,
            AssemblyMethod,
            ExecuteAsPrincipalId);
    }

    public List<Types.ServerAssemblyModulesDataType> ToList()
    {
        var list = new List<Types.ServerAssemblyModulesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
