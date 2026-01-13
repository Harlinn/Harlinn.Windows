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

public class JobcandidateDataTable
{

    DataTable _dataTable;

    public JobcandidateDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public JobcandidateDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var jobcandidateidColumn = new DataColumn("Jobcandidateid", typeof(int));
        jobcandidateidColumn.AllowDBNull = false;
        dataTable.Columns.Add(jobcandidateidColumn);
        var businessentityidColumn = new DataColumn("Businessentityid", typeof(int));
        dataTable.Columns.Add(businessentityidColumn);
        var resumeColumn = new DataColumn("Resume", typeof(SqlXml));
        dataTable.Columns.Add(resumeColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int jobcandidateid,
                        int? businessentityid,
                        SqlXml? resume,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Jobcandidateid"] = jobcandidateid;
        row["Businessentityid"] = (object?)businessentityid ?? DBNull.Value;
        row["Resume"] = (object?)resume ?? DBNull.Value;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(JobcandidateDataType data)
    {
        var row = _dataTable.NewRow();
        row["Jobcandidateid"] = data.Jobcandidateid;
        row["Businessentityid"] = (object?)data.Businessentityid ?? DBNull.Value;
        row["Resume"] = (object?)data.Resume ?? DBNull.Value;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Jobcandidateid", "[Jobcandidateid]");
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Resume", "[Resume]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[HumanResources].[JobCandidate]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
