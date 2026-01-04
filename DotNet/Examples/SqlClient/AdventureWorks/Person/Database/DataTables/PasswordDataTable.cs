using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Person.Types;

namespace AdventureWorks.Person.Database.DataTables;

public class PasswordDataTable
{

    DataTable _dataTable;

    public PasswordDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public PasswordDataTable()
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
        var passwordhashColumn = new DataColumn("Passwordhash", typeof(string));
        passwordhashColumn.AllowDBNull = false;
        dataTable.Columns.Add(passwordhashColumn);
        var passwordsaltColumn = new DataColumn("Passwordsalt", typeof(string));
        passwordsaltColumn.AllowDBNull = false;
        dataTable.Columns.Add(passwordsaltColumn);
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
                        string passwordhash,
                        string passwordsalt,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Passwordhash"] = passwordhash;
        row["Passwordsalt"] = passwordsalt;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(PasswordDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Passwordhash"] = data.Passwordhash;
        row["Passwordsalt"] = data.Passwordsalt;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Passwordhash", "[Passwordhash]");
        columnMappings.Add("Passwordsalt", "[Passwordsalt]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Person].[Password]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
