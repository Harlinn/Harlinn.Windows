using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class CSharpDataTypeGenerator : CodeWriter
    {
        readonly EntityDefinition _entityDefinition;
        public CSharpDataTypeGenerator(Context context, EntityDefinition entityDefinition) 
            : base(context)
        {
            _entityDefinition = entityDefinition;
        }

        public EntityDefinition Entity => _entityDefinition;

        public void Run()
        {
            WriteLine("using System;");
            WriteLine();
            WriteLine($"namespace {CSharpHelper.GetDataTypeNamespace(Entity)};");
            WriteLine();
            var dataTypeName = CSharpHelper.GetDataType(Entity);
            WriteLine($"public class {dataTypeName}");
            WriteLine("{");
            foreach (var field in Entity.Fields)
            {
                var fieldType = CSharpHelper.GetMemberFieldType(field);
                var fieldName = CSharpHelper.GetMemberFieldName(field);
                var defaultValue = string.Empty;
                if (CSharpHelper.MemberFieldRequiresDefaultValue(field))
                {
                    defaultValue = " = "+CSharpHelper.GetDefaultValue(field);
                }

                WriteLine($"    {fieldType} {fieldName}{defaultValue};");
            }
            WriteLine();
            WriteLine($"    public {dataTypeName}( )");
            WriteLine("    {");
            WriteLine("    }");
            WriteLine();
            var constructorArguments = CSharpHelper.GetDataTypeConstructorArguments(Entity, "        ", Entity.Fields);
            WriteLine($"    public {dataTypeName}({constructorArguments})");
            WriteLine("    {");
            foreach (var field in Entity.Fields)
            {
                var fieldName = CSharpHelper.GetMemberFieldName(field);
                var argumentName = CSharpHelper.GetInputArgumentName(field);
                WriteLine($"        {fieldName} = {argumentName};");
            }
            WriteLine("    }");
            WriteLine();

            foreach (var field in Entity.Fields)
            {
                var fieldName = CSharpHelper.GetMemberFieldName(field);
                var propertyName = CSharpHelper.GetMemberPropertyName(field);
                var fieldType = CSharpHelper.GetMemberFieldType(field);
                WriteLine($"    public {fieldType} {propertyName}");
                WriteLine("    {");
                WriteLine($"        get => {fieldName};");
                WriteLine($"        set => {fieldName} = value;");
                WriteLine("    }");
            }

            WriteLine("}");
        }

    }


}
