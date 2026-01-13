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
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class CountryregioncurrencyDataTable
{

    DataTable _dataTable;

    public CountryregioncurrencyDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public CountryregioncurrencyDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var countryregioncodeColumn = new DataColumn("Countryregioncode", typeof(string));
        countryregioncodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(countryregioncodeColumn);
        var currencycodeColumn = new DataColumn("Currencycode", typeof(string));
        currencycodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(currencycodeColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        string countryregioncode,
                        string currencycode,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Countryregioncode"] = countryregioncode;
        row["Currencycode"] = currencycode;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(CountryregioncurrencyDataType data)
    {
        var row = _dataTable.NewRow();
        row["Countryregioncode"] = data.Countryregioncode;
        row["Currencycode"] = data.Currencycode;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Countryregioncode", "[Countryregioncode]");
        columnMappings.Add("Currencycode", "[Currencycode]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[CountryRegionCurrency]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
