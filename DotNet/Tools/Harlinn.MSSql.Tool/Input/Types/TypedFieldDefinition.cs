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
    public abstract class TypedFieldDefinition : FieldDefinition
    {
        TypeDefinition? _type;
        private string? _typeName;
        

        [XmlAttribute("Type"),DefaultValue(null)]
        public string? TypeName { get => _typeName; set => _typeName = value; }

        [XmlIgnore]
        public TypeDefinition? Type { get => _type; set => _type = value; }

        override internal void Initialize2()
        {
            base.Initialize2();
            if (!string.IsNullOrEmpty(_typeName) && Owner != null)
            {
                _type = Owner.GetTypeDefinition(_typeName);
                if (_type == null)
                {
                    throw new InvalidOperationException($"Type '{_typeName}' not found for field '{Name}' in '{Owner.Name}'");
                }
            }
        }

    }


}