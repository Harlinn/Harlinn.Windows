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


using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Harlinn.MSSql.Tool.Input.Types;
using Microsoft.Data.SqlClient;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Import
{
    public static class ColumnExtensions
    {
        public static FieldDefinition ToFieldDefinition(this SchemaTypes.Column column, SqlConnection sqlConnection)
        {
            var identityColumn = sqlConnection.GetIdentityColumn(column);
            var defaultConstraint = sqlConnection.GetDefaultConstraint(column);
            var computedColumn = sqlConnection.GetComputedColumn(column);
            FieldComputed? fieldComputed = computedColumn != null ? new FieldComputed(computedColumn.ComputedDefinition, computedColumn.IsPersisted) : null;
            var checkConstraints = sqlConnection.GetCheckConstraints(column);
            List<FieldCheckConstraint>? fieldCheckConstraints = null;

            if (checkConstraints != null)
            {
                fieldCheckConstraints = new List<FieldCheckConstraint>();
                foreach (var constraint in checkConstraints)
                {
                    fieldCheckConstraints.Add(new FieldCheckConstraint(constraint));
                }
            }

            var typeName = column.TypeName.ToLowerInvariant();
            switch (typeName)
            {
                case "image":
                {
                    var result = new BinaryFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = -1
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "text":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = -1
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "uniqueidentifier":
                {
                    var result = new GuidFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if(defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint( defaultConstraint.Name, defaultConstraint.Definition );
                    }
                    return result;
                }
                case "date":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "time":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "datetime2":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "datetimeoffset":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "tinyint":
                {
                    var result = new ByteFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    if(identityColumn != null)
                    {
                        var seed = Convert.ToByte(identityColumn.SeedValue);
                        var increment = Convert.ToByte(identityColumn.IncrementValue);
                        result.Identity = new Identity<byte>(seed, increment);
                    }
                    return result;
                }
                case "smallint":
                {
                    var result = new Int16FieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToInt16(identityColumn.SeedValue);
                        var increment = Convert.ToInt16(identityColumn.IncrementValue);
                        result.Identity = new Identity<short>(seed, increment);
                    }
                    return result;
                }
                case "int":
                {
                    var result = new Int32FieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToInt32(identityColumn.SeedValue);
                        var increment = Convert.ToInt32(identityColumn.IncrementValue);
                        result.Identity = new Identity<int>(seed, increment);
                    }
                    return result;
                }
                case "smalldatetime":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "real":
                {
                    var result = new SingleFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        Precision = column.Precision,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "money":
                {
                    var result = new DecimalFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "datetime":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "float":
                {
                    var result = new DoubleFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        Precision = column.Precision,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "sql_variant":
                {
                    var result = new SqlVariantFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "ntext":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = column.MaxLength / 2
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "bit":
                {
                    var result = new BooleanFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "decimal":
                {
                    var result = new DecimalFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        Precision = column.Precision,
                        Scale = column.Scale,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToDecimal(identityColumn.SeedValue);
                        var increment = Convert.ToDecimal(identityColumn.IncrementValue);
                        result.Identity = new Identity<decimal>(seed, increment);
                    }
                    return result;
                }
                case "numeric":
                {
                    var result = new DecimalFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        Precision = column.Precision,
                        Scale = column.Scale,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToDecimal(identityColumn.SeedValue);
                        var increment = Convert.ToDecimal(identityColumn.IncrementValue);
                        result.Identity = new Identity<decimal>(seed, increment);
                    }
                    return result;
                }
                case "smallmoney":
                {
                    var result = new DecimalFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "bigint":
                {
                    var result = new Int64FieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToInt64(identityColumn.SeedValue);
                        var increment = Convert.ToInt64(identityColumn.IncrementValue);
                        result.Identity = new Identity<long>(seed, increment);
                    }
                    return result;
                }
                case "hierarchyid":
                {
                    var result = new HierarchyIdFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "geometry":
                {
                    var result = new GeometryFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "geography":
                {
                    var result = new GeographyFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "varbinary":
                {
                    var result = new BinaryFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "varchar":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                break;
                case "binary":
                {
                    var result = new BinaryFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "char":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = column.MaxLength
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "timestamp":
                {
                    var result = new DateTimeFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "nvarchar":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = column.MaxLength / 2
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "nchar":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = column.MaxLength / 2
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "xml":
                {
                    var result = new XmlFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                }
                case "sysname":
                {
                    var result = new StringFieldDefinition
                    {
                        Name = column.Name,
                        IsNullable = column.IsNullable,
                        Computed = fieldComputed,
                        Checks = fieldCheckConstraints,
                        DatabaseType = typeName,
                        Size = column.MaxLength / 2
                    };
                    if (defaultConstraint != null)
                    {
                        result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                    }
                    return result;
                } 
                default:
                {
                    return column.ToUserTypeFieldDefinition(sqlConnection, fieldComputed, fieldCheckConstraints, identityColumn, defaultConstraint);
                }
                
            }
        }


        static FieldDefinition ToUserTypeFieldDefinition(this SchemaTypes.Column column, SqlConnection sqlConnection, FieldComputed? fieldComputed, List<FieldCheckConstraint>? fieldCheckConstraints, IdentityColumn? identityColumn, DefaultConstraint? defaultConstraint)
        {
            var typeName = column.TypeName.ToLowerInvariant();
            var schemaObject = sqlConnection.GetSchemaObject(column.ObjectId);
            int schemaId = 0;
            DatabaseType? databaseType = null;
            SystemType systemType = SystemType.Unknown;
            if (schemaObject != null)
            {
                /*var*/ schemaId = schemaObject.SchemaId;
                /*var*/ databaseType = sqlConnection.GetDatabaseType(schemaId, typeName);
                if(databaseType == null)
                {
                    databaseType = sqlConnection.GetDatabaseType(typeName);
                }
                if (databaseType != null)
                {
                    /*var*/ systemType = (SystemType)databaseType.SystemTypeId;
                    switch (systemType)
                    {
                        case SystemType.Image:
                        {
                            var result = new BinaryFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = -1
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Text:
                        {
                            var result = new StringFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = -1
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Uniqueidentifier:
                        {
                            var result = new GuidFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Date:
                        {
                            var result = new DateTimeFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Time:
                        {
                            var result = new DateTimeFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.DateTime2:
                        {
                            var result = new DateTimeFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.DateTimeOffset:
                        {
                            var result = new DateTimeFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.TinyInt:
                        {
                            var result = new ByteFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            if (identityColumn != null)
                            {
                                var seed = Convert.ToByte(identityColumn.SeedValue);
                                var increment = Convert.ToByte(identityColumn.IncrementValue);
                                result.Identity = new Identity<byte>(seed, increment);
                            }
                            return result;
                        }
                        case SystemType.SmallInt:
                        {
                            var result = new Int16FieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            if (identityColumn != null)
                            {
                                var seed = Convert.ToInt16(identityColumn.SeedValue);
                                var increment = Convert.ToInt16(identityColumn.IncrementValue);
                                result.Identity = new Identity<short>(seed, increment);
                            }
                            return result;
                        }
                        case SystemType.Int:
                        {
                            var result = new Int32FieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            if (identityColumn != null)
                            {
                                var seed = Convert.ToInt32(identityColumn.SeedValue);
                                var increment = Convert.ToInt32(identityColumn.IncrementValue);
                                result.Identity = new Identity<int>(seed, increment);
                            }
                            return result;
                        }
                        case SystemType.SmallDateTime:
                        {
                            var result = new DateTimeFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Real:
                        {
                            var result = new SingleFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                Precision = column.Precision,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Money:
                        {
                            var result = new DecimalFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.DateTime:
                        {
                            var result = new DateTimeFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Float:
                        {
                            var result = new DoubleFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                Precision = column.Precision,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.SqlVariant:
                        {
                            var result = new SqlVariantFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.NText:
                        {
                            var result = new StringFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = column.MaxLength / 2
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Bit:
                        {
                            var result = new BooleanFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Decimal:
                        {
                            var result = new DecimalFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                Precision = column.Precision,
                                Scale = column.Scale,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            if (identityColumn != null)
                            {
                                var seed = Convert.ToDecimal(identityColumn.SeedValue);
                                var increment = Convert.ToDecimal(identityColumn.IncrementValue);
                                result.Identity = new Identity<decimal>(seed, increment);
                            }
                            return result;
                        }
                        case SystemType.Numeric:
                        {
                            var result = new DecimalFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                Precision = column.Precision,
                                Scale = column.Scale,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            if (identityColumn != null)
                            {
                                var seed = Convert.ToDecimal(identityColumn.SeedValue);
                                var increment = Convert.ToDecimal(identityColumn.IncrementValue);
                                result.Identity = new Identity<decimal>(seed, increment);
                            }
                            return result;
                        }
                        case SystemType.SmallMoney:
                        {
                            var result = new DecimalFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.BigInt:
                        {
                            var result = new Int64FieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            if (identityColumn != null)
                            {
                                var seed = Convert.ToInt64(identityColumn.SeedValue);
                                var increment = Convert.ToInt64(identityColumn.IncrementValue);
                                result.Identity = new Identity<long>(seed, increment);
                            }
                            return result;
                        }
                        case SystemType.HierarchyId:
                        {
                            var result = new HierarchyIdFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        /*
                        case SystemType.Geometry:
                        {
                            var result = new GeometryFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Geography:
                        {
                            var result = new GeographyFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        */
                        case SystemType.VarBinary:
                        {
                            var result = new BinaryFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = column.MaxLength
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.VarChar:
                        {
                            var result = new StringFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = column.MaxLength
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Binary:
                        {
                            var result = new BinaryFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = column.MaxLength
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Char:
                        {
                            var result = new StringFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = column.MaxLength
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Timestamp:
                        {
                            var result = new DateTimeFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.NVarChar:
                        {
                            var result = new StringFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = column.MaxLength / 2
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.NChar:
                        {
                            var result = new StringFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = column.MaxLength / 2
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        case SystemType.Xml:
                        {
                            var result = new XmlFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        /*
                        case SystemType.SysName:
                        {
                            var result = new StringFieldDefinition
                            {
                                Name = column.Name,
                                IsNullable = column.IsNullable,
                                Computed = fieldComputed,
                                Checks = fieldCheckConstraints,
                                DatabaseType = typeName,
                                Size = column.MaxLength / 2
                            };
                            if (defaultConstraint != null)
                            {
                                result.DefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
                            }
                            return result;
                        }
                        */
                        default:
                        {
                            throw new NotSupportedException($"User defined type '{typeName}' with system type '{systemType}' is not supported.");
                        }
                    }
                }
            }
            throw new NotSupportedException($"Type '{typeName}' is not supported.");
        }


    }
}
