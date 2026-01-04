using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Purchasing.Types;

namespace AdventureWorks.Purchasing.Database.DataTables;

public class VendorDataTable
{

    DataTable _dataTable;

    public VendorDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public VendorDataTable()
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
        var accountnumberColumn = new DataColumn("Accountnumber", typeof(string));
        accountnumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(accountnumberColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var creditratingColumn = new DataColumn("Creditrating", typeof(byte));
        creditratingColumn.AllowDBNull = false;
        dataTable.Columns.Add(creditratingColumn);
        var preferredvendorstatusColumn = new DataColumn("Preferredvendorstatus", typeof(bool));
        preferredvendorstatusColumn.AllowDBNull = false;
        dataTable.Columns.Add(preferredvendorstatusColumn);
        var activeflagColumn = new DataColumn("Activeflag", typeof(bool));
        activeflagColumn.AllowDBNull = false;
        dataTable.Columns.Add(activeflagColumn);
        var purchasingwebserviceurlColumn = new DataColumn("Purchasingwebserviceurl", typeof(string));
        dataTable.Columns.Add(purchasingwebserviceurlColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int businessentityid,
                        string accountnumber,
                        string name,
                        byte creditrating,
                        bool preferredvendorstatus,
                        bool activeflag,
                        string? purchasingwebserviceurl,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Accountnumber"] = accountnumber;
        row["Name"] = name;
        row["Creditrating"] = creditrating;
        row["Preferredvendorstatus"] = preferredvendorstatus;
        row["Activeflag"] = activeflag;
        row["Purchasingwebserviceurl"] = (object?)purchasingwebserviceurl ?? DBNull.Value;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(VendorDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Accountnumber"] = data.Accountnumber;
        row["Name"] = data.Name;
        row["Creditrating"] = data.Creditrating;
        row["Preferredvendorstatus"] = data.Preferredvendorstatus;
        row["Activeflag"] = data.Activeflag;
        row["Purchasingwebserviceurl"] = (object?)data.Purchasingwebserviceurl ?? DBNull.Value;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Accountnumber", "[Accountnumber]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Creditrating", "[Creditrating]");
        columnMappings.Add("Preferredvendorstatus", "[Preferredvendorstatus]");
        columnMappings.Add("Activeflag", "[Activeflag]");
        columnMappings.Add("Purchasingwebserviceurl", "[Purchasingwebserviceurl]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Purchasing].[Vendor]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
