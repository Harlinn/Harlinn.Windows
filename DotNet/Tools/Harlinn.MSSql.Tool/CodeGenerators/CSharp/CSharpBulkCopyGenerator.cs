using Harlinn.MSSql.Tool.Input.Types;
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
