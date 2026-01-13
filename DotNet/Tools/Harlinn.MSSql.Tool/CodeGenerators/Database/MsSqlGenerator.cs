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
﻿using System;
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

            MsSqlTableTypeGenerator tableTypesGenerator = new MsSqlTableTypeGenerator(_context);
            tableTypesGenerator.Run();
            tableTypesGenerator.SaveToFile(_context.Output.Mssql.CreateTableTypes);

            MsSqlInsertProceduresGenerator insertProceduresGenerator = new MsSqlInsertProceduresGenerator(_context);
            insertProceduresGenerator.Run();
            insertProceduresGenerator.SaveToFile(_context.Output.Mssql.InsertProcedures);

            MsSqlUpdateProceduresGenerator updateProceduresGenerator = new MsSqlUpdateProceduresGenerator(_context);
            updateProceduresGenerator.Run();
            updateProceduresGenerator.SaveToFile(_context.Output.Mssql.UpdateProcedures);

            MsSqlDeleteProceduresGenerator deleteProceduresGenerator = new MsSqlDeleteProceduresGenerator(_context);
            deleteProceduresGenerator.Run();
            deleteProceduresGenerator.SaveToFile(_context.Output.Mssql.DeleteProcedures);

            MsSqlMergeProceduresGenerator mergeProceduresGenerator = new MsSqlMergeProceduresGenerator(_context);
            mergeProceduresGenerator.Run();
            mergeProceduresGenerator.SaveToFile(_context.Output.Mssql.MergeProcedures);

        }

    }
}
