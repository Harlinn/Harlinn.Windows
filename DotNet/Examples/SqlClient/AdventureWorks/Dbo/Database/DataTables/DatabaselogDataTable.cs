using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Dbo.Types;

namespace AdventureWorks.Dbo.Database.DataTables;

public class DatabaselogDataTable
{

    DataTable _dataTable;

    public DatabaselogDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public DatabaselogDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var databaselogidColumn = new DataColumn("Databaselogid", typeof(int));
        databaselogidColumn.AllowDBNull = false;
        dataTable.Columns.Add(databaselogidColumn);
        var posttimeColumn = new DataColumn("Posttime", typeof(DateTime));
        posttimeColumn.AllowDBNull = false;
        dataTable.Columns.Add(posttimeColumn);
        var databaseuserColumn = new DataColumn("Databaseuser", typeof(string));
        databaseuserColumn.AllowDBNull = false;
        dataTable.Columns.Add(databaseuserColumn);
        var event__Column = new DataColumn("Event", typeof(string));
        event__Column.AllowDBNull = false;
        dataTable.Columns.Add(event__Column);
        var schemaColumn = new DataColumn("Schema", typeof(string));
        dataTable.Columns.Add(schemaColumn);
        var object__Column = new DataColumn("Object", typeof(string));
        dataTable.Columns.Add(object__Column);
        var tsqlColumn = new DataColumn("Tsql", typeof(string));
        tsqlColumn.AllowDBNull = false;
        dataTable.Columns.Add(tsqlColumn);
        var xmleventColumn = new DataColumn("Xmlevent", typeof(SqlXml));
        xmleventColumn.AllowDBNull = false;
        dataTable.Columns.Add(xmleventColumn);

        return dataTable;
    }

    public void AddRow( 
                        int databaselogid,
                        DateTime posttime,
                        string databaseuser,
                        string event__,
                        string? schema,
                        string? object__,
                        string tsql,
                        SqlXml xmlevent
                        )
    {
        var row = _dataTable.NewRow();
        row["Databaselogid"] = databaselogid;
        row["Posttime"] = posttime;
        row["Databaseuser"] = databaseuser;
        row["Event"] = event__;
        row["Schema"] = (object?)schema ?? DBNull.Value;
        row["Object"] = (object?)object__ ?? DBNull.Value;
        row["Tsql"] = tsql;
        row["Xmlevent"] = xmlevent;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(DatabaselogDataType data)
    {
        var row = _dataTable.NewRow();
        row["Databaselogid"] = data.Databaselogid;
        row["Posttime"] = data.Posttime;
        row["Databaseuser"] = data.Databaseuser;
        row["Event"] = data.Event;
        row["Schema"] = (object?)data.Schema ?? DBNull.Value;
        row["Object"] = (object?)data.Object ?? DBNull.Value;
        row["Tsql"] = data.Tsql;
        row["Xmlevent"] = data.Xmlevent;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Databaselogid", "[Databaselogid]");
        columnMappings.Add("Posttime", "[Posttime]");
        columnMappings.Add("Databaseuser", "[Databaseuser]");
        columnMappings.Add("Event", "[Event]");
        columnMappings.Add("Schema", "[Schema]");
        columnMappings.Add("Object", "[Object]");
        columnMappings.Add("Tsql", "[Tsql]");
        columnMappings.Add("Xmlevent", "[Xmlevent]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[dbo].[DatabaseLog]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
