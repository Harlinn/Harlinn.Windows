using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Person.Types;

namespace AdventureWorks.Person.Database.DataTables;

public class PersonDataTable
{

    DataTable _dataTable;

    public PersonDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public PersonDataTable()
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
        var persontypeColumn = new DataColumn("Persontype", typeof(string));
        persontypeColumn.AllowDBNull = false;
        dataTable.Columns.Add(persontypeColumn);
        var namestyleColumn = new DataColumn("Namestyle", typeof(bool));
        namestyleColumn.AllowDBNull = false;
        dataTable.Columns.Add(namestyleColumn);
        var titleColumn = new DataColumn("Title", typeof(string));
        dataTable.Columns.Add(titleColumn);
        var firstnameColumn = new DataColumn("Firstname", typeof(string));
        firstnameColumn.AllowDBNull = false;
        dataTable.Columns.Add(firstnameColumn);
        var middlenameColumn = new DataColumn("Middlename", typeof(string));
        dataTable.Columns.Add(middlenameColumn);
        var lastnameColumn = new DataColumn("Lastname", typeof(string));
        lastnameColumn.AllowDBNull = false;
        dataTable.Columns.Add(lastnameColumn);
        var suffixColumn = new DataColumn("Suffix", typeof(string));
        dataTable.Columns.Add(suffixColumn);
        var emailpromotionColumn = new DataColumn("Emailpromotion", typeof(int));
        emailpromotionColumn.AllowDBNull = false;
        dataTable.Columns.Add(emailpromotionColumn);
        var additionalcontactinfoColumn = new DataColumn("Additionalcontactinfo", typeof(SqlXml));
        dataTable.Columns.Add(additionalcontactinfoColumn);
        var demographicsColumn = new DataColumn("Demographics", typeof(SqlXml));
        dataTable.Columns.Add(demographicsColumn);
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
                        string persontype,
                        bool namestyle,
                        string? title,
                        string firstname,
                        string? middlename,
                        string lastname,
                        string? suffix,
                        int emailpromotion,
                        SqlXml? additionalcontactinfo,
                        SqlXml? demographics,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Persontype"] = persontype;
        row["Namestyle"] = namestyle;
        row["Title"] = (object?)title ?? DBNull.Value;
        row["Firstname"] = firstname;
        row["Middlename"] = (object?)middlename ?? DBNull.Value;
        row["Lastname"] = lastname;
        row["Suffix"] = (object?)suffix ?? DBNull.Value;
        row["Emailpromotion"] = emailpromotion;
        row["Additionalcontactinfo"] = (object?)additionalcontactinfo ?? DBNull.Value;
        row["Demographics"] = (object?)demographics ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(PersonDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Persontype"] = data.Persontype;
        row["Namestyle"] = data.Namestyle;
        row["Title"] = (object?)data.Title ?? DBNull.Value;
        row["Firstname"] = data.Firstname;
        row["Middlename"] = (object?)data.Middlename ?? DBNull.Value;
        row["Lastname"] = data.Lastname;
        row["Suffix"] = (object?)data.Suffix ?? DBNull.Value;
        row["Emailpromotion"] = data.Emailpromotion;
        row["Additionalcontactinfo"] = (object?)data.Additionalcontactinfo ?? DBNull.Value;
        row["Demographics"] = (object?)data.Demographics ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Persontype", "[Persontype]");
        columnMappings.Add("Namestyle", "[Namestyle]");
        columnMappings.Add("Title", "[Title]");
        columnMappings.Add("Firstname", "[Firstname]");
        columnMappings.Add("Middlename", "[Middlename]");
        columnMappings.Add("Lastname", "[Lastname]");
        columnMappings.Add("Suffix", "[Suffix]");
        columnMappings.Add("Emailpromotion", "[Emailpromotion]");
        columnMappings.Add("Additionalcontactinfo", "[Additionalcontactinfo]");
        columnMappings.Add("Demographics", "[Demographics]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Person].[Person]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
