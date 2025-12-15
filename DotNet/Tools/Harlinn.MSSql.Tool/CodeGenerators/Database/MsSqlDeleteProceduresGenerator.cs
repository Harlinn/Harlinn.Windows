using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;
using System.ComponentModel.DataAnnotations;

namespace Harlinn.MSSql.Tool.CodeGenerators.Database
{
    public class MsSqlDeleteProceduresGenerator : CodeWriter
    {
        public MsSqlDeleteProceduresGenerator(Context context) : base(context)
        {
        }

        public void Run()
        {
            var entities = Context.Project.Entities;
            foreach (var entity in entities)
            {
                CreateDeleteProcedure(entity);
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
            var fields = entityDefinition.PrimaryKeyFields;
            return GetProcedureParameters(entityDefinition, fields);
        }

        private string GetDeleteStatement(EntityDefinition entityDefinition)
        {
            var sb = new System.Text.StringBuilder();
            var qualifiedTableName = MsSqlHelper.GetQualifiedTableName(entityDefinition);
            sb.AppendLine($"      DELETE FROM {qualifiedTableName}");

            sb.AppendLine( "        WHERE");
            sb.AppendLine($"          {MsSqlHelper.GetPrimaryKeyCondition(entityDefinition)}");
            return sb.ToString();
        }

        private void CreateDeleteProcedure(EntityDefinition entityDefinition)
        {
            var procedureName = MsSqlHelper.GetQualifiedDeleteProcedureName(entityDefinition);

            var primaryKey = entityDefinition.PrimaryKey;

            WriteLine($"CREATE OR ALTER PROCEDURE {procedureName}" );
            var parameters = GetProcedureParameters(entityDefinition);
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
            string deleteStatement = GetDeleteStatement(entityDefinition);
            WriteLine(deleteStatement);
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
            WriteLine("        DECLARE @ErrorMessage NVARCHAR(4000);");
            WriteLine("        DECLARE @ErrorSeverity INT;");
            WriteLine("        DECLARE @ErrorState INT;");
            WriteLine("        SELECT @ErrorMessage = ERROR_MESSAGE(),");
            WriteLine("            @ErrorSeverity = ERROR_SEVERITY(),");
            WriteLine("            @ErrorState = ERROR_STATE();");
            WriteLine("        IF @TranCounter = 0");
            WriteLine("          ROLLBACK TRANSACTION;");
            WriteLine("        ELSE");
            WriteLine("          IF XACT_STATE() <> -1");
            WriteLine($"            ROLLBACK TRANSACTION {savePointName};");
            WriteLine("        RAISERROR(");
            WriteLine("            @ErrorMessage,");
            WriteLine("            @ErrorSeverity,");
            WriteLine("            @ErrorState);");
            WriteLine("    END CATCH");
            WriteLine("  END");
            WriteLine("GO");
            WriteLine();
        }
    }

}
