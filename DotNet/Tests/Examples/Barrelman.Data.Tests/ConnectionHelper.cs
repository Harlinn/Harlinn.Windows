using System;
using System.Collections.Generic;

using Microsoft.Data.SqlClient;

namespace Barrelman.Data.Tests
{
    internal class ConnectionHelper
    {
        const string InitialCatalog = "Barrelman";
        const string ConnectionString = "Data Source=(local);Integrated Security=true;Encrypt=false;Initial Catalog=" + InitialCatalog + ";";

        static SqlConnection? _connection = null;

        public static SqlConnection Connection 
        { 
            get
            {
                if(_connection == null)
                {
                    _connection = new SqlConnection(ConnectionString);
                    _connection.Open();
                }
                return _connection;
            }

        }
    }
}
