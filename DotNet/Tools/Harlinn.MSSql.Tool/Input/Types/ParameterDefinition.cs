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
    public abstract class ParameterDefinition
    {
        StoredProcedureDefinition? _owner;
        string _name;
        bool _isOutput;
        bool _isCursorRef;
        bool _hasDefaultValue;
        bool _isXmlDocument;
        string? _defaultValue;
        int _xmlCollectionId = 0;
        bool _isReadOnly;
        bool _isNullable;
        string? _databaseType = string.Empty;
        string? _description;

        protected ParameterDefinition()
        {
            _name = string.Empty;
        }

        protected ParameterDefinition(Parameter parameter, string? description)
        {
            _name = parameter.Name;
            _isOutput = parameter.IsOutput;
            _isCursorRef = parameter.IsCursorRef;
            _hasDefaultValue = parameter.HasDefaultValue;
            _isXmlDocument = parameter.IsXmlDocument;
            _defaultValue = parameter.DefaultValue?.ToString();
            _xmlCollectionId = parameter.XmlCollectionId ?? 0;
            _isReadOnly = parameter.IsReadOnly;
            _isNullable = parameter.IsNullable;
            _databaseType = parameter.TypeName;
            _description = description;
        }

        [XmlIgnore]
        public abstract ParameterType ParameterType { get; }

        [XmlIgnore]
        public StoredProcedureDefinition? Owner { get => _owner; set => _owner = value; }

        [XmlAttribute, DefaultValue("")]
        public string Name { get => _name; set => _name = value; }

        [XmlAttribute, DefaultValue(false)]
        public bool IsOutput { get => _isOutput; set => _isOutput = value; }

        [XmlAttribute, DefaultValue(false)]
        public bool IsCursorRef { get => _isCursorRef; set => _isCursorRef = value; }

        [XmlAttribute, DefaultValue(false)]
        public bool HasDefaultValue { get => _hasDefaultValue; set => _hasDefaultValue = value; }

        [XmlAttribute, DefaultValue(false)]
        public bool IsXmlDocument { get => _isXmlDocument; set => _isXmlDocument = value; }

        [XmlAttribute, DefaultValue(null)]
        public string? DefaultValue { get => _defaultValue; set => _defaultValue = value; }

        [XmlAttribute, DefaultValue(0)]
        public int XmlCollectionId { get => _xmlCollectionId; set => _xmlCollectionId = value; }

        [XmlAttribute, DefaultValue(false)]
        public bool IsReadOnly { get => _isReadOnly; set => _isReadOnly = value; }

        [XmlAttribute, DefaultValue(true)]
        public bool IsNullable { get => _isNullable; set => _isNullable = value; }

        [XmlAttribute, DefaultValue(null)]
        public string? DatabaseType { get => _databaseType; set => _databaseType = value; }

        [XmlElement, DefaultValue(null)]
        public string? Description { get => _description; set => _description = value; }
        

        public override string ToString()
        {
            if (IsNullable)
            {
                return $"{Name}?";
            }
            return $"{Name}";
        }

        internal virtual void Initialize()
        {
        }

        internal virtual void Initialize2()
        {
        }
    }

}
