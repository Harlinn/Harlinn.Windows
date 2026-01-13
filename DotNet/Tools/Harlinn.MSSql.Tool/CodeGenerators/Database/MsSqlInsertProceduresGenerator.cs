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
﻿using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;
using Microsoft.SqlServer.Management.HadrData;
using System.Text;

namespace Harlinn.MSSql.Tool.CodeGenerators.Database
{
    public class MsSqlInsertProceduresGenerator : CodeWriter
    {
        public MsSqlInsertProceduresGenerator(Context context) : base(context)
        {
        }

        public void Run()
        {
            var rowSources = Context.Project.Entities;
            foreach (var rowSource in rowSources)
            {
                CreateInsertProcedure(rowSource);
                CreateInsert1Procedure(rowSource);
            }
        }

        static string GetProcedureParameters(EntityDefinition rowSourceDefinition, IReadOnlyList<FieldDefinition> fields)
        {
            var parameters = new List<string>();
            bool first = true;
            foreach (var field in fields)
            {
                var paramName = MsSqlHelper.GetParameterName(field);
                var paramType = MsSqlHelper.GetRawColumnType(field);
                var output = MsSqlHelper.IsOutputParameter(field) ? " OUTPUT" : string.Empty;
                if (first)
                {
                    first = false;
                    parameters.Add($"  {paramName} {paramType}{output}");
                }
                else
                {
                    parameters.Add($"{Environment.NewLine}  {paramName} {paramType}{output}");
                }
            }
            return string.Join(", ", parameters);
        }

        static string GetProcedureParameters(EntityDefinition rowSourceDefinition)
        {
            var fields = rowSourceDefinition.PersistentFields;
            return GetProcedureParameters(rowSourceDefinition, fields);
        }

        static string GetProcedure1Parameters(EntityDefinition rowSourceDefinition)
        {
            var fields = rowSourceDefinition.NotReferenceAndNotNullableReferenceFields;
            return GetProcedureParameters(rowSourceDefinition, fields);
        }


        static string GetInsertStatement(EntityDefinition rowSourceDefinition, IReadOnlyList<FieldDefinition> fieldDefinitions)
        {
            StringBuilder statement = new();

            var fieldDefinitionsCount = fieldDefinitions.Count;

            var qualifiedTableName = MsSqlHelper.GetQualifiedTableOrViewName(rowSourceDefinition);
            var schemaName = rowSourceDefinition.Owner?.Name;
            var columnNameList = new List<string>();
            var variableNameList = new List<string>();

            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                if (fieldDefinition.IsIdentity == false)
                {
                    var variableName = MsSqlHelper.GetParameterName(fieldDefinition);
                    var columnName = MsSqlHelper.GetColumnName(fieldDefinition);
                    columnNameList.Add($"{columnName}");
                    variableNameList.Add($"{variableName}");
                }
            }

            var columnNames = string.Join($",{Environment.NewLine}            ", columnNameList);
            var variableNames = string.Join($",{Environment.NewLine}              ", variableNameList);

            var insertString = $"      INSERT INTO {qualifiedTableName}({columnNames})";
            var valueString = $"          VALUES({variableNames})";

            statement.AppendLine(insertString);
            statement.AppendLine(valueString);

            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                if (fieldDefinition.IsIdentity)
                {
                    var variableName = MsSqlHelper.GetParameterName(fieldDefinition);
                    statement.AppendLine($"      SET {variableName} = SCOPE_IDENTITY();");
                }
            }

            

