using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;
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
            var entities = Context.Project.Entities;
            foreach (var entity in entities)
            {
                CreateInsertProcedure(entity);
                CreateInsert1Procedure(entity);
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


        static string GetInsertStatement(EntityDefinition entityDefinition, IReadOnlyList<FieldDefinition> fieldDefinitions)
        {
            StringBuilder statement = new();

            var fieldDefinitionsCount = fieldDefinitions.Count;

            var qualifiedTableName = MsSqlHelper.GetQualifiedTableName(entityDefinition);
            var schemaName = entityDefinition.Owner?.Name;
            var columnNameList = new List<string>();
            var variableNameList = new List<string>();

            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                var variableName = MsSqlHelper.GetParameterName(fieldDefinition);
                var columnName = MsSqlHelper.GetColumnName(fieldDefinition);
                columnNameList.Add($"{columnName}");
                variableNameList.Add($"{variableName}");
            }

            var columnNames = string.Join($",{Environment.NewLine}            ", columnNameList);
            var variableNames = string.Join($",{Environment.NewLine}              ", variableNameList);

            var insertString = $"      INSERT INTO {qualifiedTableName}({columnNames})";
            var valueString = $"          VALUES({variableNames})";

            statement.AppendLine(insertString);
            statement.AppendLine(valueString);

            return statement.ToString();
        }

        static string GetInsertStatement(EntityDefinition entityDefinition)
        {
            return GetInsertStatement(entityDefinition, entityDefinition.Fields);
        }

        static string GetInsert1Statement(EntityDefinition entityDefinition)
        {
            return GetInsertStatement(entityDefinition, entityDefinition.NotReferenceAndNotNullableReferenceFields);
        }


        static string GetInsertProcedure(EntityDefinition entityDefinition)
        {
            var procedure = new StringBuilder();

            var procedureName = MsSqlHelper.GetQualifiedInsertProcedureName(entityDefinition);

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

            string insertStatement = GetInsertStatement(entityDefinition);
            procedure.Append(insertStatement);

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

        static string GetInsert1Procedure(EntityDefinition entityDefinition)
        {
            var procedure = new StringBuilder();

            var procedureName = MsSqlHelper.GetQualifiedInsert1ProcedureName(entityDefinition);

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

            string insertStatement = GetInsert1Statement(entityDefinition);
            procedure.Append(insertStatement);

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


        void CreateInsertProcedure(EntityDefinition entityDefinition)
        {
            var insertProcedure = GetInsertProcedure(entityDefinition);
            WriteLine(insertProcedure);
            WriteLine("GO");
            WriteLine();
        }

        void CreateInsert1Procedure(EntityDefinition entityDefinition)
        {
            var nullableReferenceFields = entityDefinition.NullableReferenceFields;
            if (nullableReferenceFields.Count > 0)
            {
                var insertProcedure = GetInsert1Procedure(entityDefinition);
                WriteLine(insertProcedure);
                WriteLine("GO");
                WriteLine();
            }
        }


    }

}
