using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class VproductanddescriptionReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[vProductAndDescription]";
    public const string TableName = "vProductAndDescription";
    public const string ShortName = "v7";
    public const string Sql = """
        SELECT
          v7.[Productid],
          v7.[Name],
          v7.[Productmodel],
          v7.[Cultureid],
          v7.[Description]
        FROM
          [Production].[vProductAndDescription] v7
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int PRODUCTMODEL_FIELD_ID = 2;
    public const int CULTUREID_FIELD_ID = 3;
    public const int DESCRIPTION_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VproductanddescriptionReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Productmodel
    {
        get
        {
            return Reader.GetString(PRODUCTMODEL_FIELD_ID);
        }
    }

    public string Cultureid
    {
        get
        {
            return Reader.GetString(CULTUREID_FIELD_ID);
        }
    }

    public string Description
    {
        get
        {
            return Reader.GetString(DESCRIPTION_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.VproductanddescriptionDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.VproductanddescriptionDataType(Productid,
            Name,
            Productmodel,
            Cultureid,
            Description);
    }

    public List<AdventureWorks.Production.Types.VproductanddescriptionDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.VproductanddescriptionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
