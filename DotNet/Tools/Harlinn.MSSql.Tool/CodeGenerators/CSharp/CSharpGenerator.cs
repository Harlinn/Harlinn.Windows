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

        public void Run()
        {
            var entities = Context.Project.Entities;
            foreach (var entity in entities)
            {
                CSharpDataTypeGenerator dataTypeGenerator = new CSharpDataTypeGenerator(Context, entity);
                dataTypeGenerator.Run();
                var typesDirectory = Context.Output.CSharp.TypesDirectory;
                var schemaDirectory = System.IO.Path.Combine(typesDirectory, string.IsNullOrEmpty(entity.Owner!.Namespace) ? entity.Owner!.Name.FirstToUpper()! : entity.Owner!.Namespace);
                var filename = System.IO.Path.Combine(schemaDirectory, $"{entity.Name}DataType.cs");
                dataTypeGenerator.SaveToFile(filename);
            }
            CSharpStoredProceduresGenerator storedProceduresGenerator = new CSharpStoredProceduresGenerator(Context);
            storedProceduresGenerator.Run();
            storedProceduresGenerator.SaveToFile(Context.Output.CSharp.StoredProcedures);

            foreach (var entity in entities)
            {
                CSharpReaderGenerator dataTypeGenerator = new CSharpReaderGenerator(Context, entity);
                dataTypeGenerator.Run();
                var readersDirectory = Context.Output.CSharp.ReadersDirectory;
                var schemaDirectory = System.IO.Path.Combine(readersDirectory, string.IsNullOrEmpty(entity.Owner!.Namespace) ? entity.Owner!.Name.FirstToUpper()! : entity.Owner!.Namespace);
                var readerClassName = CSharpHelper.GetReaderClassName(entity);
                var filename = System.IO.Path.Combine(schemaDirectory, $"{readerClassName}.cs");
                dataTypeGenerator.SaveToFile(filename);
            }

        }

    }


}
