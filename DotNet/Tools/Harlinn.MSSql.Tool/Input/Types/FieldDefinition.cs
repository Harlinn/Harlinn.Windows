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
using System.Numerics;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class FieldDefaultConstraint
    { 
        string _name = string.Empty;
        string? _definition;

        public FieldDefaultConstraint()
        { }

        public FieldDefaultConstraint(string name, string? definition)
        {
            _name = name;
            _definition = definition;
        }

        [XmlAttribute, DefaultValue(null)]
        public string Name { get => _name; set => _name = value; }
        [XmlAttribute, DefaultValue(null)]
        public string? Definition { get => _definition; set => _definition = value; }
    }


    [Serializable]
    public abstract class FieldDefinition : IEquatable<FieldDefinition>
    {
        [XmlIgnore]
        bool? _isReference;
        FieldDefaultConstraint? _defaultConstraint;

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
        
        [XmlElement("DefaultConstraint"), DefaultValue(null)]
        public FieldDefaultConstraint? DefaultConstraint { get => _defaultConstraint; set => _defaultConstraint = value; }

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


    public abstract class ValueFieldDefinition<T> : FieldDefinition where T : struct
    {
        T _default = default(T);

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

    public abstract class RangeFieldDefinition<T> : ValueFieldDefinition<T> where T : struct, IMinMaxValue<T>
    {
        static readonly T DefaultMinValue = T.MinValue;
        static readonly T DefaultMaxValue = T.MaxValue;
        T _minValue = DefaultMinValue;
        T _maxValue = DefaultMaxValue;

        [XmlAttribute("Min"), DefaultValue(null)]
        public string? MinAsString
        {
            get
            {
                if (_minValue.Equals(DefaultMinValue))
                {
                    return null;
                }
                return _minValue.ToString();
            }

            set
            {
                if (value != null)
                {
                    _minValue = (T)Convert.ChangeType(value, typeof(T));
                }
                else
                {
                    _minValue = DefaultMinValue;
                }
            }
        }

        [XmlAttribute("Max"), DefaultValue(null)]
        public string? MaxAsString
        {
            get
            {
                if (_maxValue.Equals(DefaultMaxValue))
                {
                    return null;
                }
                return _maxValue.ToString();
            }

            set
            {
                if (value != null)
                {
                    _maxValue = (T)Convert.ChangeType(value, typeof(T));
                }
                else
                {
                    _maxValue = DefaultMaxValue;
                }
            }
        }

        [XmlIgnore]
        public T Min { get => _minValue; set => _minValue = value; }
        [XmlIgnore]
        public T Max { get => _maxValue; set => _maxValue = value; }

        [XmlIgnore]
        public bool HasMin => _minValue.Equals(DefaultMinValue) == false;

        [XmlIgnore]
        public bool HasMax => _maxValue.Equals(DefaultMaxValue) == false;

        public override string ToString()
        {
            var result = base.ToString();
            if (HasMin)
            {
                if (HasMax)
                {
                    return $"{result} Min({Min}) Max({Max})";
                }
                return $"{result} Min({Min})";
            }
            else if (HasMax)
            {
                return $"{result} Max({Max})";
            }
            return result;
        }

    }

    public abstract class NumberFieldDefinition<T> : RangeFieldDefinition<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {

    }

    public class Identity<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {
        T _seed = T.One;
        T _increment = T.One;

        public Identity()
        { }

        public Identity(T seed, T increment)
        {
            _seed = seed;
            _increment = increment;
        }

        [XmlAttribute]
        public T Seed { get => _seed; set => _seed = value; }
        [XmlAttribute]
        public T Increment { get => _increment; set => _increment = value; }
    }

    public abstract class IntegerFieldDefinition<T> : NumberFieldDefinition<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {
        Identity<T> _identity;

        public Identity<T> Identity { get => _identity; set => _identity = value; }
    }

    public abstract class NumericFieldDefinition<T> : NumberFieldDefinition<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {
        
    }


}