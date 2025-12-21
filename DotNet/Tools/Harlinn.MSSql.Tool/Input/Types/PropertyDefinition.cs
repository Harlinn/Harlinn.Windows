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

using Microsoft.SqlServer.Management.Smo;
using System.ComponentModel;
using System.Numerics;
using System.Xml;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    /// <summary>
    /// Identifies the concrete PropertyDefinition type.
    /// </summary>
    public enum PropertyKind
    {
        Boolean,
        SByte,
        Byte,
        Char,
        Int16,
        UInt16,
        Int32,
        UInt32,
        Int64,
        UInt64,
        Single,
        Double,
        Decimal,
        DateTime,
        TimeSpan,
        Guid,
        String,
        Binary,
        Enum,   
        Object
    }

    [Serializable]
    public abstract class PropertyDefinition
    {
        ObjectDefinition? _owner = null;
        string _name = string.Empty;
        bool _isNullable = false;

        [XmlIgnore]
        public ObjectDefinition? Owner { get => _owner; set => _owner = value; }
        [XmlIgnore]
        public abstract PropertyKind Kind { get; }

        [XmlAttribute]
        public string Name { get => _name; set => _name = value; }
        
        [XmlAttribute, DefaultValue(false)]
        public bool IsNullable { get => _isNullable; set => _isNullable = value; }

        public override string ToString()
        {
            if(IsNullable)
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

    public abstract class ValuePropertyDefinition<T> : PropertyDefinition where T : struct
    {
        T _default = default(T);

        [XmlAttribute("Default"),DefaultValue(null)]
        public string? DefaultAsString
        {
            get
            {
                if(_default.Equals(default(T)))
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
        public T Default { get => _default; set => _default = value; }

        [XmlIgnore]
        public bool HasDefault => _default.Equals(default(T)) == false;

        public override string ToString()
        {
            var result = base.ToString();
            if(HasDefault)
            {
                return $"{result} Default({_default})";
            }
            return result;
        }
    }

    public abstract class RangePropertyDefinition<T> : ValuePropertyDefinition<T> where T : struct, IMinMaxValue<T>
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
            if(HasMin)
            {
                if(HasMax)
                {
                    return $"{result} Min({Min}) Max({Max})";
                }
                return $"{result} Min({Min})";
            }
            else if(HasMax)
            {
                return $"{result} Max({Max})";
            }
            return result;
        }


    }

    public abstract class NumberPropertyDefinition<T> : RangePropertyDefinition<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {
    }

    public abstract class IntegerPropertyDefinition<T> : NumberPropertyDefinition<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {
    }

    public abstract class NumericPropertyDefinition<T> : NumberPropertyDefinition<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {
    }


    public class BooleanPropertyDefinition : ValuePropertyDefinition<bool>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Boolean;
    }

    public class SBytePropertyDefinition : IntegerPropertyDefinition<sbyte>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.SByte;
    }

    public class BytePropertyDefinition : IntegerPropertyDefinition<byte>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Byte;
    }

    public class CharPropertyDefinition : IntegerPropertyDefinition<char>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Char;
    }

    public class Int16PropertyDefinition : IntegerPropertyDefinition<short>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Int16;
    }
    public class UInt16PropertyDefinition : IntegerPropertyDefinition<ushort>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.UInt16;
    }
    public class Int32PropertyDefinition : IntegerPropertyDefinition<int>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Int32;
    }

    public class UInt32PropertyDefinition : IntegerPropertyDefinition<uint>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.UInt32;
    }
    public class Int64PropertyDefinition : IntegerPropertyDefinition<long>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Int64;
    }
    public class UInt64PropertyDefinition : IntegerPropertyDefinition<ulong>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.UInt64;
    }
    public class SinglePropertyDefinition : NumericPropertyDefinition<float>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Single;
    }
    public class DoublePropertyDefinition : NumericPropertyDefinition<double>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Double;
    }

    public class DecimalPropertyDefinition : NumericPropertyDefinition<decimal>
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Decimal;
    }

    public class DateTimePropertyDefinition : ValuePropertyDefinition<DateTime>
    {
        static readonly DateTime DefaultMinValue = DateTime.MinValue;
        static readonly DateTime DefaultMaxValue = DateTime.MaxValue;
        DateTime _minValue = DefaultMinValue;
        DateTime _maxValue = DefaultMaxValue;

        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.DateTime;

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
                    _minValue = (DateTime)Convert.ChangeType(value, typeof(DateTime));
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
                    _maxValue = (DateTime)Convert.ChangeType(value, typeof(DateTime));
                }
                else
                {
                    _maxValue = DefaultMaxValue;
                }
            }
        }

        [XmlIgnore]
        public DateTime Min { get => _minValue; set => _minValue = value; }
        [XmlIgnore]
        public DateTime Max { get => _maxValue; set => _maxValue = value; }

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

    public class TimeSpanPropertyDefinition : ValuePropertyDefinition<TimeSpan>
    {
        static readonly TimeSpan DefaultMinValue = TimeSpan.MinValue;
        static readonly TimeSpan DefaultMaxValue = TimeSpan.MaxValue;
        TimeSpan _minValue = DefaultMinValue;
        TimeSpan _maxValue = DefaultMaxValue;

        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.TimeSpan;

        [XmlAttribute("Min", DataType = "duration"), DefaultValue(null)]
        public string? MinAsString
        {
            get
            {
                if (_minValue.Equals(DefaultMinValue))
                {
                    return null;
                }
                return XmlConvert.ToString(_minValue);
            }

            set
            {
                if (value != null)
                {
                    _minValue = XmlConvert.ToTimeSpan(value);
                }
                else
                {
                    _minValue = DefaultMinValue;
                }
            }
        }

        [XmlAttribute("Max", DataType = "duration"), DefaultValue(null)]
        public string? MaxAsString
        {
            get
            {
                if (_maxValue.Equals(DefaultMaxValue))
                {
                    return null;
                }
                return XmlConvert.ToString(_maxValue);
            }

            set
            {
                if (value != null)
                {
                    _maxValue = XmlConvert.ToTimeSpan(value);
                }
                else
                {
                    _maxValue = DefaultMaxValue;
                }
            }
        }

        [XmlIgnore]
        public TimeSpan Min { get => _minValue; set => _minValue = value; }
        [XmlIgnore]
        public TimeSpan Max { get => _maxValue; set => _maxValue = value; }

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

    public class GuidPropertyDefinition : PropertyDefinition
    {
        Guid _default = Guid.Empty;

        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Guid;

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
                if (string.IsNullOrWhiteSpace( value ) == false )
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

    public class StringPropertyDefinition : PropertyDefinition
    {
        string _defaultValue = string.Empty;
        const int DefaultSize = 128;
        int _size = DefaultSize;

        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.String;

        [XmlAttribute,DefaultValue("")]
        public string Default { get => _defaultValue; set => _defaultValue = value; }

        [XmlAttribute("Size"), DefaultValue(null)]
        public string? SizeAsString
        {
            get
            {
                if (_size.Equals(DefaultSize))
                {
                    return null;
                }
                else if (_size <= 0 ||_size >= 4000)
                {
                    return "Max";
                }
                return _size.ToString();
            }

            set
            {
                if (value != null)
                {
                    if (string.Equals(value, "Max", StringComparison.OrdinalIgnoreCase))
                    {
                        _size = -1;
                        return;
                    }
                    _size = int.Parse(value);
                    if (_size <= 0 || _size >= 4000)
                    {
                        _size = -1;
                    }
                }
                else
                {
                    _size = DefaultSize;
                }
            }
        }

        [XmlIgnore]
        public int Size { get => _size; set => _size = value; }
    }

    public class BinaryPropertyDefinition : PropertyDefinition
    {
        byte[]? _defaultValue;
        const int DefaultSize = 256;
        int _size = DefaultSize;

        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Binary;

        [XmlAttribute]
        public byte[]? Default { get => _defaultValue; set => _defaultValue = value; }

        [XmlAttribute("Size"), DefaultValue(null)]
        public string? SizeAsString
        {
            get
            {
                if (_size.Equals(DefaultSize))
                {
                    return null;
                }
                else if (_size <= 0 || _size >= 4000)
                {
                    return "Max";
                }
                return _size.ToString();
            }

            set
            {
                if (value != null)
                {
                    if (string.Equals(value, "Max", StringComparison.OrdinalIgnoreCase))
                    {
                        _size = -1;
                        return;
                    }
                    _size = int.Parse(value);
                    if (_size <= 0 || _size >= 4000)
                    {
                        _size = -1;
                    }
                }
                else
                {
                    _size = DefaultSize;
                }
            }
        }
        [XmlIgnore]
        public int Size { get => _size; set => _size = value; }
    }

    public abstract class TypedPropertyDefinition : PropertyDefinition
    {
        TypeDefinition? _type = null;
        string _typeName = string.Empty;

        [XmlAttribute("Type")]
        public string TypeName { get => _typeName; set => _typeName = value; }

        [XmlIgnore]
        public TypeDefinition? Type { get => _type; set => _type = value; }

        internal override void Initialize2()
        {
            base.Initialize2();
            if (Owner != null && string.IsNullOrEmpty(TypeName) == false)
            {
                _type = Owner.GetTypeDefinition(TypeName);
            }
        }

    }

    
    public class EnumPropertyDefinition : TypedPropertyDefinition
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Enum;
    }

    public class ObjectPropertyDefinition : TypedPropertyDefinition
    {
        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Object;
    }









}
