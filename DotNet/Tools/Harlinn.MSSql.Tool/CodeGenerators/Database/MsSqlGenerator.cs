using System;
using System.Collections.Generic;
using System.Text;

namespace Harlinn.MSSql.Tool.CodeGenerators.Database
{
    public class MsSqlGenerator
    {
        private readonly Context _context;
        public MsSqlGenerator(Context context)
        {
            _context = context;
        }


        public void Run()
        {
            MsSqlTablesGenerator tablesGenerator = new MsSqlTablesGenerator(_context);
            tablesGenerator.Run();
            tablesGenerator.SaveToFile(_context.Output.Mssql.CreateTables);

            MsSqlInsertProceduresGenerator insertProceduresGenerator = new MsSqlInsertProceduresGenerator(_context);
            insertProceduresGenerator.Run();
            insertProceduresGenerator.SaveToFile(_context.Output.Mssql.InsertProcedures);

            MsSqlUpdateProceduresGenerator updateProceduresGenerator = new MsSqlUpdateProceduresGenerator(_context);
            updateProceduresGenerator.Run();
            updateProceduresGenerator.SaveToFile(_context.Output.Mssql.UpdateProcedures);

            MsSqlDeleteProceduresGenerator deleteProceduresGenerator = new MsSqlDeleteProceduresGenerator(_context);
            deleteProceduresGenerator.Run();
            deleteProceduresGenerator.SaveToFile(_context.Output.Mssql.DeleteProcedures);

        }

    }
}
