using System;
using System.Collections.Generic;
using System.Text;
using Harlinn.Common.Core.Net;
using Harlinn.MSSql.Tool.Input.Types;

namespace Harlinn.MSSql.Tool.CodeGenerators.Database
{
    public class MsSqlHelper
    {
        public static string GetRawColumnType(FieldDefinition fieldDefinition)
        {
            var fieldType = fieldDefinition.FieldType;
            if (!string.IsNullOrEmpty(fieldDefinition.DatabaseType))
            {
                switch (fieldType)
                {
                    case FieldType.String:
                        var stringFieldDefinition = fieldDefinition as StringFieldDefinition;
                        if (stringFieldDefinition!.Size > 0 && stringFieldDefinition.Size <= 4000)
                        {
                            return $"[{fieldDefinition.DatabaseType}]({stringFieldDefinition.Size})";
                        }
                        return $"[{fieldDefinition.DatabaseType}](max)";
                    case FieldType.Binary:
                        var binaryFieldDefinition = fieldDefinition as BinaryFieldDefinition;
                        if (binaryFieldDefinition!.Size > 0 && binaryFieldDefinition.Size <= 8000)
                        {
                            return $"[{fieldDefinition.DatabaseType}]({binaryFieldDefinition.Size})";
                        }
                        return $"[{fieldDefinition.DatabaseType}](max)";
                    default:
                        return $"[{fieldDefinition.DatabaseType}]";
                }
            }

            switch (fieldType)
            {
                case FieldType.Boolean:
                    return "[bit]";
                case FieldType.Byte:
                    return "[tinyint]";
                case FieldType.SByte:
                    return "[smallint]";
                case FieldType.Char:
                    return "[nchar(1)]";
                case FieldType.Int16:
                    return "[smallint]";
                case FieldType.UInt16:
                    return "[smallint]";
                case FieldType.Int32:
                    return "[int]";
                case FieldType.UInt32:
                    return "[int]";
                case FieldType.Int64:
                    return "[bigint]";
                case FieldType.UInt64:
                    return "[bigint]";
                case FieldType.Single:
                    return "[real]";
                case FieldType.Double:
                    return "[float]";
                case FieldType.Decimal:
                    return "[decimal](18, 2)";
                case FieldType.DateTime:
                    return "[datetime2]";
                case FieldType.TimeSpan:
                    return "[bigint]";
                case FieldType.Guid:
                    return "[uniqueidentifier]";
                case FieldType.String:
                    var stringFieldDefinition = fieldDefinition as StringFieldDefinition;
                    if (stringFieldDefinition!.Size > 0 && stringFieldDefinition.Size <= 4000)
                    {
                        return $"[nvarchar]({stringFieldDefinition.Size})";
                    }
                    return "[nvarchar](max)";
                case FieldType.Binary:
                    var binaryFieldDefinition = fieldDefinition as BinaryFieldDefinition;
                    if (binaryFieldDefinition!.Size > 0 && binaryFieldDefinition.Size <= 8000)
                    {
                        return $"[varbinary]({binaryFieldDefinition.Size})";
                    }
                    return "[varbinary](max)";
                case FieldType.SqlVariant:
                    return "[sql_variant]";
                case FieldType.HierarchyId:
                    return "[hierarchyid]";
                case FieldType.Geometry:
                    return "[geometry]";
                case FieldType.Geography:
                    return "[geography]";
                case FieldType.Xml:
                    return "[xml]";
                default:
                    throw new NotSupportedException($"Field type {fieldType} is not supported.");
            }
        }

        public static string GetColumnType(FieldDefinition fieldDefinition)
        {
            var rawType = GetRawColumnType(fieldDefinition);
            var isNullable = fieldDefinition.IsNullable;
            if (isNullable)
            {
                return $"{rawType} NULL";
            }
            else
            {
                return $"{rawType} NOT NULL";
            }
        }

        public static string GetColumnName(FieldDefinition fieldDefinition)
        {
            return $"[{fieldDefinition.Name}]";
        }

