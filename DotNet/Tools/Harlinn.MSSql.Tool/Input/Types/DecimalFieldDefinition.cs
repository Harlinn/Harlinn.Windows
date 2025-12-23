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
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public class DecimalFieldDefinition : NumericFieldDefinition<decimal>
    {
        int _precision = 18;
        int _scale = 0;
        Identity<decimal>? _identity;

        public DecimalFieldDefinition()
            : base()
        {
        }

        public DecimalFieldDefinition(Column column)
            : base(column)
        {
            _precision = column.Precision;
            _scale = column.Scale;
        }

        public override FieldType FieldType => FieldType.Decimal;

        [XmlAttribute, DefaultValue(18)]
        public int Precision { get => _precision; set => _precision = value; }
        [XmlAttribute, DefaultValue(0)]
        public int Scale { get => _scale; set => _scale = value; }


        [XmlElement("Identity"), DefaultValue(null)]
        public Identity<decimal>? Identity { get => _identity; set => _identity = value; }

        [XmlIgnore]
        public override bool IsIdentity => _identity != null;
    }
}