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

public class TypeAssemblyUsagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[type_assembly_usages]";
    public const string TableName = "type_assembly_usages";
    public const string ShortName = "tau";
    public const string Sql = """
        SELECT
          tau.[user_type_id],
          tau.[assembly_id]
        FROM
          [sys].[type_assembly_usages] tau
        """;

    public const int USERTYPEID_FIELD_ID = 0;
    public const int ASSEMBLYID_FIELD_ID = 1;


    public TypeAssemblyUsagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TypeAssemblyUsagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TypeAssemblyUsagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int UserTypeId
    {
        get
        {
            return base.GetInt32(USERTYPEID_FIELD_ID);
        }
    }

    public int AssemblyId
    {
        get
        {
            return base.GetInt32(ASSEMBLYID_FIELD_ID);
        }
    }


    public Types.TypeAssemblyUsagesDataType ToDataObject()
    {
        return new Types.TypeAssemblyUsagesDataType(UserTypeId,
            AssemblyId);
    }

    public List<Types.TypeAssemblyUsagesDataType> ToList()
    {
        var list = new List<Types.TypeAssemblyUsagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
