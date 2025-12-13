using System;
using System.Collections.Generic;
using System.Text;

namespace Harlinn.MSSql.Tool.CodeGenerators
{
    public class Generator
    {
        private readonly Context _context;

        public Generator(Context context)
        {
            _context = context;
        }

        public void Run()
        {
            Database.MsSqlGenerator msSqlGenerator = new Database.MsSqlGenerator(_context);
            msSqlGenerator.Run();
        }

    }
}
