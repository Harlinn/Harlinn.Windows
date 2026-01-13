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
﻿using Harlinn.MSSql.Tool.CodeGenerators.Database;
using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;
using Microsoft.Data.SqlClient;
using System.Data;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class CSharpDataTableGenerator : CodeWriter
    {
        readonly EntityDefinition _entityDefinition;

        public CSharpDataTableGenerator(Context context, EntityDefinition entityDefinition)
            : base(context)
        {
            _entityDefinition = entityDefinition;
        }

        public EntityDefinition Entity => _entityDefinition;

        public void Run()
        {
            WriteLine("using System;");
            WriteLine("using System.Data;");
            WriteLine("using System.Data.Common;");
            WriteLine("using System.Collections.Generic;");
            WriteLine("using Microsoft.Data.SqlClient;");
            WriteLine("using Microsoft.SqlServer.Types;");
            WriteLine("using System.Data.SqlTypes;");
            
            var dataTypeNamespace = CSharpHelper.GetDataTypeNamespace(Entity);
            WriteLine($"using {dataTypeNamespace};");

            WriteLine();

            var dataTableNamespace = Entity.GetDataTableNamespace();
            WriteLine($"namespace {dataTableNamespace};");

            var persistentFields = Entity.PersistentFields;
            var persistentFieldCount = persistentFields.Count;

            var dataTableClassName = Entity.GetDataTableClassName();
            WriteLine();
            WriteLine($"public class {dataTableClassName}");
            WriteLine("{");

            WriteLine();
            WriteLine("    DataTable _dataTable;");
            WriteLine();
            WriteLine($"    public {dataTableClassName}(DataTable dataTable)");
            WriteLine("    {");
            WriteLine("        _dataTable = dataTable;");
            WriteLine("    }");

            WriteLine($"    public {dataTableClassName}()");
            WriteLine("    {");
            WriteLine("        _dataTable = CreateDataTable();");
            WriteLine("    }");

            WriteLine("    public DataTable DataTable => _dataTable;");
            WriteLine();

            WriteLine("    public static DataTable CreateDataTable( )");
            WriteLine("    {");
            WriteLine("        var dataTable = new DataTable();");
            WriteLine();
            for (int i = 0; i < persistentFieldCount; i++)
            {
                var field = persistentFields[i];
                var columnName = MsSqlHelper.GetDataTableColumnName(field);
                var columnType = CSharpHelper.GetNotNullableBaseType(field);
                var columnVariableName = CSharpHelper.GetInputArgumentName(field);
                WriteLine($"        var {columnVariableName}Column = new DataColumn(\"{columnName}\", typeof({columnType}));");
                if (!field.IsNullable)
                {
                    WriteLine($"        {columnVariableName}Column.AllowDBNull = false;");
                }
                WriteLine($"        dataTable.Columns.Add({columnVariableName}Column);");
            }

            WriteLine();
            WriteLine("        return dataTable;");
            WriteLine("    }");

            WriteLine();
            WriteLine("    public void AddRow( ");
            for (int i = 0; i < persistentFieldCount; i++)
            {
                var field = persistentFields[i];
                var argumentType = CSharpHelper.GetInputArgumentType(field);
                var argumentName = CSharpHelper.GetInputArgumentName(field);
                var comma = i < persistentFieldCount - 1 ? "," : string.Empty;
                WriteLine($"                        {argumentType} {argumentName}{comma}");

            }
            WriteLine("                        )");
            WriteLine("    {");
            WriteLine("        var row = _dataTable.NewRow();");
            for (int i = 0; i < persistentFieldCount; i++)
            {
                var field = persistentFields[i];
                var columnName = MsSqlHelper.GetDataTableColumnName(field);
                var argumentName = CSharpHelper.GetInputArgumentName(field);
                if (field.IsNullable)
                {
                    WriteLine($"        row[\"{columnName}\"] = (object?){argumentName} ?? DBNull.Value;");
                }
                else
                {
                    WriteLine($"        row[\"{columnName}\"] = {argumentName};");
                }
            }
            WriteLine("        _dataTable.Rows.Add(row);");
            WriteLine("    }");
            WriteLine();
            var dataTypeClassName = CSharpHelper.GetDataType(Entity);
            WriteLine($"    public void AddRow({dataTypeClassName} data)");
            WriteLine("    {");
            WriteLine("        var row = _dataTable.NewRow();");
            for (int i = 0; i < persistentFieldCount; i++)
            {
                var field = persistentFields[i];
                var columnName = MsSqlHelper.GetDataTableColumnName(field);
                var argumentName = CSharpHelper.GetMemberPropertyName(field);
                if (field.IsNullable)
                {
                    WriteLine($"        row[\"{columnName}\"] = (object?)data.{argumentName} ?? DBNull.Value;");
                }
                else
                {
                    WriteLine($"        row[\"{columnName}\"] = data.{argumentName};");
                }
            }
            WriteLine("        _dataTable.Rows.Add(row);");
            WriteLine("    }");
            WriteLine();

            WriteLine("    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)");
            WriteLine("    {");
            WriteLine("        var columnMappings = sqlBulkCopy.ColumnMappings;");
            for (int i = 0; i < persistentFieldCount; i++)
            {
                var field = persistentFields[i];
                var dataTableColumnName = MsSqlHelper.GetDataTableColumnName(field);
                var columnName = MsSqlHelper.GetColumnName(field);
                WriteLine($"        columnMappings.Add(\"{dataTableColumnName}\", \"{columnName}\");");
            }
            WriteLine("    }");

            WriteLine();
            var qualifiedTableName = MsSqlHelper.GetQualifiedTableOrViewName(Entity);
            WriteLine("    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)");
            WriteLine("    {");
            WriteLine("        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)");
            WriteLine("        {");
            WriteLine($"            DestinationTableName = destinationTableName ?? \"{qualifiedTableName}\"");
            WriteLine("        };");
            WriteLine("        AssignMapping(sqlBulkCopy);");
            WriteLine("        return sqlBulkCopy;");
            WriteLine("    }");
            WriteLine();
            WriteLine("}");


        }

    }


}
