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
using System.Numerics;
using System.Xml.Serialization;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public abstract class IntegerFieldDefinition<T> : NumberFieldDefinition<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {
        Identity<T>? _identity;

        public IntegerFieldDefinition()
            : base()
        {
        }

        public IntegerFieldDefinition(SystemColumnType systemColumnType, Column column, FieldDefaultConstraint? defaultConstraint, FieldComputed? computed, List<FieldCheckConstraint>? checks)
            : base(systemColumnType, column, defaultConstraint, computed, checks)
        {
        }

        [XmlElement("Identity"), DefaultValue(null)]
        public Identity<T>? Identity { get => _identity; set => _identity = value; }

        public override bool IsIdentity => _identity != null;
    }


}