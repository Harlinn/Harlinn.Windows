using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class WorkorderDataTable
{

    DataTable _dataTable;

    public WorkorderDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public WorkorderDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var workorderidColumn = new DataColumn("Workorderid", typeof(int));
        workorderidColumn.AllowDBNull = false;
        dataTable.Columns.Add(workorderidColumn);
        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var orderqtyColumn = new DataColumn("Orderqty", typeof(int));
        orderqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(orderqtyColumn);
        var scrappedqtyColumn = new DataColumn("Scrappedqty", typeof(short));
        scrappedqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(scrappedqtyColumn);
        var startdateColumn = new DataColumn("Startdate", typeof(DateTime));
        startdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(startdateColumn);
        var enddateColumn = new DataColumn("Enddate", typeof(DateTime));
        dataTable.Columns.Add(enddateColumn);
        var duedateColumn = new DataColumn("Duedate", typeof(DateTime));
        duedateColumn.AllowDBNull = false;
        dataTable.Columns.Add(duedateColumn);
        var scrapreasonidColumn = new DataColumn("Scrapreasonid", typeof(short));
        dataTable.Columns.Add(scrapreasonidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int workorderid,
                        int productid,
                        int orderqty,
                        short scrappedqty,
                        DateTime startdate,
                        DateTime? enddate,
                        DateTime duedate,
                        short? scrapreasonid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Workorderid"] = workorderid;
        row["Productid"] = productid;
        row["Orderqty"] = orderqty;
        row["Scrappedqty"] = scrappedqty;
        row["Startdate"] = startdate;
        row["Enddate"] = (object?)enddate ?? DBNull.Value;
        row["Duedate"] = duedate;
        row["Scrapreasonid"] = (object?)scrapreasonid ?? DBNull.Value;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(WorkorderDataType data)
    {
        var row = _dataTable.NewRow();
        row["Workorderid"] = data.Workorderid;
        row["Productid"] = data.Productid;
        row["Orderqty"] = data.Orderqty;
        row["Scrappedqty"] = data.Scrappedqty;
        row["Startdate"] = data.Startdate;
        row["Enddate"] = (object?)data.Enddate ?? DBNull.Value;
        row["Duedate"] = data.Duedate;
        row["Scrapreasonid"] = (object?)data.Scrapreasonid ?? DBNull.Value;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Workorderid", "[Workorderid]");
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Orderqty", "[Orderqty]");
        columnMappings.Add("Scrappedqty", "[Scrappedqty]");
        columnMappings.Add("Startdate", "[Startdate]");
        columnMappings.Add("Enddate", "[Enddate]");
        columnMappings.Add("Duedate", "[Duedate]");
        columnMappings.Add("Scrapreasonid", "[Scrapreasonid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[WorkOrder]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
