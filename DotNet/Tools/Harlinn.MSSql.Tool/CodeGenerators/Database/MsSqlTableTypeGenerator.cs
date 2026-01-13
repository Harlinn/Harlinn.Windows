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

namespace Harlinn.MSSql.Tool.CodeGenerators.Database
{
    public class MsSqlTableTypeGenerator : CodeWriter
    {
        public MsSqlTableTypeGenerator(Context context) : base(context)
        {
        }

        public void Run()
        {
            var entities = Context.Project.Entities;

            foreach (var entity in entities)
            {
                WriteCreateTableType(entity);
            }
        }

        void WriteCreateTableType(EntityDefinition entity)
        {
            var tableTypeName = entity.GetTableType();
            var schemaName = entity.Owner!.Name;

            var qualifiedTableTypeName = $"[{schemaName}].[{tableTypeName}]";

            WriteLine("/*");
            WriteLine($" * {qualifiedTableTypeName}");
            WriteLine(" */");
            WriteLine($"CREATE TYPE {qualifiedTableTypeName} AS TABLE");
            WriteLine("(");
            foreach (var field in entity.PersistentFields)
            {
                WriteColumn(field);
            }
            WritePrimaryKey(entity);
            WriteLine(")");
            if (CanBeMemoryOptimized(entity))
            {
                WriteLine("WITH (MEMORY_OPTIMIZED = ON);");
            }
            WriteLine("go");
            WriteLine();
            
            WriteLine();
        }

        static bool CanBeMemoryOptimized(EntityDefinition entity)
        {
            foreach (var field in entity.PersistentFields)
            {
                if (MsSqlHelper.GetRawColumnType(field).Equals("[TEXT]", StringComparison.OrdinalIgnoreCase) ||
                    MsSqlHelper.GetRawColumnType(field).Equals("[NTEXT]", StringComparison.OrdinalIgnoreCase) ||
                    MsSqlHelper.GetRawColumnType(field).Equals("[IMAGE]", StringComparison.OrdinalIgnoreCase) ||
                    MsSqlHelper.GetRawColumnType(field).Equals("[XML]", StringComparison.OrdinalIgnoreCase) ||
                    MsSqlHelper.GetRawColumnType(field).Equals("[TIMESTAMP]", StringComparison.OrdinalIgnoreCase) ||
                    (field is GuidFieldDefinition guidFieldDefinition && guidFieldDefinition.IsRowGuid) ||
                    field is HierarchyIdFieldDefinition)
                {
                    return false;
                }
            }
            return true;
        }

        void WriteColumn(FieldDefinition field)
        {
            var columnName = MsSqlHelper.GetColumnName(field);
            var columnType = MsSqlHelper.GetRawColumnType(field);
            var fieldType = field.FieldType;
            if (fieldType == FieldType.String)
            {
                var stringField = (StringFieldDefinition)field;
                columnType = stringField.Size <= 0 ? "[nvarchar](max)" : $"[nvarchar]({stringField.Size})";
            }
            var columnNull = field.IsNullable ? "NULL" : "NOT NULL";
            WriteLine($"    {columnName} {columnType} {columnNull},");
            
        }

        static string IndexColumnList(IndexDefinition index)
        {
            var columnNames = index.Fields.Select(f => MsSqlHelper.GetColumnName(f.Definition!));
            return string.Join(", ", columnNames);
        }

        void WritePrimaryKey(EntityDefinition entity)
        {
            var primaryKey = entity.PrimaryKey;
            var primaryKeyName = primaryKey?.Name;
            var primaryKeyColumnList = IndexColumnList(primaryKey!);

            WriteLine($"    PRIMARY KEY NONCLUSTERED({primaryKeyColumnList}),");
            WriteLine($"    INDEX idxPrimary NONCLUSTERED({primaryKeyColumnList})");
        }


    }

}
