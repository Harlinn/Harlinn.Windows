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

using CommandLine;
using Microsoft.Data.SqlClient;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool
{
    

    public class Program : IDisposable
    {
        static Program? _instance;
        private bool disposedValue;
        readonly OptionsBase _options;
        SqlConnection? _sqlConnection;
        //ServerConnection _serverConnection;

        Input.Types.Project _project;

        public Program(OptionsBase options)
        {
            _options = options;

            if (File.Exists(options.Project))
            {
                using FileStream fileStream = new FileStream(options.Project, FileMode.Open, FileAccess.Read);
                XmlSerializer xmlSerializer = new XmlSerializer(typeof(Input.Types.Project));
                _project = (Input.Types.Project)xmlSerializer.Deserialize(fileStream)!;
                _project.Initialize();
            }
            else
            {
                _project = new Input.Types.Project();
            }
        }

        public OptionsBase Options => _options;
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


        SqlConnection GetSqlConnection()
        {
            if(_sqlConnection == null)
            {
                var importOptions = (ImportOptions)_options;
                _sqlConnection = new SqlConnection(importOptions.GetConnectionString());
                _sqlConnection.Open();
            }
            return _sqlConnection;
        }


        void Run()
        {
            _instance = this;
            try
            {
                var options = (BuildOptions)_options;
                if (string.IsNullOrEmpty(options.OutputDirectory))
                {
                    options.OutputDirectory = BuildOptions.GetDefaultOutputDirectory(Options.Project);
                }
                var context = new CodeGenerators.Context(_project, options);
                var generator = new CodeGenerators.Generator(context);
                generator.Run();
            }
            finally
            {
                _instance = null;
            }
        }

        void Import()
        {
            _instance = this;
            try
            {
                var sqlConnection = GetSqlConnection();
                _project.Import(sqlConnection, (ImportOptions)_options);
                _project.SaveToFile(Options.Project);
            }
            finally
            {
                _instance = null;
            }
        }

        static void Main(string[] args)
        {
            Parser.Default.ParseArguments<BuildOptions, ImportOptions>(args)
                    .WithParsed<BuildOptions>(o => 
                    { 
                        using Program program = new Program(o); 
                        program.Run(); 
                    })
                    .WithParsed<ImportOptions>(o => 
                    {
                        using Program program = new Program(o);
                        program.Import();
                    } );
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing && _sqlConnection != null)
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
