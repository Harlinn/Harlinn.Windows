using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class LocationDataTable
{

    DataTable _dataTable;

    public LocationDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public LocationDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var locationidColumn = new DataColumn("Locationid", typeof(short));
        locationidColumn.AllowDBNull = false;
        dataTable.Columns.Add(locationidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var costrateColumn = new DataColumn("Costrate", typeof(decimal));
        costrateColumn.AllowDBNull = false;
        dataTable.Columns.Add(costrateColumn);
        var availabilityColumn = new DataColumn("Availability", typeof(decimal));
        availabilityColumn.AllowDBNull = false;
        dataTable.Columns.Add(availabilityColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        short locationid,
                        string name,
                        decimal costrate,
                        decimal availability,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Locationid"] = locationid;
        row["Name"] = name;
        row["Costrate"] = costrate;
        row["Availability"] = availability;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(LocationDataType data)
    {
        var row = _dataTable.NewRow();
        row["Locationid"] = data.Locationid;
        row["Name"] = data.Name;
        row["Costrate"] = data.Costrate;
        row["Availability"] = data.Availability;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Locationid", "[Locationid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Costrate", "[Costrate]");
        columnMappings.Add("Availability", "[Availability]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[Location]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
