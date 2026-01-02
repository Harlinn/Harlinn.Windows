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


using Harlinn.MSSql.Tool.Input.Types;
using Microsoft.Data.SqlClient;

using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Import
{
    public static class ParameterExtensions
    {
        public static ParameterDefinition ToParameterDefinition(this SchemaTypes.Parameter parameter, SqlConnection sqlConnection)
        {
            if (parameter == null)
            {
                throw new ArgumentNullException(nameof(parameter));
            }
            var systemDataType = sqlConnection.GetSystemDataType(parameter);

            var parameterDescription = sqlConnection.GetParameterDescription(parameter.ObjectId, parameter.ParameterId);

            var typeName = parameter.TypeName!.ToLowerInvariant();
            switch (systemDataType)
            {
                case SystemDataType.Image:
                {
                    var result = new BinaryParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Text:
                {
                    var result = new StringParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.UniqueIdentifier:
                {
                    var result = new GuidParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Date:
                {
                    var result = new DateTimeParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Time:
                {
                    var result = new DateTimeParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.DateTime2:
                {
                    var result = new DateTimeParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.DateTimeOffset:
                {
                    var result = new DateTimeParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.TinyInt:
                {
                    var result = new ByteParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.SmallInt:
                {
                    var result = new Int16ParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Int:
                {
                    var result = new Int32ParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.SmallDateTime:
                {
                    var result = new DateTimeParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Real:
                {
                    var result = new SingleParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Money:
                {
                    var result = new DecimalParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.DateTime:
                {
                    var result = new DateTimeParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Float:
                {
                    var result = new DoubleParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.SqlVariant:
                {
                    var result = new SqlVariantParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.NText:
                {
                    var result = new StringParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Bit:
                {
                    var result = new BooleanParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Decimal:
                {
                    var result = new DecimalParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Numeric:
                {
                    var result = new DecimalParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.SmallMoney:
                {
                    var result = new DecimalParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.BigInt:
                {
                    var result = new Int64ParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.HierarchyId:
                {
                    var result = new HierarchyIdParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Geometry:
                {
                    var result = new GeometryParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Geography:
                {
                    var result = new GeographyParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.VarBinary:
                {
                    var result = new BinaryParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.VarChar:
                {
                    var result = new StringParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Binary:
                {
                    var result = new BinaryParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Char:
                {
                    var result = new StringParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Timestamp:
                {
                    var result = new DateTimeParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.NVarChar:
                {
                    var result = new StringParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.NChar:
                {
                    var result = new StringParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.Xml:
                {
                    var result = new XmlParameterDefinition(parameter, parameterDescription);
                    return result;
                }
                case SystemDataType.SysName:
                {
                    var result = new StringParameterDefinition(systemDataType, parameter, parameterDescription);
                    return result;
                }
                default:
                {
                    throw new NotSupportedException($"The field system type '{systemDataType}' is not supported.");
                }
            }
        }
    }
}
