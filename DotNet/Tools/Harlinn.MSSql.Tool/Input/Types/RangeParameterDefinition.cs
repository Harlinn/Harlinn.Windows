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
using System.Numerics;
using System.Xml;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public abstract class RangeParameterDefinition<T> : ValueParameterDefinition<T> where T : struct, IMinMaxValue<T>
    {
        static readonly T DefaultMinValue = T.MinValue;
        static readonly T DefaultMaxValue = T.MaxValue;
        T _minValue = DefaultMinValue;
        T _maxValue = DefaultMaxValue;
        public RangeParameterDefinition()
            : base()
        { }
        public RangeParameterDefinition(Parameter parameter)
            : base(parameter)
        { }

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



}
