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

using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using System.ComponentModel;
using System.Xml;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class DecimalParameterDefinition : NumericParameterDefinition<decimal>
    {
        int _precision = 18;
        int _scale = 0;
        public DecimalParameterDefinition()
            : base()
        {
        }
        public DecimalParameterDefinition(Parameter parameter, string? description)
            : base(parameter, description)
        {
            _precision = parameter.Precision;
            _scale = parameter.Scale;
        }
        public override ParameterType ParameterType => ParameterType.Decimal;

        [XmlAttribute, DefaultValue(18)]
        public int Precision { get => _precision; set => _precision = value; }
        [XmlAttribute, DefaultValue(0)]
        public int Scale { get => _scale; set => _scale = value; }

    }



}
