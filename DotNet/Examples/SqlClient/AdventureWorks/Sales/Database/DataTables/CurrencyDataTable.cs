using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class CurrencyDataTable
{

    DataTable _dataTable;

    public CurrencyDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public CurrencyDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var currencycodeColumn = new DataColumn("Currencycode", typeof(string));
        currencycodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(currencycodeColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        string currencycode,
                        string name,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Currencycode"] = currencycode;
        row["Name"] = name;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(CurrencyDataType data)
    {
        var row = _dataTable.NewRow();
        row["Currencycode"] = data.Currencycode;
        row["Name"] = data.Name;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Currencycode", "[Currencycode]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[Currency]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
