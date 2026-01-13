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
    public class CSharpDataTypeGenerator : CodeWriter
    {
        readonly RowSourceDefinition _rowSourceDefinition;
        readonly bool _readOnly;
        public CSharpDataTypeGenerator(Context context, RowSourceDefinition rowSourceDefinition, bool readOnly) 
            : base(context)
        {
            _rowSourceDefinition = rowSourceDefinition;
            _readOnly = readOnly;
        }

        public RowSourceDefinition RowSource => _rowSourceDefinition;

        

        public void Run()
        {
            string readOnlyModifier = _readOnly ? "readonly " : string.Empty;
            WriteLine("using System;");
            WriteLine("using System.Data.SqlTypes;");
            WriteLine("using Microsoft.SqlServer.Types;");
            WriteLine();
            WriteLine($"namespace {CSharpHelper.GetDataTypeNamespace(RowSource)};");
            WriteLine();
            var dataTypeName = CSharpHelper.GetDataType(RowSource);
            WriteLine($"public class {dataTypeName}");
            WriteLine("{");
            foreach (var field in RowSource.Fields)
            {
                var fieldType = CSharpHelper.GetMemberFieldType(field);
                var fieldName = CSharpHelper.GetMemberFieldName(field);
                var defaultValue = string.Empty;
                if (CSharpHelper.MemberFieldRequiresDefaultValue(field))
                {
                    defaultValue = " = "+CSharpHelper.GetDefaultValue(field);
                }

                WriteLine($"    {readOnlyModifier}{fieldType} {fieldName}{defaultValue};");
            }
            WriteLine();
            WriteLine($"    public {dataTypeName}( )");
            WriteLine("    {");
            WriteLine("    }");
            WriteLine();
            var constructorArguments = CSharpHelper.GetDataTypeConstructorArguments(RowSource, "        ", RowSource.Fields);
            WriteLine($"    public {dataTypeName}({constructorArguments})");
            WriteLine("    {");
            foreach (var field in RowSource.Fields)
            {
                var fieldName = CSharpHelper.GetMemberFieldName(field);
                var argumentName = CSharpHelper.GetInputArgumentName(field);
                WriteLine($"        {fieldName} = {argumentName};");
            }
            WriteLine("    }");
            WriteLine();

            foreach (var field in RowSource.Fields)
            {
                var fieldName = CSharpHelper.GetMemberFieldName(field);
                var propertyName = CSharpHelper.GetMemberPropertyName(field);
                var fieldType = CSharpHelper.GetMemberFieldType(field);
                if (_readOnly)
                {
                    WriteLine($"    public {fieldType} {propertyName} => {fieldName};");
                    continue;
                }
                else
                {
                    WriteLine($"    public {fieldType} {propertyName}");
                    WriteLine("    {");
                    WriteLine($"        get => {fieldName};");
                    WriteLine($"        set => {fieldName} = value;");
                    WriteLine("    }");
                }
            }

            WriteLine("}");
        }

    }


}
