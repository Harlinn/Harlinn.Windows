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

public class SpatialReferenceSystemsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[spatial_reference_systems]";
    public const string TableName = "spatial_reference_systems";
    public const string ShortName = "srs";
    public const string Sql = """
        SELECT
          srs.[spatial_reference_id],
          srs.[authority_name],
          srs.[authorized_spatial_reference_id],
          srs.[well_known_text],
          srs.[unit_of_measure],
          srs.[unit_conversion_factor]
        FROM
          [sys].[spatial_reference_systems] srs
        """;

    public const int SPATIALREFERENCEID_FIELD_ID = 0;
    public const int AUTHORITYNAME_FIELD_ID = 1;
    public const int AUTHORIZEDSPATIALREFERENCEID_FIELD_ID = 2;
    public const int WELLKNOWNTEXT_FIELD_ID = 3;
    public const int UNITOFMEASURE_FIELD_ID = 4;
    public const int UNITCONVERSIONFACTOR_FIELD_ID = 5;


    public SpatialReferenceSystemsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SpatialReferenceSystemsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SpatialReferenceSystemsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? SpatialReferenceId
    {
        get
        {
            return base.GetNullableInt32(SPATIALREFERENCEID_FIELD_ID);
        }
    }

    public string? AuthorityName
    {
        get
        {
            return base.GetNullableString(AUTHORITYNAME_FIELD_ID);
        }
    }

    public int? AuthorizedSpatialReferenceId
    {
        get
        {
            return base.GetNullableInt32(AUTHORIZEDSPATIALREFERENCEID_FIELD_ID);
        }
    }

    public string? WellKnownText
    {
        get
        {
            return base.GetNullableString(WELLKNOWNTEXT_FIELD_ID);
        }
    }

    public string? UnitOfMeasure
    {
        get
        {
            return base.GetNullableString(UNITOFMEASURE_FIELD_ID);
        }
    }

    public double? UnitConversionFactor
    {
        get
        {
            return base.GetNullableDouble(UNITCONVERSIONFACTOR_FIELD_ID);
        }
    }


    public Types.SpatialReferenceSystemsDataType ToDataObject()
    {
        return new Types.SpatialReferenceSystemsDataType(SpatialReferenceId,
            AuthorityName,
            AuthorizedSpatialReferenceId,
            WellKnownText,
            UnitOfMeasure,
            UnitConversionFactor);
    }

    public List<Types.SpatialReferenceSystemsDataType> ToList()
    {
        var list = new List<Types.SpatialReferenceSystemsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
