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


namespace Harlinn.MSSql.Tool
{
    public class OptionsBase
    {
        static string defaultConnectionString = "Data Source=(local);Integrated Security=True;Encrypt=True;Trust Server Certificate=True";
        public OptionsBase()
        {
        }

        [Option('c', "connection_string", Required = false, HelpText = "SQL Server connection string.")]
        public string? ConnectionString { get; set; }

        [Option('i', "initial_catalog", Required = false, HelpText = "SQL Server initial catalog.")]
        public string? InitialCatalog { get; set; }

        public string GetConnectionString()
        {
            if (!string.IsNullOrEmpty(ConnectionString))
            {
                return ConnectionString;
            }
            else if (!string.IsNullOrEmpty(InitialCatalog))
            {
                return $"Data Source=(local);Initial Catalog={InitialCatalog};Integrated Security=True;Encrypt=True;Trust Server Certificate=True";
            }
            else
            {
                return defaultConnectionString;
            }
        }

        [Option('p', "project", Required = true, HelpText = "Project file path.")]
        public string Project { get; set; } = string.Empty;

        


    }


    [Verb("build", isDefault: true, HelpText = "Build the project.")]
    public class BuildOptions : OptionsBase
    {
        public BuildOptions()
        { 
        }

        [Option('o', "output", HelpText = "Output directory.")]
        public string OutputDirectory { get; set; } = string.Empty;

        public static string GetDefaultOutputDirectory(string projectFilePath)
        {
            var projectDirectory = System.IO.Path.GetDirectoryName(projectFilePath);
            if (string.IsNullOrEmpty(projectDirectory))
            {
                projectDirectory = System.IO.Directory.GetCurrentDirectory();
            }
            return System.IO.Path.Combine(projectDirectory, "Generated");
        }

    }

    [Verb("import", HelpText = "Import database objects into the project.")]
    public class ImportOptions : OptionsBase
    {
        public ImportOptions()
        {
        }

        [Option('s', "schema", Required = false, HelpText = "Schema name.")]
        public string Schema { get; set; } = string.Empty;

        [Option('t', "table", Required = false, HelpText = "Table name.")]
        public string Table { get; set; } = string.Empty;

    }

}
