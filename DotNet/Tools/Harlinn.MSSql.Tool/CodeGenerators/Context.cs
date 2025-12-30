using Harlinn.MSSql.Tool.Input.Types;

namespace Harlinn.MSSql.Tool.CodeGenerators
{
    public class Context
    {
        readonly Project _project;
        readonly BuildOptions _options;
        readonly Output _output;

        public Context(Project project, BuildOptions options)
        {
            _project = project;
            _options = options;
            _output = new Output(this);
        }

        public Project Project => _project;

        public BuildOptions Options => _options;

        public Output Output => _output;
    }

    public class Output
    {
        readonly Context _context;
        readonly MsSqlOutout _mssqlOutput;
        readonly CSharpOutout _csharpOutput;
        public Output(Context context)
        {
            _context = context;
            _mssqlOutput = new MsSqlOutout(this);
            _csharpOutput = new CSharpOutout(this);
        }

        public Context Context => _context;

        public MsSqlOutout Mssql => _mssqlOutput;

        public CSharpOutout CSharp => _csharpOutput;

        public string Directory => _context.Options.OutputDirectory;

    }

    public class MsSqlOutout
    {
        readonly Output _owner;

        public MsSqlOutout(Output owner)
        {
            _owner = owner;
        }

        public string Directory => System.IO.Path.Combine(_owner.Directory, "MSSql");

        public string CreateTables => System.IO.Path.Combine(Directory, "CreateTables.sql");
        public string InsertProcedures => System.IO.Path.Combine(Directory, "InsertProcedures.sql");
        public string UpdateProcedures => System.IO.Path.Combine(Directory, "UpdateProcedures.sql");
        public string DeleteProcedures => System.IO.Path.Combine(Directory, "DeleteProcedures.sql");


    }

    public class CSharpOutout
    {
        readonly Output _owner;

        public CSharpOutout(Output owner)
        {
            _owner = owner;
        }

        public string Directory => System.IO.Path.Combine(_owner.Directory, "CSharp");
        public string TypesDirectory => System.IO.Path.Combine(Directory, "Types");

        public string StoredProcedures => System.IO.Path.Combine(Directory, "Database\\StoredProcedures.cs");

        public string ReadersDirectory => System.IO.Path.Combine(Directory, "Database\\Readers");

        public string DatabaseDirectory => System.IO.Path.Combine(Directory, "Database");


    }



}