        public static string GetParameterName(FieldDefinition fieldDefinition)
        {
            return $"@{fieldDefinition.Name.FirstToLower()}";
        }

        public static string GetQualifiedTableName(EntityDefinition entityDefinition)
        {
            var schemaName = entityDefinition.Owner!.Name;
            var tableName = GetTableName(entityDefinition);
            return $"[{schemaName}].[{tableName}]";
        }

        public static string GetTableName(EntityDefinition entityDefinition)
        {
            return string.IsNullOrEmpty(entityDefinition.Table) ? entityDefinition.Name : entityDefinition.Table;
        }


        public static string GetShortName(EntityDefinition entityDefinition)
        {
            return entityDefinition.ShortName!;
        }

        public static string GetInsertProcedureName(EntityDefinition entityDefinition)
        {
            var tableName = GetTableName(entityDefinition);
            return $"[Insert{tableName}]";
        }

        public static string GetQualifiedInsertProcedureName(EntityDefinition entityDefinition)
        {
            
            var schemaName = entityDefinition.Owner!.Name;
            var procedureName = GetInsertProcedureName(entityDefinition);
            return $"[{schemaName}].{procedureName}";
        }

        public static string GetInsert1ProcedureName(EntityDefinition entityDefinition)
        {
            var tableName = GetTableName(entityDefinition);
            return $"[Insert1{tableName}]";
        }

        public static string GetQualifiedInsert1ProcedureName(EntityDefinition entityDefinition)
        {
            var schemaName = entityDefinition.Owner!.Name;
            var procedureName = GetInsert1ProcedureName(entityDefinition);
            return $"[{schemaName}].{procedureName}";
        }


        public static string GetUpdateProcedureName(EntityDefinition entityDefinition)
        {
            var tableName = GetTableName(entityDefinition);
            return $"[Update{tableName}]";
        }

        public static string GetQualifiedUpdateProcedureName(EntityDefinition entityDefinition)
        {

            var schemaName = entityDefinition.Owner!.Name;
            var procedureName = GetUpdateProcedureName(entityDefinition);
            return $"[{schemaName}].{procedureName}";
        }

        public static string GetUpdate1ProcedureName(EntityDefinition entityDefinition)
        {
            var tableName = GetTableName(entityDefinition);
            return $"[Update1{tableName}]";
        }

        public static string GetQualifiedUpdate1ProcedureName(EntityDefinition entityDefinition)
        {

            var schemaName = entityDefinition.Owner!.Name;
            var procedureName = GetUpdate1ProcedureName(entityDefinition);
            return $"[{schemaName}].{procedureName}";
        }

        public static string GetUpdate2ProcedureName(EntityDefinition entityDefinition)
        {
            var tableName = GetTableName(entityDefinition);
            return $"[Update2{tableName}]";
        }

        public static string GetQualifiedUpdate2ProcedureName(EntityDefinition entityDefinition)
        {

            var schemaName = entityDefinition.Owner!.Name;
            var procedureName = GetUpdate2ProcedureName(entityDefinition);
            return $"[{schemaName}].{procedureName}";
        }



        public static string GetDeleteProcedureName(EntityDefinition entityDefinition)
        {
            var tableName = GetTableName(entityDefinition);
            return $"[Delete{tableName}]";
        }

        public static string GetQualifiedDeleteProcedureName(EntityDefinition entityDefinition)
        {

            var schemaName = entityDefinition.Owner!.Name;
            var procedureName = GetDeleteProcedureName(entityDefinition);
            return $"[{schemaName}].{procedureName}";
        }

        internal static object GetPrimaryKeyCondition(EntityDefinition entityDefinition)
        {
            var primaryKeyFields = entityDefinition.PrimaryKeyFields;
            var sb = new StringBuilder();
            for (int i = 0; i < primaryKeyFields.Count; i++)
            {
                var field = primaryKeyFields[i];
                if (i > 0)
                {
                    sb.Append(" AND ");
                }
                sb.AppendFormat("{0} = {1}", GetColumnName(field), GetParameterName(field));
            }
            return sb.ToString();
        }
    }
}
