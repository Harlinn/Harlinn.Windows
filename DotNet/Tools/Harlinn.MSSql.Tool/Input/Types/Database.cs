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

using System.Xml.Serialization;
using Microsoft.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;
using System.ComponentModel;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class Database
    {
        private Dictionary<string, Schema> _schemasByName = new Dictionary<string, Schema>(StringComparer.OrdinalIgnoreCase);
        private Project? _project = null;
        private string _name = string.Empty;
        private string? _description;
        private List<Schema> _schemas = new List<Schema>();

        [XmlIgnore]
        public Dictionary<string, Schema> SchemasByName { get => _schemasByName; set => _schemasByName = value; }
        [XmlIgnore]
        public Project? Project { get => _project; set => _project = value; }
        [XmlAttribute]
        public string Name { get => _name; set => _name = value; }
        [XmlArray("Schemas")]
        [XmlArrayItem(typeof(Schema), ElementName = "Schema")]
        public List<Schema> Schemas { get => _schemas; set => _schemas = value; }
        
        [XmlElement,DefaultValue(null)]
        public string? Description { get => _description; set => _description = value; }

        public Schema AddSchema(string schemaName)
        {
            var schema = new Schema
            {
                Name = schemaName,
                Owner = this
            };
            Schemas.Add(schema);
            SchemasByName[schemaName] = schema;
            return schema;
        }

        internal void Import(SqlConnection sqlConnection, ImportOptions options)
        {
            if(string.IsNullOrEmpty(_description))
            {
                _description = sqlConnection.GetDatabaseDescription();
            }
            string[] schemaNames = ["dbo"];
            if (!string.IsNullOrEmpty(options.Schema))
            {
                schemaNames = options.Schema.Split(';');
            }
            foreach (var schemaName in schemaNames)
            {
                if (!SchemasByName.TryGetValue(schemaName, out var schema))
                {
                    schema = AddSchema(schemaName);
                    if (string.IsNullOrEmpty(schema.Description))
                    {
                        schema.Description = sqlConnection.GetSchemaDescription(schemaName);
                    }
                }
                var schemaObject = sqlConnection.GetSchemaByName(schemaName);
                if (schemaObject != null)
                {
                    var tableName = options.Table;
                    if (string.IsNullOrEmpty(tableName) || tableName == "*")
                    {
                        var tables = sqlConnection.GetTables(schemaObject);
                        schema.ImportTables(sqlConnection, tables);

                        var views = sqlConnection.GetViews(schemaObject);
                        schema.ImportViews(sqlConnection, views);

                        if ( schemaName.Equals("sys", StringComparison.OrdinalIgnoreCase))
                        {
                            var systemViews = sqlConnection.GetSystemViews(schemaObject);
                            schema.ImportViews(sqlConnection, systemViews);
                        }

                        var procedures = sqlConnection.GetProcedures(schemaObject);
                        schema.ImportProcedures(sqlConnection, procedures);

                    }
                    else
                    {
                        var table = sqlConnection.GetTable(schemaObject, tableName);
                        if (table != null)
                        {
                            schema.ImportTable(sqlConnection, table);
                        }
                    }
                }
            }
        }

        internal void Initialize()
        {
            foreach (var schema in Schemas)
            {
                schema.Owner = this;
                schema.Initialize();
                SchemasByName[schema.Name] = schema;
            }
        }

        internal void Initialize2()
        {
            foreach (var schema in Schemas)
            {
                schema.Initialize2();
            }
        }

        public override string ToString()
        {
            return Name;
        }
    }


}
