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
                    {
                        var stringFieldDefinition = fieldDefinition as StringFieldDefinition;

                        var databaseType = fieldDefinition.DatabaseType!.ToLowerInvariant();

                        if (databaseType == "nvarchar" || databaseType == "varchar" || databaseType == "char" || databaseType == "nchar")
                        {
                            if (stringFieldDefinition!.Size > 0 && stringFieldDefinition.Size <= 4000)
                            {
                                return $"[{databaseType}]({stringFieldDefinition.Size})";
                            }
                            return $"[{databaseType}](max)";
                        }
                        return $"[{databaseType}]";
                    }
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
                {
                    var singleFieldDefinition = (SingleFieldDefinition)fieldDefinition;
                    if (singleFieldDefinition.Precision != 24)
                    {
                        return $"[float]({singleFieldDefinition.Precision})";
                    }
                    return "[real]";
                }
                case FieldType.Double:
                {
                    var doubleFieldDefinition = (DoubleFieldDefinition)fieldDefinition;
                    if (doubleFieldDefinition.Precision != 53)
                    {
                        return $"[float]({doubleFieldDefinition.Precision})";
                    }
                    return "[float]";
                }
                case FieldType.Decimal:
                    var decimalFieldDefinition = (DecimalFieldDefinition)fieldDefinition;
                    if (decimalFieldDefinition!.Precision != 18 || decimalFieldDefinition.Scale != 0)
                    {
                        return $"[decimal]({decimalFieldDefinition.Precision}, {decimalFieldDefinition.Scale})";
                    }
                    return "[decimal]";
                case FieldType.DateTime:
                    return "[datetime2]";
                case FieldType.TimeSpan:
                    return "[bigint]";
                case FieldType.Guid:
                    return "[uniqueidentifier]";
                case FieldType.String:
                    var stringFieldDefinition = (StringFieldDefinition)fieldDefinition;
                    if (stringFieldDefinition!.Size > 0 && stringFieldDefinition.Size <= 4000)
                    {
                        return $"[nvarchar]({stringFieldDefinition.Size})";
                    }
                    return "[nvarchar](max)";
                case FieldType.Binary:
                    var binaryFieldDefinition = (BinaryFieldDefinition)fieldDefinition;
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

        public static string GetColumnIdentity(FieldDefinition fieldDefinition)
        {
            string result = string.Empty;
            var fieldType = fieldDefinition.FieldType;
            switch (fieldType)
            {
                case FieldType.Byte:
                {
                    var byteFieldDefinition = (ByteFieldDefinition)fieldDefinition;
                    var identity = byteFieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;
                case FieldType.SByte:
                {
                    var sbyteFieldDefinition = (SByteFieldDefinition)fieldDefinition;
                    var identity = sbyteFieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;
                case FieldType.Int16:
                {
                    var int16FieldDefinition = (Int16FieldDefinition)fieldDefinition;
                    var identity = int16FieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;
                case FieldType.UInt16:
                {
                    var uint16FieldDefinition = (UInt16FieldDefinition)fieldDefinition;
                    var identity = uint16FieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;
                case FieldType.Int32:
                {
                    var int32FieldDefinition = (Int32FieldDefinition)fieldDefinition;
                    var identity = int32FieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;
                case FieldType.UInt32:
                {
                    var uint32FieldDefinition = (UInt32FieldDefinition)fieldDefinition;
                    var identity = uint32FieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;
                case FieldType.Int64:
                {
                    var int64FieldDefinition = (Int64FieldDefinition)fieldDefinition;
                    var identity = int64FieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;
                case FieldType.UInt64:
                {
                    var uint64FieldDefinition = (UInt64FieldDefinition)fieldDefinition;
                    var identity = uint64FieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;
                case FieldType.Decimal:
                {
                    var decimalFieldDefinition = (DecimalFieldDefinition)fieldDefinition;
                    var identity = decimalFieldDefinition.Identity;
                    if (identity != null)
                    {
                        if (identity.Seed != 1 || identity.Increment != 1)
                        {
                            result = $"IDENTITY({identity.Seed},{identity.Increment})";
                        }
                        else
                        {
                            result = "IDENTITY";
                        }
                    }
                }
                break;

            }
            return result;
        }


        public static bool IsOutputParameter(FieldDefinition fieldDefinition)
        {
            return fieldDefinition.IsIdentity || fieldDefinition.IsNewId;
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
            if (string.IsNullOrEmpty(fieldDefinition.ColumnName))
            {
                return $"[{fieldDefinition.Name}]";
            }
            else
            {
                return $"[{fieldDefinition.ColumnName}]";
            }
        }

        public static string GetParameterName(FieldDefinition fieldDefinition)
        {
            return $"@{fieldDefinition.Name.FirstToLower()}";
        }

        public static string GetQualifiedTableOrViewName(RowSourceDefinition rowSourceDefinition)
        {
            var schemaName = rowSourceDefinition.Owner!.Name;
            var tableName = GetTableOrViewName(rowSourceDefinition);
            return $"[{schemaName}].[{tableName}]";
        }

        public static string GetTableOrViewName(RowSourceDefinition rowSourceDefinition)
        {
            if (rowSourceDefinition is ViewDefinition viewDefinition)
            {
                return string.IsNullOrEmpty(viewDefinition.View) ? viewDefinition.Name : viewDefinition.View;
            }
            else if (rowSourceDefinition is EntityDefinition entityDefinition)
            {
                return string.IsNullOrEmpty(entityDefinition.Table) ? entityDefinition.Name : entityDefinition.Table;
            }
            return rowSourceDefinition.Name;
        }


        public static string GetShortName(RowSourceDefinition entityDefinition)
        {
            return entityDefinition.ShortName!;
        }

        public static string GetInsertProcedureName(EntityDefinition entityDefinition)
        {
            var tableName = GetTableOrViewName(entityDefinition);
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
            var tableName = GetTableOrViewName(entityDefinition);
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
            var tableName = GetTableOrViewName(entityDefinition);
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
            var tableName = GetTableOrViewName(entityDefinition);
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
            var tableName = GetTableOrViewName(entityDefinition);
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
            var tableName = GetTableOrViewName(entityDefinition);
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
