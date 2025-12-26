using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;
using Microsoft.Data.SqlClient;
using System.Data;
using System.Xml.Linq;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{

    public class CSharpStoredProceduresGenerator : CodeWriter
    {
        public CSharpStoredProceduresGenerator(Context context) : base(context)
        {
        }

        List<string> GetDataTypeNamespaces()
        {
            var namespaces = new HashSet<string>();
            var entities = Context.Project.Entities;
            foreach (var entity in entities)
            {
                var dataTypeNamespace = CSharpHelper.GetDataTypeNamespace(entity);
                namespaces.Add(dataTypeNamespace);
            }
            return namespaces.ToList();
        }

        public void Run()
        {
            WriteLine("using System;");
            WriteLine("using System.Data;");
            WriteLine("using System.Data.Common;");
            WriteLine("using System.Collections.Generic;");
            WriteLine("using Microsoft.Data.SqlClient;");
            WriteLine();
            var dataTypeNamespaces = GetDataTypeNamespaces();
            foreach (var dataTypeNamespace in dataTypeNamespaces)
            {
                WriteLine($"using {dataTypeNamespace};");
            }

            WriteLine();
            var databaseNamespace = CSharpHelper.GetDatabaseNamespace(Context);
            WriteLine($"namespace {databaseNamespace};");
            WriteLine();

            WriteLine("public class StoredProcedures");
            WriteLine("{");
            var entities = Context.Project.RowSources;
            foreach (var entity in entities)
            {
                CreateStoredProcedurs(entity);
            }
            WriteLine("}");

        }

        void CreateStoredProcedurs(RowSourceDefinition entityDefinition)
        {
            CreateInsert(entityDefinition);

            CreateInsertObject(entityDefinition);
            CreateUpdate(entityDefinition);
            CreateUpdateObject(entityDefinition);
            CreateDelete(entityDefinition);
            CreateDeleteObject(entityDefinition);
             
            var nullableReferenceFields = entityDefinition.NullableReferenceFields;
            if (nullableReferenceFields.Count > 0)
            {
                 CreateInsert1(entityDefinition);
                 CreateInsertObject1(entityDefinition);
                 CreateUpdate1(entityDefinition);
                 CreateUpdate2(entityDefinition);
                 CreateUpdateObject1(entityDefinition);
                 CreateUpdateObject2(entityDefinition);
            }
        }


        private void CreateFunction(RowSourceDefinition entityDefinition, string qualifiedStoredProcedureName, string functionName, IReadOnlyList<FieldDefinition> fieldDefinitions)
        {
            var fieldDefinitionsCount = fieldDefinitions.Count;
            if (fieldDefinitionsCount > 1)
            {
                WriteLine($"    public static bool {functionName}(SqlConnection sqlConnection, {CSharpHelper.GetInputArgumentType(fieldDefinitions[0])} {CSharpHelper.GetInputArgumentName(fieldDefinitions[0])},");
                for (int i = 1; i < fieldDefinitionsCount; i++)
                {
                    if (i < fieldDefinitionsCount - 1)
                        WriteLine($"        {CSharpHelper.GetInputArgumentType(fieldDefinitions[i])} {CSharpHelper.GetInputArgumentName(fieldDefinitions[i])},");
                    else
                        WriteLine($"        {CSharpHelper.GetInputArgumentType(fieldDefinitions[i])} {CSharpHelper.GetInputArgumentName(fieldDefinitions[i])})");
                }
            }
            else if (fieldDefinitionsCount == 1)
            {
                WriteLine($"    public static bool {functionName}(SqlConnection sqlConnection, {CSharpHelper.GetInputArgumentType(fieldDefinitions[0])} {CSharpHelper.GetInputArgumentName(fieldDefinitions[0])})");
            }
            else
            {
                throw new InvalidOperationException("Cannot create stored procedure function with no parameters.");
            }

            WriteLine("    {");

            WriteLine("        using var command = sqlConnection.CreateCommand();");
            WriteLine("        command.CommandType = CommandType.StoredProcedure;");

            WriteLine($"        command.CommandText = \"{qualifiedStoredProcedureName}\";");
            WriteLine();
            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                var fieldType = fieldDefinition.FieldType;
                var parameterName = Database.MsSqlHelper.GetParameterName(fieldDefinition);
                var argumentName = CSharpHelper.GetInputArgumentName(fieldDefinition);
                if (fieldDefinition.IsNullable)
                {
                    if (fieldType <= FieldType.Guid)
                    {
                        WriteLine($"        command.Parameters.AddWithValue(\"{parameterName}\", {argumentName}.HasValue ? (object){argumentName}.Value : (object)DBNull.Value);");
                    }
                    else
                    {
                        WriteLine($"        command.Parameters.AddWithValue(\"{parameterName}\", (object?){argumentName} ?? (object)DBNull.Value);");
                    }
                }
                else
                {
                    WriteLine($"        command.Parameters.AddWithValue(\"{parameterName}\", {argumentName});");
                }
            }

            WriteLine();
            WriteLine("        return command.ExecuteNonQuery() > 0;");
            WriteLine("    }");
            WriteLine();
        }

        private void CreateObjectFunction(RowSourceDefinition entityDefinition, string qualifiedStoredProcedureName, string functionName, IReadOnlyList<FieldDefinition> fieldDefinitions)
        {
            var fieldDefinitionsCount = fieldDefinitions.Count;
            var dataType = CSharpHelper.GetDataType(entityDefinition);
            var qualifiedDataTypeNamespace = CSharpHelper.GetQualifiedDataTypeNamespace(entityDefinition);
            WriteLine($"    public static bool {functionName}(SqlConnection sqlConnection, {qualifiedDataTypeNamespace}.{dataType} data )");
            WriteLine("    {");
            WriteLine($"        return {functionName}( sqlConnection, ");
            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                var proprtyName = CSharpHelper.GetMemberPropertyName(fieldDefinition);
                if (i < fieldDefinitionsCount - 1)
                    WriteLine($"            data.{proprtyName},");
                else
                    WriteLine($"            data.{proprtyName} );");

            }
            WriteLine("    }");
            WriteLine();
        }


        private void CreateInsert(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedInsertProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetInsertFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.Fields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateInsertObject(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedInsertProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetInsertFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.Fields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateInsert1(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedInsert1ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetInsert1FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateInsertObject1(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedInsert1ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetInsert1FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdate(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdateProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdateFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.Fields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdateObject(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdateProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdateFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.Fields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdate1(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdate1ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdate1FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdateObject1(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdate1ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdate1FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdate2(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdate2ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdate2FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.PrimaryKeyAndNullableReferenceFields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdateObject2(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdate2ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdate2FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.PrimaryKeyAndNullableReferenceFields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateDeleteObject(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedDeleteProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetDeleteFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.PrimaryKeyFields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateDelete(RowSourceDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedDeleteProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetDeleteFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.PrimaryKeyFields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

    }


}
