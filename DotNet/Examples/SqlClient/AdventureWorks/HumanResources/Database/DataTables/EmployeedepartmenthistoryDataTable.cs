using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.HumanResources.Types;

namespace AdventureWorks.HumanResources.Database.DataTables;

public class EmployeedepartmenthistoryDataTable
{

    DataTable _dataTable;

    public EmployeedepartmenthistoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public EmployeedepartmenthistoryDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var businessentityidColumn = new DataColumn("Businessentityid", typeof(int));
        businessentityidColumn.AllowDBNull = false;
        dataTable.Columns.Add(businessentityidColumn);
        var departmentidColumn = new DataColumn("Departmentid", typeof(short));
        departmentidColumn.AllowDBNull = false;
        dataTable.Columns.Add(departmentidColumn);
        var shiftidColumn = new DataColumn("Shiftid", typeof(byte));
        shiftidColumn.AllowDBNull = false;
        dataTable.Columns.Add(shiftidColumn);
        var startdateColumn = new DataColumn("Startdate", typeof(DateTime));
        startdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(startdateColumn);
        var enddateColumn = new DataColumn("Enddate", typeof(DateTime));
        dataTable.Columns.Add(enddateColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int businessentityid,
                        short departmentid,
                        byte shiftid,
                        DateTime startdate,
                        DateTime? enddate,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Departmentid"] = departmentid;
        row["Shiftid"] = shiftid;
        row["Startdate"] = startdate;
        row["Enddate"] = (object?)enddate ?? DBNull.Value;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(EmployeedepartmenthistoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Departmentid"] = data.Departmentid;
        row["Shiftid"] = data.Shiftid;
        row["Startdate"] = data.Startdate;
        row["Enddate"] = (object?)data.Enddate ?? DBNull.Value;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Departmentid", "[Departmentid]");
        columnMappings.Add("Shiftid", "[Shiftid]");
        columnMappings.Add("Startdate", "[Startdate]");
        columnMappings.Add("Enddate", "[Enddate]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[HumanResources].[EmployeeDepartmentHistory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
