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
    public class StringFieldDefinition : FieldDefinition
    {
        string? _default = null;
        private int _size = 128;

        public StringFieldDefinition() : base()
        {
        }

        public StringFieldDefinition(SystemColumnType systemColumnType, Column column, FieldDefaultConstraint? defaultConstraint, FieldComputed? computed, List<FieldCheckConstraint>? checks)
            : base(systemColumnType, column, defaultConstraint, computed, checks)
        {
            if(systemColumnType >= SystemColumnType.NChar && systemColumnType <= SystemColumnType.SysName)
            {
                _size = column.MaxLength != -1 ? column.MaxLength / 2 : -1;
            }
            else if (systemColumnType == SystemColumnType.Char || systemColumnType == SystemColumnType.VarChar)
            {
                _size = column.MaxLength;
            }
            else
            {
                _size = -1;
            }
        }

        public override FieldType FieldType => FieldType.String;

        [XmlAttribute, DefaultValue(128)]
        public int Size { get => _size; set => _size = value; }
        [XmlAttribute("Default"), DefaultValue(null)]
        public string? Default { get => _default; set => _default = value; }
    }
}