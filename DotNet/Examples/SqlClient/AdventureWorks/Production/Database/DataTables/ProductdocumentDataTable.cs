using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductdocumentDataTable
{

    DataTable _dataTable;

    public ProductdocumentDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductdocumentDataTable()
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
        var documentnodeColumn = new DataColumn("Documentnode", typeof(SqlHierarchyId));
        documentnodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(documentnodeColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productid,
                        SqlHierarchyId documentnode,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productid"] = productid;
        row["Documentnode"] = documentnode;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductdocumentDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productid"] = data.Productid;
        row["Documentnode"] = data.Documentnode;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Documentnode", "[Documentnode]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductDocument]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
