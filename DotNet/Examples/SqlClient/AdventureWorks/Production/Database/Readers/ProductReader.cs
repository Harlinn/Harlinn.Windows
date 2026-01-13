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
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class ProductReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[Product]";
    public const string TableName = "Product";
    public const string ShortName = "p3";
    public const string Sql = """
        SELECT
          p3.[Productid],
          p3.[Name],
          p3.[Productnumber],
          p3.[Makeflag],
          p3.[Finishedgoodsflag],
          p3.[Color],
          p3.[Safetystocklevel],
          p3.[Reorderpoint],
          p3.[Standardcost],
          p3.[Listprice],
          p3.[Size],
          p3.[Sizeunitmeasurecode],
          p3.[Weightunitmeasurecode],
          p3.[Weight],
          p3.[Daystomanufacture],
          p3.[Productline],
          p3.[Class],
          p3.[Style],
          p3.[Productsubcategoryid],
          p3.[Productmodelid],
          p3.[Sellstartdate],
          p3.[Sellenddate],
          p3.[Discontinueddate],
          p3.[Rowguid],
          p3.[Modifieddate]
        FROM
          [Production].[Product] p3
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int PRODUCTNUMBER_FIELD_ID = 2;
    public const int MAKEFLAG_FIELD_ID = 3;
    public const int FINISHEDGOODSFLAG_FIELD_ID = 4;
    public const int COLOR_FIELD_ID = 5;
    public const int SAFETYSTOCKLEVEL_FIELD_ID = 6;
    public const int REORDERPOINT_FIELD_ID = 7;
    public const int STANDARDCOST_FIELD_ID = 8;
    public const int LISTPRICE_FIELD_ID = 9;
    public const int SIZE_FIELD_ID = 10;
    public const int SIZEUNITMEASURECODE_FIELD_ID = 11;
    public const int WEIGHTUNITMEASURECODE_FIELD_ID = 12;
    public const int WEIGHT_FIELD_ID = 13;
    public const int DAYSTOMANUFACTURE_FIELD_ID = 14;
    public const int PRODUCTLINE_FIELD_ID = 15;
    public const int CLASS_FIELD_ID = 16;
    public const int STYLE_FIELD_ID = 17;
    public const int PRODUCTSUBCATEGORYID_FIELD_ID = 18;
    public const int PRODUCTMODELID_FIELD_ID = 19;
    public const int SELLSTARTDATE_FIELD_ID = 20;
    public const int SELLENDDATE_FIELD_ID = 21;
    public const int DISCONTINUEDDATE_FIELD_ID = 22;
    public const int ROWGUID_FIELD_ID = 23;
    public const int MODIFIEDDATE_FIELD_ID = 24;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductReader(SqlDataReader reader, bool ownsReader = false)
    {
        _reader = reader;
        _ownsReader = ownsReader;
    }

    public SqlDataReader Reader => _reader;

    public void Dispose()
    {
        if (_ownsReader)
        {
            ((IDisposable)_reader).Dispose();
        }
    }

    public bool Read()
    {
        return _reader.Read();
    }

    public int Productid
    {
        get
        {
            return Reader.GetInt32(PRODUCTID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public string Productnumber
    {
        get
        {
            return Reader.GetString(PRODUCTNUMBER_FIELD_ID);
        }
    }

    public bool Makeflag
    {
        get
        {
            return Reader.GetBoolean(MAKEFLAG_FIELD_ID);
        }
    }

    public bool Finishedgoodsflag
    {
        get
        {
            return Reader.GetBoolean(FINISHEDGOODSFLAG_FIELD_ID);
        }
    }

    public string? Color
    {
        get
        {
            return Reader.GetNullableString(COLOR_FIELD_ID);
        }
    }

    public short Safetystocklevel
    {
        get
        {
            return Reader.GetInt16(SAFETYSTOCKLEVEL_FIELD_ID);
        }
    }

    public short Reorderpoint
    {
        get
        {
            return Reader.GetInt16(REORDERPOINT_FIELD_ID);
        }
    }

    public decimal Standardcost
    {
        get
        {
            return Reader.GetDecimal(STANDARDCOST_FIELD_ID);
        }
    }

    public decimal Listprice
    {
        get
        {
            return Reader.GetDecimal(LISTPRICE_FIELD_ID);
        }
    }

    public string? Size
    {
        get
        {
            return Reader.GetNullableString(SIZE_FIELD_ID);
        }
    }

    public string? Sizeunitmeasurecode
    {
        get
        {
            return Reader.GetNullableString(SIZEUNITMEASURECODE_FIELD_ID);
        }
    }

    public string? Weightunitmeasurecode
    {
        get
        {
            return Reader.GetNullableString(WEIGHTUNITMEASURECODE_FIELD_ID);
        }
    }

    public decimal? Weight
    {
        get
        {
            return Reader.GetNullableDecimal(WEIGHT_FIELD_ID);
        }
    }

    public int Daystomanufacture
    {
        get
        {
            return Reader.GetInt32(DAYSTOMANUFACTURE_FIELD_ID);
        }
    }

    public string? Productline
    {
        get
        {
            return Reader.GetNullableString(PRODUCTLINE_FIELD_ID);
        }
    }

    public string? Class
    {
        get
        {
            return Reader.GetNullableString(CLASS_FIELD_ID);
        }
    }

    public string? Style
    {
        get
        {
            return Reader.GetNullableString(STYLE_FIELD_ID);
        }
    }

    public int? Productsubcategoryid
    {
        get
        {
            return Reader.GetNullableInt32(PRODUCTSUBCATEGORYID_FIELD_ID);
        }
    }

    public int? Productmodelid
    {
        get
        {
            return Reader.GetNullableInt32(PRODUCTMODELID_FIELD_ID);
        }
    }

    public DateTime Sellstartdate
    {
        get
        {
            return Reader.GetDateTime(SELLSTARTDATE_FIELD_ID);
        }
    }

    public DateTime? Sellenddate
    {
        get
        {
            return Reader.GetNullableDateTime(SELLENDDATE_FIELD_ID);
        }
    }

    public DateTime? Discontinueddate
    {
        get
        {
            return Reader.GetNullableDateTime(DISCONTINUEDDATE_FIELD_ID);
        }
    }

    public Guid Rowguid
    {
        get
        {
            return Reader.GetGuid(ROWGUID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.ProductDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductDataType(Productid,
            Name,
            Productnumber,
            Makeflag,
            Finishedgoodsflag,
            Color,
            Safetystocklevel,
            Reorderpoint,
            Standardcost,
            Listprice,
            Size,
            Sizeunitmeasurecode,
            Weightunitmeasurecode,
            Weight,
            Daystomanufacture,
            Productline,
            Class,
            Style,
            Productsubcategoryid,
            Productmodelid,
            Sellstartdate,
            Sellenddate,
            Discontinueddate,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
