using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductproductphotoDataTable
{

    DataTable _dataTable;

    public ProductproductphotoDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductproductphotoDataTable()
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
        var productphotoidColumn = new DataColumn("Productphotoid", typeof(int));
        productphotoidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productphotoidColumn);
        var primaryColumn = new DataColumn("Primary", typeof(bool));
        primaryColumn.AllowDBNull = false;
        dataTable.Columns.Add(primaryColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productid,
                        int productphotoid,
                        bool primary,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productid"] = productid;
        row["Productphotoid"] = productphotoid;
        row["Primary"] = primary;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductproductphotoDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productid"] = data.Productid;
        row["Productphotoid"] = data.Productphotoid;
        row["Primary"] = data.Primary;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Productphotoid", "[Productphotoid]");
        columnMappings.Add("Primary", "[Primary]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductProductPhoto]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
