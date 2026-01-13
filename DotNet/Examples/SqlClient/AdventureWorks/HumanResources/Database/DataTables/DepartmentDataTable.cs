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
using AdventureWorks.HumanResources.Types;

namespace AdventureWorks.HumanResources.Database.DataTables;

public class DepartmentDataTable
{

    DataTable _dataTable;

    public DepartmentDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public DepartmentDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var departmentidColumn = new DataColumn("Departmentid", typeof(short));
        departmentidColumn.AllowDBNull = false;
        dataTable.Columns.Add(departmentidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var groupnameColumn = new DataColumn("Groupname", typeof(string));
        groupnameColumn.AllowDBNull = false;
        dataTable.Columns.Add(groupnameColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        short departmentid,
                        string name,
                        string groupname,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Departmentid"] = departmentid;
        row["Name"] = name;
        row["Groupname"] = groupname;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(DepartmentDataType data)
    {
        var row = _dataTable.NewRow();
        row["Departmentid"] = data.Departmentid;
        row["Name"] = data.Name;
        row["Groupname"] = data.Groupname;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Departmentid", "[Departmentid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Groupname", "[Groupname]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[HumanResources].[Department]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
