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

public class AssemblyTypesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[assembly_types]";
    public const string TableName = "assembly_types";
    public const string ShortName = "at";
    public const string Sql = """
        SELECT
          at.[Name],
          at.[system_type_id],
          at.[user_type_id],
          at.[schema_id],
          at.[principal_id],
          at.[max_length],
          at.[Precision],
          at.[Scale],
          at.[collation_name],
          at.[is_nullable],
          at.[is_user_defined],
          at.[is_assembly_type],
          at.[default_object_id],
          at.[rule_object_id],
          at.[assembly_id],
          at.[assembly_class],
          at.[is_binary_ordered],
          at.[is_fixed_length],
          at.[prog_id],
          at.[assembly_qualified_name],
          at.[is_table_type]
        FROM
          [sys].[assembly_types] at
        """;

    public const int NAME_FIELD_ID = 0;
    public const int SYSTEMTYPEID_FIELD_ID = 1;
    public const int USERTYPEID_FIELD_ID = 2;
    public const int SCHEMAID_FIELD_ID = 3;
    public const int PRINCIPALID_FIELD_ID = 4;
    public const int MAXLENGTH_FIELD_ID = 5;
    public const int PRECISION_FIELD_ID = 6;
    public const int SCALE_FIELD_ID = 7;
    public const int COLLATIONNAME_FIELD_ID = 8;
    public const int ISNULLABLE_FIELD_ID = 9;
    public const int ISUSERDEFINED_FIELD_ID = 10;
    public const int ISASSEMBLYTYPE_FIELD_ID = 11;
    public const int DEFAULTOBJECTID_FIELD_ID = 12;
    public const int RULEOBJECTID_FIELD_ID = 13;
    public const int ASSEMBLYID_FIELD_ID = 14;
    public const int ASSEMBLYCLASS_FIELD_ID = 15;
    public const int ISBINARYORDERED_FIELD_ID = 16;
    public const int ISFIXEDLENGTH_FIELD_ID = 17;
    public const int PROGID_FIELD_ID = 18;
    public const int ASSEMBLYQUALIFIEDNAME_FIELD_ID = 19;
    public const int ISTABLETYPE_FIELD_ID = 20;


    public AssemblyTypesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AssemblyTypesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AssemblyTypesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte SystemTypeId
    {
        get
        {
            return base.GetByte(SYSTEMTYPEID_FIELD_ID);
        }
    }

    public int UserTypeId
    {
        get
        {
            return base.GetInt32(USERTYPEID_FIELD_ID);
        }
    }

    public int SchemaId
    {
        get
        {
            return base.GetInt32(SCHEMAID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public short MaxLength
    {
        get
        {
            return base.GetInt16(MAXLENGTH_FIELD_ID);
        }
    }

    public byte Precision
    {
        get
        {
            return base.GetByte(PRECISION_FIELD_ID);
        }
    }

    public byte Scale
    {
        get
        {
            return base.GetByte(SCALE_FIELD_ID);
        }
    }

    public string? CollationName
    {
        get
        {
            return base.GetNullableString(COLLATIONNAME_FIELD_ID);
        }
    }

    public bool? IsNullable
    {
        get
        {
            return base.GetNullableBoolean(ISNULLABLE_FIELD_ID);
        }
    }

    public bool IsUserDefined
    {
        get
        {
            return base.GetBoolean(ISUSERDEFINED_FIELD_ID);
        }
    }

    public bool IsAssemblyType
    {
        get
        {
            return base.GetBoolean(ISASSEMBLYTYPE_FIELD_ID);
        }
    }

    public int DefaultObjectId
    {
        get
        {
            return base.GetInt32(DEFAULTOBJECTID_FIELD_ID);
        }
    }

    public int RuleObjectId
    {
        get
        {
            return base.GetInt32(RULEOBJECTID_FIELD_ID);
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

    public bool? IsBinaryOrdered
    {
        get
        {
            return base.GetNullableBoolean(ISBINARYORDERED_FIELD_ID);
        }
    }

    public bool? IsFixedLength
    {
        get
        {
            return base.GetNullableBoolean(ISFIXEDLENGTH_FIELD_ID);
        }
    }

    public string? ProgId
    {
        get
        {
            return base.GetNullableString(PROGID_FIELD_ID);
        }
    }

    public string? AssemblyQualifiedName
    {
        get
        {
            return base.GetNullableString(ASSEMBLYQUALIFIEDNAME_FIELD_ID);
        }
    }

    public bool IsTableType
    {
        get
        {
            return base.GetBoolean(ISTABLETYPE_FIELD_ID);
        }
    }


    public Types.AssemblyTypesDataType ToDataObject()
    {
        return new Types.AssemblyTypesDataType(Name,
            SystemTypeId,
            UserTypeId,
            SchemaId,
            PrincipalId,
            MaxLength,
            Precision,
            Scale,
            CollationName,
            IsNullable,
            IsUserDefined,
            IsAssemblyType,
            DefaultObjectId,
            RuleObjectId,
            AssemblyId,
            AssemblyClass,
            IsBinaryOrdered,
            IsFixedLength,
            ProgId,
            AssemblyQualifiedName,
            IsTableType);
    }

    public List<Types.AssemblyTypesDataType> ToList()
    {
        var list = new List<Types.AssemblyTypesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
