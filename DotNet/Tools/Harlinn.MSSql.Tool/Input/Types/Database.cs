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

using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Microsoft.Data.SqlClient;
using Microsoft.IdentityModel.Tokens;
using System.ComponentModel;
using System.Xml.Serialization;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;

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


        static bool IsMatch(ImportOptions options, SchemaTypes.SchemaObject schemaObject)
        {
            var schemaObjectType = schemaObject.Type;
            switch(schemaObjectType)
            {
                case SchemaTypes.SchemaObjectType.Table:
                    if (options.Tables)
                    {
                        return true;
                    }
                    break;
                case SchemaTypes.SchemaObjectType.View:
                    if (options.Views)
                    {
                        return true;
                    }
                    break;
                case SchemaTypes.SchemaObjectType.StoredProcedure:
                    if (options.Procedures)
                    {
                        return true;
                    }
                    break;
            }

            var optionsObjects = options.Objects;
            if (optionsObjects != null)
            {
                foreach (var objectNameOrPattern in optionsObjects)
                {
                    if (options.Regex)
                    {
                        if (System.Text.RegularExpressions.Regex.IsMatch(schemaObject.Name, objectNameOrPattern, System.Text.RegularExpressions.RegexOptions.IgnoreCase))
                        {
                            return true;
                        }
                    }
                    else
                    {
                        if (schemaObject.Name.Equals(objectNameOrPattern, StringComparison.OrdinalIgnoreCase))
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        static bool IsExluded(ImportOptions options, SchemaTypes.SchemaObject schemaObject)
        {
            var excludedObjects = options.ExcludedObjects;
            if (excludedObjects != null)
            {
                foreach (var objectNameOrPattern in excludedObjects)
                {
                    if (options.Regex)
                    {
                        if (System.Text.RegularExpressions.Regex.IsMatch(schemaObject.Name, objectNameOrPattern, System.Text.RegularExpressions.RegexOptions.IgnoreCase))
                        {
                            return true;
                        }
                    }
                    else
                    {
                        if (schemaObject.Name.Equals(objectNameOrPattern, StringComparison.OrdinalIgnoreCase))
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }


        internal void ImportSchemaObjectsByName(SqlConnection sqlConnection, ImportOptions options, Schema schema)
        {
            var schemaObjects = sqlConnection.GetSchemaObjects(schema.Name);
            foreach (var schemaObject in schemaObjects)
            {
                var isMatch = IsMatch(options, schemaObject);
                var isExcluded = IsExluded(options, schemaObject);
                if (isMatch && !isExcluded)
                {
                    switch (schemaObject.Type)
                    {
                        case SchemaTypes.SchemaObjectType.Table:
                            var table = sqlConnection.GetTable(schemaObject);
                            if (table != null)
                            {
                                schema.ImportTable(sqlConnection, table);
                            }
                            break;
                        case SchemaTypes.SchemaObjectType.View:
                            var view = sqlConnection.GetView(schemaObject);
                            if (view != null)
                            {
                                schema.ImportView(sqlConnection, view);
                            }
                            break;
                        case SchemaTypes.SchemaObjectType.StoredProcedure:
                            var procedure = sqlConnection.GetProcedure(schemaObject);
                            if (procedure != null)
                            {
                                schema.ImportProcedure(sqlConnection, procedure);
                            }
                            break;
                    }
                }
            }
        }

        internal void ImportSchema(SqlConnection sqlConnection, ImportOptions options, string schemaName)
        {
            if(string.IsNullOrEmpty(schemaName) == false)
            {
                var schemaNames = schemaName.Split(';');
                foreach(var name in schemaNames)
                {
                    var schemaData = sqlConnection.GetSchemaByName(name);
                    if (schemaData != null)
                    {
                        Schema? schema = null;
                        if (!SchemasByName.TryGetValue(name, out schema))
                        {
                            schema = AddSchema(name);
                            if (string.IsNullOrEmpty(schema.Description))
                            {
                                schema.Description = sqlConnection.GetSchemaDescription(name);
                            }
                        }
                        ImportSchemaObjectsByName(sqlConnection, options, schema);
                    }
                }
            }
            
        }

        internal void Import(SqlConnection sqlConnection, ImportOptions options)
        {
            if(string.IsNullOrEmpty(_description))
            {
                _description = sqlConnection.GetDatabaseDescription();
            }

            var schemas = options.Schemas;
            if(schemas == null || schemas.Count() == 0)
            {
                schemas = new string[] { "dbo" };
            }

            foreach ( var schemaName in schemas )
            {
                ImportSchema(sqlConnection, options, schemaName);
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
