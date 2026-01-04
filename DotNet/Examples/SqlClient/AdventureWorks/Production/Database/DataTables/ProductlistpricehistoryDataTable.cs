using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductlistpricehistoryDataTable
{

    DataTable _dataTable;

    public ProductlistpricehistoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductlistpricehistoryDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var startdateColumn = new DataColumn("Startdate", typeof(DateTime));
        startdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(startdateColumn);
        var enddateColumn = new DataColumn("Enddate", typeof(DateTime));
        dataTable.Columns.Add(enddateColumn);
        var listpriceColumn = new DataColumn("Listprice", typeof(decimal));
        listpriceColumn.AllowDBNull = false;
        dataTable.Columns.Add(listpriceColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productid,
                        DateTime startdate,
                        DateTime? enddate,
                        decimal listprice,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productid"] = productid;
        row["Startdate"] = startdate;
        row["Enddate"] = (object?)enddate ?? DBNull.Value;
        row["Listprice"] = listprice;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductlistpricehistoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productid"] = data.Productid;
        row["Startdate"] = data.Startdate;
        row["Enddate"] = (object?)data.Enddate ?? DBNull.Value;
        row["Listprice"] = data.Listprice;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Startdate", "[Startdate]");
        columnMappings.Add("Enddate", "[Enddate]");
        columnMappings.Add("Listprice", "[Listprice]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductListPriceHistory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
