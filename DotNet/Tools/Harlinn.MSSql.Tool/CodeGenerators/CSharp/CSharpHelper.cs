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
                case FieldType.Typed:
                    break;
            }

            return result;
        }
        public static string GetBaseType(FieldDefinition fieldDefinition)
        {
            string result = "<unknown>";
            var fieldType = fieldDefinition.FieldType;
            switch (fieldType)
            {
                case FieldType.Boolean:
                {
                    result = fieldDefinition.IsNullable ? "bool?" : "bool";
                }
                break;
                case FieldType.SByte:
                {
                    result = fieldDefinition.IsNullable ? "sbyte?" : "sbyte";
                }
                break;
                case FieldType.Byte:
                {
                    result = fieldDefinition.IsNullable ? "byte?" : "byte";
                }
                break;
                case FieldType.Int16:
                {
                    result = fieldDefinition.IsNullable ? "short?" : "short";
                }
                break;
                case FieldType.UInt16:
                {
                    result = fieldDefinition.IsNullable ? "ushort?" : "ushort";
                }
                break;
                case FieldType.Int32:
                {
                    result = fieldDefinition.IsNullable ? "int?" : "int";
                }
                break;
                case FieldType.UInt32:
                {
                    result = fieldDefinition.IsNullable ? "uint?" : "uint";
                }
                break;
                case FieldType.Int64:
                {
                    result = fieldDefinition.IsNullable ? "long?" : "long";
                }
                break;
                case FieldType.UInt64:
                {
                    result = fieldDefinition.IsNullable ? "ulong?" : "ulong";
                }
                break;
                case FieldType.Single:
                {
                    result = fieldDefinition.IsNullable ? "float?" : "float";
                }
                break;
                case FieldType.Double:
                {
                    result = fieldDefinition.IsNullable ? "double?" : "double";
                }
                break;
                case FieldType.DateTime:
                {
                    result = fieldDefinition.IsNullable ? "DateTime?" : "DateTime";
                }
                break;
                case FieldType.TimeSpan:
                {
                    result = fieldDefinition.IsNullable ? "TimeSpan?" : "TimeSpan";
                }
                break;
                case FieldType.Guid:
                {
                    result = fieldDefinition.IsNullable ? "Guid?" : "Guid";
                }
                break;
                case FieldType.String:
                {
                    result = fieldDefinition.IsNullable ? "string?" : "string";
                }
                break;
                case FieldType.Binary:
                {
                    result = fieldDefinition.IsNullable ? "byte[]?" : "byte[]";
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
                case FieldType.Typed:
                    break;
            }

            return result;
        }

        public static string GetDataReaderFunction(FieldDefinition fieldDefinition)
        {
            var fieldType = fieldDefinition.FieldType;
            var functionName = $"Get{fieldType}";
            var nullableFunctionName = $"GetNullable{fieldType}";

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
                case FieldType.Typed:
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
            if (keyWords.Contains(name))
            {
                name = name + "__";
            }
            return name;
        }

        public static string GetDataType(EntityDefinition entityDefinition)
        {
            return entityDefinition.Name + "DataType";
        }

        public static string GetReaderClassName(EntityDefinition entityDefinition)
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

        public static string GetMemberPropertyName(FieldDefinition fieldDefinition)
        {
            var name = fieldDefinition.Name.FirstToUpper();
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

        public static string GetDataTypeConstructorArguments(EntityDefinition entityDefinition, string indentation, IReadOnlyList<FieldDefinition> fieldDefinitions)
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

        public static string GetDataTypeNamespace(EntityDefinition entityDefinition)
        {
            return entityDefinition.DataTypeNamespace;
        }

        public static string GetQualifiedDataTypeNamespace(EntityDefinition entityDefinition)
        {
            var schema = entityDefinition.Owner!;
            var schemaNamespace = string.IsNullOrEmpty(schema.Namespace) ? schema.Name.FirstToUpper() : schema.Namespace;

            return "Types."+ schemaNamespace;
        }

        public static string GetDatabaseNamespace(Context context)
        {
            var project = context.Project;
            var projectNamespace = string.IsNullOrEmpty(project.Namespace) ? project.Name.FirstToUpper() : project.Namespace;
            return projectNamespace + ".Database";
        }

        public static string GetDatabaseReaderNamespace(EntityDefinition entityDefinition)
        {
            var project = entityDefinition.Project!;
            var projectNamespace = string.IsNullOrEmpty(project.Namespace) ? project.Name.FirstToUpper() : project.Namespace;
            var readersNamespace = projectNamespace + ".Database.Readers";
            var schemaNamespace = string.IsNullOrEmpty(entityDefinition.Owner!.Namespace) ? entityDefinition.Owner.Name.FirstToUpper() : entityDefinition.Owner.Namespace;
            return readersNamespace + "." + schemaNamespace;
        }

        public static string GetInsertFunctionName(EntityDefinition entityDefinition)
        {
            return "Insert" + entityDefinition.Name;
        }

        public static string GetInsert1FunctionName(EntityDefinition entityDefinition)
        {
            return "Insert1" + entityDefinition.Name;
        }

        public static string GetUpdateFunctionName(EntityDefinition entityDefinition)
        {
            return "Update" + entityDefinition.Name;
        }

        public static string GetUpdate1FunctionName(EntityDefinition entityDefinition)
        {
            return "Update1" + entityDefinition.Name;
        }

        public static string GetUpdate2FunctionName(EntityDefinition entityDefinition)
        {
            return "Update2" + entityDefinition.Name;
        }

        public static string GetDeleteFunctionName(EntityDefinition entityDefinition)
        {
            return "Delete" + entityDefinition.Name;
        }


    }


}
