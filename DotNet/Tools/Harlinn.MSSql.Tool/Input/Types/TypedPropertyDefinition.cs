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

using System.Xml;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public abstract class TypedPropertyDefinition : PropertyDefinition
    {
        TypeDefinition? _type = null;
        string _typeName = string.Empty;

        [XmlAttribute("Type")]
        public string TypeName { get => _typeName; set => _typeName = value; }

        [XmlIgnore]
        public TypeDefinition? Type { get => _type; set => _type = value; }

        internal override void Initialize2()
        {
            base.Initialize2();
            if (Owner != null && string.IsNullOrEmpty(TypeName) == false)
            {
                _type = Owner.GetTypeDefinition(TypeName);
            }
        }

    }









}
