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

public class AssembliesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[assemblies]";
    public const string TableName = "assemblies";
    public const string ShortName = "a0";
    public const string Sql = """
        SELECT
          a0.[Name],
          a0.[principal_id],
          a0.[assembly_id],
          a0.[clr_name],
          a0.[permission_set],
          a0.[permission_set_desc],
          a0.[is_visible],
          a0.[create_date],
          a0.[modify_date],
          a0.[is_user_defined]
        FROM
          [sys].[assemblies] a0
        """;

    public const int NAME_FIELD_ID = 0;
    public const int PRINCIPALID_FIELD_ID = 1;
    public const int ASSEMBLYID_FIELD_ID = 2;
    public const int CLRNAME_FIELD_ID = 3;
    public const int PERMISSIONSET_FIELD_ID = 4;
    public const int PERMISSIONSETDESC_FIELD_ID = 5;
    public const int ISVISIBLE_FIELD_ID = 6;
    public const int CREATEDATE_FIELD_ID = 7;
    public const int MODIFYDATE_FIELD_ID = 8;
    public const int ISUSERDEFINED_FIELD_ID = 9;


    public AssembliesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AssembliesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AssembliesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int AssemblyId
    {
        get
        {
            return base.GetInt32(ASSEMBLYID_FIELD_ID);
        }
    }

    public string? ClrName
    {
        get
        {
            return base.GetNullableString(CLRNAME_FIELD_ID);
        }
    }

    public byte? PermissionSet
    {
        get
        {
            return base.GetNullableByte(PERMISSIONSET_FIELD_ID);
        }
    }

    public string? PermissionSetDesc
    {
        get
        {
            return base.GetNullableString(PERMISSIONSETDESC_FIELD_ID);
        }
    }

    public bool IsVisible
    {
        get
        {
            return base.GetBoolean(ISVISIBLE_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public bool? IsUserDefined
    {
        get
        {
            return base.GetNullableBoolean(ISUSERDEFINED_FIELD_ID);
        }
    }


    public Types.AssembliesDataType ToDataObject()
    {
        return new Types.AssembliesDataType(Name,
            PrincipalId,
            AssemblyId,
            ClrName,
            PermissionSet,
            PermissionSetDesc,
            IsVisible,
            CreateDate,
            ModifyDate,
            IsUserDefined);
    }

    public List<Types.AssembliesDataType> ToList()
    {
        var list = new List<Types.AssembliesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
