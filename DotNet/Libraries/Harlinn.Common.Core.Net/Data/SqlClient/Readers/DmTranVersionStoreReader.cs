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

public class DmTranVersionStoreReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_version_store]";
    public const string TableName = "dm_tran_version_store";
    public const string ShortName = "dtvs";
    public const string Sql = """
        SELECT
          dtvs.[transaction_sequence_num],
          dtvs.[version_sequence_num],
          dtvs.[database_id],
          dtvs.[rowset_id],
          dtvs.[Status],
          dtvs.[min_length_in_bytes],
          dtvs.[record_length_first_part_in_bytes],
          dtvs.[record_image_first_part],
          dtvs.[record_length_second_part_in_bytes],
          dtvs.[record_image_second_part]
        FROM
          [sys].[dm_tran_version_store] dtvs
        """;

    public const int TRANSACTIONSEQUENCENUM_FIELD_ID = 0;
    public const int VERSIONSEQUENCENUM_FIELD_ID = 1;
    public const int DATABASEID_FIELD_ID = 2;
    public const int ROWSETID_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int MINLENGTHINBYTES_FIELD_ID = 5;
    public const int RECORDLENGTHFIRSTPARTINBYTES_FIELD_ID = 6;
    public const int RECORDIMAGEFIRSTPART_FIELD_ID = 7;
    public const int RECORDLENGTHSECONDPARTINBYTES_FIELD_ID = 8;
    public const int RECORDIMAGESECONDPART_FIELD_ID = 9;


    public DmTranVersionStoreReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranVersionStoreReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranVersionStoreReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long? TransactionSequenceNum
    {
        get
        {
            return base.GetNullableInt64(TRANSACTIONSEQUENCENUM_FIELD_ID);
        }
    }

    public long? VersionSequenceNum
    {
        get
        {
            return base.GetNullableInt64(VERSIONSEQUENCENUM_FIELD_ID);
        }
    }

    public short? DatabaseId
    {
        get
        {
            return base.GetNullableInt16(DATABASEID_FIELD_ID);
        }
    }

    public long? RowsetId
    {
        get
        {
            return base.GetNullableInt64(ROWSETID_FIELD_ID);
        }
    }

    public byte? Status
    {
        get
        {
            return base.GetNullableByte(STATUS_FIELD_ID);
        }
    }

    public short? MinLengthInBytes
    {
        get
        {
            return base.GetNullableInt16(MINLENGTHINBYTES_FIELD_ID);
        }
    }

    public short? RecordLengthFirstPartInBytes
    {
        get
        {
            return base.GetNullableInt16(RECORDLENGTHFIRSTPARTINBYTES_FIELD_ID);
        }
    }

    public byte[]? RecordImageFirstPart
    {
        get
        {
            return base.GetNullableBinary(RECORDIMAGEFIRSTPART_FIELD_ID);
        }
    }

    public short? RecordLengthSecondPartInBytes
    {
        get
        {
            return base.GetNullableInt16(RECORDLENGTHSECONDPARTINBYTES_FIELD_ID);
        }
    }

    public byte[]? RecordImageSecondPart
    {
        get
        {
            return base.GetNullableBinary(RECORDIMAGESECONDPART_FIELD_ID);
        }
    }


    public Types.DmTranVersionStoreDataType ToDataObject()
    {
        return new Types.DmTranVersionStoreDataType(TransactionSequenceNum,
            VersionSequenceNum,
            DatabaseId,
            RowsetId,
            Status,
            MinLengthInBytes,
            RecordLengthFirstPartInBytes,
            RecordImageFirstPart,
            RecordLengthSecondPartInBytes,
            RecordImageSecondPart);
    }

    public List<Types.DmTranVersionStoreDataType> ToList()
    {
        var list = new List<Types.DmTranVersionStoreDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
