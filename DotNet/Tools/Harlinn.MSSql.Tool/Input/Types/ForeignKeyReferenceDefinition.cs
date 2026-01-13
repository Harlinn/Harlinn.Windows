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
    public class ForeignKeyReferenceDefinition
    {
        [XmlIgnore]
        public FieldDefinition? Definition
        {
            get
            {
                if (Owner != null && Owner.Owner != null)
                {
                    var entity = Owner.Owner;
                    return entity.FieldsByName.TryGetValue(Field, out var fieldDefinition) ? fieldDefinition : null;
                }
                return null;
            }
        }

        [XmlIgnore]
        public FieldDefinition? ReferencesDefinition
        {
            get
            {
                if (Owner != null && Owner.Owner != null)
                {
                    var entity = Owner.Entity!;
                    return entity.FieldsByName.TryGetValue(References, out var fieldDefinition) ? fieldDefinition : null;
                }
                return null;
            }
        }


        [XmlIgnore]
        public ForeignKeyDefinition? Owner { get; set; } = null;

        [XmlAttribute]
        public string Field { get; set; } = string.Empty;

        [XmlAttribute]
        public string References { get; set; } = string.Empty;

        internal void Initialize()
        {
            
        }
    }


}
