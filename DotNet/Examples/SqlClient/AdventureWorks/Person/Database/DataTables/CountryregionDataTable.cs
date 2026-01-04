using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Person.Types;

namespace AdventureWorks.Person.Database.DataTables;

public class CountryregionDataTable
{

    DataTable _dataTable;

    public CountryregionDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public CountryregionDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var countryregioncodeColumn = new DataColumn("Countryregioncode", typeof(string));
        countryregioncodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(countryregioncodeColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        string countryregioncode,
                        string name,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Countryregioncode"] = countryregioncode;
        row["Name"] = name;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(CountryregionDataType data)
    {
        var row = _dataTable.NewRow();
        row["Countryregioncode"] = data.Countryregioncode;
        row["Name"] = data.Name;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Countryregioncode", "[Countryregioncode]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Person].[CountryRegion]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
