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
    public abstract class ValueFieldDefinition<T> : FieldDefinition where T : struct
    {
        T _default = default(T);

        public ValueFieldDefinition()
        {
        }

        public ValueFieldDefinition(SystemColumnType systemColumnType, Column column, FieldDefaultConstraint? defaultConstraint, FieldComputed? computed, List<FieldCheckConstraint>? checks)
            : base(systemColumnType, column, defaultConstraint, computed, checks)
        {
        }

        [XmlAttribute("Default"), DefaultValue(null)]
        public string? DefaultAsString
        {
            get
            {
                if (_default.Equals(default(T)))
                {
                    return null;
                }
                return _default.ToString();
            }

            set
            {
                if (value != null)
                {
                    _default = (T)Convert.ChangeType(value, typeof(T));
                }
                else
                {
                    _default = default(T);
                }
            }
        }

        [XmlIgnore]
        public T Default
        {
            get => _default;
            set => _default = value;
        }

        [XmlIgnore]
        public bool HasDefault => _default.Equals(default(T)) == false;

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