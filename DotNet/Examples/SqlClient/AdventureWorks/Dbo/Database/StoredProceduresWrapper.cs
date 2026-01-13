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
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

using AdventureWorks.Dbo.Types;
using AdventureWorks.HumanResources.Types;
using AdventureWorks.Person.Types;
using AdventureWorks.Production.Types;
using AdventureWorks.Purchasing.Types;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Dbo.Database;

public class StoredProceduresWrapper
{
    public static bool InsertAwbuildversion(SqlConnection sqlConnection, ref byte systeminformationid,
        string databaseVersion,
        DateTime versiondate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[InsertAWBuildVersion]";

        var systeminformationidParameter = command.Parameters.AddByte("@systeminformationid");
        command.Parameters.AddNVarChar("@databaseVersion", databaseVersion, 25);
        command.Parameters.AddDateTime("@versiondate", versiondate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            systeminformationid = (byte)systeminformationidParameter.Value;
        }
        return result;
    }

    public static bool MergeAwbuildversion(SqlConnection sqlConnection, AdventureWorks.Dbo.Database.DataTables.AwbuildversionDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[dbo].[MergeAWBuildVersion]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertAwbuildversion(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.AwbuildversionDataType data )
    {
        var dataSysteminformationid = data.Systeminformationid;
        var dataDatabaseVersion = data.DatabaseVersion;
        var dataVersiondate = data.Versiondate;
        var dataModifieddate = data.Modifieddate;
        var result = InsertAwbuildversion( sqlConnection, 
                        ref dataSysteminformationid,
                        dataDatabaseVersion,
                        dataVersiondate,
                        dataModifieddate );
        data.Systeminformationid = dataSysteminformationid;

        return result;
    }

    public static bool UpdateAwbuildversion(SqlConnection sqlConnection, byte systeminformationid,
        string databaseVersion,
        DateTime versiondate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[UpdateAWBuildVersion]";

        command.Parameters.AddByte("@systeminformationid", systeminformationid);
        command.Parameters.AddNVarChar("@databaseVersion", databaseVersion, 25);
        command.Parameters.AddDateTime("@versiondate", versiondate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateAwbuildversion(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.AwbuildversionDataType data )
    {
        var dataSysteminformationid = data.Systeminformationid;
        var dataDatabaseVersion = data.DatabaseVersion;
        var dataVersiondate = data.Versiondate;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateAwbuildversion( sqlConnection, 
                        dataSysteminformationid,
                        dataDatabaseVersion,
                        dataVersiondate,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteAwbuildversion(SqlConnection sqlConnection, byte systeminformationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteAWBuildVersion]";

        command.Parameters.AddByte("@systeminformationid", systeminformationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteAwbuildversion(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.AwbuildversionDataType data )
    {
        var dataSysteminformationid = data.Systeminformationid;
        var result = DeleteAwbuildversion( sqlConnection, 
                        dataSysteminformationid );

        return result;
    }

    public static bool InsertDatabaselog(SqlConnection sqlConnection, ref int databaselogid,
        DateTime posttime,
        string databaseuser,
        string event__,
        string? schema,
        string? object__,
        string tsql,
        SqlXml xmlevent)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[InsertDatabaseLog]";

        var databaselogidParameter = command.Parameters.AddInt32("@databaselogid");
        command.Parameters.AddDateTime("@posttime", posttime);
        command.Parameters.AddNVarChar("@databaseuser", databaseuser, 128);
        command.Parameters.AddNVarChar("@event", event__, 128);
        command.Parameters.AddNVarChar("@schema", schema, 128);
        command.Parameters.AddNVarChar("@object", object__, 128);
        command.Parameters.AddNVarChar("@tsql", tsql, -1);
        command.Parameters.AddSqlXml("@xmlevent", xmlevent);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            databaselogid = (int)databaselogidParameter.Value;
        }
        return result;
    }

    public static bool MergeDatabaselog(SqlConnection sqlConnection, AdventureWorks.Dbo.Database.DataTables.DatabaselogDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[dbo].[MergeDatabaseLog]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertDatabaselog(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.DatabaselogDataType data )
    {
        var dataDatabaselogid = data.Databaselogid;
        var dataPosttime = data.Posttime;
        var dataDatabaseuser = data.Databaseuser;
        var dataEvent = data.Event;
        var dataSchema = data.Schema;
        var dataObject = data.Object;
        var dataTsql = data.Tsql;
        var dataXmlevent = data.Xmlevent;
        var result = InsertDatabaselog( sqlConnection, 
                        ref dataDatabaselogid,
                        dataPosttime,
                        dataDatabaseuser,
                        dataEvent,
                        dataSchema,
                        dataObject,
                        dataTsql,
                        dataXmlevent );
        data.Databaselogid = dataDatabaselogid;

        return result;
    }

    public static bool UpdateDatabaselog(SqlConnection sqlConnection, int databaselogid,
        DateTime posttime,
        string databaseuser,
        string event__,
        string? schema,
        string? object__,
        string tsql,
        SqlXml xmlevent)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[UpdateDatabaseLog]";

        command.Parameters.AddInt32("@databaselogid", databaselogid);
        command.Parameters.AddDateTime("@posttime", posttime);
        command.Parameters.AddNVarChar("@databaseuser", databaseuser, 128);
        command.Parameters.AddNVarChar("@event", event__, 128);
        command.Parameters.AddNVarChar("@schema", schema, 128);
        command.Parameters.AddNVarChar("@object", object__, 128);
        command.Parameters.AddNVarChar("@tsql", tsql, -1);
        command.Parameters.AddSqlXml("@xmlevent", xmlevent);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateDatabaselog(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.DatabaselogDataType data )
    {
        var dataDatabaselogid = data.Databaselogid;
        var dataPosttime = data.Posttime;
        var dataDatabaseuser = data.Databaseuser;
        var dataEvent = data.Event;
        var dataSchema = data.Schema;
        var dataObject = data.Object;
        var dataTsql = data.Tsql;
        var dataXmlevent = data.Xmlevent;
        var result = UpdateDatabaselog( sqlConnection, 
                        dataDatabaselogid,
                        dataPosttime,
                        dataDatabaseuser,
                        dataEvent,
                        dataSchema,
                        dataObject,
                        dataTsql,
                        dataXmlevent );

        return result;
    }

    public static bool DeleteDatabaselog(SqlConnection sqlConnection, int databaselogid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteDatabaseLog]";

        command.Parameters.AddInt32("@databaselogid", databaselogid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteDatabaselog(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.DatabaselogDataType data )
    {
        var dataDatabaselogid = data.Databaselogid;
        var result = DeleteDatabaselog( sqlConnection, 
                        dataDatabaselogid );

        return result;
    }

    public static bool InsertErrorlog(SqlConnection sqlConnection, ref int errorlogid,
        DateTime errortime,
        string username,
        int errornumber,
        int? errorseverity,
        int? errorstate,
        string? errorprocedure,
        int? errorline,
        string errormessage)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[InsertErrorLog]";

        var errorlogidParameter = command.Parameters.AddInt32("@errorlogid");
        command.Parameters.AddDateTime("@errortime", errortime);
        command.Parameters.AddNVarChar("@username", username, 128);
        command.Parameters.AddInt32("@errornumber", errornumber);
        command.Parameters.AddInt32("@errorseverity", errorseverity);
        command.Parameters.AddInt32("@errorstate", errorstate);
        command.Parameters.AddNVarChar("@errorprocedure", errorprocedure, 126);
        command.Parameters.AddInt32("@errorline", errorline);
        command.Parameters.AddNVarChar("@errormessage", errormessage, 4000);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            errorlogid = (int)errorlogidParameter.Value;
        }
        return result;
    }

    public static bool MergeErrorlog(SqlConnection sqlConnection, AdventureWorks.Dbo.Database.DataTables.ErrorlogDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[dbo].[MergeErrorLog]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertErrorlog(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.ErrorlogDataType data )
    {
        var dataErrorlogid = data.Errorlogid;
        var dataErrortime = data.Errortime;
        var dataUsername = data.Username;
        var dataErrornumber = data.Errornumber;
        var dataErrorseverity = data.Errorseverity;
        var dataErrorstate = data.Errorstate;
        var dataErrorprocedure = data.Errorprocedure;
        var dataErrorline = data.Errorline;
        var dataErrormessage = data.Errormessage;
        var result = InsertErrorlog( sqlConnection, 
                        ref dataErrorlogid,
                        dataErrortime,
                        dataUsername,
                        dataErrornumber,
                        dataErrorseverity,
                        dataErrorstate,
                        dataErrorprocedure,
                        dataErrorline,
                        dataErrormessage );
        data.Errorlogid = dataErrorlogid;

        return result;
    }

    public static bool UpdateErrorlog(SqlConnection sqlConnection, int errorlogid,
        DateTime errortime,
        string username,
        int errornumber,
        int? errorseverity,
        int? errorstate,
        string? errorprocedure,
        int? errorline,
        string errormessage)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[UpdateErrorLog]";

        command.Parameters.AddInt32("@errorlogid", errorlogid);
        command.Parameters.AddDateTime("@errortime", errortime);
        command.Parameters.AddNVarChar("@username", username, 128);
        command.Parameters.AddInt32("@errornumber", errornumber);
        command.Parameters.AddInt32("@errorseverity", errorseverity);
        command.Parameters.AddInt32("@errorstate", errorstate);
        command.Parameters.AddNVarChar("@errorprocedure", errorprocedure, 126);
        command.Parameters.AddInt32("@errorline", errorline);
        command.Parameters.AddNVarChar("@errormessage", errormessage, 4000);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateErrorlog(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.ErrorlogDataType data )
    {
        var dataErrorlogid = data.Errorlogid;
        var dataErrortime = data.Errortime;
        var dataUsername = data.Username;
        var dataErrornumber = data.Errornumber;
        var dataErrorseverity = data.Errorseverity;
        var dataErrorstate = data.Errorstate;
        var dataErrorprocedure = data.Errorprocedure;
        var dataErrorline = data.Errorline;
        var dataErrormessage = data.Errormessage;
        var result = UpdateErrorlog( sqlConnection, 
                        dataErrorlogid,
                        dataErrortime,
                        dataUsername,
                        dataErrornumber,
                        dataErrorseverity,
                        dataErrorstate,
                        dataErrorprocedure,
                        dataErrorline,
                        dataErrormessage );

        return result;
    }

    public static bool DeleteErrorlog(SqlConnection sqlConnection, int errorlogid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteErrorLog]";

        command.Parameters.AddInt32("@errorlogid", errorlogid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteErrorlog(SqlConnection sqlConnection, AdventureWorks.Dbo.Types.ErrorlogDataType data )
    {
        var dataErrorlogid = data.Errorlogid;
        var result = DeleteErrorlog( sqlConnection, 
                        dataErrorlogid );

        return result;
    }

    public static int UspGetBillOfMaterials(SqlConnection sqlConnection, int startProductID,
        DateTime checkDate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[uspGetBillOfMaterials]";

        command.Parameters.AddInt32("@StartProductID", startProductID);
        command.Parameters.AddDateTime("@CheckDate", checkDate);

        var result = command.ExecuteNonQuery();
        return result;
    }

    public static int UspGetEmployeeManagers(SqlConnection sqlConnection, int businessEntityID)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[uspGetEmployeeManagers]";

        command.Parameters.AddInt32("@BusinessEntityID", businessEntityID);

        var result = command.ExecuteNonQuery();
        return result;
    }

    public static int UspGetManagerEmployees(SqlConnection sqlConnection, int businessEntityID)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[uspGetManagerEmployees]";

        command.Parameters.AddInt32("@BusinessEntityID", businessEntityID);

        var result = command.ExecuteNonQuery();
        return result;
    }

    public static int UspGetWhereUsedProductID(SqlConnection sqlConnection, int startProductID,
        DateTime checkDate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[uspGetWhereUsedProductID]";

        command.Parameters.AddInt32("@StartProductID", startProductID);
        command.Parameters.AddDateTime("@CheckDate", checkDate);

        var result = command.ExecuteNonQuery();
        return result;
    }

    public static int UspLogError(SqlConnection sqlConnection, ref int errorLogID)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[uspLogError]";

        var errorLogIDParameter = command.Parameters.AddInt32("@ErrorLogID");

        var result = command.ExecuteNonQuery();
        errorLogID = (int)errorLogIDParameter.Value;
        return result;
    }

    public static int UspPrintError(SqlConnection sqlConnection)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[uspPrintError]";


        var result = command.ExecuteNonQuery();
        return result;
    }

    public static int UspSearchCandidateResumes(SqlConnection sqlConnection, string searchString,
        bool useInflectional,
        bool useThesaurus,
        int language)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[uspSearchCandidateResumes]";

        command.Parameters.AddNVarChar("@searchString", searchString, 1000);
        command.Parameters.AddBoolean("@useInflectional", useInflectional);
        command.Parameters.AddBoolean("@useThesaurus", useThesaurus);
        command.Parameters.AddInt32("@language", language);

        var result = command.ExecuteNonQuery();
        return result;
    }

}
