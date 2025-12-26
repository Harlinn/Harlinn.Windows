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
using System.Diagnostics;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Import
{
    public static class ColumnExtensions
    {


        public static FieldDefinition ToFieldDefinition(this SchemaTypes.Column column, SqlConnection sqlConnection)
        {
            if (column == null)
            {
                throw new ArgumentNullException(nameof(column));
            }
            var systemColumnType = sqlConnection.GetSystemColumnType(column);

            var identityColumn = sqlConnection.GetIdentityColumn(column);
            var defaultConstraint = sqlConnection.GetDefaultConstraint(column);

            FieldDefaultConstraint? fieldDefaultConstraint = null;
            if (defaultConstraint != null)
            {
                fieldDefaultConstraint = new FieldDefaultConstraint(defaultConstraint.Name, defaultConstraint.Definition);
            }

            var computedColumn = sqlConnection.GetComputedColumn(column);
            FieldComputed? fieldComputed = computedColumn != null ? new FieldComputed(computedColumn.Definition, computedColumn.IsPersisted) : null;
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
            switch (systemColumnType)
            {
                case SystemColumnType.Image:
                {
                    var result = new BinaryFieldDefinition(systemColumnType,column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Text:
                {
                    var result = new StringFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.UniqueIdentifier:
                {
                    var result = new GuidFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Date:
                {
                    var result = new DateTimeFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Time:
                {
                    var result = new DateTimeFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.DateTime2:
                {
                    var result = new DateTimeFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.DateTimeOffset:
                {
                    var result = new DateTimeFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.TinyInt:
                {
                    var result = new ByteFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    if(identityColumn != null)
                    {
                        var seed = Convert.ToByte(identityColumn.SeedValue);
                        var increment = Convert.ToByte(identityColumn.IncrementValue);
                        result.Identity = new Identity<byte>(seed, increment);
                    }
                    return result;
                }
                case SystemColumnType.SmallInt:
                {
                    var result = new Int16FieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToInt16(identityColumn.SeedValue);
                        var increment = Convert.ToInt16(identityColumn.IncrementValue);
                        result.Identity = new Identity<short>(seed, increment);
                    }
                    return result;
                }
                case SystemColumnType.Int:
                {
                    var result = new Int32FieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    if (identityColumn != null)
                    {
                        var seed = 1;
                        var increment = 1;
                        if (identityColumn.SeedValue is not DBNull)
                        {
                            seed = Convert.ToInt32(identityColumn.SeedValue);
                        }
                        if (identityColumn.IncrementValue is not DBNull)
                        {
                            increment = Convert.ToInt32(identityColumn.IncrementValue);
                        }
                        result.Identity = new Identity<int>(seed, increment);
                    }
                    return result;
                }
                case SystemColumnType.SmallDateTime:
                {
                    var result = new DateTimeFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Real:
                {
                    var result = new SingleFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Money:
                {
                    var result = new DecimalFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.DateTime:
                {
                    var result = new DateTimeFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Float:
                {
                    var result = new DoubleFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.SqlVariant:
                {
                    var result = new SqlVariantFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.NText:
                {
                    var result = new StringFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Bit:
                {
                    var result = new BooleanFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Decimal:
                {
                    var result = new DecimalFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToDecimal(identityColumn.SeedValue);
                        var increment = Convert.ToDecimal(identityColumn.IncrementValue);
                        result.Identity = new Identity<decimal>(seed, increment);
                    }
                    return result;
                }
                case SystemColumnType.Numeric:
                {
                    var result = new DecimalFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToDecimal(identityColumn.SeedValue);
                        var increment = Convert.ToDecimal(identityColumn.IncrementValue);
                        result.Identity = new Identity<decimal>(seed, increment);
                    }
                    return result;
                }
                case SystemColumnType.SmallMoney:
                {
                    var result = new DecimalFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.BigInt:
                {
                    var result = new Int64FieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    if (identityColumn != null)
                    {
                        var seed = Convert.ToInt64(identityColumn.SeedValue);
                        var increment = Convert.ToInt64(identityColumn.IncrementValue);
                        result.Identity = new Identity<long>(seed, increment);
                    }
                    return result;
                }
                case SystemColumnType.HierarchyId:
                {
                    var result = new HierarchyIdFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Geometry:
                {
                    var result = new GeometryFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Geography:
                {
                    var result = new GeographyFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.VarBinary:
                {
                    var result = new BinaryFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.VarChar:
                {
                    var result = new StringFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Binary:
                {
                    var result = new BinaryFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Char:
                {
                    var result = new StringFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Timestamp:
                {
                    var result = new DateTimeFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.NVarChar:
                {
                    var result = new StringFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.NChar:
                {
                    var result = new StringFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.Xml:
                {
                    var result = new XmlFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                }
                case SystemColumnType.SysName:
                {
                    var result = new StringFieldDefinition(systemColumnType, column, fieldDefaultConstraint, fieldComputed, fieldCheckConstraints);
                    return result;
                } 
                default:
                {
                    throw new NotSupportedException($"The field system type '{systemColumnType}' is not supported.");
                }
            }
        }



    }
}
