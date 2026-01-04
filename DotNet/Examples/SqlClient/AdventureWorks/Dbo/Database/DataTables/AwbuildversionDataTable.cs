using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Dbo.Types;

namespace AdventureWorks.Dbo.Database.DataTables;

public class AwbuildversionDataTable
{

    DataTable _dataTable;

    public AwbuildversionDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public AwbuildversionDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var systeminformationidColumn = new DataColumn("Systeminformationid", typeof(byte));
        systeminformationidColumn.AllowDBNull = false;
        dataTable.Columns.Add(systeminformationidColumn);
        var databaseVersionColumn = new DataColumn("Database Version", typeof(string));
        databaseVersionColumn.AllowDBNull = false;
        dataTable.Columns.Add(databaseVersionColumn);
        var versiondateColumn = new DataColumn("Versiondate", typeof(DateTime));
        versiondateColumn.AllowDBNull = false;
        dataTable.Columns.Add(versiondateColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        byte systeminformationid,
                        string databaseVersion,
                        DateTime versiondate,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Systeminformationid"] = systeminformationid;
        row["Database Version"] = databaseVersion;
        row["Versiondate"] = versiondate;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(AwbuildversionDataType data)
    {
        var row = _dataTable.NewRow();
        row["Systeminformationid"] = data.Systeminformationid;
        row["Database Version"] = data.DatabaseVersion;
        row["Versiondate"] = data.Versiondate;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Systeminformationid", "[Systeminformationid]");
        columnMappings.Add("Database Version", "[Database Version]");
        columnMappings.Add("Versiondate", "[Versiondate]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[dbo].[AWBuildVersion]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
