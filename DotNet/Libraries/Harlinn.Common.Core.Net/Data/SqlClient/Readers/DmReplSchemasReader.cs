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

public class DmReplSchemasReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_repl_schemas]";
    public const string TableName = "dm_repl_schemas";
    public const string ShortName = "drs";
    public const string Sql = """
        SELECT
          drs.[artcache_schema_address],
          drs.[Tabid],
          drs.[Indexid],
          drs.[Idsch],
          drs.[Tabschema],
          drs.[Cctabschema],
          drs.[Tabname],
          drs.[Cctabname],
          drs.[rowsetid_delete],
          drs.[rowsetid_insert],
          drs.[num_pk_cols],
          drs.[Pcitee],
          drs.[re_numtextcols],
          drs.[re_schema_lsn_begin],
          drs.[re_schema_lsn_end],
          drs.[re_numcols],
          drs.[re_colid],
          drs.[re_awcName],
          drs.[re_ccName],
          drs.[re_colattr],
          drs.[re_maxlen],
          drs.[re_prec],
          drs.[re_scale],
          drs.[re_collatid],
          drs.[re_xvtype],
          drs.[re_offset],
          drs.[re_bitpos],
          drs.[re_fNullable],
          drs.[re_fAnsiTrim],
          drs.[re_computed],
          drs.[se_rowsetid],
          drs.[se_schema_lsn_begin],
          drs.[se_schema_lsn_end],
          drs.[se_numcols],
          drs.[se_colid],
          drs.[se_maxlen],
          drs.[se_prec],
          drs.[se_scale],
          drs.[se_collatid],
          drs.[se_xvtype],
          drs.[se_offset],
          drs.[se_bitpos],
          drs.[se_fNullable],
          drs.[se_fAnsiTrim],
          drs.[se_computed],
          drs.[se_nullBitInLeafRows]
        FROM
          [sys].[dm_repl_schemas] drs
        """;

    public const int ARTCACHESCHEMAADDRESS_FIELD_ID = 0;
    public const int TABID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int IDSCH_FIELD_ID = 3;
    public const int TABSCHEMA_FIELD_ID = 4;
    public const int CCTABSCHEMA_FIELD_ID = 5;
    public const int TABNAME_FIELD_ID = 6;
    public const int CCTABNAME_FIELD_ID = 7;
    public const int ROWSETIDDELETE_FIELD_ID = 8;
    public const int ROWSETIDINSERT_FIELD_ID = 9;
    public const int NUMPKCOLS_FIELD_ID = 10;
    public const int PCITEE_FIELD_ID = 11;
    public const int RENUMTEXTCOLS_FIELD_ID = 12;
    public const int RESCHEMALSNBEGIN_FIELD_ID = 13;
    public const int RESCHEMALSNEND_FIELD_ID = 14;
    public const int RENUMCOLS_FIELD_ID = 15;
    public const int RECOLID_FIELD_ID = 16;
    public const int REAWCNAME_FIELD_ID = 17;
    public const int RECCNAME_FIELD_ID = 18;
    public const int RECOLATTR_FIELD_ID = 19;
    public const int REMAXLEN_FIELD_ID = 20;
    public const int REPREC_FIELD_ID = 21;
    public const int RESCALE_FIELD_ID = 22;
    public const int RECOLLATID_FIELD_ID = 23;
    public const int REXVTYPE_FIELD_ID = 24;
    public const int REOFFSET_FIELD_ID = 25;
    public const int REBITPOS_FIELD_ID = 26;
    public const int REFNULLABLE_FIELD_ID = 27;
    public const int REFANSITRIM_FIELD_ID = 28;
    public const int RECOMPUTED_FIELD_ID = 29;
    public const int SEROWSETID_FIELD_ID = 30;
    public const int SESCHEMALSNBEGIN_FIELD_ID = 31;
    public const int SESCHEMALSNEND_FIELD_ID = 32;
    public const int SENUMCOLS_FIELD_ID = 33;
    public const int SECOLID_FIELD_ID = 34;
    public const int SEMAXLEN_FIELD_ID = 35;
    public const int SEPREC_FIELD_ID = 36;
    public const int SESCALE_FIELD_ID = 37;
    public const int SECOLLATID_FIELD_ID = 38;
    public const int SEXVTYPE_FIELD_ID = 39;
    public const int SEOFFSET_FIELD_ID = 40;
    public const int SEBITPOS_FIELD_ID = 41;
    public const int SEFNULLABLE_FIELD_ID = 42;
    public const int SEFANSITRIM_FIELD_ID = 43;
    public const int SECOMPUTED_FIELD_ID = 44;
    public const int SENULLBITINLEAFROWS_FIELD_ID = 45;


    public DmReplSchemasReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmReplSchemasReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmReplSchemasReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? ArtcacheSchemaAddress
    {
        get
        {
            return base.GetNullableBinary(ARTCACHESCHEMAADDRESS_FIELD_ID);
        }
    }

    public int? Tabid
    {
        get
        {
            return base.GetNullableInt32(TABID_FIELD_ID);
        }
    }

    public short? Indexid
    {
        get
        {
            return base.GetNullableInt16(INDEXID_FIELD_ID);
        }
    }

    public int? Idsch
    {
        get
        {
            return base.GetNullableInt32(IDSCH_FIELD_ID);
        }
    }

    public string? Tabschema
    {
        get
        {
            return base.GetNullableString(TABSCHEMA_FIELD_ID);
        }
    }

    public short? Cctabschema
    {
        get
        {
            return base.GetNullableInt16(CCTABSCHEMA_FIELD_ID);
        }
    }

    public string? Tabname
    {
        get
        {
            return base.GetNullableString(TABNAME_FIELD_ID);
        }
    }

    public short? Cctabname
    {
        get
        {
            return base.GetNullableInt16(CCTABNAME_FIELD_ID);
        }
    }

    public long? RowsetidDelete
    {
        get
        {
            return base.GetNullableInt64(ROWSETIDDELETE_FIELD_ID);
        }
    }

    public long? RowsetidInsert
    {
        get
        {
            return base.GetNullableInt64(ROWSETIDINSERT_FIELD_ID);
        }
    }

    public int? NumPkCols
    {
        get
        {
            return base.GetNullableInt32(NUMPKCOLS_FIELD_ID);
        }
    }

    public byte[]? Pcitee
    {
        get
        {
            return base.GetNullableBinary(PCITEE_FIELD_ID);
        }
    }

    public int? ReNumtextcols
    {
        get
        {
            return base.GetNullableInt32(RENUMTEXTCOLS_FIELD_ID);
        }
    }

    public string? ReSchemaLsnBegin
    {
        get
        {
            return base.GetNullableString(RESCHEMALSNBEGIN_FIELD_ID);
        }
    }

    public string? ReSchemaLsnEnd
    {
        get
        {
            return base.GetNullableString(RESCHEMALSNEND_FIELD_ID);
        }
    }

    public int? ReNumcols
    {
        get
        {
            return base.GetNullableInt32(RENUMCOLS_FIELD_ID);
        }
    }

    public int? ReColid
    {
        get
        {
            return base.GetNullableInt32(RECOLID_FIELD_ID);
        }
    }

    public string? ReAwcname
    {
        get
        {
            return base.GetNullableString(REAWCNAME_FIELD_ID);
        }
    }

    public short? ReCcname
    {
        get
        {
            return base.GetNullableInt16(RECCNAME_FIELD_ID);
        }
    }

    public short? ReColattr
    {
        get
        {
            return base.GetNullableInt16(RECOLATTR_FIELD_ID);
        }
    }

    public short? ReMaxlen
    {
        get
        {
            return base.GetNullableInt16(REMAXLEN_FIELD_ID);
        }
    }

    public byte? RePrec
    {
        get
        {
            return base.GetNullableByte(REPREC_FIELD_ID);
        }
    }

    public byte? ReScale
    {
        get
        {
            return base.GetNullableByte(RESCALE_FIELD_ID);
        }
    }

    public int? ReCollatid
    {
        get
        {
            return base.GetNullableInt32(RECOLLATID_FIELD_ID);
        }
    }

    public byte? ReXvtype
    {
        get
        {
            return base.GetNullableByte(REXVTYPE_FIELD_ID);
        }
    }

    public int? ReOffset
    {
        get
        {
            return base.GetNullableInt32(REOFFSET_FIELD_ID);
        }
    }

    public byte? ReBitpos
    {
        get
        {
            return base.GetNullableByte(REBITPOS_FIELD_ID);
        }
    }

    public byte? ReFnullable
    {
        get
        {
            return base.GetNullableByte(REFNULLABLE_FIELD_ID);
        }
    }

    public byte? ReFansitrim
    {
        get
        {
            return base.GetNullableByte(REFANSITRIM_FIELD_ID);
        }
    }

    public int? ReComputed
    {
        get
        {
            return base.GetNullableInt32(RECOMPUTED_FIELD_ID);
        }
    }

    public long? SeRowsetid
    {
        get
        {
            return base.GetNullableInt64(SEROWSETID_FIELD_ID);
        }
    }

    public string? SeSchemaLsnBegin
    {
        get
        {
            return base.GetNullableString(SESCHEMALSNBEGIN_FIELD_ID);
        }
    }

    public string? SeSchemaLsnEnd
    {
        get
        {
            return base.GetNullableString(SESCHEMALSNEND_FIELD_ID);
        }
    }

    public int? SeNumcols
    {
        get
        {
            return base.GetNullableInt32(SENUMCOLS_FIELD_ID);
        }
    }

    public int? SeColid
    {
        get
        {
            return base.GetNullableInt32(SECOLID_FIELD_ID);
        }
    }

    public short? SeMaxlen
    {
        get
        {
            return base.GetNullableInt16(SEMAXLEN_FIELD_ID);
        }
    }

    public byte? SePrec
    {
        get
        {
            return base.GetNullableByte(SEPREC_FIELD_ID);
        }
    }

    public byte? SeScale
    {
        get
        {
            return base.GetNullableByte(SESCALE_FIELD_ID);
        }
    }

    public int? SeCollatid
    {
        get
        {
            return base.GetNullableInt32(SECOLLATID_FIELD_ID);
        }
    }

    public byte? SeXvtype
    {
        get
        {
            return base.GetNullableByte(SEXVTYPE_FIELD_ID);
        }
    }

    public int? SeOffset
    {
        get
        {
            return base.GetNullableInt32(SEOFFSET_FIELD_ID);
        }
    }

    public byte? SeBitpos
    {
        get
        {
            return base.GetNullableByte(SEBITPOS_FIELD_ID);
        }
    }

    public byte? SeFnullable
    {
        get
        {
            return base.GetNullableByte(SEFNULLABLE_FIELD_ID);
        }
    }

    public byte? SeFansitrim
    {
        get
        {
            return base.GetNullableByte(SEFANSITRIM_FIELD_ID);
        }
    }

    public byte? SeComputed
    {
        get
        {
            return base.GetNullableByte(SECOMPUTED_FIELD_ID);
        }
    }

    public short? SeNullbitinleafrows
    {
        get
        {
            return base.GetNullableInt16(SENULLBITINLEAFROWS_FIELD_ID);
        }
    }


    public Types.DmReplSchemasDataType ToDataObject()
    {
        return new Types.DmReplSchemasDataType(ArtcacheSchemaAddress,
            Tabid,
            Indexid,
            Idsch,
            Tabschema,
            Cctabschema,
            Tabname,
            Cctabname,
            RowsetidDelete,
            RowsetidInsert,
            NumPkCols,
            Pcitee,
            ReNumtextcols,
            ReSchemaLsnBegin,
            ReSchemaLsnEnd,
            ReNumcols,
            ReColid,
            ReAwcname,
            ReCcname,
            ReColattr,
            ReMaxlen,
            RePrec,
            ReScale,
            ReCollatid,
            ReXvtype,
            ReOffset,
            ReBitpos,
            ReFnullable,
            ReFansitrim,
            ReComputed,
            SeRowsetid,
            SeSchemaLsnBegin,
            SeSchemaLsnEnd,
            SeNumcols,
            SeColid,
            SeMaxlen,
            SePrec,
            SeScale,
            SeCollatid,
            SeXvtype,
            SeOffset,
            SeBitpos,
            SeFnullable,
            SeFansitrim,
            SeComputed,
            SeNullbitinleafrows);
    }

    public List<Types.DmReplSchemasDataType> ToList()
    {
        var list = new List<Types.DmReplSchemasDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
