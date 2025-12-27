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

public class DmCryptographicProviderPropertiesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_cryptographic_provider_properties]";
    public const string TableName = "dm_cryptographic_provider_properties";
    public const string ShortName = "dcpp";
    public const string Sql = """
        SELECT
          dcpp.[provider_id],
          dcpp.[Guid],
          dcpp.[provider_version],
          dcpp.[sqlcrypt_version],
          dcpp.[friendly_name],
          dcpp.[authentication_type],
          dcpp.[symmetric_key_support],
          dcpp.[symmetric_key_persistance],
          dcpp.[symmetric_key_export],
          dcpp.[symmetric_key_import],
          dcpp.[asymmetric_key_support],
          dcpp.[asymmetric_key_persistance],
          dcpp.[asymmetric_key_export],
          dcpp.[asymmetric_key_import]
        FROM
          [sys].[dm_cryptographic_provider_properties] dcpp
        """;

    public const int PROVIDERID_FIELD_ID = 0;
    public const int GUID_FIELD_ID = 1;
    public const int PROVIDERVERSION_FIELD_ID = 2;
    public const int SQLCRYPTVERSION_FIELD_ID = 3;
    public const int FRIENDLYNAME_FIELD_ID = 4;
    public const int AUTHENTICATIONTYPE_FIELD_ID = 5;
    public const int SYMMETRICKEYSUPPORT_FIELD_ID = 6;
    public const int SYMMETRICKEYPERSISTANCE_FIELD_ID = 7;
    public const int SYMMETRICKEYEXPORT_FIELD_ID = 8;
    public const int SYMMETRICKEYIMPORT_FIELD_ID = 9;
    public const int ASYMMETRICKEYSUPPORT_FIELD_ID = 10;
    public const int ASYMMETRICKEYPERSISTANCE_FIELD_ID = 11;
    public const int ASYMMETRICKEYEXPORT_FIELD_ID = 12;
    public const int ASYMMETRICKEYIMPORT_FIELD_ID = 13;


    public DmCryptographicProviderPropertiesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmCryptographicProviderPropertiesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmCryptographicProviderPropertiesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? ProviderId
    {
        get
        {
            return base.GetNullableInt32(PROVIDERID_FIELD_ID);
        }
    }

    public Guid? Guid
    {
        get
        {
            return base.GetNullableGuid(GUID_FIELD_ID);
        }
    }

    public string? ProviderVersion
    {
        get
        {
            return base.GetNullableString(PROVIDERVERSION_FIELD_ID);
        }
    }

    public string? SqlcryptVersion
    {
        get
        {
            return base.GetNullableString(SQLCRYPTVERSION_FIELD_ID);
        }
    }

    public string? FriendlyName
    {
        get
        {
            return base.GetNullableString(FRIENDLYNAME_FIELD_ID);
        }
    }

    public string? AuthenticationType
    {
        get
        {
            return base.GetNullableString(AUTHENTICATIONTYPE_FIELD_ID);
        }
    }

    public byte? SymmetricKeySupport
    {
        get
        {
            return base.GetNullableByte(SYMMETRICKEYSUPPORT_FIELD_ID);
        }
    }

    public byte? SymmetricKeyPersistance
    {
        get
        {
            return base.GetNullableByte(SYMMETRICKEYPERSISTANCE_FIELD_ID);
        }
    }

    public byte? SymmetricKeyExport
    {
        get
        {
            return base.GetNullableByte(SYMMETRICKEYEXPORT_FIELD_ID);
        }
    }

    public byte? SymmetricKeyImport
    {
        get
        {
            return base.GetNullableByte(SYMMETRICKEYIMPORT_FIELD_ID);
        }
    }

    public byte? AsymmetricKeySupport
    {
        get
        {
            return base.GetNullableByte(ASYMMETRICKEYSUPPORT_FIELD_ID);
        }
    }

    public byte? AsymmetricKeyPersistance
    {
        get
        {
            return base.GetNullableByte(ASYMMETRICKEYPERSISTANCE_FIELD_ID);
        }
    }

    public byte? AsymmetricKeyExport
    {
        get
        {
            return base.GetNullableByte(ASYMMETRICKEYEXPORT_FIELD_ID);
        }
    }

    public byte? AsymmetricKeyImport
    {
        get
        {
            return base.GetNullableByte(ASYMMETRICKEYIMPORT_FIELD_ID);
        }
    }


    public Types.DmCryptographicProviderPropertiesDataType ToDataObject()
    {
        return new Types.DmCryptographicProviderPropertiesDataType(ProviderId,
            Guid,
            ProviderVersion,
            SqlcryptVersion,
            FriendlyName,
            AuthenticationType,
            SymmetricKeySupport,
            SymmetricKeyPersistance,
            SymmetricKeyExport,
            SymmetricKeyImport,
            AsymmetricKeySupport,
            AsymmetricKeyPersistance,
            AsymmetricKeyExport,
            AsymmetricKeyImport);
    }

    public List<Types.DmCryptographicProviderPropertiesDataType> ToList()
    {
        var list = new List<Types.DmCryptographicProviderPropertiesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
