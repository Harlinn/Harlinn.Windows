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
    public abstract class FieldDefinition : IEquatable<FieldDefinition>
    {
        [XmlIgnore]
        bool? _isReference;
        FieldDefaultConstraint? _defaultConstraint;
        FieldComputed? _computed = null;
        private List<FieldCheckConstraint>? _checks;
        private string _name = string.Empty;
        private bool _isNullable = false;
        private string? _databaseType = null;
        private EntityDefinition? _owner = null;

        protected FieldDefinition() 
        { }

        protected FieldDefinition(SystemColumnType systemColumnType, Column column, FieldDefaultConstraint? defaultConstraint, FieldComputed? computed, List<FieldCheckConstraint>? checks)
        {
            _name = column.Name;
            _isNullable = column.IsNullable;
            _databaseType = column.TypeName;
            _defaultConstraint = defaultConstraint;                                                                                           
            _computed = computed;
            _checks = checks;
        }


        [XmlIgnore]
        public EntityDefinition? Owner { get => _owner; set => _owner = value; }
        public abstract FieldType FieldType { get; }

        [XmlIgnore]
        public bool IsReference
        {
            get
            {
                if(_isReference.HasValue == false)
                {
                    _isReference = Owner!.GetIsReference(this);
                }
                return _isReference.Value;
            }
        }

        [XmlAttribute]
        public string Name { get => _name; set => _name = value; }
        [XmlAttribute, DefaultValue(false)]
        public bool IsNullable { get => _isNullable; set => _isNullable = value; }
        [XmlIgnore]
        public virtual bool IsIdentity => false;

        [XmlIgnore]
        public virtual bool IsNewId => false;

        [XmlAttribute]
        public string? DatabaseType { get => _databaseType; set => _databaseType = value; }
        [XmlElement("DefaultConstraint"), DefaultValue(null)]
        public FieldDefaultConstraint? DefaultConstraint { get => _defaultConstraint; set => _defaultConstraint = value; }

        [XmlElement("Computed"), DefaultValue(null)]
        public FieldComputed? Computed { get => _computed; set => _computed = value; }


        [XmlArray("Checks"), XmlArrayItem(typeof(FieldCheckConstraint), ElementName = "Check"), DefaultValue(null)]
        public List<FieldCheckConstraint>? ChecksNullIfEmpty
        {
            get
            {
                return _checks?.Count > 0 ? _checks : null;
            }

            set => _checks = value;
        }

        [XmlIgnore]
        public List<FieldCheckConstraint>? Checks
        {
            get
            {
                return _checks;
            }

            set => _checks = value;
        }

        [XmlIgnore]
        public bool HasDefaultConstraint => _defaultConstraint != null;

        [XmlIgnore]
        public bool IsComputed => _computed != null;

        public virtual bool Equals(FieldDefinition? other)
        {
            if (other is null)
            {
                return false;
            }
            return FieldType == other.FieldType && Name == other.Name && IsNullable == other.IsNullable && DatabaseType == other.DatabaseType;
        }

        public override bool Equals(object? obj)
        {
            return Equals(obj as FieldDefinition);
        }

        public override string ToString()
        {
            if (IsNullable)
            {
                return $"{Name}?";
            }
            return $"{Name}";
        }

        public static FieldType GetFieldType(Type type)
        {
            if (type == typeof(bool))
            {
                return FieldType.Boolean;
            }
            else if (type == typeof(byte))
            {
                return FieldType.Byte;
            }
            else if (type == typeof(sbyte))
            {
                return FieldType.SByte;
            }
            else if (type == typeof(char))
            {
                return FieldType.Char;
            }
            else if (type == typeof(short))
            {
                return FieldType.Int16;
            }
            else if (type == typeof(ushort))
            {
                return FieldType.UInt16;
            }
            else if (type == typeof(int))
            {
                return FieldType.Int32;
            }
            else if (type == typeof(uint))
            {
                return FieldType.UInt32;
            }
            else if (type == typeof(long))
            {
                return FieldType.Int64;
            }
            else if (type == typeof(ulong))
            {
                return FieldType.UInt64;
            }
            else if (type == typeof(float))
            {
                return FieldType.Single;
            }
            else if (type == typeof(double))
            {
                return FieldType.Double;
            }
            else if (type == typeof(decimal))
            {
                return FieldType.Decimal;
            }
            else if (type == typeof(DateTime))
            {
                return FieldType.DateTime;
            }
            else if (type == typeof(TimeSpan))
            {
                return FieldType.TimeSpan;
            }
            else if (type == typeof(Guid))
            {
                return FieldType.Guid;
            }
            else if (type == typeof(string))
            {
                return FieldType.String;
            }
            else if (type == typeof(byte[]))
            {
                return FieldType.Binary;
            }
            else
            {
                return FieldType.Unknown;
            }
        }

        

        internal virtual void Initialize()
        { }
        internal virtual void Initialize2()
        { }
    }


}