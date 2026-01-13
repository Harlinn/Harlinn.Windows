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

public class DmAuditClassTypeMapReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_audit_class_type_map]";
    public const string TableName = "dm_audit_class_type_map";
    public const string ShortName = "dactm";
    public const string Sql = """
        SELECT
          dactm.[class_type],
          dactm.[class_type_desc],
          dactm.[securable_class_desc]
        FROM
          [sys].[dm_audit_class_type_map] dactm
        """;

    public const int CLASSTYPE_FIELD_ID = 0;
    public const int CLASSTYPEDESC_FIELD_ID = 1;
    public const int SECURABLECLASSDESC_FIELD_ID = 2;


    public DmAuditClassTypeMapReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmAuditClassTypeMapReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmAuditClassTypeMapReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ClassType
    {
        get
        {
            return base.GetNullableString(CLASSTYPE_FIELD_ID);
        }
    }

    public string? ClassTypeDesc
    {
        get
        {
            return base.GetNullableString(CLASSTYPEDESC_FIELD_ID);
        }
    }

    public string? SecurableClassDesc
    {
        get
        {
            return base.GetNullableString(SECURABLECLASSDESC_FIELD_ID);
        }
    }


    public Types.DmAuditClassTypeMapDataType ToDataObject()
    {
        return new Types.DmAuditClassTypeMapDataType(ClassType,
            ClassTypeDesc,
            SecurableClassDesc);
    }

    public List<Types.DmAuditClassTypeMapDataType> ToList()
    {
        var list = new List<Types.DmAuditClassTypeMapDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
