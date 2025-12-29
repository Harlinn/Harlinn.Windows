using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class VproductmodelcatalogdescriptionReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[vProductModelCatalogDescription]";
    public const string TableName = "vProductModelCatalogDescription";
    public const string ShortName = "v8";
    public const string Sql = """
        SELECT
          v8.[Productmodelid],
          v8.[Name],
          v8.[Summary],
          v8.[Manufacturer],
          v8.[Copyright],
          v8.[Producturl],
          v8.[Warrantyperiod],
          v8.[Warrantydescription],
          v8.[Noofyears],
          v8.[Maintenancedescription],
          v8.[Wheel],
          v8.[Saddle],
          v8.[Pedal],
          v8.[Bikeframe],
          v8.[Crankset],
          v8.[Pictureangle],
          v8.[Picturesize],
          v8.[Productphotoid],
          v8.[Material],
          v8.[Color],
          v8.[Productline],
          v8.[Style],
          v8.[Riderexperience],
          v8.[Rowguid],
          v8.[Modifieddate]
        FROM
          [Production].[vProductModelCatalogDescription] v8
        """;

    public const int PRODUCTMODELID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int SUMMARY_FIELD_ID = 2;
    public const int MANUFACTURER_FIELD_ID = 3;
    public const int COPYRIGHT_FIELD_ID = 4;
    public const int PRODUCTURL_FIELD_ID = 5;
    public const int WARRANTYPERIOD_FIELD_ID = 6;
    public const int WARRANTYDESCRIPTION_FIELD_ID = 7;
    public const int NOOFYEARS_FIELD_ID = 8;
    public const int MAINTENANCEDESCRIPTION_FIELD_ID = 9;
    public const int WHEEL_FIELD_ID = 10;
    public const int SADDLE_FIELD_ID = 11;
    public const int PEDAL_FIELD_ID = 12;
    public const int BIKEFRAME_FIELD_ID = 13;
    public const int CRANKSET_FIELD_ID = 14;
    public const int PICTUREANGLE_FIELD_ID = 15;
    public const int PICTURESIZE_FIELD_ID = 16;
    public const int PRODUCTPHOTOID_FIELD_ID = 17;
    public const int MATERIAL_FIELD_ID = 18;
    public const int COLOR_FIELD_ID = 19;
    public const int PRODUCTLINE_FIELD_ID = 20;
    public const int STYLE_FIELD_ID = 21;
    public const int RIDEREXPERIENCE_FIELD_ID = 22;
    public const int ROWGUID_FIELD_ID = 23;
    public const int MODIFIEDDATE_FIELD_ID = 24;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VproductmodelcatalogdescriptionReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productmodelid
    {
        get
        {
            return Reader.GetInt32(PRODUCTMODELID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public string? Summary
    {
        get
        {
            return Reader.GetNullableString(SUMMARY_FIELD_ID);
        }
    }

    public string? Manufacturer
    {
        get
        {
            return Reader.GetNullableString(MANUFACTURER_FIELD_ID);
        }
    }

    public string? Copyright
    {
        get
        {
            return Reader.GetNullableString(COPYRIGHT_FIELD_ID);
        }
    }

    public string? Producturl
    {
        get
        {
            return Reader.GetNullableString(PRODUCTURL_FIELD_ID);
        }
    }

    public string? Warrantyperiod
    {
        get
        {
            return Reader.GetNullableString(WARRANTYPERIOD_FIELD_ID);
        }
    }

    public string? Warrantydescription
    {
        get
        {
            return Reader.GetNullableString(WARRANTYDESCRIPTION_FIELD_ID);
        }
    }

    public string? Noofyears
    {
        get
        {
            return Reader.GetNullableString(NOOFYEARS_FIELD_ID);
        }
    }

    public string? Maintenancedescription
    {
        get
        {
            return Reader.GetNullableString(MAINTENANCEDESCRIPTION_FIELD_ID);
        }
    }

    public string? Wheel
    {
        get
        {
            return Reader.GetNullableString(WHEEL_FIELD_ID);
        }
    }

    public string? Saddle
    {
        get
        {
            return Reader.GetNullableString(SADDLE_FIELD_ID);
        }
    }

    public string? Pedal
    {
        get
        {
            return Reader.GetNullableString(PEDAL_FIELD_ID);
        }
    }

    public string? Bikeframe
    {
        get
        {
            return Reader.GetNullableString(BIKEFRAME_FIELD_ID);
        }
    }

    public string? Crankset
    {
        get
        {
            return Reader.GetNullableString(CRANKSET_FIELD_ID);
        }
    }

    public string? Pictureangle
    {
        get
        {
            return Reader.GetNullableString(PICTUREANGLE_FIELD_ID);
        }
    }

    public string? Picturesize
    {
        get
        {
            return Reader.GetNullableString(PICTURESIZE_FIELD_ID);
        }
    }

    public string? Productphotoid
    {
        get
        {
            return Reader.GetNullableString(PRODUCTPHOTOID_FIELD_ID);
        }
    }

    public string? Material
    {
        get
        {
            return Reader.GetNullableString(MATERIAL_FIELD_ID);
        }
    }

    public string? Color
    {
        get
        {
            return Reader.GetNullableString(COLOR_FIELD_ID);
        }
    }

    public string? Productline
    {
        get
        {
            return Reader.GetNullableString(PRODUCTLINE_FIELD_ID);
        }
    }

    public string? Style
    {
        get
        {
            return Reader.GetNullableString(STYLE_FIELD_ID);
        }
    }

    public string? Riderexperience
    {
        get
        {
            return Reader.GetNullableString(RIDEREXPERIENCE_FIELD_ID);
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


    public Types.Production.VproductmodelcatalogdescriptionDataType ToDataObject()
    {
        return new Types.Production.VproductmodelcatalogdescriptionDataType(Productmodelid,
            Name,
            Summary,
            Manufacturer,
            Copyright,
            Producturl,
            Warrantyperiod,
            Warrantydescription,
            Noofyears,
            Maintenancedescription,
            Wheel,
            Saddle,
            Pedal,
            Bikeframe,
            Crankset,
            Pictureangle,
            Picturesize,
            Productphotoid,
            Material,
            Color,
            Productline,
            Style,
            Riderexperience,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Production.VproductmodelcatalogdescriptionDataType> ToList()
    {
        var list = new List<Types.Production.VproductmodelcatalogdescriptionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
