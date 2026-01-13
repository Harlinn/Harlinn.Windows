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
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Harlinn.Common.Core.Net;
using System.ComponentModel;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public abstract class CheckConstraint
    {
        string? _name;
        string? _definition;
        bool _isSystemNamed;

        protected CheckConstraint()
        { }

        protected CheckConstraint(SchemaTypes.CheckConstraint checkConstraint)
        {
            _name = checkConstraint.Name;
            _definition = checkConstraint.Definition;
            _isSystemNamed = checkConstraint.IsSystemNamed;
        }

        protected CheckConstraint(string? name, string? definition, bool isSystemNamed)
        {
            _name = name;
            _definition = definition;
            _isSystemNamed = isSystemNamed;
        }

        [XmlAttribute]
        public string? Name { get => _name; set => _name = value; }

        /*
        [XmlElement("Definition"), DefaultValue(null)]
        public string? DefinitionHtmlEncoded
        {
            get
            {
                return _definition.HtmlEncode();
            }
            set
            {
                _definition = value.HtmlDecode();
            }
        }
        [XmlIgnore]
        */
        [XmlElement("Definition"), DefaultValue(null)]
        public string? Definition { get => _definition; set => _definition = value; }
        [XmlAttribute, DefaultValue(false)]
        public bool IsSystemNamed { get => _isSystemNamed; set => _isSystemNamed = value; }
    }

}
