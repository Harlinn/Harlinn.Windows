using Harlinn.Common.Core.Net;
using System;
using System.Collections.Generic;
using System.Text;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class CSharpGenerator
    {
        readonly Context _context;
        public CSharpGenerator(Context context)
        {
            _context = context;
        }
        public Context Context => _context;

        public BuildOptions BuildOptions => (BuildOptions)Context.Options;
        public bool UseWrappers => BuildOptions.UseWrappers;

        public void Run()
        {
            var entities = Context.Project.Entities;
            var rowSources = Context.Project.RowSources;
            foreach (var rowSource in rowSources)
            {
                CSharpDataTypeGenerator dataTypeGenerator = new CSharpDataTypeGenerator(Context, rowSource, rowSource.Type == Input.Types.SchemaObjectType.View);
                dataTypeGenerator.Run();
                var typesDirectory = Context.Output.CSharp.TypesDirectory;
                var schemaDirectory = System.IO.Path.Combine(typesDirectory, string.IsNullOrEmpty(rowSource.Owner!.Namespace) ? rowSource.Owner!.Name.FirstToUpper()! : rowSource.Owner!.Namespace);
                var filename = System.IO.Path.Combine(schemaDirectory, $"{rowSource.Name}DataType.cs");
                dataTypeGenerator.SaveToFile(filename);
            }
            CSharpStoredProceduresGenerator storedProceduresGenerator = new CSharpStoredProceduresGenerator(Context);
            storedProceduresGenerator.Run();
            storedProceduresGenerator.SaveToFile(Context.Output.CSharp.StoredProcedures);

            CSharpSqlDataReaderExtensionsGenerator sqlDataReaderExtensionsGenerator = new CSharpSqlDataReaderExtensionsGenerator(Context);
            sqlDataReaderExtensionsGenerator.Run();
            sqlDataReaderExtensionsGenerator.SaveToFile(Path.Combine(Context.Output.CSharp.ReadersDirectory, "SqlDataReaderExtensions.cs"));

            foreach (var rowSource in rowSources)
            {
                CSharpReaderGenerator dataTypeGenerator = new CSharpReaderGenerator(Context, rowSource);
                dataTypeGenerator.Run();
                var readersDirectory = Context.Output.CSharp.ReadersDirectory;
                var schemaDirectory = System.IO.Path.Combine(readersDirectory, string.IsNullOrEmpty(rowSource.Owner!.Namespace) ? rowSource.Owner!.Name.FirstToUpper()! : rowSource.Owner!.Namespace);
                var readerClassName = CSharpHelper.GetReaderClassName(rowSource);
                var filename = System.IO.Path.Combine(schemaDirectory, $"{readerClassName}.cs");
                dataTypeGenerator.SaveToFile(filename);
            }
            var typeDefinitions = Context.Project.TypeDefinitions;
            foreach (var entry in typeDefinitions)
            {
                var typeDefinition = entry.Value;
                if(typeDefinition is Input.Types.EnumDefinition enumDefinition)
                {
                    CSharpEnumGenerator enumGenerator = new CSharpEnumGenerator(Context, enumDefinition);
                    enumGenerator.Run();
                    var typesDirectory = Context.Output.CSharp.TypesDirectory;
                    var schemaDirectory = System.IO.Path.Combine(typesDirectory, string.IsNullOrEmpty(enumDefinition.Owner!.Namespace) ? enumDefinition.Owner!.Name.FirstToUpper()! : enumDefinition.Owner!.Namespace);
                    var filename = System.IO.Path.Combine(schemaDirectory, $"{enumDefinition.Name}.cs");
                    enumGenerator.SaveToFile(filename);
                }
                else if (typeDefinition is Input.Types.ObjectDefinition objectDefinition)
                {
                    CSharpObjectGenerator objectGenerator = new CSharpObjectGenerator(Context, objectDefinition);
                    objectGenerator.Run();
                    var typesDirectory = Context.Output.CSharp.TypesDirectory;
                    var schemaDirectory = System.IO.Path.Combine(typesDirectory, string.IsNullOrEmpty(objectDefinition.Owner!.Namespace) ? objectDefinition.Owner!.Name.FirstToUpper()! : objectDefinition.Owner!.Namespace);
                    var filename = System.IO.Path.Combine(schemaDirectory, $"{objectDefinition.Name}.cs");
                    objectGenerator.SaveToFile(filename);
                }


            }

        }

    }


}
