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
    public class CSharpBulkCopyGenerator : CodeWriter
    {
        readonly EntityDefinition _entityDefinition;

        public CSharpBulkCopyGenerator(Context context, EntityDefinition entityDefinition)
            : base(context)
        {
            _entityDefinition = entityDefinition;
        }

        public EntityDefinition Entity => _entityDefinition;

        public void Run()
        {
            WriteLine("using System;");
            WriteLine("using System.Data;");
            WriteLine("using System.Data.Common;");
            WriteLine("using System.Collections.Generic;");
            WriteLine("using Microsoft.Data.SqlClient;");
            WriteLine("using Microsoft.SqlServer.Types;");
            WriteLine("using System.Data.SqlTypes;");
            if (UseWrappers)
            {
                WriteLine("using Harlinn.Common.Core.Net.Data.SqlClient;");
                WriteLine("using Microsoft.Extensions.Logging;");
                WriteLine("using System.Diagnostics.CodeAnalysis;");
            }
            WriteLine();

            var bulkCopyNamespace = Entity.GetBulkCopyNamespace();
            WriteLine($"namespace {bulkCopyNamespace};");

            var bulkCopyClassName = Entity.GetBulkCopyClassName();
            WriteLine();
            WriteLine($"public class {bulkCopyClassName}");
            WriteLine("{");

            WriteLine("}");


        }

    }


}
