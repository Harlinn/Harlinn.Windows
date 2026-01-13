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

using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using System.ComponentModel;
using System.Xml;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class TimeSpanParameterDefinition : ValueParameterDefinition<TimeSpan>
    {
        static readonly TimeSpan DefaultMinValue = TimeSpan.MinValue;
        static readonly TimeSpan DefaultMaxValue = TimeSpan.MaxValue;
        TimeSpan _minValue = DefaultMinValue;
        TimeSpan _maxValue = DefaultMaxValue;

        public TimeSpanParameterDefinition()
            : base()
        {
        }

        public TimeSpanParameterDefinition(Parameter parameter, string? description)
            : base(parameter, description)
        {
        }

        public override ParameterType ParameterType => ParameterType.TimeSpan;

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



}
