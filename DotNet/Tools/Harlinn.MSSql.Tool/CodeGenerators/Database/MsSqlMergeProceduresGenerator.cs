using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;
using Microsoft.SqlServer.Management.HadrData;
using Microsoft.SqlServer.Management.XEvent;
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Harlinn.MSSql.Tool.CodeGenerators.Database
{
    public class MsSqlMergeProceduresGenerator : CodeWriter
    {
        public MsSqlMergeProceduresGenerator(Context context) : base(context)
        {
        }

        public void Run()
        {
            var entities = Context.Project.Entities;
            foreach (var entity in entities)
            {
                CreateMergeProcedure(entity);
            }
        }

        

        private string GetMergeStatement(EntityDefinition entityDefinition)
        {
            var sb = new System.Text.StringBuilder();
            var qualifiedTableName = MsSqlHelper.GetQualifiedTableOrViewName(entityDefinition);

            var primaryKeyFields = entityDefinition.PrimaryKeyFields;
            var joins = new List<string>();
            for (int i = 0; i < primaryKeyFields.Count; i++)
            {
                var field = primaryKeyFields[i];
                var join = $"Target.{MsSqlHelper.GetColumnName(field)} = Source.{MsSqlHelper.GetColumnName(field)}";
                joins.Add(join);
            }
            var mergeJoin = string.Join(" AND ", joins);

            sb.AppendLine($"      MERGE INTO {qualifiedTableName} AS Target");
            sb.AppendLine($"      USING @Data AS Source");
            sb.AppendLine($"          ON {mergeJoin}");
            sb.AppendLine($"      WHEN MATCHED THEN");
            sb.AppendLine($"          UPDATE SET");

            var nonPrimaryKeyFields = entityDefinition.NonPrimaryKeyFields;
            for (int i = 0; i < nonPrimaryKeyFields.Count; i++)
            {
                var field = nonPrimaryKeyFields[i];
                var columnName = MsSqlHelper.GetColumnName(field);
                sb.AppendLine($"              Target.{columnName} = Source.{columnName}{(i < nonPrimaryKeyFields.Count - 1 ? "," : "")}");
            }
            sb.AppendLine($"      WHEN NOT MATCHED BY TARGET THEN");

            var persistentFields = entityDefinition.PersistentFields;
            var insertTargetColumns = new List<string>();
            var insertSourceValues = new List<string>();

            for (int i = 0; i < persistentFields.Count; i++)
            {
                var field = persistentFields[i];
                var columnName = MsSqlHelper.GetColumnName(field);
                insertTargetColumns.Add(columnName);
                insertSourceValues.Add($"Source.{columnName}");
            }

            var insertTarget = string.Join(", ", insertTargetColumns);
            var insertSource = string.Join(", ", insertSourceValues);

            sb.AppendLine($"          INSERT({insertTarget})");
            sb.AppendLine($"          VALUES({insertSource});");

            return sb.ToString();
        }

        private void CreateMergeProcedure(EntityDefinition entityDefinition)
        {
            var procedureName = MsSqlHelper.GetQualifiedMergeProcedureName(entityDefinition);

            var primaryKey = entityDefinition.PrimaryKey;
            var tableTypeName = entityDefinition.GetTableType();
            
            var schemaName = entityDefinition.Owner!.Name;

            var qualifiedTableTypeName = $"[{schemaName}].[{tableTypeName}]";

            WriteLine($"CREATE OR ALTER PROCEDURE {procedureName}");
            var parameters =  $"@Data {qualifiedTableTypeName} READONLY";
            WriteLine(parameters);

            var savePointName = $"SavePoint{entityDefinition.Id}";
            WriteLine("AS");
            WriteLine("  BEGIN");
            WriteLine("    DECLARE @TranCounter INT;");
            WriteLine("    DECLARE @RowCount INT;");
            WriteLine("    SET @TranCounter = @@TRANCOUNT;");
            WriteLine("    IF @TranCounter > 0");
            WriteLine($"      SAVE TRANSACTION {savePointName};");
            WriteLine("    ELSE");
            WriteLine("      BEGIN TRANSACTION;");
            WriteLine("    BEGIN TRY");
            string mergeStatement = GetMergeStatement(entityDefinition);
            WriteLine(mergeStatement);
            WriteLine("      SET @RowCount = @@ROWCOUNT;");
            WriteLine("      IF @RowCount = 0");
            WriteLine("      BEGIN");
            WriteLine("        IF @TranCounter = 0");
            WriteLine("          ROLLBACK TRANSACTION;");
            WriteLine("        ELSE");
            WriteLine("          IF XACT_STATE() <> -1");
            WriteLine($"            ROLLBACK TRANSACTION {savePointName};");
            WriteLine("        RETURN");
            WriteLine("      END");
            WriteLine("      IF @TranCounter = 0");
            WriteLine("          COMMIT TRANSACTION;");
            WriteLine("    END TRY");
            WriteLine("    BEGIN CATCH");
            WriteLine("        DECLARE @MyXErrorMessage NVARCHAR(4000);");
            WriteLine("        DECLARE @MyXErrorSeverity INT;");
            WriteLine("        DECLARE @MyXErrorState INT;");
            WriteLine("        SELECT @MyXErrorMessage = ERROR_MESSAGE(),");
            WriteLine("            @MyXErrorSeverity = ERROR_SEVERITY(),");
            WriteLine("            @MyXErrorState = ERROR_STATE();");
            WriteLine("        IF @TranCounter = 0");
            WriteLine("          ROLLBACK TRANSACTION;");
            WriteLine("        ELSE");
            WriteLine("          IF XACT_STATE() <> -1");
            WriteLine($"            ROLLBACK TRANSACTION {savePointName};");
            WriteLine("        RAISERROR(");
            WriteLine("            @MyXErrorMessage,");
            WriteLine("            @MyXErrorSeverity,");
            WriteLine("            @MyXErrorState);");
            WriteLine("    END CATCH");
            WriteLine("  END");
            WriteLine("GO");
            WriteLine();
        }
    }



}
