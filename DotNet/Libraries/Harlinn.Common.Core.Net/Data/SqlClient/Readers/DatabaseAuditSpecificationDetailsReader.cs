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

public class DatabaseAuditSpecificationDetailsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_audit_specification_details]";
    public const string TableName = "database_audit_specification_details";
    public const string ShortName = "dasd";
    public const string Sql = """
        SELECT
          dasd.[database_specification_id],
          dasd.[audit_action_id],
          dasd.[audit_action_name],
          dasd.[Class],
          dasd.[class_desc],
          dasd.[major_id],
          dasd.[minor_id],
          dasd.[audited_principal_id],
          dasd.[audited_result],
          dasd.[is_group]
        FROM
          [sys].[database_audit_specification_details] dasd
        """;

    public const int DATABASESPECIFICATIONID_FIELD_ID = 0;
    public const int AUDITACTIONID_FIELD_ID = 1;
    public const int AUDITACTIONNAME_FIELD_ID = 2;
    public const int CLASS_FIELD_ID = 3;
    public const int CLASSDESC_FIELD_ID = 4;
    public const int MAJORID_FIELD_ID = 5;
    public const int MINORID_FIELD_ID = 6;
    public const int AUDITEDPRINCIPALID_FIELD_ID = 7;
    public const int AUDITEDRESULT_FIELD_ID = 8;
    public const int ISGROUP_FIELD_ID = 9;


    public DatabaseAuditSpecificationDetailsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseAuditSpecificationDetailsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseAuditSpecificationDetailsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseSpecificationId
    {
        get
        {
            return base.GetInt32(DATABASESPECIFICATIONID_FIELD_ID);
        }
    }

    public string AuditActionId
    {
        get
        {
            return base.GetString(AUDITACTIONID_FIELD_ID);
        }
    }

    public string? AuditActionName
    {
        get
        {
            return base.GetNullableString(AUDITACTIONNAME_FIELD_ID);
        }
    }

    public byte Class
    {
        get
        {
            return base.GetByte(CLASS_FIELD_ID);
        }
    }

    public string? ClassDesc
    {
        get
        {
            return base.GetNullableString(CLASSDESC_FIELD_ID);
        }
    }

    public int MajorId
    {
        get
        {
            return base.GetInt32(MAJORID_FIELD_ID);
        }
    }

    public int MinorId
    {
        get
        {
            return base.GetInt32(MINORID_FIELD_ID);
        }
    }

    public int AuditedPrincipalId
    {
        get
        {
            return base.GetInt32(AUDITEDPRINCIPALID_FIELD_ID);
        }
    }

    public string? AuditedResult
    {
        get
        {
            return base.GetNullableString(AUDITEDRESULT_FIELD_ID);
        }
    }

    public bool? IsGroup
    {
        get
        {
            return base.GetNullableBoolean(ISGROUP_FIELD_ID);
        }
    }


    public Types.DatabaseAuditSpecificationDetailsDataType ToDataObject()
    {
        return new Types.DatabaseAuditSpecificationDetailsDataType(DatabaseSpecificationId,
            AuditActionId,
            AuditActionName,
            Class,
            ClassDesc,
            MajorId,
            MinorId,
            AuditedPrincipalId,
            AuditedResult,
            IsGroup);
    }

    public List<Types.DatabaseAuditSpecificationDetailsDataType> ToList()
    {
        var list = new List<Types.DatabaseAuditSpecificationDetailsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
