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

public class AssemblyModulesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[assembly_modules]";
    public const string TableName = "assembly_modules";
    public const string ShortName = "am";
    public const string Sql = """
        SELECT
          am.[object_id],
          am.[assembly_id],
          am.[assembly_class],
          am.[assembly_method],
          am.[null_on_null_input],
          am.[execute_as_principal_id]
        FROM
          [sys].[assembly_modules] am
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int ASSEMBLYID_FIELD_ID = 1;
    public const int ASSEMBLYCLASS_FIELD_ID = 2;
    public const int ASSEMBLYMETHOD_FIELD_ID = 3;
    public const int NULLONNULLINPUT_FIELD_ID = 4;
    public const int EXECUTEASPRINCIPALID_FIELD_ID = 5;


    public AssemblyModulesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AssemblyModulesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AssemblyModulesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool? NullOnNullInput
    {
        get
        {
            return base.GetNullableBoolean(NULLONNULLINPUT_FIELD_ID);
        }
    }

    public int? ExecuteAsPrincipalId
    {
        get
        {
            return base.GetNullableInt32(EXECUTEASPRINCIPALID_FIELD_ID);
        }
    }


    public Types.AssemblyModulesDataType ToDataObject()
    {
        return new Types.AssemblyModulesDataType(ObjectId,
            AssemblyId,
            AssemblyClass,
            AssemblyMethod,
            NullOnNullInput,
            ExecuteAsPrincipalId);
    }

    public List<Types.AssemblyModulesDataType> ToList()
    {
        var list = new List<Types.AssemblyModulesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
