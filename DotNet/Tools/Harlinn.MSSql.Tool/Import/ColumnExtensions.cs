/*
   Copyright 2024-2025 Espen Harlinn

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


using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Harlinn.MSSql.Tool.Input.Types;

namespace Harlinn.MSSql.Tool.Import
{
    public static class ColumnExtensions
    {
        public static FieldDefinition ToFieldDefinition(this SchemaTypes.Column column)
        {
            var typeName = column.TypeName.ToLowerInvariant();
            switch (typeName)
            {
                case "image":
                {
                    var result = new BinaryFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = -1
                    };
                    return result;
                }
                case "text":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = -1
                    };
                    return result;
                }
                case "uniqueidentifier":
                {
                    var result = new GuidFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "date":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "time":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "datetime2":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "datetimeoffset":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "tinyint":
                {
                    var result = new ByteFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "smallint":
                {
                    var result = new Int16FieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "int":
                {
                    var result = new Int32FieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "smalldatetime":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "real":
                {
                    var result = new SingleFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "money":
                {
                    var result = new DecimalFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "datetime":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "float":
                {
                    var result = new DoubleFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "sql_variant":
                {
                    var result = new SqlVariantFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                break;
                case "ntext":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    return result;
                }
                case "bit":
                {
                    var result = new BooleanFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "decimal":
                {
                    var result = new DecimalFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "numeric":
                {
                    var result = new DecimalFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "smallmoney":
                {
                    var result = new DecimalFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "bigint":
                {
                    var result = new Int64FieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "hierarchyid":
                {
                    var result = new HierarchyIdFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "geometry":
                {
                    var result = new GeometryFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "geography":
                {
                    var result = new GeographyFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "varbinary":
                {
                    var result = new BinaryFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    return result;
                }
                case "varchar":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    return result;
                }
                break;
                case "binary":
                {
                    var result = new BinaryFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    return result;
                }
                case "char":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    return result;
                }
                case "timestamp":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "nvarchar":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    return result;
                }
                case "nchar":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    return result;
                }
                case "xml":
                {
                    var result = new XmlFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName
                    };
                    return result;
                }
                case "sysname":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    return result;
                } 
                default:
                    throw new NotSupportedException($"Type '{typeName}' is not supported.");
            }
        }


    }
}
