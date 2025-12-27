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

public class SymmetricKeysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[symmetric_keys]";
    public const string TableName = "symmetric_keys";
    public const string ShortName = "sk";
    public const string Sql = """
        SELECT
          sk.[Name],
          sk.[principal_id],
          sk.[symmetric_key_id],
          sk.[key_length],
          sk.[key_algorithm],
          sk.[algorithm_desc],
          sk.[create_date],
          sk.[modify_date],
          sk.[key_guid],
          sk.[key_thumbprint],
          sk.[provider_type],
          sk.[cryptographic_provider_guid],
          sk.[cryptographic_provider_algid]
        FROM
          [sys].[symmetric_keys] sk
        """;

    public const int NAME_FIELD_ID = 0;
    public const int PRINCIPALID_FIELD_ID = 1;
    public const int SYMMETRICKEYID_FIELD_ID = 2;
    public const int KEYLENGTH_FIELD_ID = 3;
    public const int KEYALGORITHM_FIELD_ID = 4;
    public const int ALGORITHMDESC_FIELD_ID = 5;
    public const int CREATEDATE_FIELD_ID = 6;
    public const int MODIFYDATE_FIELD_ID = 7;
    public const int KEYGUID_FIELD_ID = 8;
    public const int KEYTHUMBPRINT_FIELD_ID = 9;
    public const int PROVIDERTYPE_FIELD_ID = 10;
    public const int CRYPTOGRAPHICPROVIDERGUID_FIELD_ID = 11;
    public const int CRYPTOGRAPHICPROVIDERALGID_FIELD_ID = 12;


    public SymmetricKeysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SymmetricKeysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SymmetricKeysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int SymmetricKeyId
    {
        get
        {
            return base.GetInt32(SYMMETRICKEYID_FIELD_ID);
        }
    }

    public int KeyLength
    {
        get
        {
            return base.GetInt32(KEYLENGTH_FIELD_ID);
        }
    }

    public string KeyAlgorithm
    {
        get
        {
            return base.GetString(KEYALGORITHM_FIELD_ID);
        }
    }

    public string? AlgorithmDesc
    {
        get
        {
            return base.GetNullableString(ALGORITHMDESC_FIELD_ID);
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

    public Guid? KeyGuid
    {
        get
        {
            return base.GetNullableGuid(KEYGUID_FIELD_ID);
        }
    }

    public object? KeyThumbprint
    {
        get
        {
            return base.GetNullableValue(KEYTHUMBPRINT_FIELD_ID);
        }
    }

    public string? ProviderType
    {
        get
        {
            return base.GetNullableString(PROVIDERTYPE_FIELD_ID);
        }
    }

    public Guid? CryptographicProviderGuid
    {
        get
        {
            return base.GetNullableGuid(CRYPTOGRAPHICPROVIDERGUID_FIELD_ID);
        }
    }

    public object? CryptographicProviderAlgid
    {
        get
        {
            return base.GetNullableValue(CRYPTOGRAPHICPROVIDERALGID_FIELD_ID);
        }
    }


    public Types.SymmetricKeysDataType ToDataObject()
    {
        return new Types.SymmetricKeysDataType(Name,
            PrincipalId,
            SymmetricKeyId,
            KeyLength,
            KeyAlgorithm,
            AlgorithmDesc,
            CreateDate,
            ModifyDate,
            KeyGuid,
            KeyThumbprint,
            ProviderType,
            CryptographicProviderGuid,
            CryptographicProviderAlgid);
    }

    public List<Types.SymmetricKeysDataType> ToList()
    {
        var list = new List<Types.SymmetricKeysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
