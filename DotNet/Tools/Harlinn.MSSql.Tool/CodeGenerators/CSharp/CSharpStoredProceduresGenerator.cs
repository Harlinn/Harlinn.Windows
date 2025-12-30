
using Harlinn.MSSql.Tool.CodeGenerators.Database;
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
            WriteLine("using System.Data.SqlTypes;");
            WriteLine("using Microsoft.SqlServer.Types;");
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
            var entities = Context.Project.Entities;
            foreach (var entity in entities)
            {
                CreateStoredProcedurs(entity);
            }
            WriteLine("}");

        }

        void CreateStoredProcedurs(EntityDefinition entityDefinition)
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


        private void CreateFunction(EntityDefinition entityDefinition, string qualifiedStoredProcedureName, string functionName, IReadOnlyList<FieldDefinition> fieldDefinitions, bool isInsert = false)
        {
            var outParameters = new List<FieldDefinition>();
            var fieldDefinitionsCount = fieldDefinitions.Count;
            if (fieldDefinitionsCount > 1)
            {
                var fieldDefinition = fieldDefinitions[0];
                var refModifier = "";
                if(isInsert && MsSqlHelper.IsOutputParameter(fieldDefinition))
                {
                    refModifier = "ref ";
                    outParameters.Add(fieldDefinition);
                }
                WriteLine($"    public static bool {functionName}(SqlConnection sqlConnection, {refModifier}{CSharpHelper.GetInputArgumentType(fieldDefinitions[0])} {CSharpHelper.GetInputArgumentName(fieldDefinitions[0])},");
                for (int i = 1; i < fieldDefinitionsCount; i++)
                {
                    fieldDefinition = fieldDefinitions[i];
                    refModifier = "";
                    if (isInsert && MsSqlHelper.IsOutputParameter(fieldDefinition))
                    {
                        refModifier = "ref ";
                        outParameters.Add(fieldDefinition);
                    }
                    if (i < fieldDefinitionsCount - 1)
                        WriteLine($"        {refModifier}{CSharpHelper.GetInputArgumentType(fieldDefinition)} {CSharpHelper.GetInputArgumentName(fieldDefinition)},");
                    else
                        WriteLine($"        {refModifier}{CSharpHelper.GetInputArgumentType(fieldDefinition)} {CSharpHelper.GetInputArgumentName(fieldDefinition)})");
                }
            }
            else if (fieldDefinitionsCount == 1)
            {
                var fieldDefinition = fieldDefinitions[0];
                var refModifier = "";
                if (isInsert && MsSqlHelper.IsOutputParameter(fieldDefinition))
                {
                    refModifier = "ref ";
                    outParameters.Add(fieldDefinition);
                }
                WriteLine($"    public static bool {functionName}(SqlConnection sqlConnection, {refModifier}{CSharpHelper.GetInputArgumentType(fieldDefinitions[0])} {CSharpHelper.GetInputArgumentName(fieldDefinitions[0])})");
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
                var isOutputParameter = MsSqlHelper.IsOutputParameter(fieldDefinition);
                var argumentName = CSharpHelper.GetInputArgumentName(fieldDefinition);
                var addParameterFunction = CSharpHelper.GetAddParameterFunction(fieldDefinition);
                var sqlParameterName = $"{argumentName}Parameter";
                var size = "";
                if(fieldType == FieldType.String)
                {
                    var stringFieldDefinition = (StringFieldDefinition)fieldDefinition;
                    size = $", {stringFieldDefinition.Size}";
                }
                else if (fieldType == FieldType.Binary)
                {
                    var binaryFieldDefinition = (BinaryFieldDefinition)fieldDefinition;
                    size = $", {binaryFieldDefinition.Size}";
                }
                if (isInsert && isOutputParameter)
                {
                    WriteLine($"        var {sqlParameterName} = command.Parameters.{addParameterFunction}(\"{parameterName}\"{size});");
                }
                else
                {
                    WriteLine($"        command.Parameters.{addParameterFunction}(\"{parameterName}\", {argumentName}{size});");
                }
            }

            WriteLine();
            WriteLine("        var result = command.ExecuteNonQuery() > 0;");
            if(outParameters.Count > 0)
            {
                WriteLine("        if(result)");
                WriteLine("        {");
                foreach (var outParameter in outParameters)
                {
                    var argumentName = CSharpHelper.GetInputArgumentName(outParameter);
                    var sqlParameterName = $"{argumentName}Parameter";
                    WriteLine($"            {argumentName} = ({CSharpHelper.GetInputArgumentType(outParameter)}){sqlParameterName}.Value;");
                }
                WriteLine("        }");
            }
            WriteLine("        return result;");
            WriteLine("    }");
            WriteLine();
        }

        private void CreateObjectFunction(EntityDefinition entityDefinition, string qualifiedStoredProcedureName, string functionName, IReadOnlyList<FieldDefinition> fieldDefinitions, bool isInsert = false)
        {
            var fieldDefinitionsCount = fieldDefinitions.Count;
            var dataType = CSharpHelper.GetDataType(entityDefinition);
            var qualifiedDataTypeNamespace = CSharpHelper.GetQualifiedDataTypeNamespace(entityDefinition);
            WriteLine($"    public static bool {functionName}(SqlConnection sqlConnection, {qualifiedDataTypeNamespace}.{dataType} data )");
            WriteLine("    {");
            for (int i = 0; i < fieldDefinitionsCount; i++)
            { 
                var fieldDefinition = fieldDefinitions[i];
                var proprtyName = CSharpHelper.GetMemberPropertyName(fieldDefinition);
                WriteLine($"        var data{proprtyName} = data.{proprtyName};");

            }
            WriteLine($"        var result = {functionName}( sqlConnection, ");
            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                var proprtyName = CSharpHelper.GetMemberPropertyName(fieldDefinition);
                var refModifier = "";
                if (isInsert)
                {
                    refModifier = MsSqlHelper.IsOutputParameter(fieldDefinition) ? "ref " : "";
                }
                if (i < fieldDefinitionsCount - 1)
                    WriteLine($"                        {refModifier}data{proprtyName},");
                else
                    WriteLine($"                        {refModifier}data{proprtyName} );");

            }

            if (isInsert)
            {

                for (int i = 0; i < fieldDefinitionsCount; i++)
                {   
                    var fieldDefinition = fieldDefinitions[i];
                    var proprtyName = CSharpHelper.GetMemberPropertyName(fieldDefinition);
                    if (MsSqlHelper.IsOutputParameter(fieldDefinition))
                    {
                        WriteLine($"        data.{proprtyName} = data{proprtyName};");
                    }
                }
            }

            WriteLine();
            WriteLine($"        return result;");
            WriteLine("    }");
            WriteLine();
        }


        private void CreateInsert(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedInsertProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetInsertFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.Fields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions, true);
        }

        private void CreateInsertObject(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedInsertProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetInsertFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.Fields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions, true);
        }

        private void CreateInsert1(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedInsert1ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetInsert1FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions, true);
        }

        private void CreateInsertObject1(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedInsert1ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetInsert1FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions, true);
        }

        private void CreateUpdate(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdateProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdateFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.Fields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdateObject(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdateProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdateFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.Fields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdate1(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdate1ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdate1FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdateObject1(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdate1ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdate1FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.NotReferenceAndNotNullableReferenceFields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdate2(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdate2ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdate2FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.PrimaryKeyAndNullableReferenceFields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateUpdateObject2(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedUpdate2ProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetUpdate2FunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.PrimaryKeyAndNullableReferenceFields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateDeleteObject(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedDeleteProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetDeleteFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.PrimaryKeyFields;
            CreateObjectFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

        private void CreateDelete(EntityDefinition entityDefinition)
        {
            var qualifiedStoredProcedureName = Database.MsSqlHelper.GetQualifiedDeleteProcedureName(entityDefinition);
            var functionName = CSharpHelper.GetDeleteFunctionName(entityDefinition);
            var fieldDefinitions = entityDefinition.PrimaryKeyFields;
            CreateFunction(entityDefinition, qualifiedStoredProcedureName, functionName, fieldDefinitions);
        }

    }


}
