/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Dbo.Types;

namespace AdventureWorks.Dbo.Database.DataTables;

public class ErrorlogDataTable
{

    DataTable _dataTable;

    public ErrorlogDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ErrorlogDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var errorlogidColumn = new DataColumn("Errorlogid", typeof(int));
        errorlogidColumn.AllowDBNull = false;
        dataTable.Columns.Add(errorlogidColumn);
        var errortimeColumn = new DataColumn("Errortime", typeof(DateTime));
        errortimeColumn.AllowDBNull = false;
        dataTable.Columns.Add(errortimeColumn);
        var usernameColumn = new DataColumn("Username", typeof(string));
        usernameColumn.AllowDBNull = false;
        dataTable.Columns.Add(usernameColumn);
        var errornumberColumn = new DataColumn("Errornumber", typeof(int));
        errornumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(errornumberColumn);
        var errorseverityColumn = new DataColumn("Errorseverity", typeof(int));
        dataTable.Columns.Add(errorseverityColumn);
        var errorstateColumn = new DataColumn("Errorstate", typeof(int));
        dataTable.Columns.Add(errorstateColumn);
        var errorprocedureColumn = new DataColumn("Errorprocedure", typeof(string));
        dataTable.Columns.Add(errorprocedureColumn);
        var errorlineColumn = new DataColumn("Errorline", typeof(int));
        dataTable.Columns.Add(errorlineColumn);
        var errormessageColumn = new DataColumn("Errormessage", typeof(string));
        errormessageColumn.AllowDBNull = false;
        dataTable.Columns.Add(errormessageColumn);

        return dataTable;
    }

    public void AddRow( 
                        int errorlogid,
                        DateTime errortime,
                        string username,
                        int errornumber,
                        int? errorseverity,
                        int? errorstate,
                        string? errorprocedure,
                        int? errorline,
                        string errormessage
                        )
    {
        var row = _dataTable.NewRow();
        row["Errorlogid"] = errorlogid;
        row["Errortime"] = errortime;
        row["Username"] = username;
        row["Errornumber"] = errornumber;
        row["Errorseverity"] = (object?)errorseverity ?? DBNull.Value;
        row["Errorstate"] = (object?)errorstate ?? DBNull.Value;
        row["Errorprocedure"] = (object?)errorprocedure ?? DBNull.Value;
        row["Errorline"] = (object?)errorline ?? DBNull.Value;
        row["Errormessage"] = errormessage;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ErrorlogDataType data)
    {
        var row = _dataTable.NewRow();
        row["Errorlogid"] = data.Errorlogid;
        row["Errortime"] = data.Errortime;
        row["Username"] = data.Username;
        row["Errornumber"] = data.Errornumber;
        row["Errorseverity"] = (object?)data.Errorseverity ?? DBNull.Value;
        row["Errorstate"] = (object?)data.Errorstate ?? DBNull.Value;
        row["Errorprocedure"] = (object?)data.Errorprocedure ?? DBNull.Value;
        row["Errorline"] = (object?)data.Errorline ?? DBNull.Value;
        row["Errormessage"] = data.Errormessage;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Errorlogid", "[Errorlogid]");
        columnMappings.Add("Errortime", "[Errortime]");
        columnMappings.Add("Username", "[Username]");
        columnMappings.Add("Errornumber", "[Errornumber]");
        columnMappings.Add("Errorseverity", "[Errorseverity]");
        columnMappings.Add("Errorstate", "[Errorstate]");
        columnMappings.Add("Errorprocedure", "[Errorprocedure]");
        columnMappings.Add("Errorline", "[Errorline]");
        columnMappings.Add("Errormessage", "[Errormessage]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[dbo].[ErrorLog]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
