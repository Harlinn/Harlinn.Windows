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

public class CryptPropertiesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[crypt_properties]";
    public const string TableName = "crypt_properties";
    public const string ShortName = "cp0";
    public const string Sql = """
        SELECT
          cp0.[Class],
          cp0.[class_desc],
          cp0.[major_id],
          cp0.[Thumbprint],
          cp0.[crypt_type],
          cp0.[crypt_type_desc],
          cp0.[crypt_property]
        FROM
          [sys].[crypt_properties] cp0
        """;

    public const int CLASS_FIELD_ID = 0;
    public const int CLASSDESC_FIELD_ID = 1;
    public const int MAJORID_FIELD_ID = 2;
    public const int THUMBPRINT_FIELD_ID = 3;
    public const int CRYPTTYPE_FIELD_ID = 4;
    public const int CRYPTTYPEDESC_FIELD_ID = 5;
    public const int CRYPTPROPERTY_FIELD_ID = 6;


    public CryptPropertiesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public CryptPropertiesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public CryptPropertiesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
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

    public byte[] Thumbprint
    {
        get
        {
            return base.GetBinary(THUMBPRINT_FIELD_ID);
        }
    }

    public string CryptType
    {
        get
        {
            return base.GetString(CRYPTTYPE_FIELD_ID);
        }
    }

    public string? CryptTypeDesc
    {
        get
        {
            return base.GetNullableString(CRYPTTYPEDESC_FIELD_ID);
        }
    }

    public byte[] CryptProperty
    {
        get
        {
            return base.GetBinary(CRYPTPROPERTY_FIELD_ID);
        }
    }


    public Types.CryptPropertiesDataType ToDataObject()
    {
        return new Types.CryptPropertiesDataType(Class,
            ClassDesc,
            MajorId,
            Thumbprint,
            CryptType,
            CryptTypeDesc,
            CryptProperty);
    }

    public List<Types.CryptPropertiesDataType> ToList()
    {
        var list = new List<Types.CryptPropertiesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
