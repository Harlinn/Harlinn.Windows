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

using Microsoft.SqlServer.Management.Smo;
using System.ComponentModel;
using System.Xml;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{

    [Serializable]
    public abstract class PropertyDefinition
    {
        ObjectDefinition? _owner = null;
        string _name = string.Empty;
        bool _isNullable = false;

        [XmlIgnore]
        public ObjectDefinition? Owner { get => _owner; set => _owner = value; }
        [XmlIgnore]
        public abstract PropertyKind Kind { get; }

        [XmlAttribute]
        public string Name { get => _name; set => _name = value; }
        
        [XmlAttribute, DefaultValue(false)]
        public bool IsNullable { get => _isNullable; set => _isNullable = value; }

        public override string ToString()
        {
            if(IsNullable)
            {
                return $"{Name}?";
            }
            return $"{Name}";
        }

        internal virtual void Initialize()
        {
        }

        internal virtual void Initialize2()
        {
        }


    }

}
