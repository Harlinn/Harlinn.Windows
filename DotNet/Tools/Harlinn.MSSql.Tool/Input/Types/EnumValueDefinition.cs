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
    [Serializable]
    public class EnumValueDefinition
    {
        EnumDefinition? _owner = null;
        string _name = string.Empty;
        long? _value;

        public EnumValueDefinition()
        { }

        public EnumValueDefinition(string name, long? value)
        {
            _name = name;
            _value = value;
        }

        [XmlIgnore]
        public EnumDefinition? Owner { get => _owner; set => _owner = value; }

        [XmlAttribute]
        public string Name { get => _name; set => _name = value; }

        [XmlAttribute("Value"),DefaultValue(null)]
        public string ? ValueString
        {
            get => _value.HasValue ? _value.Value.ToString() : null;
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    _value = null;
                }
                else
                {
                    if (long.TryParse(value, out var longValue))
                    {
                        _value = longValue;
                    }
                    else
                    {
                        throw new FormatException($"Invalid enum value: '{value}' for enum value name: '{Name}'");
                    }
                }
            }
        }

        [XmlIgnore]
        public long? Value { get => _value; set => _value = value; }
        

        public override string ToString()
        {
            return $"{Name}:{Value}";
        }

    }



}
