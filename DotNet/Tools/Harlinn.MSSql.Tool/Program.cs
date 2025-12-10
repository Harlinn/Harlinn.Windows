/*
   Copyright 2024-2025 Espen Harlinn

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

using CommandLine;
using Microsoft.Data.SqlClient;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool
{
    

    public class Program : IDisposable
    {
        static Program? _instance;
        private bool disposedValue;
        readonly Options _options;
        readonly SqlConnection _sqlConnection;
        //ServerConnection _serverConnection;

        Input.Types.Project _project;

        public Program(Options options)
        {
            _options = options;
            _sqlConnection = new SqlConnection(options.GetConnectionString());
            _sqlConnection.Open();

            using FileStream fileStream = new FileStream(options.Project, FileMode.Open, FileAccess.Read);
            XmlSerializer xmlSerializer = new XmlSerializer(typeof(Input.Types.Project));
            _project = (Input.Types.Project)xmlSerializer.Deserialize(fileStream)!;
        }

        public Options Options => _options;
        public Input.Types.Project Project => _project;

        public Program Instance
        {
            get
            {
                if (_instance == null)
                {
                    throw new InvalidOperationException("Program instance is not initialized.");
                }
                return _instance;
            }
        }


        void Run()
        {
            _instance = this;
            try
            {

            }
            finally
            {
                _instance = null;
            }
        }

        static void Main(string[] args)
        {
            Parser.Default.ParseArguments<Options>(args)
                    .WithParsed<Options>(o =>
                {
                    using Program program = new Program(o);
                    program.Run();
                });
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    _sqlConnection.Dispose();
                }

                // TODO: free unmanaged resources (unmanaged objects) and override finalizer
                // TODO: set large fields to null
                disposedValue = true;
            }
        }

        public void Dispose()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
    }
}
