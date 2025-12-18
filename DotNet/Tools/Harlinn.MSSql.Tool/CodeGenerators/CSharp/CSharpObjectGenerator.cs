using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class CSharpObjectGenerator : CodeWriter
    {
        readonly ObjectDefinition _definition;
        public CSharpObjectGenerator(Context context, ObjectDefinition definition)
            : base(context)
        {
            _definition = definition;
        }

        public ObjectDefinition Definition => _definition;

        public void Run()
        {
            WriteLine("using System;");
            WriteLine();
            WriteLine($"namespace {CSharpHelper.GetTypeNamespace(Definition)};");
            WriteLine();
            var dataTypeName = Definition.Name;
            WriteLine($"public class {dataTypeName}");
            WriteLine("{");
            foreach (var property in Definition.Properties)
            {
                var fieldType = CSharpHelper.GetMemberFieldType(property);
                var fieldName = CSharpHelper.GetMemberFieldName(property);
                var defaultValue = string.Empty;
                if (CSharpHelper.MemberFieldRequiresDefaultValue(property))
                {
                    defaultValue = " = " + CSharpHelper.GetDefaultValue(property);
                }

                WriteLine($"    {fieldType} {fieldName}{defaultValue};");
            }
            WriteLine();
            WriteLine($"    public {dataTypeName}( )");
            WriteLine("    {");
            WriteLine("    }");
            WriteLine();
            var constructorArguments = CSharpHelper.GetConstructorArguments(Definition, "        ", Definition.Properties);
            WriteLine($"    public {dataTypeName}({constructorArguments})");
            WriteLine("    {");
            foreach (var property in Definition.Properties)
            {
                var fieldName = CSharpHelper.GetMemberFieldName(property);
                var argumentName = CSharpHelper.GetInputArgumentName(property);
                WriteLine($"        {fieldName} = {argumentName};");
            }
            WriteLine("    }");
            WriteLine();

            foreach (var property in Definition.Properties)
            {
                var fieldName = CSharpHelper.GetMemberFieldName(property);
                var propertyName = CSharpHelper.GetMemberPropertyName(property);
                var fieldType = CSharpHelper.GetMemberFieldType(property);
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
