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

public class DmReplArticlesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_repl_articles]";
    public const string TableName = "dm_repl_articles";
    public const string ShortName = "dra";
    public const string Sql = """
        SELECT
          dra.[artcache_db_address],
          dra.[artcache_table_address],
          dra.[artcache_schema_address],
          dra.[artcache_article_address],
          dra.[Artid],
          dra.[Artfilter],
          dra.[Artobjid],
          dra.[Artpubid],
          dra.[Artstatus],
          dra.[Arttype],
          dra.[Wszartdesttable],
          dra.[Wszartdesttableowner],
          dra.[Wszartinscmd],
          dra.[Cmdtypeins],
          dra.[Wszartdelcmd],
          dra.[Cmdtypedel],
          dra.[Wszartupdcmd],
          dra.[Cmdtypeupd],
          dra.[Wszartpartialupdcmd],
          dra.[Cmdtypepartialupd],
          dra.[Numcol],
          dra.[Artcmdtype],
          dra.[Artgeninscmd],
          dra.[Artgendelcmd],
          dra.[Artgenupdcmd],
          dra.[Artpartialupdcmd],
          dra.[Artupdtxtcmd],
          dra.[Artgenins2cmd],
          dra.[Artgendel2cmd],
          dra.[Finreconcile],
          dra.[Fpuballowupdate],
          dra.[Intpublicationoptions]
        FROM
          [sys].[dm_repl_articles] dra
        """;

    public const int ARTCACHEDBADDRESS_FIELD_ID = 0;
    public const int ARTCACHETABLEADDRESS_FIELD_ID = 1;
    public const int ARTCACHESCHEMAADDRESS_FIELD_ID = 2;
    public const int ARTCACHEARTICLEADDRESS_FIELD_ID = 3;
    public const int ARTID_FIELD_ID = 4;
    public const int ARTFILTER_FIELD_ID = 5;
    public const int ARTOBJID_FIELD_ID = 6;
    public const int ARTPUBID_FIELD_ID = 7;
    public const int ARTSTATUS_FIELD_ID = 8;
    public const int ARTTYPE_FIELD_ID = 9;
    public const int WSZARTDESTTABLE_FIELD_ID = 10;
    public const int WSZARTDESTTABLEOWNER_FIELD_ID = 11;
    public const int WSZARTINSCMD_FIELD_ID = 12;
    public const int CMDTYPEINS_FIELD_ID = 13;
    public const int WSZARTDELCMD_FIELD_ID = 14;
    public const int CMDTYPEDEL_FIELD_ID = 15;
    public const int WSZARTUPDCMD_FIELD_ID = 16;
    public const int CMDTYPEUPD_FIELD_ID = 17;
    public const int WSZARTPARTIALUPDCMD_FIELD_ID = 18;
    public const int CMDTYPEPARTIALUPD_FIELD_ID = 19;
    public const int NUMCOL_FIELD_ID = 20;
    public const int ARTCMDTYPE_FIELD_ID = 21;
    public const int ARTGENINSCMD_FIELD_ID = 22;
    public const int ARTGENDELCMD_FIELD_ID = 23;
    public const int ARTGENUPDCMD_FIELD_ID = 24;
    public const int ARTPARTIALUPDCMD_FIELD_ID = 25;
    public const int ARTUPDTXTCMD_FIELD_ID = 26;
    public const int ARTGENINS2CMD_FIELD_ID = 27;
    public const int ARTGENDEL2CMD_FIELD_ID = 28;
    public const int FINRECONCILE_FIELD_ID = 29;
    public const int FPUBALLOWUPDATE_FIELD_ID = 30;
    public const int INTPUBLICATIONOPTIONS_FIELD_ID = 31;


    public DmReplArticlesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmReplArticlesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmReplArticlesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? ArtcacheDbAddress
    {
        get
        {
            return base.GetNullableBinary(ARTCACHEDBADDRESS_FIELD_ID);
        }
    }

    public byte[]? ArtcacheTableAddress
    {
        get
        {
            return base.GetNullableBinary(ARTCACHETABLEADDRESS_FIELD_ID);
        }
    }

    public byte[]? ArtcacheSchemaAddress
    {
        get
        {
            return base.GetNullableBinary(ARTCACHESCHEMAADDRESS_FIELD_ID);
        }
    }

    public byte[]? ArtcacheArticleAddress
    {
        get
        {
            return base.GetNullableBinary(ARTCACHEARTICLEADDRESS_FIELD_ID);
        }
    }

    public int? Artid
    {
        get
        {
            return base.GetNullableInt32(ARTID_FIELD_ID);
        }
    }

    public int? Artfilter
    {
        get
        {
            return base.GetNullableInt32(ARTFILTER_FIELD_ID);
        }
    }

    public int? Artobjid
    {
        get
        {
            return base.GetNullableInt32(ARTOBJID_FIELD_ID);
        }
    }

    public int? Artpubid
    {
        get
        {
            return base.GetNullableInt32(ARTPUBID_FIELD_ID);
        }
    }

    public byte? Artstatus
    {
        get
        {
            return base.GetNullableByte(ARTSTATUS_FIELD_ID);
        }
    }

    public byte? Arttype
    {
        get
        {
            return base.GetNullableByte(ARTTYPE_FIELD_ID);
        }
    }

    public string? Wszartdesttable
    {
        get
        {
            return base.GetNullableString(WSZARTDESTTABLE_FIELD_ID);
        }
    }

    public string? Wszartdesttableowner
    {
        get
        {
            return base.GetNullableString(WSZARTDESTTABLEOWNER_FIELD_ID);
        }
    }

    public string? Wszartinscmd
    {
        get
        {
            return base.GetNullableString(WSZARTINSCMD_FIELD_ID);
        }
    }

    public int? Cmdtypeins
    {
        get
        {
            return base.GetNullableInt32(CMDTYPEINS_FIELD_ID);
        }
    }

    public string? Wszartdelcmd
    {
        get
        {
            return base.GetNullableString(WSZARTDELCMD_FIELD_ID);
        }
    }

    public int? Cmdtypedel
    {
        get
        {
            return base.GetNullableInt32(CMDTYPEDEL_FIELD_ID);
        }
    }

    public string? Wszartupdcmd
    {
        get
        {
            return base.GetNullableString(WSZARTUPDCMD_FIELD_ID);
        }
    }

    public int? Cmdtypeupd
    {
        get
        {
            return base.GetNullableInt32(CMDTYPEUPD_FIELD_ID);
        }
    }

    public string? Wszartpartialupdcmd
    {
        get
        {
            return base.GetNullableString(WSZARTPARTIALUPDCMD_FIELD_ID);
        }
    }

    public int? Cmdtypepartialupd
    {
        get
        {
            return base.GetNullableInt32(CMDTYPEPARTIALUPD_FIELD_ID);
        }
    }

    public int? Numcol
    {
        get
        {
            return base.GetNullableInt32(NUMCOL_FIELD_ID);
        }
    }

    public byte? Artcmdtype
    {
        get
        {
            return base.GetNullableByte(ARTCMDTYPE_FIELD_ID);
        }
    }

    public string? Artgeninscmd
    {
        get
        {
            return base.GetNullableString(ARTGENINSCMD_FIELD_ID);
        }
    }

    public string? Artgendelcmd
    {
        get
        {
            return base.GetNullableString(ARTGENDELCMD_FIELD_ID);
        }
    }

    public string? Artgenupdcmd
    {
        get
        {
            return base.GetNullableString(ARTGENUPDCMD_FIELD_ID);
        }
    }

    public string? Artpartialupdcmd
    {
        get
        {
            return base.GetNullableString(ARTPARTIALUPDCMD_FIELD_ID);
        }
    }

    public string? Artupdtxtcmd
    {
        get
        {
            return base.GetNullableString(ARTUPDTXTCMD_FIELD_ID);
        }
    }

    public string? Artgenins2cmd
    {
        get
        {
            return base.GetNullableString(ARTGENINS2CMD_FIELD_ID);
        }
    }

    public string? Artgendel2cmd
    {
        get
        {
            return base.GetNullableString(ARTGENDEL2CMD_FIELD_ID);
        }
    }

    public byte? Finreconcile
    {
        get
        {
            return base.GetNullableByte(FINRECONCILE_FIELD_ID);
        }
    }

    public byte? Fpuballowupdate
    {
        get
        {
            return base.GetNullableByte(FPUBALLOWUPDATE_FIELD_ID);
        }
    }

    public int? Intpublicationoptions
    {
        get
        {
            return base.GetNullableInt32(INTPUBLICATIONOPTIONS_FIELD_ID);
        }
    }


    public Types.DmReplArticlesDataType ToDataObject()
    {
        return new Types.DmReplArticlesDataType(ArtcacheDbAddress,
            ArtcacheTableAddress,
            ArtcacheSchemaAddress,
            ArtcacheArticleAddress,
            Artid,
            Artfilter,
            Artobjid,
            Artpubid,
            Artstatus,
            Arttype,
            Wszartdesttable,
            Wszartdesttableowner,
            Wszartinscmd,
            Cmdtypeins,
            Wszartdelcmd,
            Cmdtypedel,
            Wszartupdcmd,
            Cmdtypeupd,
            Wszartpartialupdcmd,
            Cmdtypepartialupd,
            Numcol,
            Artcmdtype,
            Artgeninscmd,
            Artgendelcmd,
            Artgenupdcmd,
            Artpartialupdcmd,
            Artupdtxtcmd,
            Artgenins2cmd,
            Artgendel2cmd,
            Finreconcile,
            Fpuballowupdate,
            Intpublicationoptions);
    }

    public List<Types.DmReplArticlesDataType> ToList()
    {
        var list = new List<Types.DmReplArticlesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
