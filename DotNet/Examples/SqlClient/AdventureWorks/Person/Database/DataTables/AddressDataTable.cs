using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Person.Types;

namespace AdventureWorks.Person.Database.DataTables;

public class AddressDataTable
{

    DataTable _dataTable;

    public AddressDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public AddressDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var addressidColumn = new DataColumn("Addressid", typeof(int));
        addressidColumn.AllowDBNull = false;
        dataTable.Columns.Add(addressidColumn);
        var addressline1Column = new DataColumn("Addressline1", typeof(string));
        addressline1Column.AllowDBNull = false;
        dataTable.Columns.Add(addressline1Column);
        var addressline2Column = new DataColumn("Addressline2", typeof(string));
        dataTable.Columns.Add(addressline2Column);
        var cityColumn = new DataColumn("City", typeof(string));
        cityColumn.AllowDBNull = false;
        dataTable.Columns.Add(cityColumn);
        var stateprovinceidColumn = new DataColumn("Stateprovinceid", typeof(int));
        stateprovinceidColumn.AllowDBNull = false;
        dataTable.Columns.Add(stateprovinceidColumn);
        var postalcodeColumn = new DataColumn("Postalcode", typeof(string));
        postalcodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(postalcodeColumn);
        var spatiallocationColumn = new DataColumn("Spatiallocation", typeof(SqlGeography));
        dataTable.Columns.Add(spatiallocationColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int addressid,
                        string addressline1,
                        string? addressline2,
                        string city,
                        int stateprovinceid,
                        string postalcode,
                        SqlGeography? spatiallocation,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Addressid"] = addressid;
        row["Addressline1"] = addressline1;
        row["Addressline2"] = (object?)addressline2 ?? DBNull.Value;
        row["City"] = city;
        row["Stateprovinceid"] = stateprovinceid;
        row["Postalcode"] = postalcode;
        row["Spatiallocation"] = (object?)spatiallocation ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(AddressDataType data)
    {
        var row = _dataTable.NewRow();
        row["Addressid"] = data.Addressid;
        row["Addressline1"] = data.Addressline1;
        row["Addressline2"] = (object?)data.Addressline2 ?? DBNull.Value;
        row["City"] = data.City;
        row["Stateprovinceid"] = data.Stateprovinceid;
        row["Postalcode"] = data.Postalcode;
        row["Spatiallocation"] = (object?)data.Spatiallocation ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Addressid", "[Addressid]");
        columnMappings.Add("Addressline1", "[Addressline1]");
        columnMappings.Add("Addressline2", "[Addressline2]");
        columnMappings.Add("City", "[City]");
        columnMappings.Add("Stateprovinceid", "[Stateprovinceid]");
        columnMappings.Add("Postalcode", "[Postalcode]");
        columnMappings.Add("Spatiallocation", "[Spatiallocation]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Person].[Address]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
