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

public class MasterKeyPasswordsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[master_key_passwords]";
    public const string TableName = "master_key_passwords";
    public const string ShortName = "mkp";
    public const string Sql = """
        SELECT
          mkp.[credential_id],
          mkp.[family_guid]
        FROM
          [sys].[master_key_passwords] mkp
        """;

    public const int CREDENTIALID_FIELD_ID = 0;
    public const int FAMILYGUID_FIELD_ID = 1;


    public MasterKeyPasswordsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public MasterKeyPasswordsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public MasterKeyPasswordsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int CredentialId
    {
        get
        {
            return base.GetInt32(CREDENTIALID_FIELD_ID);
        }
    }

    public Guid? FamilyGuid
    {
        get
        {
            return base.GetNullableGuid(FAMILYGUID_FIELD_ID);
        }
    }


    public Types.MasterKeyPasswordsDataType ToDataObject()
    {
        return new Types.MasterKeyPasswordsDataType(CredentialId,
            FamilyGuid);
    }

    public List<Types.MasterKeyPasswordsDataType> ToList()
    {
        var list = new List<Types.MasterKeyPasswordsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
