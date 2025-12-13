
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

namespace Harlinn.MSSql.Tool.Input.Types
{

    [Serializable]
    public abstract class FieldDefinition : IEquatable<FieldDefinition>
    {
        [XmlIgnore]
        bool? _isReference;

        [XmlIgnore]
        public EntityDefinition? Owner { get; set; } = null;
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
        public string Name { get; set; } = string.Empty;

        [XmlAttribute, DefaultValue(false)]
        public bool IsNullable { get; set; } = false;

        [XmlAttribute]
        public String? DatabaseType { get; set; } = null;

        public virtual bool Equals(FieldDefinition? other)
        {
            if (other is null)
            {
                return false;
            }
            return FieldType == other.FieldType && Name == other.Name && IsNullable == other.IsNullable && DatabaseType == other.DatabaseType;
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
    }
}