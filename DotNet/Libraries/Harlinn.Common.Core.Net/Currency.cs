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

using System.Diagnostics.CodeAnalysis;
using System.Globalization;

namespace Harlinn.Common.Core.Net
{
    /// <summary>
    /// A Currency number stored as a long, scaled by 10,000 to give a fixed-point 
    /// number with 15 digits to the left of the decimal point and 4 digits to the right.
    /// </summary>
    public struct Currency : IEquatable<Currency>, IEquatable<long>, IEquatable<int>, IEquatable<short>, IEquatable<decimal>, IEquatable<double>, IEquatable<float>, 
        IComparable<Currency>, IComparable<decimal>, IComparable<double>, IComparable<float>, IComparable<long>, IComparable<int>, IComparable<short>
    {
        public const long Scale = 10000;
        const float ScaleFloat = 10000.0f;
        const double ScaleDouble = 10000.0;
        const decimal ScaleDecimal = 10000.0m;
        long _value = 0;

        public Currency()
        { }
        public Currency(long value)
        {
            _value = value* Scale;
        }


        public Currency(float value)
        {
            _value = (long)(value * ScaleFloat);
        }

        public Currency(double value)
        {
            _value = (long)(value * ScaleDouble);
        }

        public Currency(decimal value)
        {
            _value = decimal.ToOACurrency( value );
        }

        private Currency(long value, bool b)
        {
            _value = value;
        }

        public static Currency FromScaled(long value) => new Currency(value, false);
        public long ToScaled() => _value;

        public decimal ToDecimal() => decimal.FromOACurrency(_value);

        public override int GetHashCode()
        {
            return HashCode.Combine(_value);
        }
        public override bool Equals([NotNullWhen(true)] object? obj)
        {
            return obj is Currency && Equals((Currency)obj);
        }

        public bool Equals(long other)
        {
            return _value == (other*Scale);
        }

        public bool Equals(int other)
        {
            return _value == ((long)other * Scale);
        }

        public bool Equals(short other)
        {
            return _value == ((long)other * Scale);
        }

        public bool Equals(Currency other)
        {
            return _value == other._value;
        }

        public bool Equals(decimal other)
        {
            return (((decimal)_value) / ScaleDecimal) == other;
        }

        public bool Equals(double other)
        {
            return (((double)_value)/ScaleDouble) == other;
        }

        public bool Equals(float other)
        {
            return (((float)_value) / ScaleFloat) == other;
        }

        public int CompareTo(Currency other)
        {
            return _value.CompareTo(other._value);
        }


        public int CompareTo(decimal other)
        {
            return (((decimal)_value) / ScaleDecimal).CompareTo(other);
        }
        public int CompareTo(double other)
        {
            return (((double)_value) / ScaleDouble).CompareTo(other);
        }

        public int CompareTo(float other)
        {
            return (((float)_value) / ScaleFloat).CompareTo(other);
        }

        public int CompareTo(long other)
        {
            return (_value / Scale).CompareTo(other);
        }

        public int CompareTo(int other)
        {
            return (_value / Scale).CompareTo(other);
        }

        public int CompareTo(short other)
        {
            return (_value / Scale).CompareTo(other);
        }

        public static bool operator == (Currency first, Currency second) => first._value == second._value;
        public static bool operator !=(Currency first, Currency second) => first._value != second._value;

        public static bool operator < (Currency first, Currency second) => first._value < second._value;
        public static bool operator <=(Currency first, Currency second) => first._value <= second._value;

        public static bool operator > (Currency first, Currency second) => first._value > second._value;

        public static bool operator >=(Currency first, Currency second) => first._value >= second._value;

        public static bool operator !(Currency currency) => currency._value == 0;

        public static bool operator true(Currency currency) => currency._value != 0;
        public static bool operator false(Currency currency) => currency._value == 0;

        public static Currency operator ++(Currency currency) => new Currency(currency._value + Scale, false);

        public static Currency operator --(Currency currency) => new Currency(currency._value - Scale, false);
        public static Currency operator +(Currency currency) => currency;
        public static Currency operator -(Currency currency) => new Currency(-currency._value, false);
        public static Currency operator +(Currency first, Currency second) => new Currency(first._value + second._value, false);

        public static Currency operator +(float first, Currency second) => new Currency((long)(first*ScaleFloat) + second._value, false);

        public static Currency operator +(Currency first, float second) => new Currency(first._value + (long)(second* ScaleFloat), false);

        public static Currency operator +(double first, Currency second) => new Currency((long)(first * ScaleDouble) + second._value, false);

        public static Currency operator +(Currency first, double second) => new Currency(first._value + (long)(second * ScaleDouble), false);

        public static Currency operator +(decimal first, Currency second) => new Currency((long)(first * ScaleDecimal) + second._value, false);

        public static Currency operator +(Currency first, decimal second) => new Currency(first._value + (long)(second * ScaleDecimal), false);

        public static Currency operator +(long first, Currency second) => new Currency((first * Scale) + second._value, false);

        public static Currency operator +(Currency first, long second) => new Currency(first._value + (second * Scale), false);

        public static Currency operator +(int first, Currency second) => new Currency(((long)first * Scale) + second._value, false);

        public static Currency operator +(Currency first, int second) => new Currency(first._value + ((long)second * Scale), false);

        public static Currency operator +(short first, Currency second) => new Currency(((long)first * Scale) + second._value, false);

        public static Currency operator +(Currency first, short second) => new Currency(first._value + ((long)second * Scale), false);

        public static Currency operator -(Currency first, Currency second) => new Currency(first._value - second._value, false);

        public static Currency operator -(float first, Currency second) => new Currency((long)(first * ScaleFloat) - second._value, false);

        public static Currency operator -(Currency first, float second) => new Currency(first._value - (long)(second * ScaleFloat), false);

        public static Currency operator -(double first, Currency second) => new Currency((long)(first * ScaleDouble) - second._value, false);

        public static Currency operator -(Currency first, double second) => new Currency(first._value - (long)(second * ScaleDouble), false);

        public static Currency operator -(decimal first, Currency second) => new Currency((long)(first * ScaleDecimal) - second._value, false);

        public static Currency operator -(Currency first, decimal second) => new Currency(first._value - (long)(second * ScaleDecimal), false);

        public static Currency operator -(long first, Currency second) => new Currency((first * Scale) - second._value, false);

        public static Currency operator -(Currency first, long second) => new Currency(first._value - (second * Scale), false);

        public static Currency operator -(int first, Currency second) => new Currency(((long)first * Scale) - second._value, false);

        public static Currency operator -(Currency first, int second) => new Currency(first._value - ((long)second * Scale), false);

        public static Currency operator -(short first, Currency second) => new Currency(((long)first * Scale) - second._value, false);

        public static Currency operator -(Currency first, short second) => new Currency(first._value - ((long)second * Scale), false);

        public static Currency operator *(float first, Currency second) => new Currency((long)((first * ((float)second._value)/ScaleFloat)* ScaleFloat), false);

        public static Currency operator *(Currency first, float second) => new Currency((long)((((float)first._value) / ScaleFloat) * second * ScaleFloat), false);

        public static Currency operator *(double first, Currency second) => new Currency((long)((first * ((double)second._value) / ScaleDouble) * ScaleDouble), false);

        public static Currency operator *(Currency first, double second) => new Currency((long)((((double)first._value) / ScaleDouble) * second * ScaleDouble), false);

        public static Currency operator *(decimal first, Currency second) => new Currency((long)((first * ((decimal)second._value) / ScaleDecimal) * ScaleDecimal), false);

        public static Currency operator *(Currency first, decimal second) => new Currency((long)((((decimal)first._value) / ScaleDecimal) * second * ScaleDecimal), false);

        public static Currency operator *(long first, Currency second) => new Currency(first * second._value, false);

        public static Currency operator *(Currency first, long second) => new Currency(first._value * second, false);

        public static Currency operator /(float first, Currency second) => new Currency((long)((first * ScaleFloat) / ((float)second._value / ScaleFloat)), false);

        public static Currency operator /(Currency first, float second) => new Currency((long)((float)first._value / second), false);

        public static Currency operator /(double first, Currency second) => new Currency((long)((first * ScaleDouble) / ((float)second._value / ScaleDouble)), false);

        public static Currency operator /(Currency first, double second) => new Currency((long)((double)first._value / second), false);

        public static Currency operator /(decimal first, Currency second) => new Currency((long)((first * ScaleDecimal) / ((decimal)second._value / ScaleDecimal)), false);

        public static Currency operator /(Currency first, decimal second) => new Currency((long)((decimal)first._value / second), false);

        public static Currency operator /(long first, Currency second) => new Currency((first * Scale )/(second._value / Scale), false);

        public static Currency operator /(Currency first, long second) => new Currency(first._value / second, false);


        public override string? ToString()
        {
            decimal v = ToDecimal();
            return v.ToString();
        }

        public string ToString([StringSyntax(StringSyntaxAttribute.NumericFormat)] string? format)
        {
            decimal v = ToDecimal();
            return v.ToString(format);
        }

        public string ToString(IFormatProvider? provider)
        {
            decimal v = ToDecimal();
            return v.ToString(provider);
        }

        public string ToString([StringSyntax(StringSyntaxAttribute.NumericFormat)] string? format, IFormatProvider? provider)
        {
            decimal v = ToDecimal();
            return v.ToString(format, provider);
        }

        public static Currency Parse(string s)
        {
            var v = decimal.Parse(s);
            return new Currency(v);
        }

        public static Currency Parse(string s, NumberStyles style)
        {
            var v = decimal.Parse(s, style);
            return new Currency(v);
        }

        public static Currency Parse(string s, IFormatProvider? provider)
        {
            var v = decimal.Parse(s, provider);
            return new Currency(v);
        }

        public static Currency Parse(string s, NumberStyles style, IFormatProvider? provider)
        {
            var v = decimal.Parse(s, style, provider);
            return new Currency(v);
        }

        public static Currency Parse(ReadOnlySpan<char> s, NumberStyles style = NumberStyles.Number, IFormatProvider? provider = null)
        {
            var v = decimal.Parse(s, style, provider);
            return new Currency(v);
        }

        public static bool TryParse([NotNullWhen(true)] string? s, out Currency result)
        {
            if(decimal.TryParse(s, out var v))
            {
                result = new Currency(v);
                return true;
            }
            else
            {
                result = new Currency();
                return false;
            }
        }

        public static bool TryParse(ReadOnlySpan<char> s, out Currency result)
        {
            if (decimal.TryParse(s, out var v))
            {
                result = new Currency(v);
                return true;
            }
            else
            {
                result = new Currency();
                return false;
            }
        }

        public static bool TryParse(ReadOnlySpan<byte> s, out Currency result)
        {
            if (decimal.TryParse(s, out var v))
            {
                result = new Currency(v);
                return true;
            }
            else
            {
                result = new Currency();
                return false;
            }
        }

        public static bool TryParse([NotNullWhen(true)] string? s, NumberStyles style, IFormatProvider? provider, out Currency result)
        {
            if (decimal.TryParse(s, style, provider, out var v))
            {
                result = new Currency(v);
                return true;
            }
            else
            {
                result = new Currency();
                return false;
            }
        }

        public static bool TryParse(ReadOnlySpan<char> s, NumberStyles style, IFormatProvider? provider, out Currency result)
        {
            if (decimal.TryParse(s, style, provider, out var v))
            {
                result = new Currency(v);
                return true;
            }
            else
            {
                result = new Currency();
                return false;
            }
        }

        
    }
}
