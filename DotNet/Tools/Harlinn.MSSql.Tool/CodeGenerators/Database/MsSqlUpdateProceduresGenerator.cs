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
using System.Text;

namespace Harlinn.MSSql.Tool.CodeGenerators.Database
{
    public class MsSqlUpdateProceduresGenerator : CodeWriter
    {
        public MsSqlUpdateProceduresGenerator(Context context) : base(context)
        {
        }

        public void Run()
        {
            var entities = Context.Project.Entities;
            foreach (var entity in entities)
            {
                CreateUpdateProcedure(entity);
                CreateUpdate1Procedure(entity);
                CreateUpdate2Procedure(entity);
            }
        }

        static string GetProcedureParameters(EntityDefinition entityDefinition, IReadOnlyList<FieldDefinition> fields)
        {
            var parameters = new List<string>();
            bool first = true;
            foreach (var field in fields)
            {
                var paramName = MsSqlHelper.GetParameterName(field);
                var paramType = MsSqlHelper.GetRawColumnType(field);
                if (first)
                {
                    first = false;
                    parameters.Add($"  {paramName} {paramType}");
                }
                else
                {
                    parameters.Add($"{Environment.NewLine}  {paramName} {paramType}");
                }
            }
            return string.Join(", ", parameters);
        }

        static string GetProcedureParameters(EntityDefinition entityDefinition)
        {
            var fields = entityDefinition.Fields;
            return GetProcedureParameters(entityDefinition, fields);
        }

        static string GetProcedure1Parameters(EntityDefinition entityDefinition)
        {
            var fields = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            return GetProcedureParameters(entityDefinition, fields);
        }

        static string GetProcedure2Parameters(EntityDefinition entityDefinition)
        {
            var fields = entityDefinition.PrimaryKeyAndNullableReferenceFields;
            return GetProcedureParameters(entityDefinition, fields);
        }

