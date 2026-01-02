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

using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using System.ComponentModel;
using System.Xml;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class GuidParameterDefinition : ParameterDefinition
    {
        Guid _default = Guid.Empty;
        public GuidParameterDefinition()
            : base()
        {
        }
        public GuidParameterDefinition(Parameter parameter, string? description)
            : base(parameter, description)
        {
        }
        public override ParameterType ParameterType => ParameterType.Guid;

        [XmlAttribute("Default"), DefaultValue(null)]
        public string? DefaultAsString
        {
            get
            {
                if (_default == Guid.Empty)
                {
                    return null;
                }
                return _default.ToString();
            }

            set
            {
                if (string.IsNullOrWhiteSpace(value) == false)
                {
                    if (Guid.TryParse(value, out var guid) == false)
                    {
                        _default = Guid.Parse($"{{{value}}}");
                    }
                    else
                    {
                        _default = guid;
                    }
                }
                else
                {
                    _default = Guid.Empty;
                }
            }
        }

        [XmlIgnore]
        public Guid Default { get => _default; set => _default = value; }

        [XmlIgnore]
        public bool HasDefault => _default != Guid.Empty;

        public override string ToString()
        {
            var result = base.ToString();
            if (HasDefault)
            {
                return $"{result} Default({_default})";
            }
            return result;
        }
    }



}
