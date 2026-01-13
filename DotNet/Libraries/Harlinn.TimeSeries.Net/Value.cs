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

using System.Numerics;
using System.Runtime.InteropServices;

namespace Harlinn.TimeSeries.Net
{
    [StructLayout(LayoutKind.Explicit)]
    public struct Value : IEquatable<Value>,
        IComparable<DateTime>, 
        IComparable<Value>,
        IComparable<double>,
        IAdditionOperators<Value, Value, Value>, ISubtractionOperators<Value, Value, Value>,
        IAdditionOperators<Value, double, Value>, ISubtractionOperators<Value, double, Value>,
        IMultiplyOperators<Value, Value, Value>, IDivisionOperators<Value, Value, Value>,
        IMultiplyOperators<Value, double, Value>, IDivisionOperators<Value, double, Value>,
        IModulusOperators<Value, Value, Value>,
        IModulusOperators<Value, double, Value>,
        IIncrementOperators<Value>, IDecrementOperators<Value>,
        IComparisonOperators<Value, Value, bool>
    {
        [FieldOffset(0)]
        readonly DateTime _time;
        [FieldOffset(8)]
        readonly ValueFlags _flags;
        [FieldOffset(12)]
        readonly int _code;
        [FieldOffset(16)]
        readonly double _data;

        public const int SizeInBytes = 24;

        public Value()
        { }

        public Value(DateTime time, double data)
        {
            _time = time;
            _data = data;
        }
        public Value(DateTime time, ValueFlags flags, double data)
        {
            _time = time;
            _flags = flags;
            _data = data;
        }

        public Value(DateTime time, ValueFlags flags, int code, double data)
        {
            _time = time;
            _flags = flags;
            _code = code;
            _data = data;
        }

        public Value(in Value other, DateTime newTime)
        {
            _time = newTime;
            _flags = other._flags;
            _code = other._code;
            _data = other._data;
        }

        public DateTime Time => _time;

        public ValueFlags Flags => _flags;
        public int Code => _code;

        public double Data => _data;

        

        public static implicit operator double(Value v) => v.Data;

        public int CompareTo(DateTime other)
        {
            return _time.CompareTo(other);
        }

        public int CompareTo(Value other)
        {
            return _data.CompareTo(other._data);
        }

        public int CompareTo(double other)
        {
            return _data.CompareTo(other);
        }

        public bool Equals(Value other)
        {
            return _time.Equals(other._time) && _flags.Equals(other._flags) && _code.Equals(other._code) && _data.Equals(other._data);
        }

        public override bool Equals(object? obj)
        {
            return obj is Value other && Equals(other);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(_time, _flags, _code, _data);
        }

        public override string ToString()
        {
            return $"Time: {_time}, Flags: {_flags}, Code: {_code}, Data: {_data}";
        }

        

        public static Value operator +(Value left, Value right)
        {
            return new Value(left._time, left._flags | right._flags, left._code, left._data + right._data);
        }

        public static Value operator +(Value left, double right)
        {
            return new Value(left._time, left._flags, left._code, left._data + right);
        }

        public static Value operator -(Value left, Value right)
        {
            return new Value(left._time, left._flags | right._flags, left._code, left._data - right._data);
        }

        public static Value operator -(Value left, double right)
        {
            return new Value(left._time, left._flags, left._code, left._data - right);
        }

        public static Value operator *(Value left, Value right)
        {
            return new Value(left._time, left._flags | right._flags, left._code, left._data * right._data);
        }

        public static Value operator *(Value left, double right)
        {
            return new Value(left._time, left._flags, left._code, left._data * right);
        }

        public static Value operator /(Value left, Value right)
        {
            return new Value(left._time, left._flags | right._flags, left._code, left._data / right._data);
        }

        public static Value operator /(Value left, double right)
        {
            return new Value(left._time, left._flags, left._code, left._data / right);
        }

        public static Value operator %(Value left, Value right)
        {
            return new Value(left._time, left._flags | right._flags, left._code, left._data % right._data);
        }

        public static Value operator %(Value left, double right)
        {
            return new Value(left._time, left._flags, left._code, left._data % right);
        }

        public static bool operator ==(Value left, Value right)
        {
            return left.Data == right.Data;
        }

        public static bool operator !=(Value left, Value right)
        {
            return left.Data != right.Data;
        }

        public static bool operator <(Value left, Value right)
        {
            return left.Data < right.Data;
        }

        public static bool operator >(Value left, Value right)
        {
            return left.Data > right.Data;
        }

        public static bool operator <=(Value left, Value right)
        {
            return left.Data <= right.Data;
        }

        public static bool operator >=(Value left, Value right)
        {
            return left.Data >= right.Data;
        }

        public static Value operator ++(Value value)
        {
            return new Value(value._time, value._flags, value._code, value._data + 1.0);
        }

        public static Value operator --(Value value)
        {
            return new Value(value._time, value._flags, value._code, value._data - 1.0);
        }
    }


}