        static string GetUpdateProcedure(EntityDefinition entityDefinition)
        {
            var procedure = new StringBuilder();

            var procedureName = MsSqlHelper.GetQualifiedUpdateProcedureName(entityDefinition);

            procedure.AppendLine($"CREATE OR ALTER PROCEDURE {procedureName}");

            var parameters = GetProcedureParameters(entityDefinition);
            procedure.Append(parameters);

            var savePointName = $"SavePoint{entityDefinition.Id}";
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

            string updateStatement = GetUpdateStatement(entityDefinition);
            procedure.Append(updateStatement);

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

        private static string GetUpdateStatement(EntityDefinition entityDefinition)
        {
            var statement = new StringBuilder();

            statement.AppendLine($"      UPDATE {MsSqlHelper.GetQualifiedTableOrViewName(entityDefinition)}");
            statement.AppendLine( "        SET");

            var fields = entityDefinition.NonPrimaryKeyFields;
            for (int i = 0; i < fields.Count; i++)
            {
                var field = fields[i];
                var columnName = MsSqlHelper.GetColumnName(field);
                var paramName = MsSqlHelper.GetParameterName(field);
                statement.AppendLine($"           {columnName} = {paramName}{(i < fields.Count - 1 ? "," : "")}");
            }

            statement.AppendLine( "         WHERE");
            statement.AppendLine($"           {MsSqlHelper.GetPrimaryKeyCondition(entityDefinition)}");

            return statement.ToString();
        }

        static string GetUpdate1Procedure(EntityDefinition entityDefinition)
        {
            var procedure = new StringBuilder();

            var procedureName = MsSqlHelper.GetQualifiedUpdate1ProcedureName(entityDefinition);

            procedure.AppendLine($"CREATE OR ALTER PROCEDURE {procedureName}");

            var parameters = GetProcedure1Parameters(entityDefinition);
            procedure.Append(parameters);

            var savePointName = $"SavePoint{entityDefinition.Id}";
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

            string updateStatement = GetUpdate1Statement(entityDefinition);
            procedure.Append(updateStatement);

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

        private static string GetUpdate1Statement(EntityDefinition entityDefinition)
        {
            var statement = new StringBuilder();

            statement.AppendLine($"      UPDATE {MsSqlHelper.GetQualifiedTableOrViewName(entityDefinition)}");
            statement.AppendLine("        SET");

            var nonPrimaryKeyFields = entityDefinition.NonPrimaryKeyFields;
            for (int i = 0; i < nonPrimaryKeyFields.Count; i++)
            {
                var nonPrimaryKeyField = nonPrimaryKeyFields[i];
                if (nonPrimaryKeyField.IsReference == false || (nonPrimaryKeyField.IsReference && nonPrimaryKeyField.IsNullable == false))
                {
                    var columnName = MsSqlHelper.GetColumnName(nonPrimaryKeyField);
                    var paramName = MsSqlHelper.GetParameterName(nonPrimaryKeyField);
                    statement.AppendLine($"           {columnName} = {paramName}{(i < nonPrimaryKeyFields.Count - 1 ? "," : "")}");
                }
                else
                {
                    var columnName = MsSqlHelper.GetColumnName(nonPrimaryKeyField);
                    statement.AppendLine($"           {columnName} = NULL{(i < nonPrimaryKeyFields.Count - 1 ? "," : "")}");
                }
            }

            statement.AppendLine("         WHERE");
            statement.AppendLine($"           {MsSqlHelper.GetPrimaryKeyCondition(entityDefinition)}");

            return statement.ToString();
        }


        static string GetUpdate2Procedure(EntityDefinition entityDefinition)
        {
            var procedure = new StringBuilder();

            var procedureName = MsSqlHelper.GetQualifiedUpdate2ProcedureName(entityDefinition);

            procedure.AppendLine($"CREATE OR ALTER PROCEDURE {procedureName}");

            var parameters = GetProcedure2Parameters(entityDefinition);
            procedure.Append(parameters);

            var savePointName = $"SavePoint{entityDefinition.Id}";
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

            string updateStatement = GetUpdate2Statement(entityDefinition);
            procedure.Append(updateStatement);

            procedure.AppendLine("      IF @TranCounter = 0");
            procedure.AppendLine("          COMMIT TRANSACTION;");
            procedure.AppendLine("    END TRY");
            procedure.AppendLine("    BEGIN CATCH");
            procedure.AppendLine("        DECLARE @ErrorMessage NVARCHAR(4000);");
            procedure.AppendLine("        DECLARE @ErrorSeverity INT;");
            procedure.AppendLine("        DECLARE @ErrorState INT;");
            procedure.AppendLine("        SELECT @ErrorMessage = ERROR_MESSAGE(),");
            procedure.AppendLine("            @ErrorSeverity = ERROR_SEVERITY(),");
            procedure.AppendLine("            @ErrorState = ERROR_STATE();");
            procedure.AppendLine("        IF @TranCounter = 0");
            procedure.AppendLine("          ROLLBACK TRANSACTION;");
            procedure.AppendLine("        ELSE");
            procedure.AppendLine("          IF XACT_STATE() <> -1");
            procedure.AppendLine($"            ROLLBACK TRANSACTION {savePointName};");
            procedure.AppendLine("        RAISERROR(");
            procedure.AppendLine("            @ErrorMessage,");
            procedure.AppendLine("            @ErrorSeverity,");
            procedure.AppendLine("            @ErrorState);");
            procedure.AppendLine("    END CATCH");
            procedure.AppendLine("  END");

            return procedure.ToString();
        }

        private static string GetUpdate2Statement(EntityDefinition entityDefinition)
        {
            var statement = new StringBuilder();

            statement.AppendLine($"      UPDATE {MsSqlHelper.GetQualifiedTableOrViewName(entityDefinition)}");
            statement.AppendLine("        SET");

            var nullableReferenceFields = entityDefinition.NullableReferenceFields;
            for (int i = 0; i < nullableReferenceFields.Count; i++)
            {
                var nullableReferenceField = nullableReferenceFields[i];
                var columnName = MsSqlHelper.GetColumnName(nullableReferenceField);
                var paramName = MsSqlHelper.GetParameterName(nullableReferenceField);
                statement.AppendLine($"           {columnName} = {paramName}{(i < nullableReferenceFields.Count - 1 ? "," : "")}");
            }

            statement.AppendLine("         WHERE");
            statement.AppendLine($"           {MsSqlHelper.GetPrimaryKeyCondition(entityDefinition)}");

            return statement.ToString();
        }


        void CreateUpdateProcedure(EntityDefinition entityDefinition)
        {
            var updateProcedure = GetUpdateProcedure(entityDefinition);
            WriteLine(updateProcedure);
            WriteLine("GO");
            WriteLine();
        }

        void CreateUpdate1Procedure(EntityDefinition entityDefinition)
        {
            var nullableReferenceFields = entityDefinition.NullableReferenceFields;
            if (nullableReferenceFields.Count > 0)
            {
                var updateProcedure = GetUpdate1Procedure(entityDefinition);
                WriteLine(updateProcedure);
                WriteLine("GO");
                WriteLine();
            }
        }

        void CreateUpdate2Procedure(EntityDefinition entityDefinition)
        {
            var nullableReferenceFields = entityDefinition.NullableReferenceFields;
            if (nullableReferenceFields.Count > 0)
            {
                var updateProcedure = GetUpdate2Procedure(entityDefinition);
                WriteLine(updateProcedure);
                WriteLine("GO");
                WriteLine();
            }
        }

    }

}
