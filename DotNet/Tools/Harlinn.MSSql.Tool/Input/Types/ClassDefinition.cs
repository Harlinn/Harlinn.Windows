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
using System.Reflection.Metadata;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public class ClassDefinition : ObjectDefinition
    {
        ClassDefinition? _baseClass = null;
        public override TypeKind Kind => TypeKind.Class;

        [XmlAttribute("Base"), DefaultValue(null)]
        public string? BaseTypeName { get; set; }

        [XmlIgnore]
        public ClassDefinition? BaseClass { get => _baseClass; set => _baseClass = value; }

        internal override void Initialize2()
        {
            base.Initialize2();

            if (string.IsNullOrEmpty(BaseTypeName) == false)
            {
                _baseClass = GetTypeDefinition(BaseTypeName) as ClassDefinition;
            }

            foreach (var property in Properties)
            {
                property.Initialize2();
            }
        }

    }



}
