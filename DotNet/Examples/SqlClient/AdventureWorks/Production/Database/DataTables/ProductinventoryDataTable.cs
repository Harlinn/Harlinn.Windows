using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductinventoryDataTable
{

    DataTable _dataTable;

    public ProductinventoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductinventoryDataTable()
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
        var locationidColumn = new DataColumn("Locationid", typeof(short));
        locationidColumn.AllowDBNull = false;
        dataTable.Columns.Add(locationidColumn);
        var shelfColumn = new DataColumn("Shelf", typeof(string));
        shelfColumn.AllowDBNull = false;
        dataTable.Columns.Add(shelfColumn);
        var binColumn = new DataColumn("Bin", typeof(byte));
        binColumn.AllowDBNull = false;
        dataTable.Columns.Add(binColumn);
        var quantityColumn = new DataColumn("Quantity", typeof(short));
        quantityColumn.AllowDBNull = false;
        dataTable.Columns.Add(quantityColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productid,
                        short locationid,
                        string shelf,
                        byte bin,
                        short quantity,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productid"] = productid;
        row["Locationid"] = locationid;
        row["Shelf"] = shelf;
        row["Bin"] = bin;
        row["Quantity"] = quantity;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductinventoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productid"] = data.Productid;
        row["Locationid"] = data.Locationid;
        row["Shelf"] = data.Shelf;
        row["Bin"] = data.Bin;
        row["Quantity"] = data.Quantity;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Locationid", "[Locationid]");
        columnMappings.Add("Shelf", "[Shelf]");
        columnMappings.Add("Bin", "[Bin]");
        columnMappings.Add("Quantity", "[Quantity]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductInventory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
