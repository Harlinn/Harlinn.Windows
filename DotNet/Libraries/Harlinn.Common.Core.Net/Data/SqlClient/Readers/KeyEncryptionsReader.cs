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

public class KeyEncryptionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[key_encryptions]";
    public const string TableName = "key_encryptions";
    public const string ShortName = "ke";
    public const string Sql = """
        SELECT
          ke.[key_id],
          ke.[Thumbprint],
          ke.[crypt_type],
          ke.[crypt_type_desc],
          ke.[crypt_property]
        FROM
          [sys].[key_encryptions] ke
        """;

    public const int KEYID_FIELD_ID = 0;
    public const int THUMBPRINT_FIELD_ID = 1;
    public const int CRYPTTYPE_FIELD_ID = 2;
    public const int CRYPTTYPEDESC_FIELD_ID = 3;
    public const int CRYPTPROPERTY_FIELD_ID = 4;


    public KeyEncryptionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public KeyEncryptionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public KeyEncryptionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int KeyId
    {
        get
        {
            return base.GetInt32(KEYID_FIELD_ID);
        }
    }

    public byte[]? Thumbprint
    {
        get
        {
            return base.GetNullableBinary(THUMBPRINT_FIELD_ID);
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

    public byte[]? CryptProperty
    {
        get
        {
            return base.GetNullableBinary(CRYPTPROPERTY_FIELD_ID);
        }
    }


    public Types.KeyEncryptionsDataType ToDataObject()
    {
        return new Types.KeyEncryptionsDataType(KeyId,
            Thumbprint,
            CryptType,
            CryptTypeDesc,
            CryptProperty);
    }

    public List<Types.KeyEncryptionsDataType> ToList()
    {
        var list = new List<Types.KeyEncryptionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
