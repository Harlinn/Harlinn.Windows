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

using Harlinn.Common.Core.Net;
using Harlinn.MSSql.Tool.Input.Types;
using System.Text;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class  CSharpHelper
    {
        static readonly CSharpKeyWords keyWords = new CSharpKeyWords();

        public static string GetNotNullableBaseType(FieldDefinition fieldDefinition)
        {
            string result = "<unknown>";
            var fieldType = fieldDefinition.FieldType;
            switch (fieldType)
            {
                case FieldType.Boolean:
                {
                    result = "bool";
                }
                break;
                case FieldType.SByte:
                {
                    result = "sbyte";
                }
                break;
                case FieldType.Byte:
                {
                    result = "byte";
                }
                break;
                case FieldType.Int16:
                {
                    result = "short";
                }
                break;
                case FieldType.UInt16:
                {
                    result = "ushort";
                }
                break;
                case FieldType.Int32:
                {
                    result = "int";
                }
                break;
                case FieldType.UInt32:
                {
                    result = "uint";
                }
                break;
                case FieldType.Int64:
                {
                    result = "long";
                }
                break;
                case FieldType.UInt64:
                {
                    result = "ulong";
                }
                break;
                case FieldType.Single:
                {
                    result = "float";
                }
                break;
                case FieldType.Double:
                {
                    result = "double";
                }
                break;
                case FieldType.DateTime:
                {
                    result = "DateTime";
                }
                break;
                case FieldType.TimeSpan:
                {
                    result = "TimeSpan";
                }
                break;
                case FieldType.Guid:
                {
                    result = "Guid";
                }
                break;
                case FieldType.String:
                {
                    result = "string";
                }
                break;
                case FieldType.Binary:
                {
                    result = "byte[]";
                }
                break;
                case FieldType.Unknown:
                    break;
                case FieldType.Char:
                    result = "string";
                    break;
                case FieldType.Decimal:
                    result = "decimal";
                    break;
                case FieldType.SqlVariant:
                    result = "object";
                    break;
                case FieldType.HierarchyId:
                    result = "SqlHierarchyId";
                    break;
                case FieldType.Geometry:
                    result = "SqlGeometry";
                    break;
                case FieldType.Geography:
                    result = "SqlGeography";
                    break;
                case FieldType.Xml:
                    result = "SqlXml";
                    break;
                case FieldType.Object:
                    result = "object";
                    break;
            }

            return result;
        }


        public static string GetNotNullableBaseType(PropertyDefinition propertyDefinition)
        {
            string result = "<unknown>";
            var fieldType = propertyDefinition.Kind;
            switch (fieldType)
            {
                case PropertyKind.Boolean:
                {
                    result = "bool";
                }
                break;
                case PropertyKind.SByte:
                {
                    result = "sbyte";
                }
                break;
                case PropertyKind.Byte:
                {
                    result = "byte";
                }
                break;
                case PropertyKind.Char:
                {
                    result = "char";
                }
                break;
                case PropertyKind.Int16:
                {
                    result = "short";
                }
                break;
                case PropertyKind.UInt16:
                {
                    result = "ushort";
                }
                break;
                case PropertyKind.Int32:
                {
                    result = "int";
                }
                break;
                case PropertyKind.UInt32:
                {
                    result = "uint";
                }
                break;
                case PropertyKind.Int64:
                {
                    result = "long";
                }
                break;
                case PropertyKind.UInt64:
                {
                    result = "ulong";
                }
                break;
                case PropertyKind.Single:
                {
                    result = "float";
                }
                break;
                case PropertyKind.Double:
                {
                    result = "double";
                }
                break;
                case PropertyKind.Decimal:
                {
                    result = "decimal";
                }
                break;
                case PropertyKind.DateTime:
                {
                    result = "DateTime";
                }
                break;
                case PropertyKind.TimeSpan:
                {
                    result = "TimeSpan";
                }
                break;
                case PropertyKind.Guid:
                {
                    result = "Guid";
                }
                break;
                case PropertyKind.String:
                {
                    result = "string";
                }
                break;
                case PropertyKind.Binary:
                {
                    result = "byte[]";
                }
                break;
                case PropertyKind.Enum:
                {
                    var enumPropertyDefinition = propertyDefinition as EnumPropertyDefinition;
                    var enumDefinition = enumPropertyDefinition?.Type;
                    if (enumDefinition != null)
                    {
                        result = enumDefinition.Name;
                    }
                    else
                    {
                        throw new InvalidOperationException($"Enum property '{propertyDefinition.Name}' does not have a type defined.");
                    }
                }
                break;
                case PropertyKind.Object:
                {
                    var typedPropertyDefinition = propertyDefinition as TypedPropertyDefinition;
                    var typeDefinition = typedPropertyDefinition?.Type;
                    if(typeDefinition != null)
                    {
                        result = typeDefinition.Name;
                    }
                    else
                    {
                        throw new InvalidOperationException($"Typed property '{propertyDefinition.Name}' does not have a type defined.");
                    }
                }
                break;


            }

            return result;
        }

        public static string GetBaseType(FieldDefinition fieldDefinition)
        {
            string result = GetNotNullableBaseType(fieldDefinition);
            if (fieldDefinition.IsNullable)
            {
                result += "?";
            }
            return result;
        }

        public static string GetBaseType(PropertyDefinition propertyDefinition)
        {
            string result = GetNotNullableBaseType(propertyDefinition);
            if(propertyDefinition.IsNullable)
            {
                result += "?";
            }
            return result;
        }


        public static string GetDataReaderFunction(FieldDefinition fieldDefinition)
        {
            var fieldType = fieldDefinition.FieldType;
            var functionName = $"Get{fieldType}";
            var nullableFunctionName = $"GetNullable{fieldType}";
            if (fieldType == FieldType.HierarchyId)
            {
                functionName = "GetSqlHierarchyId";
                nullableFunctionName = "GetNullableSqlHierarchyId";
            }
            else if (fieldType == FieldType.Geometry)
            {
                functionName = "GetSqlGeometry";
                nullableFunctionName = "GetNullableSqlGeometry";
            }
            else if (fieldType == FieldType.Geography)
            {
                functionName = "GetSqlGeography";
                nullableFunctionName = "GetNullableSqlGeography";
            }
            else if (fieldType == FieldType.Xml)
            {
                functionName = "GetSqlXml";
                nullableFunctionName = "GetNullableSqlXml";
            }
            else if (fieldType == FieldType.SqlVariant)
            {
                functionName = "GetValue";
                nullableFunctionName = "GetNullableValue";
            }

            return fieldDefinition.IsNullable ? nullableFunctionName : functionName;
        }

        public static string GetDefaultValue(FieldDefinition fieldDefinition)
        {
            string result = string.Empty;
            var fieldType = fieldDefinition.FieldType;
            switch (fieldType)
            {
                case FieldType.Boolean:
                {
                    result = "false";
                }
                break;
                case FieldType.SByte:
                {
                    result = "0";
                }
                break;
                case FieldType.Byte:
                {
                    result = "0";
                }
                break;
                case FieldType.Int16:
                {
                    result = "0";
                }
                break;
                case FieldType.UInt16:
                {
                    result = "0";
                }
                break;
                case FieldType.Int32:
                {
                    result = "0";
                }
                break;
                case FieldType.UInt32:
                {
                    result = "0";
                }
                break;
                case FieldType.Int64:
                {
                    result = "0";
                }
                break;
                case FieldType.UInt64:
                {
                    result = "0";
                }
                break;
                case FieldType.Single:
                {
                    result = "0.0f";
                }
                break;
                case FieldType.Double:
                {
                    result = "0.0";
                }
                break;
                case FieldType.DateTime:
                {
                    result = "default";
                }
                break;
                case FieldType.TimeSpan:
                {
                    result = "default";
                }
                break;
                case FieldType.Guid:
                {
                    result = "default";
                }
                break;
                case FieldType.String:
                {
                    if (fieldDefinition.IsNullable)
                    {
                        result = "default";
                    }
                    else
                    {
                        result = "string.Empty";
                    }
                }
                break;
                case FieldType.Binary:
                {
                    if (fieldDefinition.IsNullable)
                    {
                        result = "default";
                    }
                    else
                    {
                        result = "Array.Empty<byte>()";
                    }
                }
                break;
                case FieldType.Unknown:
                    break;
                case FieldType.Char:
                    break;
                case FieldType.Decimal:
                    break;
                case FieldType.SqlVariant:
                    break;
                case FieldType.HierarchyId:
                    break;
                case FieldType.Geometry:
                    break;
                case FieldType.Geography:
                    break;
                case FieldType.Xml:
                    break;
                case FieldType.Object:
                    break;
            }

            return result;
        }

        public static string GetDefaultValue(PropertyDefinition propertyDefinition)
        {
            string result = "<unknown>";
            var fieldType = propertyDefinition.Kind;
            switch (fieldType)
            {
                case PropertyKind.Boolean:
                {
                    result = "false";
                }
                break;
                case PropertyKind.SByte:
                {
                    result = "0";
                }
                break;
                case PropertyKind.Byte:
                {
                    result = "0";
                }
                break;
                case PropertyKind.Char:
                {
                    result = "\'\\0\'";
                }
                break;
                case PropertyKind.Int16:
                {
                    result = "0";
                }
                break;
                case PropertyKind.UInt16:
                {
                    result = "0";
                }
                break;
                case PropertyKind.Int32:
                {
                    result = "0";
                }
                break;
                case PropertyKind.UInt32:
                {
                    result = "0";
                }
                break;
                case PropertyKind.Int64:
                {
                    result = "0L";
                }
                break;
                case PropertyKind.UInt64:
                {
                    result = "0UL";
                }
                break;
                case PropertyKind.Single:
                {
                    result = "0.0f";
                }
                break;
                case PropertyKind.Double:
                {
                    result = "0.0";
                }
                break;
                case PropertyKind.Decimal:
                {
                    result = "0.0m";
                }
                break;
                case PropertyKind.DateTime:
                {
                    result = "default(DateTime)";
                }
                break;
                case PropertyKind.TimeSpan:
                {
                    result = "default(TimeSpan)";
                }
                break;
                case PropertyKind.Guid:
                {
                    result = "Guid.Empty";
                }
                break;
                case PropertyKind.String:
                {
                    result = "string.Empty";
                }
                break;
                case PropertyKind.Binary:
                {
                    result = "Array.Empty<byte>()";
                }
                break;
                case PropertyKind.Enum:
                {
                    var enumPropertyDefinition = propertyDefinition as EnumPropertyDefinition;
                    var enumDefinition = enumPropertyDefinition?.Type as EnumDefinition;
                    if (enumDefinition != null)
                    {
                        result = enumDefinition.DefaultValue;
                    }
                    else
                    {
                        throw new InvalidOperationException($"Enum property '{propertyDefinition.Name}' does not have a type defined.");
                    }
                }
                break;
                case PropertyKind.Object:
                {
                    var typedPropertyDefinition = propertyDefinition as TypedPropertyDefinition;
                    var typeDefinition = typedPropertyDefinition?.Type;
                    if (typeDefinition != null)
                    {
                        if (typeDefinition.Kind == TypeKind.Class)
                        {
                            result = "null";
                        }
                        else
                        {
                            result = $"new {typeDefinition.Name}()";
                        }
                    }
                    else
                    {
                        throw new InvalidOperationException($"Typed property '{propertyDefinition.Name}' does not have a type defined.");
                    }
                }
                break;


            }

            return result;
        }


        public static string GetInputArgumentType(FieldDefinition fieldDefinition)
        {
            return GetBaseType(fieldDefinition);
        }

        public static string GetInputArgumentName(FieldDefinition fieldDefinition)
        {
            var name = fieldDefinition.Name.FirstToLower();
            if (keyWords.Contains(name!))
            {
                name = name + "__";
            }
            return name;
        }

        public static string GetInputArgumentType(PropertyDefinition propertyDefinition)
        {
            return GetBaseType(propertyDefinition);
        }

        public static string GetInputArgumentName(PropertyDefinition propertyDefinition)
        {
            var name = propertyDefinition.Name.FirstToLower();
            if (keyWords.Contains(name!))
            {
                name = name + "__";
            }
            return name;
        }

        public static string GetDataType(RowSourceDefinition entityDefinition)
        {
            return entityDefinition.Name + "DataType";
        }

        public static string GetReaderClassName(RowSourceDefinition entityDefinition)
        {
            return entityDefinition.Name + "Reader";
        }

        public static string GetMemberFieldType(FieldDefinition fieldDefinition)
        {
            return GetBaseType(fieldDefinition);
        }

        public static string GetMemberFieldName(FieldDefinition fieldDefinition)
        {
            var name = "_" + fieldDefinition.Name.FirstToLower();
            return name;
        }

        public static string GetMemberFieldType(PropertyDefinition propertyDefinition)
        {
            return GetBaseType(propertyDefinition);
        }

        public static string GetMemberFieldName(PropertyDefinition propertyDefinition)
        {
            var name = "_" + propertyDefinition.Name.FirstToLower();
            return name;
        }


        public static string GetMemberPropertyName(FieldDefinition fieldDefinition)
        {
            var name = fieldDefinition.Name.FirstToUpper();
            return name!;
        }

        public static string GetMemberPropertyName(PropertyDefinition propertyDefinition)
        {
            var name = propertyDefinition.Name.FirstToUpper();
            return name!;
        }


        public static bool MemberFieldRequiresDefaultValue(FieldDefinition fieldDefinition)
        {
            FieldType memberType = fieldDefinition.FieldType;
            if (fieldDefinition.IsNullable == false && (memberType <= FieldType.Decimal || memberType == FieldType.String || memberType == FieldType.Binary))
            {
                return true;
            }
            return false;
        }

        public static bool MemberFieldRequiresDefaultValue(PropertyDefinition propertyDefinition)
        {
            var memberType = propertyDefinition.Kind;
            if (propertyDefinition.IsNullable == false && (memberType <= PropertyKind.Decimal || memberType == PropertyKind.String || memberType == PropertyKind.Binary))
            {
                return true;
            }
            return false;
        }

        public static string GetDataTypeConstructorArguments(RowSourceDefinition entityDefinition, string indentation, IReadOnlyList<FieldDefinition> fieldDefinitions)
        {
            var fieldDefinitionsCount = fieldDefinitions.Count;
            var arguments = new List<string>();
            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var member = fieldDefinitions[i];
                var argumentType = GetInputArgumentType(member);
                var argumentName = GetInputArgumentName(member);
                if(i == 0)
                {
                    arguments.Add($"{argumentType} {argumentName}");
                }
                else
                {
                    arguments.Add($"{indentation}{argumentType} {argumentName}");
                }
                    
            }
            return string.Join($",{Environment.NewLine}", arguments);
        }

        public static string GetConstructorArguments(ObjectDefinition objectDefinition, string indentation, IReadOnlyList<PropertyDefinition> propertyDefinitions)
        {
            var fieldDefinitionsCount = propertyDefinitions.Count;
            var arguments = new List<string>();
            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var member = propertyDefinitions[i];
                var argumentType = GetInputArgumentType(member);
                var argumentName = GetInputArgumentName(member);
                if (i == 0)
                {
                    arguments.Add($"{argumentType} {argumentName}");
                }
                else
                {
                    arguments.Add($"{indentation}{argumentType} {argumentName}");
                }

            }
            return string.Join($",{Environment.NewLine}", arguments);
        }


        public static string GetDataTypeNamespace(RowSourceDefinition entityDefinition)
        {
            return entityDefinition.DataTypeNamespace;
        }

        public static string GetQualifiedDataTypeNamespace(RowSourceDefinition entityDefinition)
        {
            var schema = entityDefinition.Owner!;
            var schemaNamespace = string.IsNullOrEmpty(schema.Namespace) ? schema.Name.FirstToUpper() : schema.Namespace;

            return "Types."+ schemaNamespace;
        }

        public static string GetTypeNamespace(TypeDefinition typeDefinition)
        {
            return typeDefinition.TypeNamespace;
        }

        public static string GetQualifiedTypeNamespace(TypeDefinition typeDefinition)
        {
            var schema = typeDefinition.Owner!;
            var schemaNamespace = string.IsNullOrEmpty(schema.Namespace) ? schema.Name.FirstToUpper() : schema.Namespace;

            return "Types." + schemaNamespace;
        }


        public static string GetDatabaseNamespace(Context context)
        {
            var project = context.Project;
            var projectNamespace = string.IsNullOrEmpty(project.Namespace) ? project.Name.FirstToUpper() : project.Namespace;
            return projectNamespace + ".Database";
        }

        public static string GetDatabaseReaderNamespace(Context context)
        {
            var project = context.Project;
            var projectNamespace = string.IsNullOrEmpty(project.Namespace) ? project.Name.FirstToUpper() : project.Namespace;
            return projectNamespace + ".Database.Readers";
        }

        public static string GetDatabaseReaderNamespace(RowSourceDefinition entityDefinition)
        {
            var project = entityDefinition.Project!;
            var projectNamespace = string.IsNullOrEmpty(project.Namespace) ? project.Name.FirstToUpper() : project.Namespace;
            var readersNamespace = projectNamespace + ".Database.Readers";
            var schemaNamespace = string.IsNullOrEmpty(entityDefinition.Owner!.Namespace) ? entityDefinition.Owner.Name.FirstToUpper() : entityDefinition.Owner.Namespace;
            return readersNamespace + "." + schemaNamespace;
        }

        public static string GetInsertFunctionName(RowSourceDefinition entityDefinition)
        {
            return "Insert" + entityDefinition.Name;
        }

        public static string GetInsert1FunctionName(RowSourceDefinition entityDefinition)
        {
            return "Insert1" + entityDefinition.Name;
        }

        public static string GetUpdateFunctionName(RowSourceDefinition entityDefinition)
        {
            return "Update" + entityDefinition.Name;
        }

        public static string GetUpdate1FunctionName(RowSourceDefinition entityDefinition)
        {
            return "Update1" + entityDefinition.Name;
        }

        public static string GetUpdate2FunctionName(RowSourceDefinition entityDefinition)
        {
            return "Update2" + entityDefinition.Name;
        }

        public static string GetDeleteFunctionName(RowSourceDefinition entityDefinition)
        {
            return "Delete" + entityDefinition.Name;
        }


    }


}
