using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Person.Types;

namespace AdventureWorks.Person.Database.DataTables;

public class StateprovinceDataTable
{

    DataTable _dataTable;

    public StateprovinceDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public StateprovinceDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var stateprovinceidColumn = new DataColumn("Stateprovinceid", typeof(int));
        stateprovinceidColumn.AllowDBNull = false;
        dataTable.Columns.Add(stateprovinceidColumn);
        var stateprovincecodeColumn = new DataColumn("Stateprovincecode", typeof(string));
        stateprovincecodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(stateprovincecodeColumn);
        var countryregioncodeColumn = new DataColumn("Countryregioncode", typeof(string));
        countryregioncodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(countryregioncodeColumn);
        var isonlystateprovinceflagColumn = new DataColumn("Isonlystateprovinceflag", typeof(bool));
        isonlystateprovinceflagColumn.AllowDBNull = false;
        dataTable.Columns.Add(isonlystateprovinceflagColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var territoryidColumn = new DataColumn("Territoryid", typeof(int));
        territoryidColumn.AllowDBNull = false;
        dataTable.Columns.Add(territoryidColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int stateprovinceid,
                        string stateprovincecode,
                        string countryregioncode,
                        bool isonlystateprovinceflag,
                        string name,
                        int territoryid,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Stateprovinceid"] = stateprovinceid;
        row["Stateprovincecode"] = stateprovincecode;
        row["Countryregioncode"] = countryregioncode;
        row["Isonlystateprovinceflag"] = isonlystateprovinceflag;
        row["Name"] = name;
        row["Territoryid"] = territoryid;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(StateprovinceDataType data)
    {
        var row = _dataTable.NewRow();
        row["Stateprovinceid"] = data.Stateprovinceid;
        row["Stateprovincecode"] = data.Stateprovincecode;
        row["Countryregioncode"] = data.Countryregioncode;
        row["Isonlystateprovinceflag"] = data.Isonlystateprovinceflag;
        row["Name"] = data.Name;
        row["Territoryid"] = data.Territoryid;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Stateprovinceid", "[Stateprovinceid]");
        columnMappings.Add("Stateprovincecode", "[Stateprovincecode]");
        columnMappings.Add("Countryregioncode", "[Countryregioncode]");
        columnMappings.Add("Isonlystateprovinceflag", "[Isonlystateprovinceflag]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Territoryid", "[Territoryid]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Person].[StateProvince]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
