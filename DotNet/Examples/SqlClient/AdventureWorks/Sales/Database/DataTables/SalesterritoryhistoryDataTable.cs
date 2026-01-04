using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class SalesterritoryhistoryDataTable
{

    DataTable _dataTable;

    public SalesterritoryhistoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalesterritoryhistoryDataTable()
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
        var territoryidColumn = new DataColumn("Territoryid", typeof(int));
        territoryidColumn.AllowDBNull = false;
        dataTable.Columns.Add(territoryidColumn);
        var startdateColumn = new DataColumn("Startdate", typeof(DateTime));
        startdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(startdateColumn);
        var enddateColumn = new DataColumn("Enddate", typeof(DateTime));
        dataTable.Columns.Add(enddateColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int businessentityid,
                        int territoryid,
                        DateTime startdate,
                        DateTime? enddate,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Territoryid"] = territoryid;
        row["Startdate"] = startdate;
        row["Enddate"] = (object?)enddate ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalesterritoryhistoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Territoryid"] = data.Territoryid;
        row["Startdate"] = data.Startdate;
        row["Enddate"] = (object?)data.Enddate ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Territoryid", "[Territoryid]");
        columnMappings.Add("Startdate", "[Startdate]");
        columnMappings.Add("Enddate", "[Enddate]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesTerritoryHistory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
