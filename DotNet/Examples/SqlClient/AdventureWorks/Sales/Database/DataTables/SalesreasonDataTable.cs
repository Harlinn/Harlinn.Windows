using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class SalesreasonDataTable
{

    DataTable _dataTable;

    public SalesreasonDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalesreasonDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var salesreasonidColumn = new DataColumn("Salesreasonid", typeof(int));
        salesreasonidColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesreasonidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var reasontypeColumn = new DataColumn("Reasontype", typeof(string));
        reasontypeColumn.AllowDBNull = false;
        dataTable.Columns.Add(reasontypeColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int salesreasonid,
                        string name,
                        string reasontype,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Salesreasonid"] = salesreasonid;
        row["Name"] = name;
        row["Reasontype"] = reasontype;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalesreasonDataType data)
    {
        var row = _dataTable.NewRow();
        row["Salesreasonid"] = data.Salesreasonid;
        row["Name"] = data.Name;
        row["Reasontype"] = data.Reasontype;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Salesreasonid", "[Salesreasonid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Reasontype", "[Reasontype]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesReason]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
