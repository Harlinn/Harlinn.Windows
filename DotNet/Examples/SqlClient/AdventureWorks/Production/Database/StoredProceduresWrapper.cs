using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

using AdventureWorks.Dbo.Types;
using AdventureWorks.HumanResources.Types;
using AdventureWorks.Person.Types;
using AdventureWorks.Production.Types;
using AdventureWorks.Purchasing.Types;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Production.Database;

public class StoredProceduresWrapper
{
    public static bool InsertBillofmaterials(SqlConnection sqlConnection, ref int billofmaterialsid,
        int? productassemblyid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertBillOfMaterials]";

        var billofmaterialsidParameter = command.Parameters.AddInt32("@billofmaterialsid");
        command.Parameters.AddInt32("@productassemblyid", productassemblyid);
        command.Parameters.AddInt32("@componentid", componentid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddInt16("@bomlevel", bomlevel);
        command.Parameters.AddDecimal("@perassemblyqty", perassemblyqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            billofmaterialsid = (int)billofmaterialsidParameter.Value;
        }
        return result;
    }

    public static bool MergeBillofmaterials(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.BillofmaterialsDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeBillOfMaterials]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertBillofmaterials(SqlConnection sqlConnection, AdventureWorks.Production.Types.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataProductassemblyid = data.Productassemblyid;
        var dataComponentid = data.Componentid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataBomlevel = data.Bomlevel;
        var dataPerassemblyqty = data.Perassemblyqty;
        var dataModifieddate = data.Modifieddate;
        var result = InsertBillofmaterials( sqlConnection, 
                        ref dataBillofmaterialsid,
                        dataProductassemblyid,
                        dataComponentid,
                        dataStartdate,
                        dataEnddate,
                        dataUnitmeasurecode,
                        dataBomlevel,
                        dataPerassemblyqty,
                        dataModifieddate );
        data.Billofmaterialsid = dataBillofmaterialsid;

        return result;
    }

