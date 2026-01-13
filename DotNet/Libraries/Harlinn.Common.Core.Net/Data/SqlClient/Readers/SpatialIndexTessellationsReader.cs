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

public class SpatialIndexTessellationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[spatial_index_tessellations]";
    public const string TableName = "spatial_index_tessellations";
    public const string ShortName = "sit";
    public const string Sql = """
        SELECT
          sit.[object_id],
          sit.[index_id],
          sit.[tessellation_scheme],
          sit.[bounding_box_xmin],
          sit.[bounding_box_ymin],
          sit.[bounding_box_xmax],
          sit.[bounding_box_ymax],
          sit.[level_1_grid],
          sit.[level_1_grid_desc],
          sit.[level_2_grid],
          sit.[level_2_grid_desc],
          sit.[level_3_grid],
          sit.[level_3_grid_desc],
          sit.[level_4_grid],
          sit.[level_4_grid_desc],
          sit.[cells_per_object]
        FROM
          [sys].[spatial_index_tessellations] sit
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int INDEXID_FIELD_ID = 1;
    public const int TESSELLATIONSCHEME_FIELD_ID = 2;
    public const int BOUNDINGBOXXMIN_FIELD_ID = 3;
    public const int BOUNDINGBOXYMIN_FIELD_ID = 4;
    public const int BOUNDINGBOXXMAX_FIELD_ID = 5;
    public const int BOUNDINGBOXYMAX_FIELD_ID = 6;
    public const int LEVEL1GRID_FIELD_ID = 7;
    public const int LEVEL1GRIDDESC_FIELD_ID = 8;
    public const int LEVEL2GRID_FIELD_ID = 9;
    public const int LEVEL2GRIDDESC_FIELD_ID = 10;
    public const int LEVEL3GRID_FIELD_ID = 11;
    public const int LEVEL3GRIDDESC_FIELD_ID = 12;
    public const int LEVEL4GRID_FIELD_ID = 13;
    public const int LEVEL4GRIDDESC_FIELD_ID = 14;
    public const int CELLSPEROBJECT_FIELD_ID = 15;


    public SpatialIndexTessellationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SpatialIndexTessellationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SpatialIndexTessellationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public string? TessellationScheme
    {
        get
        {
            return base.GetNullableString(TESSELLATIONSCHEME_FIELD_ID);
        }
    }

    public double? BoundingBoxXmin
    {
        get
        {
            return base.GetNullableDouble(BOUNDINGBOXXMIN_FIELD_ID);
        }
    }

    public double? BoundingBoxYmin
    {
        get
        {
            return base.GetNullableDouble(BOUNDINGBOXYMIN_FIELD_ID);
        }
    }

    public double? BoundingBoxXmax
    {
        get
        {
            return base.GetNullableDouble(BOUNDINGBOXXMAX_FIELD_ID);
        }
    }

    public double? BoundingBoxYmax
    {
        get
        {
            return base.GetNullableDouble(BOUNDINGBOXYMAX_FIELD_ID);
        }
    }

    public short? Level1Grid
    {
        get
        {
            return base.GetNullableInt16(LEVEL1GRID_FIELD_ID);
        }
    }

    public string? Level1GridDesc
    {
        get
        {
            return base.GetNullableString(LEVEL1GRIDDESC_FIELD_ID);
        }
    }

    public short? Level2Grid
    {
        get
        {
            return base.GetNullableInt16(LEVEL2GRID_FIELD_ID);
        }
    }

    public string? Level2GridDesc
    {
        get
        {
            return base.GetNullableString(LEVEL2GRIDDESC_FIELD_ID);
        }
    }

    public short? Level3Grid
    {
        get
        {
            return base.GetNullableInt16(LEVEL3GRID_FIELD_ID);
        }
    }

    public string? Level3GridDesc
    {
        get
        {
            return base.GetNullableString(LEVEL3GRIDDESC_FIELD_ID);
        }
    }

    public short? Level4Grid
    {
        get
        {
            return base.GetNullableInt16(LEVEL4GRID_FIELD_ID);
        }
    }

    public string? Level4GridDesc
    {
        get
        {
            return base.GetNullableString(LEVEL4GRIDDESC_FIELD_ID);
        }
    }

    public int? CellsPerObject
    {
        get
        {
            return base.GetNullableInt32(CELLSPEROBJECT_FIELD_ID);
        }
    }


    public Types.SpatialIndexTessellationsDataType ToDataObject()
    {
        return new Types.SpatialIndexTessellationsDataType(ObjectId,
            IndexId,
            TessellationScheme,
            BoundingBoxXmin,
            BoundingBoxYmin,
            BoundingBoxXmax,
            BoundingBoxYmax,
            Level1Grid,
            Level1GridDesc,
            Level2Grid,
            Level2GridDesc,
            Level3Grid,
            Level3GridDesc,
            Level4Grid,
            Level4GridDesc,
            CellsPerObject);
    }

    public List<Types.SpatialIndexTessellationsDataType> ToList()
    {
        var list = new List<Types.SpatialIndexTessellationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
