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
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class EntityCheckConstraint : CheckConstraint
    {
        EntityDefinition? _owner;
        public EntityCheckConstraint()
        { }

        public EntityCheckConstraint(EntityDefinition? owner, SchemaTypes.CheckConstraint checkConstraint)
            : base(checkConstraint)
        {
            _owner = owner;
        }

        public EntityCheckConstraint(string? name, string? definition, bool isSystemNamed) 
            : base(name, definition, isSystemNamed)
        {
        }

        [XmlIgnore]
        public EntityDefinition? Owner { get => _owner; set => _owner = value; }
    }


}
