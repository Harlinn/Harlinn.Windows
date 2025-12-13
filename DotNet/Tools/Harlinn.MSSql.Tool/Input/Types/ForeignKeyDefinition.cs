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
    public class ForeignKeyDefinition
    {
        [XmlIgnore]
        public Dictionary<string, ForeignKeyReferenceDefinition> ReferencesByName { get; set; } = new Dictionary<string, ForeignKeyReferenceDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        EntityDefinition? _entity;
        [XmlIgnore]
        string? _entityName;
        [XmlIgnore]
        public EntityDefinition? Owner { get; set; } = null;

        [XmlAttribute]
        public string Name { get; set; } = string.Empty;

        [XmlIgnore]
        public EntityDefinition? Entity
        {
            get
            {
                if (_entity == null)
                {
                    var entityName = EntityName;
                    if (Owner != null && string.IsNullOrEmpty(entityName) == false)
                    {
                        _entity = Owner.GetSchemaObject(entityName) as EntityDefinition;
                    }
                }
                return _entity;
            }

            set => _entity = value;
        }

        [XmlAttribute("Entity")]
        public string EntityName
        {
            get
            {
                if (string.IsNullOrEmpty(_entityName) )
                {
                    _entityName = GetEntityName();
                }
                return _entityName ?? string.Empty;
            }
            set
            {
                _entityName = value;
            }
        }

        [XmlAttribute]
        public string ReferencedTableName { get; set; } = string.Empty;
        [XmlAttribute]
        public string ReferencedSchemaName { get; set; } = string.Empty;

        [XmlArray("References")]
        [XmlArrayItem("Reference")]
        public List<ForeignKeyReferenceDefinition> References { get; set; } = new List<ForeignKeyReferenceDefinition>();
        

        internal void Initialize()
        {
            foreach (var reference in References)
            {
                reference.Owner = this;
                ReferencesByName[reference.Field] = reference;
                reference.Initialize();
            }
        }

        internal void Initialize2()
        {
            FixupEntityName();
            foreach (var reference in References)
            {
                //reference.Initialize2();
            }
        }

        string GetEntityName()
        {
            if (Owner != null)
            {
                if (null != _entity)
                {
                    var schemaName = _entity.Owner!.Name;
                    return $"{schemaName}.{_entity.Name}";
                }
                if (string.IsNullOrEmpty(ReferencedTableName) == false)
                {
                    string fullName;
                    if (string.IsNullOrEmpty(ReferencedSchemaName) == false)
                    {
                        fullName = $"{ReferencedSchemaName}.{ReferencedTableName}";
                    }
                    else
                    {
                        fullName = ReferencedTableName;
                    }
                    var entity = Owner.GetSchemaObject(fullName) as EntityDefinition;
                    if (null != entity)
                    {
                        var schemaName = entity.Owner!.Name;
                        return $"{schemaName}.{entity.Name}";
                    }
                }
            }
            return string.Empty;
        }

        void FixupEntityName()
        {
            if (Owner != null)
            {
                if(string.IsNullOrEmpty(_entityName) == false)
                {
                    _entity = Owner.GetSchemaObject(_entityName) as EntityDefinition;
                    if (null != _entity)
                    {
                        // Valid _entityName
                        var schemaName = _entity.Owner!.Name;
                        _entityName = $"{schemaName}.{_entity.Name}";
                        return; 
                    }
                }
                if (string.IsNullOrEmpty(ReferencedTableName) == false)
                {
                    string fullName;
                    if (string.IsNullOrEmpty(ReferencedSchemaName) == false)
                    {
                        fullName = $"{ReferencedSchemaName}.{ReferencedTableName}";
                    }
                    else
                    {
                        fullName = ReferencedTableName;
                    }
                    _entity = Owner.GetSchemaObject(fullName) as EntityDefinition;
                    if (null != _entity)
                    {
                        var schemaName = _entity.Owner!.Name;
                        _entityName = $"{schemaName}.{_entity.Name}";
                        return;
                    }
                }
            }
        }

        internal int GetIndexOfReference(string fieldName)
        {
            for (int i = 0; i < References.Count; i++)
            {
                if (References[i].Field.Equals(fieldName, StringComparison.OrdinalIgnoreCase))
                {
                    return i;
                }
            }
            return -1;
        }

        internal void AddReference(ForeignKeyReferenceDefinition reference)
        {
            reference.Owner = this;
            int index = GetIndexOfReference(reference.Field);
            if (index >= 0)
            {
                References[index] = reference;
            }
            else
            {
                References.Add(reference);
            }
            ReferencesByName[reference.Field] = reference;
            reference.Initialize();
        }

    }


}
