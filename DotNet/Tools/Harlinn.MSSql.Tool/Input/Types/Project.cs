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

using Harlinn.Common.Core.Net;
using Microsoft.Data.SqlClient;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [XmlRoot("Project")]
    public class Project
    {
        [XmlIgnore]
        public Dictionary<string, Database> DatabasesByName { get; set; } = new Dictionary<string, Database>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public Dictionary<string, SchemaObject> SchemaObjects { get; set; } = new Dictionary<string, SchemaObject>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public Dictionary<string, RowSourceDefinition> RowSourcesByName { get; set; } = new Dictionary<string, RowSourceDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public Dictionary<string, RowSourceDefinition> RowSourcesByAcronym { get; set; } = new Dictionary<string, RowSourceDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public List<RowSourceDefinition> RowSources { get; set; } = new List<RowSourceDefinition>();

        [XmlIgnore]
        public List<EntityDefinition> Entities => RowSources.Where(rs => rs.Type == SchemaObjectType.Entity).Cast<EntityDefinition>().ToList();

        [XmlIgnore]
        public List<ViewDefinition> Views => RowSources.Where(rs => rs.Type == SchemaObjectType.View).Cast<ViewDefinition>().ToList();

        [XmlIgnore]
        public Dictionary<string, TypeDefinition> TypeDefinitions { get; set; } = new Dictionary<string, TypeDefinition>();


        [XmlAttribute]
        public string Name { get; set; } = string.Empty;

        [XmlAttribute]
        public string Namespace { get; set; } = string.Empty;

        public string GetNamespace()
        {
            if (!string.IsNullOrEmpty(Namespace))
            {
                return Namespace;
            }
            return Name.FirstToUpper() ?? string.Empty;
        }


        [XmlArray("Databases")]
        [XmlArrayItem(typeof(Database), ElementName = "Database")]
        public List<Database> Databases { get; set; } = new List<Database>();

        public void Initialize()
        {
            foreach (var database in Databases)
            {
                database.Project = this;
                database.Initialize();
                DatabasesByName[database.Name] = database;
            }

            foreach (var database in Databases)
            {
                database.Initialize2();
            }
        }

        public Database AddDatabase(string name)
        {
            var database = new Database { Name = name, Project = this };
            DatabasesByName[name] = database;
            Databases.Add(database);
            return database;
        }


        public void SaveToFile(string filePath)
        {
            using FileStream fileStream = new FileStream(filePath, FileMode.Create, FileAccess.Write);
            XmlSerializer xmlSerializer = new XmlSerializer(typeof(Project));
            xmlSerializer.Serialize(fileStream, this);
        }

        public void Import(SqlConnection sqlConnection, ImportOptions options)
        {
            var databaseName = sqlConnection.Database;
            if (DatabasesByName.TryGetValue(databaseName, out var database))
            {
                database.Import(sqlConnection, options);
            }
            else
            {
                var newDatabase = AddDatabase(databaseName);
                newDatabase.Import(sqlConnection, options);
            }
        }

        public override string ToString()
        {
            return Name;
        }
    }


}
