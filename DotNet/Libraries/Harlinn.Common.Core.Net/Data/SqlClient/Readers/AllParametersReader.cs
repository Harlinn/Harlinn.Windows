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

public class AllParametersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[all_parameters]";
    public const string TableName = "all_parameters";
    public const string ShortName = "ap";
    public const string Sql = """
        SELECT
          ap.[object_id],
          ap.[Name],
          ap.[parameter_id],
          ap.[system_type_id],
          ap.[user_type_id],
          ap.[max_length],
          ap.[Precision],
          ap.[Scale],
          ap.[is_output],
          ap.[is_cursor_ref],
          ap.[has_default_value],
          ap.[is_xml_document],
          ap.[default_value],
          ap.[xml_collection_id],
          ap.[is_readonly],
          ap.[is_nullable],
          ap.[encryption_type],
          ap.[encryption_type_desc],
          ap.[encryption_algorithm_name],
          ap.[column_encryption_key_id],
          ap.[column_encryption_key_database_name]
        FROM
          [sys].[all_parameters] ap
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int PARAMETERID_FIELD_ID = 2;
    public const int SYSTEMTYPEID_FIELD_ID = 3;
    public const int USERTYPEID_FIELD_ID = 4;
    public const int MAXLENGTH_FIELD_ID = 5;
    public const int PRECISION_FIELD_ID = 6;
    public const int SCALE_FIELD_ID = 7;
    public const int ISOUTPUT_FIELD_ID = 8;
    public const int ISCURSORREF_FIELD_ID = 9;
    public const int HASDEFAULTVALUE_FIELD_ID = 10;
    public const int ISXMLDOCUMENT_FIELD_ID = 11;
    public const int DEFAULTVALUE_FIELD_ID = 12;
    public const int XMLCOLLECTIONID_FIELD_ID = 13;
    public const int ISREADONLY_FIELD_ID = 14;
    public const int ISNULLABLE_FIELD_ID = 15;
    public const int ENCRYPTIONTYPE_FIELD_ID = 16;
    public const int ENCRYPTIONTYPEDESC_FIELD_ID = 17;
    public const int ENCRYPTIONALGORITHMNAME_FIELD_ID = 18;
    public const int COLUMNENCRYPTIONKEYID_FIELD_ID = 19;
    public const int COLUMNENCRYPTIONKEYDATABASENAME_FIELD_ID = 20;


    public AllParametersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AllParametersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AllParametersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public int ParameterId
    {
        get
        {
            return base.GetInt32(PARAMETERID_FIELD_ID);
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

    public bool IsOutput
    {
        get
        {
            return base.GetBoolean(ISOUTPUT_FIELD_ID);
        }
    }

    public bool IsCursorRef
    {
        get
        {
            return base.GetBoolean(ISCURSORREF_FIELD_ID);
        }
    }

    public bool HasDefaultValue
    {
        get
        {
            return base.GetBoolean(HASDEFAULTVALUE_FIELD_ID);
        }
    }

    public bool IsXmlDocument
    {
        get
        {
            return base.GetBoolean(ISXMLDOCUMENT_FIELD_ID);
        }
    }

    public object? DefaultValue
    {
        get
        {
            return base.GetNullableValue(DEFAULTVALUE_FIELD_ID);
        }
    }

    public int XmlCollectionId
    {
        get
        {
            return base.GetInt32(XMLCOLLECTIONID_FIELD_ID);
        }
    }

    public bool IsReadonly
    {
        get
        {
            return base.GetBoolean(ISREADONLY_FIELD_ID);
        }
    }

    public bool? IsNullable
    {
        get
        {
            return base.GetNullableBoolean(ISNULLABLE_FIELD_ID);
        }
    }

    public int? EncryptionType
    {
        get
        {
            return base.GetNullableInt32(ENCRYPTIONTYPE_FIELD_ID);
        }
    }

    public string? EncryptionTypeDesc
    {
        get
        {
            return base.GetNullableString(ENCRYPTIONTYPEDESC_FIELD_ID);
        }
    }

    public string? EncryptionAlgorithmName
    {
        get
        {
            return base.GetNullableString(ENCRYPTIONALGORITHMNAME_FIELD_ID);
        }
    }

    public int? ColumnEncryptionKeyId
    {
        get
        {
            return base.GetNullableInt32(COLUMNENCRYPTIONKEYID_FIELD_ID);
        }
    }

    public string? ColumnEncryptionKeyDatabaseName
    {
        get
        {
            return base.GetNullableString(COLUMNENCRYPTIONKEYDATABASENAME_FIELD_ID);
        }
    }


    public Types.AllParametersDataType ToDataObject()
    {
        return new Types.AllParametersDataType(ObjectId,
            Name,
            ParameterId,
            SystemTypeId,
            UserTypeId,
            MaxLength,
            Precision,
            Scale,
            IsOutput,
            IsCursorRef,
            HasDefaultValue,
            IsXmlDocument,
            DefaultValue,
            XmlCollectionId,
            IsReadonly,
            IsNullable,
            EncryptionType,
            EncryptionTypeDesc,
            EncryptionAlgorithmName,
            ColumnEncryptionKeyId,
            ColumnEncryptionKeyDatabaseName);
    }

    public List<Types.AllParametersDataType> ToList()
    {
        var list = new List<Types.AllParametersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
