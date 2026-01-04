using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductdescriptionDataTable
{

    DataTable _dataTable;

    public ProductdescriptionDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductdescriptionDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productdescriptionidColumn = new DataColumn("Productdescriptionid", typeof(int));
        productdescriptionidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productdescriptionidColumn);
        var descriptionColumn = new DataColumn("Description", typeof(string));
        descriptionColumn.AllowDBNull = false;
        dataTable.Columns.Add(descriptionColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productdescriptionid,
                        string description,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productdescriptionid"] = productdescriptionid;
        row["Description"] = description;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductdescriptionDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productdescriptionid"] = data.Productdescriptionid;
        row["Description"] = data.Description;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productdescriptionid", "[Productdescriptionid]");
        columnMappings.Add("Description", "[Description]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductDescription]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