            return statement.ToString();
        }

        static string GetInsertStatement(EntityDefinition rowSourceDefinition)
        {
            return GetInsertStatement(rowSourceDefinition, rowSourceDefinition.PersistentFields);
        }

        static string GetInsert1Statement(EntityDefinition rowSourceDefinition)
        {
            return GetInsertStatement(rowSourceDefinition, rowSourceDefinition.NotReferenceAndNotNullableReferenceFields);
        }


        static string GetInsertProcedure(EntityDefinition rowSourceDefinition)
        {
            var procedure = new StringBuilder();

            var procedureName = MsSqlHelper.GetQualifiedInsertProcedureName(rowSourceDefinition);

            procedure.AppendLine($"CREATE OR ALTER PROCEDURE {procedureName}");

            var parameters = GetProcedureParameters(rowSourceDefinition);
            procedure.Append(parameters);

            var savePointName = $"SavePoint{rowSourceDefinition.Id}";
            procedure.AppendLine();
            procedure.AppendLine("AS");
            procedure.AppendLine("  BEGIN");
            procedure.AppendLine("    DECLARE @TranCounter INT;");
            procedure.AppendLine("    SET @TranCounter = @@TRANCOUNT;");
            procedure.AppendLine("    IF @TranCounter > 0");
            procedure.AppendLine($"      SAVE TRANSACTION {savePointName};");
            procedure.AppendLine("    ELSE");
            procedure.AppendLine("      BEGIN TRANSACTION;");
            procedure.AppendLine("    BEGIN TRY");

            string insertStatement = GetInsertStatement(rowSourceDefinition);
            procedure.Append(insertStatement);

            procedure.AppendLine("      IF @TranCounter = 0");
            procedure.AppendLine("          COMMIT TRANSACTION;");
            procedure.AppendLine("    END TRY");
            procedure.AppendLine("    BEGIN CATCH");
            procedure.AppendLine("        DECLARE @MyXErrorMessage NVARCHAR(4000);");
            procedure.AppendLine("        DECLARE @MyXErrorSeverity INT;");
            procedure.AppendLine("        DECLARE @MyXErrorState INT;");
            procedure.AppendLine("        SELECT @MyXErrorMessage = ERROR_MESSAGE(),");
            procedure.AppendLine("            @MyXErrorSeverity = ERROR_SEVERITY(),");
            procedure.AppendLine("            @MyXErrorState = ERROR_STATE();");
            procedure.AppendLine("        IF @TranCounter = 0");
            procedure.AppendLine("          ROLLBACK TRANSACTION;");
            procedure.AppendLine("        ELSE");
            procedure.AppendLine("          IF XACT_STATE() <> -1");
            procedure.AppendLine($"            ROLLBACK TRANSACTION {savePointName};");
            procedure.AppendLine("        RAISERROR(");
            procedure.AppendLine("            @MyXErrorMessage,");
            procedure.AppendLine("            @MyXErrorSeverity,");
            procedure.AppendLine("            @MyXErrorState);");
            procedure.AppendLine("    END CATCH");
            procedure.AppendLine("  END");

            return procedure.ToString();
        }

        static string GetInsert1Procedure(EntityDefinition rowSourceDefinition)
        {
            var procedure = new StringBuilder();

            var procedureName = MsSqlHelper.GetQualifiedInsert1ProcedureName(rowSourceDefinition);

            procedure.AppendLine($"CREATE OR ALTER PROCEDURE {procedureName}");

            var parameters = GetProcedure1Parameters(rowSourceDefinition);
            procedure.Append(parameters);

            var savePointName = $"SavePoint{rowSourceDefinition.Id}";
            procedure.AppendLine();
            procedure.AppendLine("AS");
            procedure.AppendLine("  BEGIN");
            procedure.AppendLine("    DECLARE @TranCounter INT;");
            procedure.AppendLine("    SET @TranCounter = @@TRANCOUNT;");
            procedure.AppendLine("    IF @TranCounter > 0");
            procedure.AppendLine($"      SAVE TRANSACTION {savePointName};");
            procedure.AppendLine("    ELSE");
            procedure.AppendLine("      BEGIN TRANSACTION;");
            procedure.AppendLine("    BEGIN TRY");

            string insertStatement = GetInsert1Statement(rowSourceDefinition);
            procedure.Append(insertStatement);

            procedure.AppendLine("      IF @TranCounter = 0");
            procedure.AppendLine("          COMMIT TRANSACTION;");
            procedure.AppendLine("    END TRY");
            procedure.AppendLine("    BEGIN CATCH");
            procedure.AppendLine("        DECLARE @MyXErrorMessage NVARCHAR(4000);");
            procedure.AppendLine("        DECLARE @MyXErrorSeverity INT;");
            procedure.AppendLine("        DECLARE @MyXErrorState INT;");
            procedure.AppendLine("        SELECT @MyXErrorMessage = ERROR_MESSAGE(),");
            procedure.AppendLine("            @MyXErrorSeverity = ERROR_SEVERITY(),");
            procedure.AppendLine("            @MyXErrorState = ERROR_STATE();");
            procedure.AppendLine("        IF @TranCounter = 0");
            procedure.AppendLine("          ROLLBACK TRANSACTION;");
            procedure.AppendLine("        ELSE");
            procedure.AppendLine("          IF XACT_STATE() <> -1");
            procedure.AppendLine($"            ROLLBACK TRANSACTION {savePointName};");
            procedure.AppendLine("        RAISERROR(");
            procedure.AppendLine("            @MyXErrorMessage,");
            procedure.AppendLine("            @MyXErrorSeverity,");
            procedure.AppendLine("            @MyXErrorState);");
            procedure.AppendLine("    END CATCH");
            procedure.AppendLine("  END");

            return procedure.ToString();
        }


        void CreateInsertProcedure(EntityDefinition rowSourceDefinition)
        {
            var insertProcedure = GetInsertProcedure(rowSourceDefinition);
            WriteLine(insertProcedure);
            WriteLine("GO");
            WriteLine();
        }

        void CreateInsert1Procedure(EntityDefinition rowSourceDefinition)
        {
            var nullableReferenceFields = rowSourceDefinition.NullableReferenceFields;
            if (nullableReferenceFields.Count > 0)
            {
                var insertProcedure = GetInsert1Procedure(rowSourceDefinition);
                WriteLine(insertProcedure);
                WriteLine("GO");
                WriteLine();
            }
        }


    }

}
