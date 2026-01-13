/*
    Copyright 2024-2026 Espen Harlinn
 
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
﻿using Harlinn.MSSql.Tool.Input.Types;
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
