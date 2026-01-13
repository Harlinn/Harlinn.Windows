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

namespace AdventureWorks.Sales.Database.Readers;

public class CountryregioncurrencyReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[CountryRegionCurrency]";
    public const string TableName = "CountryRegionCurrency";
    public const string ShortName = "c2";
    public const string Sql = """
        SELECT
          c2.[Countryregioncode],
          c2.[Currencycode],
          c2.[Modifieddate]
        FROM
          [Sales].[CountryRegionCurrency] c2
        """;

    public const int COUNTRYREGIONCODE_FIELD_ID = 0;
    public const int CURRENCYCODE_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CountryregioncurrencyReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Countryregioncode
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONCODE_FIELD_ID);
        }
    }

    public string Currencycode
    {
        get
        {
            return Reader.GetString(CURRENCYCODE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.CountryregioncurrencyDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.CountryregioncurrencyDataType(Countryregioncode,
            Currencycode,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.CountryregioncurrencyDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.CountryregioncurrencyDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
