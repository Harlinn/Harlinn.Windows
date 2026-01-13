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

public class AllColumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[all_columns]";
    public const string TableName = "all_columns";
    public const string ShortName = "ac";
    public const string Sql = """
        SELECT
          ac.[object_id],
          ac.[Name],
          ac.[column_id],
          ac.[system_type_id],
          ac.[user_type_id],
          ac.[max_length],
          ac.[Precision],
          ac.[Scale],
          ac.[collation_name],
          ac.[is_nullable],
          ac.[is_ansi_padded],
          ac.[is_rowguidcol],
          ac.[is_identity],
          ac.[is_computed],
          ac.[is_filestream],
          ac.[is_replicated],
          ac.[is_non_sql_subscribed],
          ac.[is_merge_published],
          ac.[is_dts_replicated],
          ac.[is_xml_document],
          ac.[xml_collection_id],
          ac.[default_object_id],
          ac.[rule_object_id],
          ac.[is_sparse],
          ac.[is_column_set],
          ac.[generated_always_type],
          ac.[generated_always_type_desc],
          ac.[encryption_type],
          ac.[encryption_type_desc],
          ac.[encryption_algorithm_name],
          ac.[column_encryption_key_id],
          ac.[column_encryption_key_database_name],
          ac.[is_hidden],
          ac.[is_masked],
          ac.[graph_type],
          ac.[graph_type_desc],
          t.[name] AS [type_name]
        FROM
          [sys].[all_columns] ac
        INNER JOIN sys.types t ON ac.user_type_id = t.user_type_id
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int COLUMNID_FIELD_ID = 2;
    public const int SYSTEMTYPEID_FIELD_ID = 3;
    public const int USERTYPEID_FIELD_ID = 4;
    public const int MAXLENGTH_FIELD_ID = 5;
    public const int PRECISION_FIELD_ID = 6;
    public const int SCALE_FIELD_ID = 7;
    public const int COLLATIONNAME_FIELD_ID = 8;
    public const int ISNULLABLE_FIELD_ID = 9;
    public const int ISANSIPADDED_FIELD_ID = 10;
    public const int ISROWGUIDCOL_FIELD_ID = 11;
    public const int ISIDENTITY_FIELD_ID = 12;
    public const int ISCOMPUTED_FIELD_ID = 13;
    public const int ISFILESTREAM_FIELD_ID = 14;
    public const int ISREPLICATED_FIELD_ID = 15;
    public const int ISNONSQLSUBSCRIBED_FIELD_ID = 16;
    public const int ISMERGEPUBLISHED_FIELD_ID = 17;
    public const int ISDTSREPLICATED_FIELD_ID = 18;
    public const int ISXMLDOCUMENT_FIELD_ID = 19;
    public const int XMLCOLLECTIONID_FIELD_ID = 20;
    public const int DEFAULTOBJECTID_FIELD_ID = 21;
    public const int RULEOBJECTID_FIELD_ID = 22;
    public const int ISSPARSE_FIELD_ID = 23;
    public const int ISCOLUMNSET_FIELD_ID = 24;
    public const int GENERATEDALWAYSTYPE_FIELD_ID = 25;
    public const int GENERATEDALWAYSTYPEDESC_FIELD_ID = 26;
    public const int ENCRYPTIONTYPE_FIELD_ID = 27;
    public const int ENCRYPTIONTYPEDESC_FIELD_ID = 28;
    public const int ENCRYPTIONALGORITHMNAME_FIELD_ID = 29;
    public const int COLUMNENCRYPTIONKEYID_FIELD_ID = 30;
    public const int COLUMNENCRYPTIONKEYDATABASENAME_FIELD_ID = 31;
    public const int ISHIDDEN_FIELD_ID = 32;
    public const int ISMASKED_FIELD_ID = 33;
    public const int GRAPHTYPE_FIELD_ID = 34;
    public const int GRAPHTYPEDESC_FIELD_ID = 35;
    public const int TYPENAME_FIELD_ID = 36;

    public AllColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AllColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AllColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int ColumnId
    {
        get
        {
            return base.GetInt32(COLUMNID_FIELD_ID);
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

    public bool IsAnsiPadded
    {
        get
        {
            return base.GetBoolean(ISANSIPADDED_FIELD_ID);
        }
    }

    public bool IsRowguidcol
    {
        get
        {
            return base.GetBoolean(ISROWGUIDCOL_FIELD_ID);
        }
    }

    public bool IsIdentity
    {
        get
        {
            return base.GetBoolean(ISIDENTITY_FIELD_ID);
        }
    }

    public bool IsComputed
    {
        get
        {
            return base.GetBoolean(ISCOMPUTED_FIELD_ID);
        }
    }

    public bool IsFilestream
    {
        get
        {
            return base.GetBoolean(ISFILESTREAM_FIELD_ID);
        }
    }

    public bool? IsReplicated
    {
        get
        {
            return base.GetNullableBoolean(ISREPLICATED_FIELD_ID);
        }
    }

    public bool? IsNonSqlSubscribed
    {
        get
        {
            return base.GetNullableBoolean(ISNONSQLSUBSCRIBED_FIELD_ID);
        }
    }

    public bool? IsMergePublished
    {
        get
        {
            return base.GetNullableBoolean(ISMERGEPUBLISHED_FIELD_ID);
        }
    }

    public bool? IsDtsReplicated
    {
        get
        {
            return base.GetNullableBoolean(ISDTSREPLICATED_FIELD_ID);
        }
    }

    public bool IsXmlDocument
    {
        get
        {
            return base.GetBoolean(ISXMLDOCUMENT_FIELD_ID);
        }
    }

    public int XmlCollectionId
    {
        get
        {
            return base.GetInt32(XMLCOLLECTIONID_FIELD_ID);
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

    public bool? IsSparse
    {
        get
        {
            return base.GetNullableBoolean(ISSPARSE_FIELD_ID);
        }
    }

    public bool? IsColumnSet
    {
        get
        {
            return base.GetNullableBoolean(ISCOLUMNSET_FIELD_ID);
        }
    }

    public byte? GeneratedAlwaysType
    {
        get
        {
            return base.GetNullableByte(GENERATEDALWAYSTYPE_FIELD_ID);
        }
    }

    public string? GeneratedAlwaysTypeDesc
    {
        get
        {
            return base.GetNullableString(GENERATEDALWAYSTYPEDESC_FIELD_ID);
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

    public bool? IsHidden
    {
        get
        {
            return base.GetNullableBoolean(ISHIDDEN_FIELD_ID);
        }
    }

    public bool IsMasked
    {
        get
        {
            return base.GetBoolean(ISMASKED_FIELD_ID);
        }
    }

    public int? GraphType
    {
        get
        {
            return base.GetNullableInt32(GRAPHTYPE_FIELD_ID);
        }
    }

    public string? GraphTypeDesc
    {
        get
        {
            return base.GetNullableString(GRAPHTYPEDESC_FIELD_ID);
        }
    }

    public string TypeName
    {
        get
        {
            return base.GetString(TYPENAME_FIELD_ID);
        }
    }


    public Types.AllColumnsDataType ToDataObject()
    {
        return new Types.AllColumnsDataType(ObjectId,
            Name,
            ColumnId,
            SystemTypeId,
            UserTypeId,
            MaxLength,
            Precision,
            Scale,
            CollationName,
            IsNullable,
            IsAnsiPadded,
            IsRowguidcol,
            IsIdentity,
            IsComputed,
            IsFilestream,
            IsReplicated,
            IsNonSqlSubscribed,
            IsMergePublished,
            IsDtsReplicated,
            IsXmlDocument,
            XmlCollectionId,
            DefaultObjectId,
            RuleObjectId,
            IsSparse,
            IsColumnSet,
            GeneratedAlwaysType,
            GeneratedAlwaysTypeDesc,
            EncryptionType,
            EncryptionTypeDesc,
            EncryptionAlgorithmName,
            ColumnEncryptionKeyId,
            ColumnEncryptionKeyDatabaseName,
            IsHidden,
            IsMasked,
            GraphType,
            GraphTypeDesc,
            TypeName);
    }

    public List<Types.AllColumnsDataType> ToList()
    {
        var list = new List<Types.AllColumnsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
