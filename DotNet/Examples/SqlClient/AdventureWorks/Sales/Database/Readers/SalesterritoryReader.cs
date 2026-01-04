using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Sales.Database.Readers;

public class SalesterritoryReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesTerritory]";
    public const string TableName = "SalesTerritory";
    public const string ShortName = "s10";
    public const string Sql = """
        SELECT
          s10.[Territoryid],
          s10.[Name],
          s10.[Countryregioncode],
          s10.[Group],
          s10.[Salesytd],
          s10.[Saleslastyear],
          s10.[Costytd],
          s10.[Costlastyear],
          s10.[Rowguid],
          s10.[Modifieddate]
        FROM
          [Sales].[SalesTerritory] s10
        """;

    public const int TERRITORYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int COUNTRYREGIONCODE_FIELD_ID = 2;
    public const int GROUP_FIELD_ID = 3;
    public const int SALESYTD_FIELD_ID = 4;
    public const int SALESLASTYEAR_FIELD_ID = 5;
    public const int COSTYTD_FIELD_ID = 6;
    public const int COSTLASTYEAR_FIELD_ID = 7;
    public const int ROWGUID_FIELD_ID = 8;
    public const int MODIFIEDDATE_FIELD_ID = 9;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalesterritoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Territoryid
    {
        get
        {
            return Reader.GetInt32(TERRITORYID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public string Countryregioncode
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONCODE_FIELD_ID);
        }
    }

    public string Group
    {
        get
        {
            return Reader.GetString(GROUP_FIELD_ID);
        }
    }

    public decimal Salesytd
    {
        get
        {
            return Reader.GetDecimal(SALESYTD_FIELD_ID);
        }
    }

    public decimal Saleslastyear
    {
        get
        {
            return Reader.GetDecimal(SALESLASTYEAR_FIELD_ID);
        }
    }

    public decimal Costytd
    {
        get
        {
            return Reader.GetDecimal(COSTYTD_FIELD_ID);
        }
    }

    public decimal Costlastyear
    {
        get
        {
            return Reader.GetDecimal(COSTLASTYEAR_FIELD_ID);
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


    public AdventureWorks.Sales.Types.SalesterritoryDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.SalesterritoryDataType(Territoryid,
            Name,
            Countryregioncode,
            Group,
            Salesytd,
            Saleslastyear,
            Costytd,
            Costlastyear,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.SalesterritoryDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.SalesterritoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
