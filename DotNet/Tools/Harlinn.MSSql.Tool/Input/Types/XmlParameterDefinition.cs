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
    public class XmlParameterDefinition : ParameterDefinition
    {
        string? _default = null;
        public XmlParameterDefinition() : base()
        {
        }
        public XmlParameterDefinition(Parameter parameter, string? description)
            : base(parameter, description)
        {
        }
        public override ParameterType ParameterType => ParameterType.Xml;
        [XmlAttribute("Default"), DefaultValue(null)]
        public string? Default { get => _default; set => _default = value; }
    }



}
