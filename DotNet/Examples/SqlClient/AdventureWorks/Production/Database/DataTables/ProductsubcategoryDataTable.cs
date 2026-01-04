using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductsubcategoryDataTable
{

    DataTable _dataTable;

    public ProductsubcategoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductsubcategoryDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productsubcategoryidColumn = new DataColumn("Productsubcategoryid", typeof(int));
        productsubcategoryidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productsubcategoryidColumn);
        var productcategoryidColumn = new DataColumn("Productcategoryid", typeof(int));
        productcategoryidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productcategoryidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productsubcategoryid,
                        int productcategoryid,
                        string name,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productsubcategoryid"] = productsubcategoryid;
        row["Productcategoryid"] = productcategoryid;
        row["Name"] = name;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductsubcategoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productsubcategoryid"] = data.Productsubcategoryid;
        row["Productcategoryid"] = data.Productcategoryid;
        row["Name"] = data.Name;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productsubcategoryid", "[Productsubcategoryid]");
        columnMappings.Add("Productcategoryid", "[Productcategoryid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductSubcategory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
