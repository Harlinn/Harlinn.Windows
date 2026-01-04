using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class DocumentDataTable
{

    DataTable _dataTable;

    public DocumentDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public DocumentDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var documentnodeColumn = new DataColumn("Documentnode", typeof(SqlHierarchyId));
        documentnodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(documentnodeColumn);
        var titleColumn = new DataColumn("Title", typeof(string));
        titleColumn.AllowDBNull = false;
        dataTable.Columns.Add(titleColumn);
        var ownerColumn = new DataColumn("Owner", typeof(int));
        ownerColumn.AllowDBNull = false;
        dataTable.Columns.Add(ownerColumn);
        var folderflagColumn = new DataColumn("Folderflag", typeof(bool));
        folderflagColumn.AllowDBNull = false;
        dataTable.Columns.Add(folderflagColumn);
        var filenameColumn = new DataColumn("Filename", typeof(string));
        filenameColumn.AllowDBNull = false;
        dataTable.Columns.Add(filenameColumn);
        var fileextensionColumn = new DataColumn("Fileextension", typeof(string));
        fileextensionColumn.AllowDBNull = false;
        dataTable.Columns.Add(fileextensionColumn);
        var revisionColumn = new DataColumn("Revision", typeof(string));
        revisionColumn.AllowDBNull = false;
        dataTable.Columns.Add(revisionColumn);
        var changenumberColumn = new DataColumn("Changenumber", typeof(int));
        changenumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(changenumberColumn);
        var statusColumn = new DataColumn("Status", typeof(byte));
        statusColumn.AllowDBNull = false;
        dataTable.Columns.Add(statusColumn);
        var documentsummaryColumn = new DataColumn("Documentsummary", typeof(string));
        dataTable.Columns.Add(documentsummaryColumn);
        var documentColumn = new DataColumn("Document", typeof(byte[]));
        dataTable.Columns.Add(documentColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        SqlHierarchyId documentnode,
                        string title,
                        int owner,
                        bool folderflag,
                        string filename,
                        string fileextension,
                        string revision,
                        int changenumber,
                        byte status,
                        string? documentsummary,
                        byte[]? document,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Documentnode"] = documentnode;
        row["Title"] = title;
        row["Owner"] = owner;
        row["Folderflag"] = folderflag;
        row["Filename"] = filename;
        row["Fileextension"] = fileextension;
        row["Revision"] = revision;
        row["Changenumber"] = changenumber;
        row["Status"] = status;
        row["Documentsummary"] = (object?)documentsummary ?? DBNull.Value;
        row["Document"] = (object?)document ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(DocumentDataType data)
    {
        var row = _dataTable.NewRow();
        row["Documentnode"] = data.Documentnode;
        row["Title"] = data.Title;
        row["Owner"] = data.Owner;
        row["Folderflag"] = data.Folderflag;
        row["Filename"] = data.Filename;
        row["Fileextension"] = data.Fileextension;
        row["Revision"] = data.Revision;
        row["Changenumber"] = data.Changenumber;
        row["Status"] = data.Status;
        row["Documentsummary"] = (object?)data.Documentsummary ?? DBNull.Value;
        row["Document"] = (object?)data.Document ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Documentnode", "[Documentnode]");
        columnMappings.Add("Title", "[Title]");
        columnMappings.Add("Owner", "[Owner]");
        columnMappings.Add("Folderflag", "[Folderflag]");
        columnMappings.Add("Filename", "[Filename]");
        columnMappings.Add("Fileextension", "[Fileextension]");
        columnMappings.Add("Revision", "[Revision]");
        columnMappings.Add("Changenumber", "[Changenumber]");
        columnMappings.Add("Status", "[Status]");
        columnMappings.Add("Documentsummary", "[Documentsummary]");
        columnMappings.Add("Document", "[Document]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[Document]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
