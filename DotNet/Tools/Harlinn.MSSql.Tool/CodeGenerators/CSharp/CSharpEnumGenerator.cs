using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class CSharpEnumGenerator : CodeWriter
    {
        readonly EnumDefinition _definition;
        public CSharpEnumGenerator(Context context, EnumDefinition definition)
            : base(context)
        {
            _definition = definition;
        }

        public EnumDefinition Definition => _definition;

        public void Run()
        {
            WriteLine("using System;");
            WriteLine();
            WriteLine($"namespace {CSharpHelper.GetTypeNamespace(Definition)};");
            WriteLine();
            if (Definition.IsFlags)
            {
                WriteLine("[Flags]");
            }
            WriteLine($"public enum {Definition.Name}");
            WriteLine("{");
            var valueCount = Definition.Values.Count;
            for (int i = 0; i < valueCount; i++)
            {
                var member = Definition.Values[i];
                var memberName = member.Name;
                var memberValue = member.Value;
                var comma = i < valueCount - 1 ? "," : string.Empty;
                WriteLine($"    {memberName} = {memberValue}{comma}");
            }
            WriteLine("}");
        }
    }


}
