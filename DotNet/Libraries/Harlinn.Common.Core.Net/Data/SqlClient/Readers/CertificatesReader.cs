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

public class CertificatesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[certificates]";
    public const string TableName = "certificates";
    public const string ShortName = "c";
    public const string Sql = """
        SELECT
          c.[Name],
          c.[certificate_id],
          c.[principal_id],
          c.[pvt_key_encryption_type],
          c.[pvt_key_encryption_type_desc],
          c.[is_active_for_begin_dialog],
          c.[issuer_name],
          c.[cert_serial_number],
          c.[Sid],
          c.[string_sid],
          c.[Subject],
          c.[expiry_date],
          c.[start_date],
          c.[Thumbprint],
          c.[attested_by],
          c.[pvt_key_last_backup_date],
          c.[key_length]
        FROM
          [sys].[certificates] c
        """;

    public const int NAME_FIELD_ID = 0;
    public const int CERTIFICATEID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int PVTKEYENCRYPTIONTYPE_FIELD_ID = 3;
    public const int PVTKEYENCRYPTIONTYPEDESC_FIELD_ID = 4;
    public const int ISACTIVEFORBEGINDIALOG_FIELD_ID = 5;
    public const int ISSUERNAME_FIELD_ID = 6;
    public const int CERTSERIALNUMBER_FIELD_ID = 7;
    public const int SID_FIELD_ID = 8;
    public const int STRINGSID_FIELD_ID = 9;
    public const int SUBJECT_FIELD_ID = 10;
    public const int EXPIRYDATE_FIELD_ID = 11;
    public const int STARTDATE_FIELD_ID = 12;
    public const int THUMBPRINT_FIELD_ID = 13;
    public const int ATTESTEDBY_FIELD_ID = 14;
    public const int PVTKEYLASTBACKUPDATE_FIELD_ID = 15;
    public const int KEYLENGTH_FIELD_ID = 16;


    public CertificatesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public CertificatesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public CertificatesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int CertificateId
    {
        get
        {
            return base.GetInt32(CERTIFICATEID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
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

    public bool? IsActiveForBeginDialog
    {
        get
        {
            return base.GetNullableBoolean(ISACTIVEFORBEGINDIALOG_FIELD_ID);
        }
    }

    public string? IssuerName
    {
        get
        {
            return base.GetNullableString(ISSUERNAME_FIELD_ID);
        }
    }

    public string? CertSerialNumber
    {
        get
        {
            return base.GetNullableString(CERTSERIALNUMBER_FIELD_ID);
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

    public string? Subject
    {
        get
        {
            return base.GetNullableString(SUBJECT_FIELD_ID);
        }
    }

    public DateTime? ExpiryDate
    {
        get
        {
            return base.GetNullableDateTime(EXPIRYDATE_FIELD_ID);
        }
    }

    public DateTime? StartDate
    {
        get
        {
            return base.GetNullableDateTime(STARTDATE_FIELD_ID);
        }
    }

    public byte[] Thumbprint
    {
        get
        {
            return base.GetBinary(THUMBPRINT_FIELD_ID);
        }
    }

    public string? AttestedBy
    {
        get
        {
            return base.GetNullableString(ATTESTEDBY_FIELD_ID);
        }
    }

    public DateTime? PvtKeyLastBackupDate
    {
        get
        {
            return base.GetNullableDateTime(PVTKEYLASTBACKUPDATE_FIELD_ID);
        }
    }

    public int? KeyLength
    {
        get
        {
            return base.GetNullableInt32(KEYLENGTH_FIELD_ID);
        }
    }


    public Types.CertificatesDataType ToDataObject()
    {
        return new Types.CertificatesDataType(Name,
            CertificateId,
            PrincipalId,
            PvtKeyEncryptionType,
            PvtKeyEncryptionTypeDesc,
            IsActiveForBeginDialog,
            IssuerName,
            CertSerialNumber,
            Sid,
            StringSid,
            Subject,
            ExpiryDate,
            StartDate,
            Thumbprint,
            AttestedBy,
            PvtKeyLastBackupDate,
            KeyLength);
    }

    public List<Types.CertificatesDataType> ToList()
    {
        var list = new List<Types.CertificatesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
