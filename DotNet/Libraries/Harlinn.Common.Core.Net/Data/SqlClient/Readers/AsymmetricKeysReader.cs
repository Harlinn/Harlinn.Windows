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

public class AsymmetricKeysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[asymmetric_keys]";
    public const string TableName = "asymmetric_keys";
    public const string ShortName = "ak";
    public const string Sql = """
        SELECT
          ak.[Name],
          ak.[principal_id],
          ak.[asymmetric_key_id],
          ak.[pvt_key_encryption_type],
          ak.[pvt_key_encryption_type_desc],
          ak.[Thumbprint],
          ak.[Algorithm],
          ak.[algorithm_desc],
          ak.[key_length],
          ak.[Sid],
          ak.[string_sid],
          ak.[public_key],
          ak.[attested_by],
          ak.[provider_type],
          ak.[cryptographic_provider_guid],
          ak.[cryptographic_provider_algid]
        FROM
          [sys].[asymmetric_keys] ak
        """;

    public const int NAME_FIELD_ID = 0;
    public const int PRINCIPALID_FIELD_ID = 1;
    public const int ASYMMETRICKEYID_FIELD_ID = 2;
    public const int PVTKEYENCRYPTIONTYPE_FIELD_ID = 3;
    public const int PVTKEYENCRYPTIONTYPEDESC_FIELD_ID = 4;
    public const int THUMBPRINT_FIELD_ID = 5;
    public const int ALGORITHM_FIELD_ID = 6;
    public const int ALGORITHMDESC_FIELD_ID = 7;
    public const int KEYLENGTH_FIELD_ID = 8;
    public const int SID_FIELD_ID = 9;
    public const int STRINGSID_FIELD_ID = 10;
    public const int PUBLICKEY_FIELD_ID = 11;
    public const int ATTESTEDBY_FIELD_ID = 12;
    public const int PROVIDERTYPE_FIELD_ID = 13;
    public const int CRYPTOGRAPHICPROVIDERGUID_FIELD_ID = 14;
    public const int CRYPTOGRAPHICPROVIDERALGID_FIELD_ID = 15;


    public AsymmetricKeysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AsymmetricKeysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AsymmetricKeysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int AsymmetricKeyId
    {
        get
        {
            return base.GetInt32(ASYMMETRICKEYID_FIELD_ID);
        }
    }

    public string PvtKeyEncryptionType
    {
        get
        {
            return base.GetString(PVTKEYENCRYPTIONTYPE_FIELD_ID);
        }
    }

    public string? PvtKeyEncryptionTypeDesc
    {
        get
        {
            return base.GetNullableString(PVTKEYENCRYPTIONTYPEDESC_FIELD_ID);
        }
    }

    public byte[] Thumbprint
    {
        get
        {
            return base.GetBinary(THUMBPRINT_FIELD_ID);
        }
    }

    public string Algorithm
    {
        get
        {
            return base.GetString(ALGORITHM_FIELD_ID);
        }
    }

    public string? AlgorithmDesc
    {
        get
        {
            return base.GetNullableString(ALGORITHMDESC_FIELD_ID);
        }
    }

    public int KeyLength
    {
        get
        {
            return base.GetInt32(KEYLENGTH_FIELD_ID);
        }
    }

    public byte[]? Sid
    {
        get
        {
            return base.GetNullableBinary(SID_FIELD_ID);
        }
    }

    public string? StringSid
    {
        get
        {
            return base.GetNullableString(STRINGSID_FIELD_ID);
        }
    }

    public byte[] PublicKey
    {
        get
        {
            return base.GetBinary(PUBLICKEY_FIELD_ID);
        }
    }

    public string? AttestedBy
    {
        get
        {
            return base.GetNullableString(ATTESTEDBY_FIELD_ID);
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


    public Types.AsymmetricKeysDataType ToDataObject()
    {
        return new Types.AsymmetricKeysDataType(Name,
            PrincipalId,
            AsymmetricKeyId,
            PvtKeyEncryptionType,
            PvtKeyEncryptionTypeDesc,
            Thumbprint,
            Algorithm,
            AlgorithmDesc,
            KeyLength,
            Sid,
            StringSid,
            PublicKey,
            AttestedBy,
            ProviderType,
            CryptographicProviderGuid,
            CryptographicProviderAlgid);
    }

    public List<Types.AsymmetricKeysDataType> ToList()
    {
        var list = new List<Types.AsymmetricKeysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
