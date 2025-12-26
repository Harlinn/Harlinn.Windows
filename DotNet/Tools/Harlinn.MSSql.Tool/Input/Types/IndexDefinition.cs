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

using System.ComponentModel;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class IndexDefinition
    {
        [XmlIgnore]
        public Dictionary<string, IndexFieldDefinition> FieldsByName { get; set; } = new Dictionary<string, IndexFieldDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public RowSourceDefinition? Owner { get; set; } = null;

        [XmlAttribute]
        public string Name { get; set; } = string.Empty;

        [XmlAttribute, DefaultValue(false)]
        public bool IsUnique { get; set; } = false;

        [XmlAttribute, DefaultValue(false)]
        public bool IsPrimaryKey { get; set; } = false;

        [XmlArray("Fields")]
        [XmlArrayItem(typeof(IndexFieldDefinition), ElementName = "Field")]
        public List<IndexFieldDefinition> Fields { get; set; } = new List<IndexFieldDefinition>();
        

        internal void Initialize()
        {
            foreach (var field in Fields)
            {
                field.Owner = this;
                FieldsByName[field.Name] = field;
                field.Initialize();
            }
        }

        internal int GetIndexOfField(string fieldName)
        {
            for (int i = 0; i < Fields.Count; i++)
            {
                if (Fields[i].Name.Equals(fieldName, StringComparison.OrdinalIgnoreCase))
                {
                    return i;
                }
            }
            return -1;
        }

        internal void AddField(IndexFieldDefinition field)
        {
            field.Owner = this;
            int index = GetIndexOfField(field.Name);
            if (index >= 0)
            {
                Fields[index] = field;
            }
            else
            {
                Fields.Add(field);
            }
            FieldsByName[field.Name] = field;
            field.Initialize();
        }

    }



}
