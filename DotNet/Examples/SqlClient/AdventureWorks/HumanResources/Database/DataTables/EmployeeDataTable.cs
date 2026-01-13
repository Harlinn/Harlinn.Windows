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

public class EmployeeDataTable
{

    DataTable _dataTable;

    public EmployeeDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public EmployeeDataTable()
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
        var nationalidnumberColumn = new DataColumn("Nationalidnumber", typeof(string));
        nationalidnumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(nationalidnumberColumn);
        var loginidColumn = new DataColumn("Loginid", typeof(string));
        loginidColumn.AllowDBNull = false;
        dataTable.Columns.Add(loginidColumn);
        var organizationnodeColumn = new DataColumn("Organizationnode", typeof(SqlHierarchyId));
        dataTable.Columns.Add(organizationnodeColumn);
        var jobtitleColumn = new DataColumn("Jobtitle", typeof(string));
        jobtitleColumn.AllowDBNull = false;
        dataTable.Columns.Add(jobtitleColumn);
        var birthdateColumn = new DataColumn("Birthdate", typeof(DateTime));
        birthdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(birthdateColumn);
        var maritalstatusColumn = new DataColumn("Maritalstatus", typeof(string));
        maritalstatusColumn.AllowDBNull = false;
        dataTable.Columns.Add(maritalstatusColumn);
        var genderColumn = new DataColumn("Gender", typeof(string));
        genderColumn.AllowDBNull = false;
        dataTable.Columns.Add(genderColumn);
        var hiredateColumn = new DataColumn("Hiredate", typeof(DateTime));
        hiredateColumn.AllowDBNull = false;
        dataTable.Columns.Add(hiredateColumn);
        var salariedflagColumn = new DataColumn("Salariedflag", typeof(bool));
        salariedflagColumn.AllowDBNull = false;
        dataTable.Columns.Add(salariedflagColumn);
        var vacationhoursColumn = new DataColumn("Vacationhours", typeof(short));
        vacationhoursColumn.AllowDBNull = false;
        dataTable.Columns.Add(vacationhoursColumn);
        var sickleavehoursColumn = new DataColumn("Sickleavehours", typeof(short));
        sickleavehoursColumn.AllowDBNull = false;
        dataTable.Columns.Add(sickleavehoursColumn);
        var currentflagColumn = new DataColumn("Currentflag", typeof(bool));
        currentflagColumn.AllowDBNull = false;
        dataTable.Columns.Add(currentflagColumn);
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
                        string nationalidnumber,
                        string loginid,
                        SqlHierarchyId? organizationnode,
                        string jobtitle,
                        DateTime birthdate,
                        string maritalstatus,
                        string gender,
                        DateTime hiredate,
                        bool salariedflag,
                        short vacationhours,
                        short sickleavehours,
                        bool currentflag,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Nationalidnumber"] = nationalidnumber;
        row["Loginid"] = loginid;
        row["Organizationnode"] = (object?)organizationnode ?? DBNull.Value;
        row["Jobtitle"] = jobtitle;
        row["Birthdate"] = birthdate;
        row["Maritalstatus"] = maritalstatus;
        row["Gender"] = gender;
        row["Hiredate"] = hiredate;
        row["Salariedflag"] = salariedflag;
        row["Vacationhours"] = vacationhours;
        row["Sickleavehours"] = sickleavehours;
        row["Currentflag"] = currentflag;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(EmployeeDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Nationalidnumber"] = data.Nationalidnumber;
        row["Loginid"] = data.Loginid;
        row["Organizationnode"] = (object?)data.Organizationnode ?? DBNull.Value;
        row["Jobtitle"] = data.Jobtitle;
        row["Birthdate"] = data.Birthdate;
        row["Maritalstatus"] = data.Maritalstatus;
        row["Gender"] = data.Gender;
        row["Hiredate"] = data.Hiredate;
        row["Salariedflag"] = data.Salariedflag;
        row["Vacationhours"] = data.Vacationhours;
        row["Sickleavehours"] = data.Sickleavehours;
        row["Currentflag"] = data.Currentflag;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Nationalidnumber", "[Nationalidnumber]");
        columnMappings.Add("Loginid", "[Loginid]");
        columnMappings.Add("Organizationnode", "[Organizationnode]");
        columnMappings.Add("Jobtitle", "[Jobtitle]");
        columnMappings.Add("Birthdate", "[Birthdate]");
        columnMappings.Add("Maritalstatus", "[Maritalstatus]");
        columnMappings.Add("Gender", "[Gender]");
        columnMappings.Add("Hiredate", "[Hiredate]");
        columnMappings.Add("Salariedflag", "[Salariedflag]");
        columnMappings.Add("Vacationhours", "[Vacationhours]");
        columnMappings.Add("Sickleavehours", "[Sickleavehours]");
        columnMappings.Add("Currentflag", "[Currentflag]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[HumanResources].[Employee]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