    public static bool UpdateBillofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int? productassemblyid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateBillOfMaterials]";

        command.Parameters.AddInt32("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddInt32("@productassemblyid", productassemblyid);
        command.Parameters.AddInt32("@componentid", componentid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddInt16("@bomlevel", bomlevel);
        command.Parameters.AddDecimal("@perassemblyqty", perassemblyqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateBillofmaterials(SqlConnection sqlConnection, AdventureWorks.Production.Types.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataProductassemblyid = data.Productassemblyid;
        var dataComponentid = data.Componentid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataBomlevel = data.Bomlevel;
        var dataPerassemblyqty = data.Perassemblyqty;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateBillofmaterials( sqlConnection, 
                        dataBillofmaterialsid,
                        dataProductassemblyid,
                        dataComponentid,
                        dataStartdate,
                        dataEnddate,
                        dataUnitmeasurecode,
                        dataBomlevel,
                        dataPerassemblyqty,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteBillofmaterials(SqlConnection sqlConnection, int billofmaterialsid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteBillOfMaterials]";

        command.Parameters.AddInt32("@billofmaterialsid", billofmaterialsid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteBillofmaterials(SqlConnection sqlConnection, AdventureWorks.Production.Types.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var result = DeleteBillofmaterials( sqlConnection, 
                        dataBillofmaterialsid );

        return result;
    }

    public static bool Insert1Billofmaterials(SqlConnection sqlConnection, ref int billofmaterialsid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Insert1BillOfMaterials]";

        var billofmaterialsidParameter = command.Parameters.AddInt32("@billofmaterialsid");
        command.Parameters.AddInt32("@componentid", componentid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddInt16("@bomlevel", bomlevel);
        command.Parameters.AddDecimal("@perassemblyqty", perassemblyqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            billofmaterialsid = (int)billofmaterialsidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Billofmaterials(SqlConnection sqlConnection, AdventureWorks.Production.Types.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataComponentid = data.Componentid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataBomlevel = data.Bomlevel;
        var dataPerassemblyqty = data.Perassemblyqty;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Billofmaterials( sqlConnection, 
                        ref dataBillofmaterialsid,
                        dataComponentid,
                        dataStartdate,
                        dataEnddate,
                        dataUnitmeasurecode,
                        dataBomlevel,
                        dataPerassemblyqty,
                        dataModifieddate );
        data.Billofmaterialsid = dataBillofmaterialsid;

        return result;
    }

    public static bool Update1Billofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update1BillOfMaterials]";

        command.Parameters.AddInt32("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddInt32("@componentid", componentid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddInt16("@bomlevel", bomlevel);
        command.Parameters.AddDecimal("@perassemblyqty", perassemblyqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Billofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int? productassemblyid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update2BillOfMaterials]";

        command.Parameters.AddInt32("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddInt32("@productassemblyid", productassemblyid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Billofmaterials(SqlConnection sqlConnection, AdventureWorks.Production.Types.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataComponentid = data.Componentid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataBomlevel = data.Bomlevel;
        var dataPerassemblyqty = data.Perassemblyqty;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Billofmaterials( sqlConnection, 
                        dataBillofmaterialsid,
                        dataComponentid,
                        dataStartdate,
                        dataEnddate,
                        dataUnitmeasurecode,
                        dataBomlevel,
                        dataPerassemblyqty,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Billofmaterials(SqlConnection sqlConnection, AdventureWorks.Production.Types.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataProductassemblyid = data.Productassemblyid;
        var result = Update2Billofmaterials( sqlConnection, 
                        dataBillofmaterialsid,
                        dataProductassemblyid );

        return result;
    }

    public static bool InsertCulture(SqlConnection sqlConnection, string cultureid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertCulture]";

        command.Parameters.AddNChar("@cultureid", cultureid, 6);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeCulture(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.CultureDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeCulture]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertCulture(SqlConnection sqlConnection, AdventureWorks.Production.Types.CultureDataType data )
    {
        var dataCultureid = data.Cultureid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCulture( sqlConnection, 
                        dataCultureid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateCulture(SqlConnection sqlConnection, string cultureid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateCulture]";

        command.Parameters.AddNChar("@cultureid", cultureid, 6);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCulture(SqlConnection sqlConnection, AdventureWorks.Production.Types.CultureDataType data )
    {
        var dataCultureid = data.Cultureid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCulture( sqlConnection, 
                        dataCultureid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCulture(SqlConnection sqlConnection, string cultureid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteCulture]";

        command.Parameters.AddNChar("@cultureid", cultureid, 6);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCulture(SqlConnection sqlConnection, AdventureWorks.Production.Types.CultureDataType data )
    {
        var dataCultureid = data.Cultureid;
        var result = DeleteCulture( sqlConnection, 
                        dataCultureid );

        return result;
    }

    public static bool InsertDocument(SqlConnection sqlConnection, SqlHierarchyId documentnode,
        short? documentlevel,
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
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertDocument]";

        command.Parameters.AddHierarchyId("@documentnode", documentnode);
        command.Parameters.AddInt16("@documentlevel", documentlevel);
        command.Parameters.AddNVarChar("@title", title, 50);
        command.Parameters.AddInt32("@owner", owner);
        command.Parameters.AddBoolean("@folderflag", folderflag);
        command.Parameters.AddNVarChar("@filename", filename, 400);
        command.Parameters.AddNVarChar("@fileextension", fileextension, 8);
        command.Parameters.AddNChar("@revision", revision, 5);
        command.Parameters.AddInt32("@changenumber", changenumber);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddNVarChar("@documentsummary", documentsummary, -1);
        command.Parameters.AddBinary("@document", document, -1);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeDocument(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.DocumentDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeDocument]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertDocument(SqlConnection sqlConnection, AdventureWorks.Production.Types.DocumentDataType data )
    {
        var dataDocumentnode = data.Documentnode;
        var dataDocumentlevel = data.Documentlevel;
        var dataTitle = data.Title;
        var dataOwner = data.Owner;
        var dataFolderflag = data.Folderflag;
        var dataFilename = data.Filename;
        var dataFileextension = data.Fileextension;
        var dataRevision = data.Revision;
        var dataChangenumber = data.Changenumber;
        var dataStatus = data.Status;
        var dataDocumentsummary = data.Documentsummary;
        var dataDocument = data.Document;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertDocument( sqlConnection, 
                        dataDocumentnode,
                        dataDocumentlevel,
                        dataTitle,
                        dataOwner,
                        dataFolderflag,
                        dataFilename,
                        dataFileextension,
                        dataRevision,
                        dataChangenumber,
                        dataStatus,
                        dataDocumentsummary,
                        dataDocument,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateDocument(SqlConnection sqlConnection, SqlHierarchyId documentnode,
        short? documentlevel,
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
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateDocument]";

        command.Parameters.AddHierarchyId("@documentnode", documentnode);
        command.Parameters.AddInt16("@documentlevel", documentlevel);
        command.Parameters.AddNVarChar("@title", title, 50);
        command.Parameters.AddInt32("@owner", owner);
        command.Parameters.AddBoolean("@folderflag", folderflag);
        command.Parameters.AddNVarChar("@filename", filename, 400);
        command.Parameters.AddNVarChar("@fileextension", fileextension, 8);
        command.Parameters.AddNChar("@revision", revision, 5);
        command.Parameters.AddInt32("@changenumber", changenumber);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddNVarChar("@documentsummary", documentsummary, -1);
        command.Parameters.AddBinary("@document", document, -1);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateDocument(SqlConnection sqlConnection, AdventureWorks.Production.Types.DocumentDataType data )
    {
        var dataDocumentnode = data.Documentnode;
        var dataDocumentlevel = data.Documentlevel;
        var dataTitle = data.Title;
        var dataOwner = data.Owner;
        var dataFolderflag = data.Folderflag;
        var dataFilename = data.Filename;
        var dataFileextension = data.Fileextension;
        var dataRevision = data.Revision;
        var dataChangenumber = data.Changenumber;
        var dataStatus = data.Status;
        var dataDocumentsummary = data.Documentsummary;
        var dataDocument = data.Document;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateDocument( sqlConnection, 
                        dataDocumentnode,
                        dataDocumentlevel,
                        dataTitle,
                        dataOwner,
                        dataFolderflag,
                        dataFilename,
                        dataFileextension,
                        dataRevision,
                        dataChangenumber,
                        dataStatus,
                        dataDocumentsummary,
                        dataDocument,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteDocument(SqlConnection sqlConnection, SqlHierarchyId documentnode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteDocument]";

        command.Parameters.AddHierarchyId("@documentnode", documentnode);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteDocument(SqlConnection sqlConnection, AdventureWorks.Production.Types.DocumentDataType data )
    {
        var dataDocumentnode = data.Documentnode;
        var result = DeleteDocument( sqlConnection, 
                        dataDocumentnode );

        return result;
    }

    public static bool InsertIllustration(SqlConnection sqlConnection, ref int illustrationid,
        SqlXml? diagram,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertIllustration]";

        var illustrationidParameter = command.Parameters.AddInt32("@illustrationid");
        command.Parameters.AddSqlXml("@diagram", diagram);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            illustrationid = (int)illustrationidParameter.Value;
        }
        return result;
    }

    public static bool MergeIllustration(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.IllustrationDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeIllustration]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertIllustration(SqlConnection sqlConnection, AdventureWorks.Production.Types.IllustrationDataType data )
    {
        var dataIllustrationid = data.Illustrationid;
        var dataDiagram = data.Diagram;
        var dataModifieddate = data.Modifieddate;
        var result = InsertIllustration( sqlConnection, 
                        ref dataIllustrationid,
                        dataDiagram,
                        dataModifieddate );
        data.Illustrationid = dataIllustrationid;

        return result;
    }

    public static bool UpdateIllustration(SqlConnection sqlConnection, int illustrationid,
        SqlXml? diagram,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateIllustration]";

        command.Parameters.AddInt32("@illustrationid", illustrationid);
        command.Parameters.AddSqlXml("@diagram", diagram);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateIllustration(SqlConnection sqlConnection, AdventureWorks.Production.Types.IllustrationDataType data )
    {
        var dataIllustrationid = data.Illustrationid;
        var dataDiagram = data.Diagram;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateIllustration( sqlConnection, 
                        dataIllustrationid,
                        dataDiagram,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteIllustration(SqlConnection sqlConnection, int illustrationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteIllustration]";

        command.Parameters.AddInt32("@illustrationid", illustrationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteIllustration(SqlConnection sqlConnection, AdventureWorks.Production.Types.IllustrationDataType data )
    {
        var dataIllustrationid = data.Illustrationid;
        var result = DeleteIllustration( sqlConnection, 
                        dataIllustrationid );

        return result;
    }

    public static bool InsertLocation(SqlConnection sqlConnection, ref short locationid,
        string name,
        decimal costrate,
        decimal availability,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertLocation]";

        var locationidParameter = command.Parameters.AddInt16("@locationid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDecimal("@costrate", costrate);
        command.Parameters.AddDecimal("@availability", availability);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            locationid = (short)locationidParameter.Value;
        }
        return result;
    }

    public static bool MergeLocation(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.LocationDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeLocation]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertLocation(SqlConnection sqlConnection, AdventureWorks.Production.Types.LocationDataType data )
    {
        var dataLocationid = data.Locationid;
        var dataName = data.Name;
        var dataCostrate = data.Costrate;
        var dataAvailability = data.Availability;
        var dataModifieddate = data.Modifieddate;
        var result = InsertLocation( sqlConnection, 
                        ref dataLocationid,
                        dataName,
                        dataCostrate,
                        dataAvailability,
                        dataModifieddate );
        data.Locationid = dataLocationid;

        return result;
    }

    public static bool UpdateLocation(SqlConnection sqlConnection, short locationid,
        string name,
        decimal costrate,
        decimal availability,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateLocation]";

        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDecimal("@costrate", costrate);
        command.Parameters.AddDecimal("@availability", availability);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateLocation(SqlConnection sqlConnection, AdventureWorks.Production.Types.LocationDataType data )
    {
        var dataLocationid = data.Locationid;
        var dataName = data.Name;
        var dataCostrate = data.Costrate;
        var dataAvailability = data.Availability;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateLocation( sqlConnection, 
                        dataLocationid,
                        dataName,
                        dataCostrate,
                        dataAvailability,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteLocation(SqlConnection sqlConnection, short locationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteLocation]";

        command.Parameters.AddInt16("@locationid", locationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteLocation(SqlConnection sqlConnection, AdventureWorks.Production.Types.LocationDataType data )
    {
        var dataLocationid = data.Locationid;
        var result = DeleteLocation( sqlConnection, 
                        dataLocationid );

        return result;
    }

    public static bool InsertProduct(SqlConnection sqlConnection, ref int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        string? sizeunitmeasurecode,
        string? weightunitmeasurecode,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        int? productsubcategoryid,
        int? productmodelid,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProduct]";

        var productidParameter = command.Parameters.AddInt32("@productid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@productnumber", productnumber, 25);
        command.Parameters.AddBoolean("@makeflag", makeflag);
        command.Parameters.AddBoolean("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddNVarChar("@color", color, 15);
        command.Parameters.AddInt16("@safetystocklevel", safetystocklevel);
        command.Parameters.AddInt16("@reorderpoint", reorderpoint);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddNVarChar("@size", size, 5);
        command.Parameters.AddNChar("@sizeunitmeasurecode", sizeunitmeasurecode, 3);
        command.Parameters.AddNChar("@weightunitmeasurecode", weightunitmeasurecode, 3);
        command.Parameters.AddDecimal("@weight", weight);
        command.Parameters.AddInt32("@daystomanufacture", daystomanufacture);
        command.Parameters.AddNChar("@productline", productline, 2);
        command.Parameters.AddNChar("@class", class__, 2);
        command.Parameters.AddNChar("@style", style, 2);
        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddDateTime("@sellstartdate", sellstartdate);
        command.Parameters.AddDateTime("@sellenddate", sellenddate);
        command.Parameters.AddDateTime("@discontinueddate", discontinueddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productid = (int)productidParameter.Value;
        }
        return result;
    }

    public static bool MergeProduct(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProduct]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProduct(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataName = data.Name;
        var dataProductnumber = data.Productnumber;
        var dataMakeflag = data.Makeflag;
        var dataFinishedgoodsflag = data.Finishedgoodsflag;
        var dataColor = data.Color;
        var dataSafetystocklevel = data.Safetystocklevel;
        var dataReorderpoint = data.Reorderpoint;
        var dataStandardcost = data.Standardcost;
        var dataListprice = data.Listprice;
        var dataSize = data.Size;
        var dataSizeunitmeasurecode = data.Sizeunitmeasurecode;
        var dataWeightunitmeasurecode = data.Weightunitmeasurecode;
        var dataWeight = data.Weight;
        var dataDaystomanufacture = data.Daystomanufacture;
        var dataProductline = data.Productline;
        var dataClass = data.Class;
        var dataStyle = data.Style;
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductmodelid = data.Productmodelid;
        var dataSellstartdate = data.Sellstartdate;
        var dataSellenddate = data.Sellenddate;
        var dataDiscontinueddate = data.Discontinueddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProduct( sqlConnection, 
                        ref dataProductid,
                        dataName,
                        dataProductnumber,
                        dataMakeflag,
                        dataFinishedgoodsflag,
                        dataColor,
                        dataSafetystocklevel,
                        dataReorderpoint,
                        dataStandardcost,
                        dataListprice,
                        dataSize,
                        dataSizeunitmeasurecode,
                        dataWeightunitmeasurecode,
                        dataWeight,
                        dataDaystomanufacture,
                        dataProductline,
                        dataClass,
                        dataStyle,
                        dataProductsubcategoryid,
                        dataProductmodelid,
                        dataSellstartdate,
                        dataSellenddate,
                        dataDiscontinueddate,
                        dataRowguid,
                        dataModifieddate );
        data.Productid = dataProductid;

        return result;
    }

    public static bool UpdateProduct(SqlConnection sqlConnection, int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        string? sizeunitmeasurecode,
        string? weightunitmeasurecode,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        int? productsubcategoryid,
        int? productmodelid,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProduct]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@productnumber", productnumber, 25);
        command.Parameters.AddBoolean("@makeflag", makeflag);
        command.Parameters.AddBoolean("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddNVarChar("@color", color, 15);
        command.Parameters.AddInt16("@safetystocklevel", safetystocklevel);
        command.Parameters.AddInt16("@reorderpoint", reorderpoint);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddNVarChar("@size", size, 5);
        command.Parameters.AddNChar("@sizeunitmeasurecode", sizeunitmeasurecode, 3);
        command.Parameters.AddNChar("@weightunitmeasurecode", weightunitmeasurecode, 3);
        command.Parameters.AddDecimal("@weight", weight);
        command.Parameters.AddInt32("@daystomanufacture", daystomanufacture);
        command.Parameters.AddNChar("@productline", productline, 2);
        command.Parameters.AddNChar("@class", class__, 2);
        command.Parameters.AddNChar("@style", style, 2);
        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddDateTime("@sellstartdate", sellstartdate);
        command.Parameters.AddDateTime("@sellenddate", sellenddate);
        command.Parameters.AddDateTime("@discontinueddate", discontinueddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProduct(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataName = data.Name;
        var dataProductnumber = data.Productnumber;
        var dataMakeflag = data.Makeflag;
        var dataFinishedgoodsflag = data.Finishedgoodsflag;
        var dataColor = data.Color;
        var dataSafetystocklevel = data.Safetystocklevel;
        var dataReorderpoint = data.Reorderpoint;
        var dataStandardcost = data.Standardcost;
        var dataListprice = data.Listprice;
        var dataSize = data.Size;
        var dataSizeunitmeasurecode = data.Sizeunitmeasurecode;
        var dataWeightunitmeasurecode = data.Weightunitmeasurecode;
        var dataWeight = data.Weight;
        var dataDaystomanufacture = data.Daystomanufacture;
        var dataProductline = data.Productline;
        var dataClass = data.Class;
        var dataStyle = data.Style;
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductmodelid = data.Productmodelid;
        var dataSellstartdate = data.Sellstartdate;
        var dataSellenddate = data.Sellenddate;
        var dataDiscontinueddate = data.Discontinueddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProduct( sqlConnection, 
                        dataProductid,
                        dataName,
                        dataProductnumber,
                        dataMakeflag,
                        dataFinishedgoodsflag,
                        dataColor,
                        dataSafetystocklevel,
                        dataReorderpoint,
                        dataStandardcost,
                        dataListprice,
                        dataSize,
                        dataSizeunitmeasurecode,
                        dataWeightunitmeasurecode,
                        dataWeight,
                        dataDaystomanufacture,
                        dataProductline,
                        dataClass,
                        dataStyle,
                        dataProductsubcategoryid,
                        dataProductmodelid,
                        dataSellstartdate,
                        dataSellenddate,
                        dataDiscontinueddate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProduct(SqlConnection sqlConnection, int productid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProduct]";

        command.Parameters.AddInt32("@productid", productid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProduct(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var result = DeleteProduct( sqlConnection, 
                        dataProductid );

        return result;
    }

    public static bool Insert1Product(SqlConnection sqlConnection, ref int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Insert1Product]";

        var productidParameter = command.Parameters.AddInt32("@productid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@productnumber", productnumber, 25);
        command.Parameters.AddBoolean("@makeflag", makeflag);
        command.Parameters.AddBoolean("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddNVarChar("@color", color, 15);
        command.Parameters.AddInt16("@safetystocklevel", safetystocklevel);
        command.Parameters.AddInt16("@reorderpoint", reorderpoint);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddNVarChar("@size", size, 5);
        command.Parameters.AddDecimal("@weight", weight);
        command.Parameters.AddInt32("@daystomanufacture", daystomanufacture);
        command.Parameters.AddNChar("@productline", productline, 2);
        command.Parameters.AddNChar("@class", class__, 2);
        command.Parameters.AddNChar("@style", style, 2);
        command.Parameters.AddDateTime("@sellstartdate", sellstartdate);
        command.Parameters.AddDateTime("@sellenddate", sellenddate);
        command.Parameters.AddDateTime("@discontinueddate", discontinueddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productid = (int)productidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Product(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataName = data.Name;
        var dataProductnumber = data.Productnumber;
        var dataMakeflag = data.Makeflag;
        var dataFinishedgoodsflag = data.Finishedgoodsflag;
        var dataColor = data.Color;
        var dataSafetystocklevel = data.Safetystocklevel;
        var dataReorderpoint = data.Reorderpoint;
        var dataStandardcost = data.Standardcost;
        var dataListprice = data.Listprice;
        var dataSize = data.Size;
        var dataWeight = data.Weight;
        var dataDaystomanufacture = data.Daystomanufacture;
        var dataProductline = data.Productline;
        var dataClass = data.Class;
        var dataStyle = data.Style;
        var dataSellstartdate = data.Sellstartdate;
        var dataSellenddate = data.Sellenddate;
        var dataDiscontinueddate = data.Discontinueddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Product( sqlConnection, 
                        ref dataProductid,
                        dataName,
                        dataProductnumber,
                        dataMakeflag,
                        dataFinishedgoodsflag,
                        dataColor,
                        dataSafetystocklevel,
                        dataReorderpoint,
                        dataStandardcost,
                        dataListprice,
                        dataSize,
                        dataWeight,
                        dataDaystomanufacture,
                        dataProductline,
                        dataClass,
                        dataStyle,
                        dataSellstartdate,
                        dataSellenddate,
                        dataDiscontinueddate,
                        dataRowguid,
                        dataModifieddate );
        data.Productid = dataProductid;

        return result;
    }

    public static bool Update1Product(SqlConnection sqlConnection, int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update1Product]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@productnumber", productnumber, 25);
        command.Parameters.AddBoolean("@makeflag", makeflag);
        command.Parameters.AddBoolean("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddNVarChar("@color", color, 15);
        command.Parameters.AddInt16("@safetystocklevel", safetystocklevel);
        command.Parameters.AddInt16("@reorderpoint", reorderpoint);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddNVarChar("@size", size, 5);
        command.Parameters.AddDecimal("@weight", weight);
        command.Parameters.AddInt32("@daystomanufacture", daystomanufacture);
        command.Parameters.AddNChar("@productline", productline, 2);
        command.Parameters.AddNChar("@class", class__, 2);
        command.Parameters.AddNChar("@style", style, 2);
        command.Parameters.AddDateTime("@sellstartdate", sellstartdate);
        command.Parameters.AddDateTime("@sellenddate", sellenddate);
        command.Parameters.AddDateTime("@discontinueddate", discontinueddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Product(SqlConnection sqlConnection, int productid,
        string? sizeunitmeasurecode,
        string? weightunitmeasurecode,
        int? productsubcategoryid,
        int? productmodelid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update2Product]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNChar("@sizeunitmeasurecode", sizeunitmeasurecode, 3);
        command.Parameters.AddNChar("@weightunitmeasurecode", weightunitmeasurecode, 3);
        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddInt32("@productmodelid", productmodelid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Product(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataName = data.Name;
        var dataProductnumber = data.Productnumber;
        var dataMakeflag = data.Makeflag;
        var dataFinishedgoodsflag = data.Finishedgoodsflag;
        var dataColor = data.Color;
        var dataSafetystocklevel = data.Safetystocklevel;
        var dataReorderpoint = data.Reorderpoint;
        var dataStandardcost = data.Standardcost;
        var dataListprice = data.Listprice;
        var dataSize = data.Size;
        var dataWeight = data.Weight;
        var dataDaystomanufacture = data.Daystomanufacture;
        var dataProductline = data.Productline;
        var dataClass = data.Class;
        var dataStyle = data.Style;
        var dataSellstartdate = data.Sellstartdate;
        var dataSellenddate = data.Sellenddate;
        var dataDiscontinueddate = data.Discontinueddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Product( sqlConnection, 
                        dataProductid,
                        dataName,
                        dataProductnumber,
                        dataMakeflag,
                        dataFinishedgoodsflag,
                        dataColor,
                        dataSafetystocklevel,
                        dataReorderpoint,
                        dataStandardcost,
                        dataListprice,
                        dataSize,
                        dataWeight,
                        dataDaystomanufacture,
                        dataProductline,
                        dataClass,
                        dataStyle,
                        dataSellstartdate,
                        dataSellenddate,
                        dataDiscontinueddate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Product(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataSizeunitmeasurecode = data.Sizeunitmeasurecode;
        var dataWeightunitmeasurecode = data.Weightunitmeasurecode;
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductmodelid = data.Productmodelid;
        var result = Update2Product( sqlConnection, 
                        dataProductid,
                        dataSizeunitmeasurecode,
                        dataWeightunitmeasurecode,
                        dataProductsubcategoryid,
                        dataProductmodelid );

        return result;
    }

    public static bool InsertProductcategory(SqlConnection sqlConnection, ref int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductCategory]";

        var productcategoryidParameter = command.Parameters.AddInt32("@productcategoryid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productcategoryid = (int)productcategoryidParameter.Value;
        }
        return result;
    }

    public static bool MergeProductcategory(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductcategoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductCategory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductcategory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductcategoryDataType data )
    {
        var dataProductcategoryid = data.Productcategoryid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductcategory( sqlConnection, 
                        ref dataProductcategoryid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );
        data.Productcategoryid = dataProductcategoryid;

        return result;
    }

    public static bool UpdateProductcategory(SqlConnection sqlConnection, int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductCategory]";

        command.Parameters.AddInt32("@productcategoryid", productcategoryid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductcategory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductcategoryDataType data )
    {
        var dataProductcategoryid = data.Productcategoryid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductcategory( sqlConnection, 
                        dataProductcategoryid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductcategory(SqlConnection sqlConnection, int productcategoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductCategory]";

        command.Parameters.AddInt32("@productcategoryid", productcategoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductcategory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductcategoryDataType data )
    {
        var dataProductcategoryid = data.Productcategoryid;
        var result = DeleteProductcategory( sqlConnection, 
                        dataProductcategoryid );

        return result;
    }

    public static bool InsertProductcosthistory(SqlConnection sqlConnection, int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal standardcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductCostHistory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeProductcosthistory(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductcosthistoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductCostHistory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductcosthistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductcosthistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataStandardcost = data.Standardcost;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductcosthistory( sqlConnection, 
                        dataProductid,
                        dataStartdate,
                        dataEnddate,
                        dataStandardcost,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductcosthistory(SqlConnection sqlConnection, int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal standardcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductCostHistory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductcosthistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductcosthistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataStandardcost = data.Standardcost;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductcosthistory( sqlConnection, 
                        dataProductid,
                        dataStartdate,
                        dataEnddate,
                        dataStandardcost,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductcosthistory(SqlConnection sqlConnection, int productid,
        DateTime startdate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductCostHistory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductcosthistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductcosthistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var result = DeleteProductcosthistory( sqlConnection, 
                        dataProductid,
                        dataStartdate );

        return result;
    }

    public static bool InsertProductdescription(SqlConnection sqlConnection, ref int productdescriptionid,
        string description,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductDescription]";

        var productdescriptionidParameter = command.Parameters.AddInt32("@productdescriptionid");
        command.Parameters.AddNVarChar("@description", description, 400);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productdescriptionid = (int)productdescriptionidParameter.Value;
        }
        return result;
    }

    public static bool MergeProductdescription(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductdescriptionDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductDescription]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductdescription(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductdescriptionDataType data )
    {
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataDescription = data.Description;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductdescription( sqlConnection, 
                        ref dataProductdescriptionid,
                        dataDescription,
                        dataRowguid,
                        dataModifieddate );
        data.Productdescriptionid = dataProductdescriptionid;

        return result;
    }

    public static bool UpdateProductdescription(SqlConnection sqlConnection, int productdescriptionid,
        string description,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductDescription]";

        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);
        command.Parameters.AddNVarChar("@description", description, 400);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductdescription(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductdescriptionDataType data )
    {
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataDescription = data.Description;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductdescription( sqlConnection, 
                        dataProductdescriptionid,
                        dataDescription,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductdescription(SqlConnection sqlConnection, int productdescriptionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductDescription]";

        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductdescription(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductdescriptionDataType data )
    {
        var dataProductdescriptionid = data.Productdescriptionid;
        var result = DeleteProductdescription( sqlConnection, 
                        dataProductdescriptionid );

        return result;
    }

    public static bool InsertProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductDocument]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddHierarchyId("@documentnode", documentnode);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeProductdocument(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductdocumentDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductDocument]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductdocument(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductdocumentDataType data )
    {
        var dataProductid = data.Productid;
        var dataDocumentnode = data.Documentnode;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductdocument( sqlConnection, 
                        dataProductid,
                        dataDocumentnode,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductDocument]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddHierarchyId("@documentnode", documentnode);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductdocument(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductdocumentDataType data )
    {
        var dataProductid = data.Productid;
        var dataDocumentnode = data.Documentnode;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductdocument( sqlConnection, 
                        dataProductid,
                        dataDocumentnode,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductDocument]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddHierarchyId("@documentnode", documentnode);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductdocument(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductdocumentDataType data )
    {
        var dataProductid = data.Productid;
        var dataDocumentnode = data.Documentnode;
        var result = DeleteProductdocument( sqlConnection, 
                        dataProductid,
                        dataDocumentnode );

        return result;
    }

    public static bool InsertProductinventory(SqlConnection sqlConnection, int productid,
        short locationid,
        string shelf,
        byte bin,
        short quantity,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductInventory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddNVarChar("@shelf", shelf, 10);
        command.Parameters.AddByte("@bin", bin);
        command.Parameters.AddInt16("@quantity", quantity);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeProductinventory(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductinventoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductInventory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductinventory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductinventoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataLocationid = data.Locationid;
        var dataShelf = data.Shelf;
        var dataBin = data.Bin;
        var dataQuantity = data.Quantity;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductinventory( sqlConnection, 
                        dataProductid,
                        dataLocationid,
                        dataShelf,
                        dataBin,
                        dataQuantity,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductinventory(SqlConnection sqlConnection, int productid,
        short locationid,
        string shelf,
        byte bin,
        short quantity,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductInventory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddNVarChar("@shelf", shelf, 10);
        command.Parameters.AddByte("@bin", bin);
        command.Parameters.AddInt16("@quantity", quantity);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductinventory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductinventoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataLocationid = data.Locationid;
        var dataShelf = data.Shelf;
        var dataBin = data.Bin;
        var dataQuantity = data.Quantity;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductinventory( sqlConnection, 
                        dataProductid,
                        dataLocationid,
                        dataShelf,
                        dataBin,
                        dataQuantity,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductinventory(SqlConnection sqlConnection, int productid,
        short locationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductInventory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@locationid", locationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductinventory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductinventoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataLocationid = data.Locationid;
        var result = DeleteProductinventory( sqlConnection, 
                        dataProductid,
                        dataLocationid );

        return result;
    }

    public static bool InsertProductlistpricehistory(SqlConnection sqlConnection, int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal listprice,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductListPriceHistory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeProductlistpricehistory(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductlistpricehistoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductListPriceHistory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductlistpricehistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductlistpricehistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataListprice = data.Listprice;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductlistpricehistory( sqlConnection, 
                        dataProductid,
                        dataStartdate,
                        dataEnddate,
                        dataListprice,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductlistpricehistory(SqlConnection sqlConnection, int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal listprice,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductListPriceHistory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductlistpricehistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductlistpricehistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataListprice = data.Listprice;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductlistpricehistory( sqlConnection, 
                        dataProductid,
                        dataStartdate,
                        dataEnddate,
                        dataListprice,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductlistpricehistory(SqlConnection sqlConnection, int productid,
        DateTime startdate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductListPriceHistory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductlistpricehistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductlistpricehistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var result = DeleteProductlistpricehistory( sqlConnection, 
                        dataProductid,
                        dataStartdate );

        return result;
    }

    public static bool InsertProductmodel(SqlConnection sqlConnection, ref int productmodelid,
        string name,
        SqlXml? catalogdescription,
        SqlXml? instructions,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModel]";

        var productmodelidParameter = command.Parameters.AddInt32("@productmodelid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddSqlXml("@catalogdescription", catalogdescription);
        command.Parameters.AddSqlXml("@instructions", instructions);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productmodelid = (int)productmodelidParameter.Value;
        }
        return result;
    }

    public static bool MergeProductmodel(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductmodelDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductModel]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductmodel(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataName = data.Name;
        var dataCatalogdescription = data.Catalogdescription;
        var dataInstructions = data.Instructions;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductmodel( sqlConnection, 
                        ref dataProductmodelid,
                        dataName,
                        dataCatalogdescription,
                        dataInstructions,
                        dataRowguid,
                        dataModifieddate );
        data.Productmodelid = dataProductmodelid;

        return result;
    }

    public static bool UpdateProductmodel(SqlConnection sqlConnection, int productmodelid,
        string name,
        SqlXml? catalogdescription,
        SqlXml? instructions,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductModel]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddSqlXml("@catalogdescription", catalogdescription);
        command.Parameters.AddSqlXml("@instructions", instructions);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductmodel(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataName = data.Name;
        var dataCatalogdescription = data.Catalogdescription;
        var dataInstructions = data.Instructions;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductmodel( sqlConnection, 
                        dataProductmodelid,
                        dataName,
                        dataCatalogdescription,
                        dataInstructions,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductmodel(SqlConnection sqlConnection, int productmodelid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModel]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductmodel(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var result = DeleteProductmodel( sqlConnection, 
                        dataProductmodelid );

        return result;
    }

    public static bool InsertProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModelIllustration]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@illustrationid", illustrationid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeProductmodelillustration(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductmodelillustrationDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductModelIllustration]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductmodelillustration(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelillustrationDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataIllustrationid = data.Illustrationid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductmodelillustration( sqlConnection, 
                        dataProductmodelid,
                        dataIllustrationid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductModelIllustration]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@illustrationid", illustrationid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductmodelillustration(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelillustrationDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataIllustrationid = data.Illustrationid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductmodelillustration( sqlConnection, 
                        dataProductmodelid,
                        dataIllustrationid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModelIllustration]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@illustrationid", illustrationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductmodelillustration(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelillustrationDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataIllustrationid = data.Illustrationid;
        var result = DeleteProductmodelillustration( sqlConnection, 
                        dataProductmodelid,
                        dataIllustrationid );

        return result;
    }

    public static bool InsertProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModelProductDescriptionCulture]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);
        command.Parameters.AddNChar("@cultureid", cultureid, 6);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeProductmodelproductdescriptionculture(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductmodelproductdescriptioncultureDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductModelProductDescriptionCulture]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductmodelproductdescriptionculture(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelproductdescriptioncultureDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataCultureid = data.Cultureid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductmodelproductdescriptionculture( sqlConnection, 
                        dataProductmodelid,
                        dataProductdescriptionid,
                        dataCultureid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductModelProductDescriptionCulture]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);
        command.Parameters.AddNChar("@cultureid", cultureid, 6);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductmodelproductdescriptionculture(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelproductdescriptioncultureDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataCultureid = data.Cultureid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductmodelproductdescriptionculture( sqlConnection, 
                        dataProductmodelid,
                        dataProductdescriptionid,
                        dataCultureid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModelProductDescriptionCulture]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);
        command.Parameters.AddNChar("@cultureid", cultureid, 6);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductmodelproductdescriptionculture(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductmodelproductdescriptioncultureDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataCultureid = data.Cultureid;
        var result = DeleteProductmodelproductdescriptionculture( sqlConnection, 
                        dataProductmodelid,
                        dataProductdescriptionid,
                        dataCultureid );

        return result;
    }

    public static bool InsertProductphoto(SqlConnection sqlConnection, ref int productphotoid,
        byte[]? thumbnailphoto,
        string? thumbnailphotofilename,
        byte[]? largephoto,
        string? largephotofilename,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductPhoto]";

        var productphotoidParameter = command.Parameters.AddInt32("@productphotoid");
        command.Parameters.AddBinary("@thumbnailphoto", thumbnailphoto, -1);
        command.Parameters.AddNVarChar("@thumbnailphotofilename", thumbnailphotofilename, 50);
        command.Parameters.AddBinary("@largephoto", largephoto, -1);
        command.Parameters.AddNVarChar("@largephotofilename", largephotofilename, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productphotoid = (int)productphotoidParameter.Value;
        }
        return result;
    }

    public static bool MergeProductphoto(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductphotoDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductPhoto]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductphoto(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductphotoDataType data )
    {
        var dataProductphotoid = data.Productphotoid;
        var dataThumbnailphoto = data.Thumbnailphoto;
        var dataThumbnailphotofilename = data.Thumbnailphotofilename;
        var dataLargephoto = data.Largephoto;
        var dataLargephotofilename = data.Largephotofilename;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductphoto( sqlConnection, 
                        ref dataProductphotoid,
                        dataThumbnailphoto,
                        dataThumbnailphotofilename,
                        dataLargephoto,
                        dataLargephotofilename,
                        dataModifieddate );
        data.Productphotoid = dataProductphotoid;

        return result;
    }

    public static bool UpdateProductphoto(SqlConnection sqlConnection, int productphotoid,
        byte[]? thumbnailphoto,
        string? thumbnailphotofilename,
        byte[]? largephoto,
        string? largephotofilename,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductPhoto]";

        command.Parameters.AddInt32("@productphotoid", productphotoid);
        command.Parameters.AddBinary("@thumbnailphoto", thumbnailphoto, -1);
        command.Parameters.AddNVarChar("@thumbnailphotofilename", thumbnailphotofilename, 50);
        command.Parameters.AddBinary("@largephoto", largephoto, -1);
        command.Parameters.AddNVarChar("@largephotofilename", largephotofilename, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductphoto(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductphotoDataType data )
    {
        var dataProductphotoid = data.Productphotoid;
        var dataThumbnailphoto = data.Thumbnailphoto;
        var dataThumbnailphotofilename = data.Thumbnailphotofilename;
        var dataLargephoto = data.Largephoto;
        var dataLargephotofilename = data.Largephotofilename;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductphoto( sqlConnection, 
                        dataProductphotoid,
                        dataThumbnailphoto,
                        dataThumbnailphotofilename,
                        dataLargephoto,
                        dataLargephotofilename,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductphoto(SqlConnection sqlConnection, int productphotoid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductPhoto]";

        command.Parameters.AddInt32("@productphotoid", productphotoid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductphoto(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductphotoDataType data )
    {
        var dataProductphotoid = data.Productphotoid;
        var result = DeleteProductphoto( sqlConnection, 
                        dataProductphotoid );

        return result;
    }

    public static bool InsertProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid,
        bool primary,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductProductPhoto]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@productphotoid", productphotoid);
        command.Parameters.AddBoolean("@primary", primary);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeProductproductphoto(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductproductphotoDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductProductPhoto]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductproductphoto(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductproductphotoDataType data )
    {
        var dataProductid = data.Productid;
        var dataProductphotoid = data.Productphotoid;
        var dataPrimary = data.Primary;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductproductphoto( sqlConnection, 
                        dataProductid,
                        dataProductphotoid,
                        dataPrimary,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid,
        bool primary,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductProductPhoto]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@productphotoid", productphotoid);
        command.Parameters.AddBoolean("@primary", primary);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductproductphoto(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductproductphotoDataType data )
    {
        var dataProductid = data.Productid;
        var dataProductphotoid = data.Productphotoid;
        var dataPrimary = data.Primary;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductproductphoto( sqlConnection, 
                        dataProductid,
                        dataProductphotoid,
                        dataPrimary,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductProductPhoto]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@productphotoid", productphotoid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductproductphoto(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductproductphotoDataType data )
    {
        var dataProductid = data.Productid;
        var dataProductphotoid = data.Productphotoid;
        var result = DeleteProductproductphoto( sqlConnection, 
                        dataProductid,
                        dataProductphotoid );

        return result;
    }

    public static bool InsertProductreview(SqlConnection sqlConnection, ref int productreviewid,
        int productid,
        string reviewername,
        DateTime reviewdate,
        string emailaddress,
        int rating,
        string? comments,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductReview]";

        var productreviewidParameter = command.Parameters.AddInt32("@productreviewid");
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNVarChar("@reviewername", reviewername, 50);
        command.Parameters.AddDateTime("@reviewdate", reviewdate);
        command.Parameters.AddNVarChar("@emailaddress", emailaddress, 50);
        command.Parameters.AddInt32("@rating", rating);
        command.Parameters.AddNVarChar("@comments", comments, 3850);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productreviewid = (int)productreviewidParameter.Value;
        }
        return result;
    }

    public static bool MergeProductreview(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductreviewDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductReview]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductreview(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductreviewDataType data )
    {
        var dataProductreviewid = data.Productreviewid;
        var dataProductid = data.Productid;
        var dataReviewername = data.Reviewername;
        var dataReviewdate = data.Reviewdate;
        var dataEmailaddress = data.Emailaddress;
        var dataRating = data.Rating;
        var dataComments = data.Comments;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductreview( sqlConnection, 
                        ref dataProductreviewid,
                        dataProductid,
                        dataReviewername,
                        dataReviewdate,
                        dataEmailaddress,
                        dataRating,
                        dataComments,
                        dataModifieddate );
        data.Productreviewid = dataProductreviewid;

        return result;
    }

    public static bool UpdateProductreview(SqlConnection sqlConnection, int productreviewid,
        int productid,
        string reviewername,
        DateTime reviewdate,
        string emailaddress,
        int rating,
        string? comments,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductReview]";

        command.Parameters.AddInt32("@productreviewid", productreviewid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNVarChar("@reviewername", reviewername, 50);
        command.Parameters.AddDateTime("@reviewdate", reviewdate);
        command.Parameters.AddNVarChar("@emailaddress", emailaddress, 50);
        command.Parameters.AddInt32("@rating", rating);
        command.Parameters.AddNVarChar("@comments", comments, 3850);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductreview(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductreviewDataType data )
    {
        var dataProductreviewid = data.Productreviewid;
        var dataProductid = data.Productid;
        var dataReviewername = data.Reviewername;
        var dataReviewdate = data.Reviewdate;
        var dataEmailaddress = data.Emailaddress;
        var dataRating = data.Rating;
        var dataComments = data.Comments;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductreview( sqlConnection, 
                        dataProductreviewid,
                        dataProductid,
                        dataReviewername,
                        dataReviewdate,
                        dataEmailaddress,
                        dataRating,
                        dataComments,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductreview(SqlConnection sqlConnection, int productreviewid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductReview]";

        command.Parameters.AddInt32("@productreviewid", productreviewid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductreview(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductreviewDataType data )
    {
        var dataProductreviewid = data.Productreviewid;
        var result = DeleteProductreview( sqlConnection, 
                        dataProductreviewid );

        return result;
    }

    public static bool InsertProductsubcategory(SqlConnection sqlConnection, ref int productsubcategoryid,
        int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductSubcategory]";

        var productsubcategoryidParameter = command.Parameters.AddInt32("@productsubcategoryid");
        command.Parameters.AddInt32("@productcategoryid", productcategoryid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productsubcategoryid = (int)productsubcategoryidParameter.Value;
        }
        return result;
    }

    public static bool MergeProductsubcategory(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ProductsubcategoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeProductSubcategory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertProductsubcategory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductsubcategoryDataType data )
    {
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductcategoryid = data.Productcategoryid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductsubcategory( sqlConnection, 
                        ref dataProductsubcategoryid,
                        dataProductcategoryid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );
        data.Productsubcategoryid = dataProductsubcategoryid;

        return result;
    }

    public static bool UpdateProductsubcategory(SqlConnection sqlConnection, int productsubcategoryid,
        int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductSubcategory]";

        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddInt32("@productcategoryid", productcategoryid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductsubcategory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductsubcategoryDataType data )
    {
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductcategoryid = data.Productcategoryid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductsubcategory( sqlConnection, 
                        dataProductsubcategoryid,
                        dataProductcategoryid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductsubcategory(SqlConnection sqlConnection, int productsubcategoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductSubcategory]";

        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductsubcategory(SqlConnection sqlConnection, AdventureWorks.Production.Types.ProductsubcategoryDataType data )
    {
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var result = DeleteProductsubcategory( sqlConnection, 
                        dataProductsubcategoryid );

        return result;
    }

    public static bool InsertScrapreason(SqlConnection sqlConnection, ref short scrapreasonid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertScrapReason]";

        var scrapreasonidParameter = command.Parameters.AddInt16("@scrapreasonid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            scrapreasonid = (short)scrapreasonidParameter.Value;
        }
        return result;
    }

    public static bool MergeScrapreason(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.ScrapreasonDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeScrapReason]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertScrapreason(SqlConnection sqlConnection, AdventureWorks.Production.Types.ScrapreasonDataType data )
    {
        var dataScrapreasonid = data.Scrapreasonid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertScrapreason( sqlConnection, 
                        ref dataScrapreasonid,
                        dataName,
                        dataModifieddate );
        data.Scrapreasonid = dataScrapreasonid;

        return result;
    }

    public static bool UpdateScrapreason(SqlConnection sqlConnection, short scrapreasonid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateScrapReason]";

        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateScrapreason(SqlConnection sqlConnection, AdventureWorks.Production.Types.ScrapreasonDataType data )
    {
        var dataScrapreasonid = data.Scrapreasonid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateScrapreason( sqlConnection, 
                        dataScrapreasonid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteScrapreason(SqlConnection sqlConnection, short scrapreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteScrapReason]";

        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteScrapreason(SqlConnection sqlConnection, AdventureWorks.Production.Types.ScrapreasonDataType data )
    {
        var dataScrapreasonid = data.Scrapreasonid;
        var result = DeleteScrapreason( sqlConnection, 
                        dataScrapreasonid );

        return result;
    }

    public static bool InsertTransactionhistory(SqlConnection sqlConnection, ref int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertTransactionHistory]";

        var transactionidParameter = command.Parameters.AddInt32("@transactionid");
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@referenceorderid", referenceorderid);
        command.Parameters.AddInt32("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddDateTime("@transactiondate", transactiondate);
        command.Parameters.AddNChar("@transactiontype", transactiontype, 1);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            transactionid = (int)transactionidParameter.Value;
        }
        return result;
    }

    public static bool MergeTransactionhistory(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.TransactionhistoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeTransactionHistory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertTransactionhistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.TransactionhistoryDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var dataProductid = data.Productid;
        var dataReferenceorderid = data.Referenceorderid;
        var dataReferenceorderlineid = data.Referenceorderlineid;
        var dataTransactiondate = data.Transactiondate;
        var dataTransactiontype = data.Transactiontype;
        var dataQuantity = data.Quantity;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = InsertTransactionhistory( sqlConnection, 
                        ref dataTransactionid,
                        dataProductid,
                        dataReferenceorderid,
                        dataReferenceorderlineid,
                        dataTransactiondate,
                        dataTransactiontype,
                        dataQuantity,
                        dataActualcost,
                        dataModifieddate );
        data.Transactionid = dataTransactionid;

        return result;
    }

    public static bool UpdateTransactionhistory(SqlConnection sqlConnection, int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateTransactionHistory]";

        command.Parameters.AddInt32("@transactionid", transactionid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@referenceorderid", referenceorderid);
        command.Parameters.AddInt32("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddDateTime("@transactiondate", transactiondate);
        command.Parameters.AddNChar("@transactiontype", transactiontype, 1);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateTransactionhistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.TransactionhistoryDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var dataProductid = data.Productid;
        var dataReferenceorderid = data.Referenceorderid;
        var dataReferenceorderlineid = data.Referenceorderlineid;
        var dataTransactiondate = data.Transactiondate;
        var dataTransactiontype = data.Transactiontype;
        var dataQuantity = data.Quantity;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateTransactionhistory( sqlConnection, 
                        dataTransactionid,
                        dataProductid,
                        dataReferenceorderid,
                        dataReferenceorderlineid,
                        dataTransactiondate,
                        dataTransactiontype,
                        dataQuantity,
                        dataActualcost,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteTransactionhistory(SqlConnection sqlConnection, int transactionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteTransactionHistory]";

        command.Parameters.AddInt32("@transactionid", transactionid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteTransactionhistory(SqlConnection sqlConnection, AdventureWorks.Production.Types.TransactionhistoryDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var result = DeleteTransactionhistory( sqlConnection, 
                        dataTransactionid );

        return result;
    }

    public static bool InsertTransactionhistoryarchive(SqlConnection sqlConnection, int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertTransactionHistoryArchive]";

        command.Parameters.AddInt32("@transactionid", transactionid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@referenceorderid", referenceorderid);
        command.Parameters.AddInt32("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddDateTime("@transactiondate", transactiondate);
        command.Parameters.AddNChar("@transactiontype", transactiontype, 1);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeTransactionhistoryarchive(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.TransactionhistoryarchiveDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeTransactionHistoryArchive]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertTransactionhistoryarchive(SqlConnection sqlConnection, AdventureWorks.Production.Types.TransactionhistoryarchiveDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var dataProductid = data.Productid;
        var dataReferenceorderid = data.Referenceorderid;
        var dataReferenceorderlineid = data.Referenceorderlineid;
        var dataTransactiondate = data.Transactiondate;
        var dataTransactiontype = data.Transactiontype;
        var dataQuantity = data.Quantity;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = InsertTransactionhistoryarchive( sqlConnection, 
                        dataTransactionid,
                        dataProductid,
                        dataReferenceorderid,
                        dataReferenceorderlineid,
                        dataTransactiondate,
                        dataTransactiontype,
                        dataQuantity,
                        dataActualcost,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateTransactionhistoryarchive(SqlConnection sqlConnection, int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateTransactionHistoryArchive]";

        command.Parameters.AddInt32("@transactionid", transactionid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@referenceorderid", referenceorderid);
        command.Parameters.AddInt32("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddDateTime("@transactiondate", transactiondate);
        command.Parameters.AddNChar("@transactiontype", transactiontype, 1);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateTransactionhistoryarchive(SqlConnection sqlConnection, AdventureWorks.Production.Types.TransactionhistoryarchiveDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var dataProductid = data.Productid;
        var dataReferenceorderid = data.Referenceorderid;
        var dataReferenceorderlineid = data.Referenceorderlineid;
        var dataTransactiondate = data.Transactiondate;
        var dataTransactiontype = data.Transactiontype;
        var dataQuantity = data.Quantity;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateTransactionhistoryarchive( sqlConnection, 
                        dataTransactionid,
                        dataProductid,
                        dataReferenceorderid,
                        dataReferenceorderlineid,
                        dataTransactiondate,
                        dataTransactiontype,
                        dataQuantity,
                        dataActualcost,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteTransactionhistoryarchive(SqlConnection sqlConnection, int transactionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteTransactionHistoryArchive]";

        command.Parameters.AddInt32("@transactionid", transactionid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteTransactionhistoryarchive(SqlConnection sqlConnection, AdventureWorks.Production.Types.TransactionhistoryarchiveDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var result = DeleteTransactionhistoryarchive( sqlConnection, 
                        dataTransactionid );

        return result;
    }

    public static bool InsertUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertUnitMeasure]";

        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeUnitmeasure(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.UnitmeasureDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeUnitMeasure]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertUnitmeasure(SqlConnection sqlConnection, AdventureWorks.Production.Types.UnitmeasureDataType data )
    {
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertUnitmeasure( sqlConnection, 
                        dataUnitmeasurecode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateUnitMeasure]";

        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateUnitmeasure(SqlConnection sqlConnection, AdventureWorks.Production.Types.UnitmeasureDataType data )
    {
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateUnitmeasure( sqlConnection, 
                        dataUnitmeasurecode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteUnitMeasure]";

        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteUnitmeasure(SqlConnection sqlConnection, AdventureWorks.Production.Types.UnitmeasureDataType data )
    {
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var result = DeleteUnitmeasure( sqlConnection, 
                        dataUnitmeasurecode );

        return result;
    }

    public static bool InsertWorkorder(SqlConnection sqlConnection, ref int workorderid,
        int productid,
        int orderqty,
        int stockedqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        short? scrapreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertWorkOrder]";

        var workorderidParameter = command.Parameters.AddInt32("@workorderid");
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@orderqty", orderqty);
        command.Parameters.AddInt32("@stockedqty", stockedqty);
        command.Parameters.AddInt16("@scrappedqty", scrappedqty);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            workorderid = (int)workorderidParameter.Value;
        }
        return result;
    }

    public static bool MergeWorkorder(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.WorkorderDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeWorkOrder]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertWorkorder(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOrderqty = data.Orderqty;
        var dataStockedqty = data.Stockedqty;
        var dataScrappedqty = data.Scrappedqty;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataDuedate = data.Duedate;
        var dataScrapreasonid = data.Scrapreasonid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertWorkorder( sqlConnection, 
                        ref dataWorkorderid,
                        dataProductid,
                        dataOrderqty,
                        dataStockedqty,
                        dataScrappedqty,
                        dataStartdate,
                        dataEnddate,
                        dataDuedate,
                        dataScrapreasonid,
                        dataModifieddate );
        data.Workorderid = dataWorkorderid;

        return result;
    }

    public static bool UpdateWorkorder(SqlConnection sqlConnection, int workorderid,
        int productid,
        int orderqty,
        int stockedqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        short? scrapreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateWorkOrder]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@orderqty", orderqty);
        command.Parameters.AddInt32("@stockedqty", stockedqty);
        command.Parameters.AddInt16("@scrappedqty", scrappedqty);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateWorkorder(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOrderqty = data.Orderqty;
        var dataStockedqty = data.Stockedqty;
        var dataScrappedqty = data.Scrappedqty;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataDuedate = data.Duedate;
        var dataScrapreasonid = data.Scrapreasonid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateWorkorder( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOrderqty,
                        dataStockedqty,
                        dataScrappedqty,
                        dataStartdate,
                        dataEnddate,
                        dataDuedate,
                        dataScrapreasonid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteWorkorder(SqlConnection sqlConnection, int workorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteWorkOrder]";

        command.Parameters.AddInt32("@workorderid", workorderid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteWorkorder(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var result = DeleteWorkorder( sqlConnection, 
                        dataWorkorderid );

        return result;
    }

    public static bool Insert1Workorder(SqlConnection sqlConnection, ref int workorderid,
        int productid,
        int orderqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Insert1WorkOrder]";

        var workorderidParameter = command.Parameters.AddInt32("@workorderid");
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@orderqty", orderqty);
        command.Parameters.AddInt16("@scrappedqty", scrappedqty);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            workorderid = (int)workorderidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Workorder(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOrderqty = data.Orderqty;
        var dataScrappedqty = data.Scrappedqty;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataDuedate = data.Duedate;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Workorder( sqlConnection, 
                        ref dataWorkorderid,
                        dataProductid,
                        dataOrderqty,
                        dataScrappedqty,
                        dataStartdate,
                        dataEnddate,
                        dataDuedate,
                        dataModifieddate );
        data.Workorderid = dataWorkorderid;

        return result;
    }

    public static bool Update1Workorder(SqlConnection sqlConnection, int workorderid,
        int productid,
        int orderqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update1WorkOrder]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@orderqty", orderqty);
        command.Parameters.AddInt16("@scrappedqty", scrappedqty);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Workorder(SqlConnection sqlConnection, int workorderid,
        short? scrapreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update2WorkOrder]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Workorder(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOrderqty = data.Orderqty;
        var dataScrappedqty = data.Scrappedqty;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataDuedate = data.Duedate;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Workorder( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOrderqty,
                        dataScrappedqty,
                        dataStartdate,
                        dataEnddate,
                        dataDuedate,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Workorder(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataScrapreasonid = data.Scrapreasonid;
        var result = Update2Workorder( sqlConnection, 
                        dataWorkorderid,
                        dataScrapreasonid );

        return result;
    }

    public static bool InsertWorkorderrouting(SqlConnection sqlConnection, int workorderid,
        int productid,
        short operationsequence,
        short locationid,
        DateTime scheduledstartdate,
        DateTime scheduledenddate,
        DateTime? actualstartdate,
        DateTime? actualenddate,
        decimal? actualresourcehrs,
        decimal plannedcost,
        decimal? actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertWorkOrderRouting]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@operationsequence", operationsequence);
        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddDateTime("@scheduledstartdate", scheduledstartdate);
        command.Parameters.AddDateTime("@scheduledenddate", scheduledenddate);
        command.Parameters.AddDateTime("@actualstartdate", actualstartdate);
        command.Parameters.AddDateTime("@actualenddate", actualenddate);
        command.Parameters.AddDecimal("@actualresourcehrs", actualresourcehrs);
        command.Parameters.AddDecimal("@plannedcost", plannedcost);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeWorkorderrouting(SqlConnection sqlConnection, AdventureWorks.Production.Database.DataTables.WorkorderroutingDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Production].[MergeWorkOrderRouting]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertWorkorderrouting(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderroutingDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOperationsequence = data.Operationsequence;
        var dataLocationid = data.Locationid;
        var dataScheduledstartdate = data.Scheduledstartdate;
        var dataScheduledenddate = data.Scheduledenddate;
        var dataActualstartdate = data.Actualstartdate;
        var dataActualenddate = data.Actualenddate;
        var dataActualresourcehrs = data.Actualresourcehrs;
        var dataPlannedcost = data.Plannedcost;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = InsertWorkorderrouting( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOperationsequence,
                        dataLocationid,
                        dataScheduledstartdate,
                        dataScheduledenddate,
                        dataActualstartdate,
                        dataActualenddate,
                        dataActualresourcehrs,
                        dataPlannedcost,
                        dataActualcost,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateWorkorderrouting(SqlConnection sqlConnection, int workorderid,
        int productid,
        short operationsequence,
        short locationid,
        DateTime scheduledstartdate,
        DateTime scheduledenddate,
        DateTime? actualstartdate,
        DateTime? actualenddate,
        decimal? actualresourcehrs,
        decimal plannedcost,
        decimal? actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateWorkOrderRouting]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@operationsequence", operationsequence);
        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddDateTime("@scheduledstartdate", scheduledstartdate);
        command.Parameters.AddDateTime("@scheduledenddate", scheduledenddate);
        command.Parameters.AddDateTime("@actualstartdate", actualstartdate);
        command.Parameters.AddDateTime("@actualenddate", actualenddate);
        command.Parameters.AddDecimal("@actualresourcehrs", actualresourcehrs);
        command.Parameters.AddDecimal("@plannedcost", plannedcost);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateWorkorderrouting(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderroutingDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOperationsequence = data.Operationsequence;
        var dataLocationid = data.Locationid;
        var dataScheduledstartdate = data.Scheduledstartdate;
        var dataScheduledenddate = data.Scheduledenddate;
        var dataActualstartdate = data.Actualstartdate;
        var dataActualenddate = data.Actualenddate;
        var dataActualresourcehrs = data.Actualresourcehrs;
        var dataPlannedcost = data.Plannedcost;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateWorkorderrouting( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOperationsequence,
                        dataLocationid,
                        dataScheduledstartdate,
                        dataScheduledenddate,
                        dataActualstartdate,
                        dataActualenddate,
                        dataActualresourcehrs,
                        dataPlannedcost,
                        dataActualcost,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteWorkorderrouting(SqlConnection sqlConnection, int workorderid,
        int productid,
        short operationsequence)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteWorkOrderRouting]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@operationsequence", operationsequence);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteWorkorderrouting(SqlConnection sqlConnection, AdventureWorks.Production.Types.WorkorderroutingDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOperationsequence = data.Operationsequence;
        var result = DeleteWorkorderrouting( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOperationsequence );

        return result;
    }

}
