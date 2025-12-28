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
    public class BinaryFieldDefinition : FieldDefinition
    {
        byte[]? _default = null;
        private int _size = 128;

        public BinaryFieldDefinition() : base()
        {
        }

        public BinaryFieldDefinition(SystemDataType systemColumnType, Column column, FieldDefaultConstraint? defaultConstraint, FieldComputed? computed, List<FieldCheckConstraint>? checks) 
            : base(systemColumnType, column, defaultConstraint, computed, checks)
        {
            if (systemColumnType == SystemDataType.Image)
            {
                _size = -1;
            }
            else
            {
                _size = column.MaxLength;
            }
        }

        public override FieldType FieldType => FieldType.Binary;

        [XmlAttribute, DefaultValue(128)]
        public int Size { get => _size; set => _size = value; }
        [XmlIgnore]
        public byte[]? Default { get => _default; set => _default = value; }
        [XmlAttribute("Default"), DefaultValue(null)]
        public string? DefaultAsBase64
        {
            get
            {
                if (_default == null || _default.Length == 0)
                {
                    return null;
                }
                return Convert.ToBase64String(_default);
            }
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    _default = null;
                }
                else
                {
                    _default = Convert.FromBase64String(value);
                }
            }
        }
        public override string ToString()
        {
            var result = base.ToString();
            if (_default != null && _default.Length > 0)
            {
                return $"{result} Default(0x{BitConverter.ToString(_default).Replace("-", "")})";
            }
            return result;
        }
    }






}