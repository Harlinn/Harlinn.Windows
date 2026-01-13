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
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class CreditcardDataTable
{

    DataTable _dataTable;

    public CreditcardDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public CreditcardDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var creditcardidColumn = new DataColumn("Creditcardid", typeof(int));
        creditcardidColumn.AllowDBNull = false;
        dataTable.Columns.Add(creditcardidColumn);
        var cardtypeColumn = new DataColumn("Cardtype", typeof(string));
        cardtypeColumn.AllowDBNull = false;
        dataTable.Columns.Add(cardtypeColumn);
        var cardnumberColumn = new DataColumn("Cardnumber", typeof(string));
        cardnumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(cardnumberColumn);
        var expmonthColumn = new DataColumn("Expmonth", typeof(byte));
        expmonthColumn.AllowDBNull = false;
        dataTable.Columns.Add(expmonthColumn);
        var expyearColumn = new DataColumn("Expyear", typeof(short));
        expyearColumn.AllowDBNull = false;
        dataTable.Columns.Add(expyearColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int creditcardid,
                        string cardtype,
                        string cardnumber,
                        byte expmonth,
                        short expyear,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Creditcardid"] = creditcardid;
        row["Cardtype"] = cardtype;
        row["Cardnumber"] = cardnumber;
        row["Expmonth"] = expmonth;
        row["Expyear"] = expyear;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(CreditcardDataType data)
    {
        var row = _dataTable.NewRow();
        row["Creditcardid"] = data.Creditcardid;
        row["Cardtype"] = data.Cardtype;
        row["Cardnumber"] = data.Cardnumber;
        row["Expmonth"] = data.Expmonth;
        row["Expyear"] = data.Expyear;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Creditcardid", "[Creditcardid]");
        columnMappings.Add("Cardtype", "[Cardtype]");
        columnMappings.Add("Cardnumber", "[Cardnumber]");
        columnMappings.Add("Expmonth", "[Expmonth]");
        columnMappings.Add("Expyear", "[Expyear]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[CreditCard]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
