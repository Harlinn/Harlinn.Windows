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

using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{

    [Serializable]
    public abstract class TypeDefinition
    {
        Schema? owner;
        [XmlIgnore]
        public abstract TypeKind Kind { get; }
        [XmlIgnore]
        public Schema? Owner { get => owner; set => owner = value; }

        [XmlAttribute]
        public string Name { get; set; } = string.Empty;

        public override string ToString()
        {
            return Name;
        }


        [XmlIgnore]
        public Project? Project => Owner?.Project;

        [XmlIgnore]
        public string TypeNamespace
        {
            get
            {
                var project = Project;
                var rootNamespace = project?.Namespace;
                var schemaNamespace = Owner?.Namespace;
                if (!string.IsNullOrEmpty(schemaNamespace))
                {
                    return $"{rootNamespace}.Types.{schemaNamespace}";
                }
                else
                {
                    return rootNamespace! + ".Types";
                }
            }
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
                project.TypeDefinitions[key] = this;
            }
        }

        internal virtual void Initialize()
        {
            AddToProject();
        }

        internal virtual void Initialize2()
        {
        }

        internal TypeDefinition? GetTypeDefinition(string typeDefinitionName)
        {
            if (string.IsNullOrEmpty(typeDefinitionName))
            {
                throw new ArgumentException("Type definition name cannot be null or empty.", nameof(typeDefinitionName));
            }
            var parts = typeDefinitionName.Split('.');
            if (parts.Length == 1)
            {
                // Only object name provided, use current schema
                var objectName = parts[0];
                if (Owner != null)
                {
                    if (Owner.TypeDefinitions.TryGetValue(objectName, out var typeDefinition))
                    {
                        return typeDefinition;
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
                            if (Owner!.TypeDefinitions.TryGetValue(objectName, out var typeDefinition))
                            {
                                return typeDefinition;
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
                    if (project.TypeDefinitions.TryGetValue(typeDefinitionName, out var typeDefinition))
                    {
                        return typeDefinition;
                    }
                }
            }
            return null;
        }


    }



}
