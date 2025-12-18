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
using System.ComponentModel;
using System.Xml.Serialization;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class Schema
    {
        [XmlIgnore]
        public Dictionary<string, SchemaObject> ObjectsByName { get; set; } = new Dictionary<string, SchemaObject>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public Dictionary<string, EntityDefinition> EntitiesByTableName { get; set; } = new Dictionary<string, EntityDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public Dictionary<string, TypeDefinition> TypeDefinitions { get; set; } = new Dictionary<string, TypeDefinition>();

        [XmlIgnore]
        public Database? Owner { get; set; } = null;

        [XmlIgnore]
        public Project? Project => Owner?.Project;

        [XmlAttribute]
        public string Name { get; set; } = string.Empty;

        [XmlAttribute, DefaultValue("")]
        public string Namespace { get; set; } = string.Empty;

        [XmlArray("Types")]
        [XmlArrayItem(typeof(EnumDefinition), ElementName = "Enum")]
        [XmlArrayItem(typeof(ClassDefinition), ElementName = "Class")]
        [XmlArrayItem(typeof(StructDefinition), ElementName = "Struct")]
        public List<TypeDefinition> Types { get; set; } = new List<TypeDefinition>();

        [XmlArray("Objects")]
        [XmlArrayItem(typeof(EntityDefinition), ElementName = "Entity")]
        [XmlArrayItem(typeof(ViewDefinition), ElementName = "View")]
        [XmlArrayItem(typeof(StoredProcedureDefinition), ElementName = "StoredProcedure")]
        [XmlArrayItem(typeof(FunctionDefinition), ElementName = "Function")]
        public List<SchemaObject> Objects { get; set; } = new List<SchemaObject>();

        


        internal void Initialize()
        {
            foreach (var typeDefinition in Types)
            {
                typeDefinition.Owner = this;
                TypeDefinitions[typeDefinition.Name] = typeDefinition;
                typeDefinition.Initialize();
            }

            foreach (var schemaObject in Objects)
            {
                schemaObject.Owner = this;
                schemaObject.Initialize();
                ObjectsByName[schemaObject.Name] = schemaObject;
                if (schemaObject is EntityDefinition entity && entity.Table != null)
                {
                    var tableName = string.IsNullOrEmpty(entity.Table) ? entity.Name : entity.Table;
                    EntitiesByTableName[tableName] = entity;
                }
            }
        }

        public EntityDefinition AddEntity(SchemaTypes.Table table) 
        {
            if(EntitiesByTableName.TryGetValue(table.Name, out var existingEntity))
            {
                return existingEntity;
            }
            var entity = new EntityDefinition
            {
                Name = table.Name,
                Owner = this,
                Table = table.Name
            };
            Objects.Add(entity);
            ObjectsByName[entity.Name] = entity;
            EntitiesByTableName[entity.Table] = entity;
            entity.AddToProject();
            return entity;
        }

        internal void Initialize2()
        {
            foreach (var typeDefinition in Types)
            {
                typeDefinition.Initialize2();
            }

            foreach (var schemaObject in Objects)
            {
                schemaObject.Initialize2();
            }
        }

        internal void ImportTables(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.Table> tables)
        {
            foreach (var table in tables)
            {
                ImportTable(sqlConnection, table);
            }
        }

        internal void ImportTable(SqlConnection sqlConnection, SchemaTypes.Table table)
        {
            var schemaObject = AddEntity(table);

            if (schemaObject is EntityDefinition entity)
            {
                entity.ImportTable(sqlConnection, table);
            }
        }

        public override string ToString()
        {
            return Name;
        }

    }


}
