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


using System.Collections;

namespace Harlinn.TimeSeries.Net
{
    public class ConstantTimeSeries : ITimeSeries
    {
        Value _constantValue;

        class Enumerator : IEnumerator<Value>
        {
            Value _value;
            bool _hasMoved;
            public Enumerator(Value value)
            {
                _value = value;
                _hasMoved = false;
            }
            public Value Current => _value;

            object IEnumerator.Current => Current;

            public void Dispose()
            {
            }

            public bool MoveNext()
            {
                if (!_hasMoved)
                {
                    _hasMoved = true;
                    return true;
                }
                return false;
            }
            public void Reset()
            {
                _hasMoved = false;
            }
        }

        public ConstantTimeSeries(Value constantValue)
        {
            _constantValue = constantValue;
        }

        public TimeSeriesType Type => TimeSeriesType.Constant;
        public Value this[DateTime time] => _constantValue;

        public bool Step => true;

        public Value First => _constantValue;

        public Value Last => _constantValue;

        public int Count => 1;

        public int Capacity => 1;

        public Value this[int index] => _constantValue;

        public Value[] GetValues(Interval interval) => new[] { _constantValue };

        public double GetAvgValue(Interval duration, TimeSpan interval) => _constantValue.Data;
        public double GetMinValue(Interval duration, TimeSpan interval) => _constantValue.Data;
        public double GetMaxValue(Interval duration, TimeSpan interval) => _constantValue.Data;

        public IEnumerator<Value> GetEnumerator()
        {
            return new Enumerator(_constantValue);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }

}
