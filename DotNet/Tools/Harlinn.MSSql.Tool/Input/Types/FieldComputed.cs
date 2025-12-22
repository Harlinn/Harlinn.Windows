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

using Harlinn.Common.Core.Net;
using System.ComponentModel;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class FieldComputed
    {
        string? _definition = string.Empty;
        bool _isPersisted = false;
        
        public FieldComputed()
        { }
        public FieldComputed(string expression,  bool isPersisted)
        {
            _definition = expression;
            _isPersisted = isPersisted;
        }

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
        public string? Definition { get => _definition; set => _definition = value; }
        [XmlAttribute, DefaultValue(false)]
        public bool IsPersisted { get => _isPersisted; set => _isPersisted = value; }
        
    }


}