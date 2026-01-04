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
