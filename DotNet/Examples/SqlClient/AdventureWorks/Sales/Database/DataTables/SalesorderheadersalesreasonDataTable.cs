using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class SalesorderheadersalesreasonDataTable
{

    DataTable _dataTable;

    public SalesorderheadersalesreasonDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalesorderheadersalesreasonDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var salesorderidColumn = new DataColumn("Salesorderid", typeof(int));
        salesorderidColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesorderidColumn);
        var salesreasonidColumn = new DataColumn("Salesreasonid", typeof(int));
        salesreasonidColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesreasonidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int salesorderid,
                        int salesreasonid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Salesorderid"] = salesorderid;
        row["Salesreasonid"] = salesreasonid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalesorderheadersalesreasonDataType data)
    {
        var row = _dataTable.NewRow();
        row["Salesorderid"] = data.Salesorderid;
        row["Salesreasonid"] = data.Salesreasonid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Salesorderid", "[Salesorderid]");
        columnMappings.Add("Salesreasonid", "[Salesreasonid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesOrderHeaderSalesReason]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
