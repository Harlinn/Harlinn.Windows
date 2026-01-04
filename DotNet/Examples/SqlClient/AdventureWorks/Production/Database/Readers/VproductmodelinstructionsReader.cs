using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class VproductmodelinstructionsReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[vProductModelInstructions]";
    public const string TableName = "vProductModelInstructions";
    public const string ShortName = "v9";
    public const string Sql = """
        SELECT
          v9.[Productmodelid],
          v9.[Name],
          v9.[Instructions],
          v9.[Locationid],
          v9.[Setuphours],
          v9.[Machinehours],
          v9.[Laborhours],
          v9.[Lotsize],
          v9.[Step],
          v9.[Rowguid],
          v9.[Modifieddate]
        FROM
          [Production].[vProductModelInstructions] v9
        """;

    public const int PRODUCTMODELID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int INSTRUCTIONS_FIELD_ID = 2;
    public const int LOCATIONID_FIELD_ID = 3;
    public const int SETUPHOURS_FIELD_ID = 4;
    public const int MACHINEHOURS_FIELD_ID = 5;
    public const int LABORHOURS_FIELD_ID = 6;
    public const int LOTSIZE_FIELD_ID = 7;
    public const int STEP_FIELD_ID = 8;
    public const int ROWGUID_FIELD_ID = 9;
    public const int MODIFIEDDATE_FIELD_ID = 10;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VproductmodelinstructionsReader(SqlDataReader reader, bool ownsReader = false)
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

    public string? Instructions
    {
        get
        {
            return Reader.GetNullableString(INSTRUCTIONS_FIELD_ID);
        }
    }

    public int? Locationid
    {
        get
        {
            return Reader.GetNullableInt32(LOCATIONID_FIELD_ID);
        }
    }

    public decimal? Setuphours
    {
        get
        {
            return Reader.GetNullableDecimal(SETUPHOURS_FIELD_ID);
        }
    }

    public decimal? Machinehours
    {
        get
        {
            return Reader.GetNullableDecimal(MACHINEHOURS_FIELD_ID);
        }
    }

    public decimal? Laborhours
    {
        get
        {
            return Reader.GetNullableDecimal(LABORHOURS_FIELD_ID);
        }
    }

    public int? Lotsize
    {
        get
        {
            return Reader.GetNullableInt32(LOTSIZE_FIELD_ID);
        }
    }

    public string? Step
    {
        get
        {
            return Reader.GetNullableString(STEP_FIELD_ID);
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


    public AdventureWorks.Production.Types.VproductmodelinstructionsDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.VproductmodelinstructionsDataType(Productmodelid,
            Name,
            Instructions,
            Locationid,
            Setuphours,
            Machinehours,
            Laborhours,
            Lotsize,
            Step,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.VproductmodelinstructionsDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.VproductmodelinstructionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
