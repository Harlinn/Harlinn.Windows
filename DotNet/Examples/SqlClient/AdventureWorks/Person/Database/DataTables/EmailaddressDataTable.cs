using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Person.Types;

namespace AdventureWorks.Person.Database.DataTables;

public class EmailaddressDataTable
{

    DataTable _dataTable;

    public EmailaddressDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public EmailaddressDataTable()
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
        var emailaddressidColumn = new DataColumn("Emailaddressid", typeof(int));
        emailaddressidColumn.AllowDBNull = false;
        dataTable.Columns.Add(emailaddressidColumn);
        var emailaddressColumn = new DataColumn("Emailaddress", typeof(string));
        dataTable.Columns.Add(emailaddressColumn);
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
                        int emailaddressid,
                        string? emailaddress,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Emailaddressid"] = emailaddressid;
        row["Emailaddress"] = (object?)emailaddress ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(EmailaddressDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Emailaddressid"] = data.Emailaddressid;
        row["Emailaddress"] = (object?)data.Emailaddress ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Emailaddressid", "[Emailaddressid]");
        columnMappings.Add("Emailaddress", "[Emailaddress]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Person].[EmailAddress]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
