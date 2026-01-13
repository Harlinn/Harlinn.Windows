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

public class CurrencyrateDataTable
{

    DataTable _dataTable;

    public CurrencyrateDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public CurrencyrateDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var currencyrateidColumn = new DataColumn("Currencyrateid", typeof(int));
        currencyrateidColumn.AllowDBNull = false;
        dataTable.Columns.Add(currencyrateidColumn);
        var currencyratedateColumn = new DataColumn("Currencyratedate", typeof(DateTime));
        currencyratedateColumn.AllowDBNull = false;
        dataTable.Columns.Add(currencyratedateColumn);
        var fromcurrencycodeColumn = new DataColumn("Fromcurrencycode", typeof(string));
        fromcurrencycodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(fromcurrencycodeColumn);
        var tocurrencycodeColumn = new DataColumn("Tocurrencycode", typeof(string));
        tocurrencycodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(tocurrencycodeColumn);
        var averagerateColumn = new DataColumn("Averagerate", typeof(decimal));
        averagerateColumn.AllowDBNull = false;
        dataTable.Columns.Add(averagerateColumn);
        var endofdayrateColumn = new DataColumn("Endofdayrate", typeof(decimal));
        endofdayrateColumn.AllowDBNull = false;
        dataTable.Columns.Add(endofdayrateColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int currencyrateid,
                        DateTime currencyratedate,
                        string fromcurrencycode,
                        string tocurrencycode,
                        decimal averagerate,
                        decimal endofdayrate,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Currencyrateid"] = currencyrateid;
        row["Currencyratedate"] = currencyratedate;
        row["Fromcurrencycode"] = fromcurrencycode;
        row["Tocurrencycode"] = tocurrencycode;
        row["Averagerate"] = averagerate;
        row["Endofdayrate"] = endofdayrate;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(CurrencyrateDataType data)
    {
        var row = _dataTable.NewRow();
        row["Currencyrateid"] = data.Currencyrateid;
        row["Currencyratedate"] = data.Currencyratedate;
        row["Fromcurrencycode"] = data.Fromcurrencycode;
        row["Tocurrencycode"] = data.Tocurrencycode;
        row["Averagerate"] = data.Averagerate;
        row["Endofdayrate"] = data.Endofdayrate;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Currencyrateid", "[Currencyrateid]");
        columnMappings.Add("Currencyratedate", "[Currencyratedate]");
        columnMappings.Add("Fromcurrencycode", "[Fromcurrencycode]");
        columnMappings.Add("Tocurrencycode", "[Tocurrencycode]");
        columnMappings.Add("Averagerate", "[Averagerate]");
        columnMappings.Add("Endofdayrate", "[Endofdayrate]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[CurrencyRate]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
