using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class WorkorderroutingDataTable
{

    DataTable _dataTable;

    public WorkorderroutingDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public WorkorderroutingDataTable()
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
        var operationsequenceColumn = new DataColumn("Operationsequence", typeof(short));
        operationsequenceColumn.AllowDBNull = false;
        dataTable.Columns.Add(operationsequenceColumn);
        var locationidColumn = new DataColumn("Locationid", typeof(short));
        locationidColumn.AllowDBNull = false;
        dataTable.Columns.Add(locationidColumn);
        var scheduledstartdateColumn = new DataColumn("Scheduledstartdate", typeof(DateTime));
        scheduledstartdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(scheduledstartdateColumn);
        var scheduledenddateColumn = new DataColumn("Scheduledenddate", typeof(DateTime));
        scheduledenddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(scheduledenddateColumn);
        var actualstartdateColumn = new DataColumn("Actualstartdate", typeof(DateTime));
        dataTable.Columns.Add(actualstartdateColumn);
        var actualenddateColumn = new DataColumn("Actualenddate", typeof(DateTime));
        dataTable.Columns.Add(actualenddateColumn);
        var actualresourcehrsColumn = new DataColumn("Actualresourcehrs", typeof(decimal));
        dataTable.Columns.Add(actualresourcehrsColumn);
        var plannedcostColumn = new DataColumn("Plannedcost", typeof(decimal));
        plannedcostColumn.AllowDBNull = false;
        dataTable.Columns.Add(plannedcostColumn);
        var actualcostColumn = new DataColumn("Actualcost", typeof(decimal));
        dataTable.Columns.Add(actualcostColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int workorderid,
                        int productid,
                        short operationsequence,
                        short locationid,
                        DateTime scheduledstartdate,
                        DateTime scheduledenddate,
                        DateTime? actualstartdate,
                        DateTime? actualenddate,
                        decimal? actualresourcehrs,
                        decimal plannedcost,
                        decimal? actualcost,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Workorderid"] = workorderid;
        row["Productid"] = productid;
        row["Operationsequence"] = operationsequence;
        row["Locationid"] = locationid;
        row["Scheduledstartdate"] = scheduledstartdate;
        row["Scheduledenddate"] = scheduledenddate;
        row["Actualstartdate"] = (object?)actualstartdate ?? DBNull.Value;
        row["Actualenddate"] = (object?)actualenddate ?? DBNull.Value;
        row["Actualresourcehrs"] = (object?)actualresourcehrs ?? DBNull.Value;
        row["Plannedcost"] = plannedcost;
        row["Actualcost"] = (object?)actualcost ?? DBNull.Value;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(WorkorderroutingDataType data)
    {
        var row = _dataTable.NewRow();
        row["Workorderid"] = data.Workorderid;
        row["Productid"] = data.Productid;
        row["Operationsequence"] = data.Operationsequence;
        row["Locationid"] = data.Locationid;
        row["Scheduledstartdate"] = data.Scheduledstartdate;
        row["Scheduledenddate"] = data.Scheduledenddate;
        row["Actualstartdate"] = (object?)data.Actualstartdate ?? DBNull.Value;
        row["Actualenddate"] = (object?)data.Actualenddate ?? DBNull.Value;
        row["Actualresourcehrs"] = (object?)data.Actualresourcehrs ?? DBNull.Value;
        row["Plannedcost"] = data.Plannedcost;
        row["Actualcost"] = (object?)data.Actualcost ?? DBNull.Value;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Workorderid", "[Workorderid]");
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Operationsequence", "[Operationsequence]");
        columnMappings.Add("Locationid", "[Locationid]");
        columnMappings.Add("Scheduledstartdate", "[Scheduledstartdate]");
        columnMappings.Add("Scheduledenddate", "[Scheduledenddate]");
        columnMappings.Add("Actualstartdate", "[Actualstartdate]");
        columnMappings.Add("Actualenddate", "[Actualenddate]");
        columnMappings.Add("Actualresourcehrs", "[Actualresourcehrs]");
        columnMappings.Add("Plannedcost", "[Plannedcost]");
        columnMappings.Add("Actualcost", "[Actualcost]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[WorkOrderRouting]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
