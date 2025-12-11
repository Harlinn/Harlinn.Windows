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
        string? _entity;
        [XmlIgnore]
        public EntityDefinition? Owner { get; set; } = null;

        [XmlAttribute]
        public string Name { get; set; } = string.Empty;
        
        [XmlAttribute]
        public string Entity
        {
            get
            {
                if (string.IsNullOrEmpty(_entity) )
                {
                    if (string.IsNullOrEmpty(ReferencedTableName) == false)
                    {
                        if (string.IsNullOrEmpty(ReferencedSchemaName) == false)
                        {
                            return $"{ReferencedSchemaName}.{ReferencedTableName}";
                        }
                        return ReferencedTableName;
                    }
                    
                }
                return _entity ?? string.Empty;
            }

            set
            {
                _entity = value;
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
                reference.Initialize();
            }
        }
    }


}
