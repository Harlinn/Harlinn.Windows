using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Person.Types;

namespace AdventureWorks.Person.Database.DataTables;

public class AddresstypeDataTable
{

    DataTable _dataTable;

    public AddresstypeDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public AddresstypeDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var addresstypeidColumn = new DataColumn("Addresstypeid", typeof(int));
        addresstypeidColumn.AllowDBNull = false;
        dataTable.Columns.Add(addresstypeidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int addresstypeid,
                        string name,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Addresstypeid"] = addresstypeid;
        row["Name"] = name;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(AddresstypeDataType data)
    {
        var row = _dataTable.NewRow();
        row["Addresstypeid"] = data.Addresstypeid;
        row["Name"] = data.Name;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Addresstypeid", "[Addresstypeid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Person].[AddressType]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
