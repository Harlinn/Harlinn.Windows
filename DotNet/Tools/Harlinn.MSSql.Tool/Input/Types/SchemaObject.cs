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

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public abstract class SchemaObject
    {
        public abstract SchemaObjectType Type { get; }

        [XmlIgnore]
        public Schema? Owner { get; set; } = null;

        [XmlIgnore]
        public Project? Project => Owner?.Project;

        [XmlAttribute]
        public string Name { get; set; } = string.Empty;

        internal virtual void Initialize()
        {
            AddToProject();
        }

        internal void AddToProject()
        {
            var project = Owner?.Owner?.Project;
            if (project != null)
            {
                var databaseName = Owner?.Owner?.Name;
                var schemaName = Owner?.Name;
                var objectName = Name;
                var key = $"{databaseName}.{schemaName}.{objectName}";
                project.SchemaObjects[key] = this;
                if (this is EntityDefinition entity)
                {
                    var tableName = entity.Name;
                    var qualifiedTableName = $"{databaseName}.{schemaName}.{tableName}";
                    project.EntitiesByTableName[qualifiedTableName] = entity;
                    project.Entities.Add(entity);
                }
            }
        }

        internal virtual void Initialize2()
        {
            
        }

        internal SchemaObject? GetSchemaObject( string schemaObjectName)
        {
            if (string.IsNullOrEmpty(schemaObjectName))
            {
                throw new ArgumentException("Schema object name cannot be null or empty.", nameof(schemaObjectName));
            }
            var parts = schemaObjectName.Split('.');
            if (parts.Length == 1)
            {
                // Only object name provided, use current schema
                var objectName = parts[0];
                if (Owner != null)
                {
                    if (Owner.ObjectsByName.TryGetValue(objectName, out var schemaObject))
                    {  
                        return schemaObject; 
                    }
                    if (Owner.EntitiesByTableName.TryGetValue(objectName, out var entity))
                    {
                        return entity;
                    }
                }
            }
            else if (parts.Length == 2)
            {
                // Schema and object name provided
                var schemaName = parts[0];
                var objectName = parts[1];
                var database = Owner?.Owner;
                if (database != null)
                {
                    foreach (var schema in database.Schemas)
                    {
                        if (schema.Name.Equals(schemaName, StringComparison.OrdinalIgnoreCase))
                        {
                            if (schema.ObjectsByName.TryGetValue(objectName, out var schemaObject))
                            {
                                return schemaObject;
                            }
                            if (schema.EntitiesByTableName.TryGetValue(objectName, out var entity))
                            {
                                return entity;
                            }
                        }
                    }
                }
            }
            else if (parts.Length == 3)
            {
                var project = Owner?.Owner?.Project;
                if (project != null)
                {
                    if (project.SchemaObjects.TryGetValue(schemaObjectName, out var schemaObject))
                    {
                        return schemaObject;
                    }
                    if (project.EntitiesByTableName.TryGetValue(schemaObjectName, out var entity))
                    {
                        return entity;
                    }
                }
            }
            return null;
        }

    }


}
