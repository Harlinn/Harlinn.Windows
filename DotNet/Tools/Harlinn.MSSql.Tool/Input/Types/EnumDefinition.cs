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

using System.ComponentModel;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public class EnumDefinition : TypeDefinition
    {
        [XmlIgnore]
        Dictionary<string, EnumValueDefinition> ValuesByName { get; set; } = new Dictionary<string, EnumValueDefinition>(); 
        public override TypeKind Kind => TypeKind.Enum;

        [XmlAttribute,DefaultValue("Int32")]
        public string UnderlyingType { get; set; } = "Int32";

        [XmlAttribute, DefaultValue(false)]
        public bool IsFlags { get; set; } = false;

        [XmlArray("Values")]
        [XmlArrayItem(typeof(EnumValueDefinition), ElementName = "Value")]
        public List<EnumValueDefinition> Values { get; set; } = new List<EnumValueDefinition>();

        [XmlIgnore]
        public string DefaultValue
        {
            get
            {
                if (Values.Count > 0)
                {
                    return $"{Name}.{Values[0].Name}";
                }
                else
                {
                    return string.Empty;
                }
            }
        }

        internal override void Initialize()
        {
            base.Initialize();
            ValuesByName.Clear();
            foreach (var value in Values)
            {
                value.Owner = this;
                ValuesByName[value.Name] = value;
            }

            long previousValue = 0;

            for (int i = 0; i < Values.Count; i++)
            {
                var value = Values[i];
                if (value.Value.HasValue)
                {
                    previousValue = value.Value.Value;
                }
                else
                {
                    if (IsFlags)
                    {
                        var k = long.Log2(previousValue) / long.Log2(2);
                        previousValue = 1L << (int)(k + 1);
                    }
                    else
                    {
                        previousValue++;
                    }
                    value.Value = previousValue;
                }
            }

        }

    }



}
