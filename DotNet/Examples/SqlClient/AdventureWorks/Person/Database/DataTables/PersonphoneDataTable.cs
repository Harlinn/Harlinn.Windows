using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Person.Types;

namespace AdventureWorks.Person.Database.DataTables;

public class PersonphoneDataTable
{

    DataTable _dataTable;

    public PersonphoneDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public PersonphoneDataTable()
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
        var phonenumberColumn = new DataColumn("Phonenumber", typeof(string));
        phonenumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(phonenumberColumn);
        var phonenumbertypeidColumn = new DataColumn("Phonenumbertypeid", typeof(int));
        phonenumbertypeidColumn.AllowDBNull = false;
        dataTable.Columns.Add(phonenumbertypeidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int businessentityid,
                        string phonenumber,
                        int phonenumbertypeid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Phonenumber"] = phonenumber;
        row["Phonenumbertypeid"] = phonenumbertypeid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(PersonphoneDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Phonenumber"] = data.Phonenumber;
        row["Phonenumbertypeid"] = data.Phonenumbertypeid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Phonenumber", "[Phonenumber]");
        columnMappings.Add("Phonenumbertypeid", "[Phonenumbertypeid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Person].[PersonPhone]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
