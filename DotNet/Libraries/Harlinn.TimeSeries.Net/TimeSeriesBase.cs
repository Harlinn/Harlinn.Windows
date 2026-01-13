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
using System.ComponentModel.DataAnnotations;
using static Harlinn.TimeSeries.Net.Common;

namespace Harlinn.TimeSeries.Net
{

    public abstract class TimeSeriesBase : ITimeSeries
    {
        
        static readonly ValueDateTimeComparer _valueDateTimeComparer = new();
        const int DeltaCapacity = 4096; // 2*8192; // 4096; //8192;
        readonly bool _step;
        Value[]? _values;
        int _count;


        class Enumerator : IEnumerator<Value>
        {
            private readonly TimeSeriesBase _timeSeries;
            private int _index;
            public Enumerator(TimeSeriesBase timeSeries)
            {
                _timeSeries = timeSeries;
                _index = -1;
            }
            public Value Current => _timeSeries[_index];
            object System.Collections.IEnumerator.Current => Current;
            public void Dispose()
            {
            }
            public bool MoveNext()
            {
                _index++;
                return _index < _timeSeries.Count;
            }
            public void Reset()
            {
                _index = -1;
            }
        }

        public TimeSeriesBase(bool step = false)
        {
            _step = step;
        }

        public TimeSeriesBase(int capacity, bool step = false)
        {
            if (capacity < 0)
            {
                throw new ArgumentOutOfRangeException(nameof(capacity), "capacity cannot be less than 0.");
            }
            _step = step;
            if (capacity > 0)
            {
                int newCapacity = CalculateCapacity(capacity, DeltaCapacity);
                _values = new Value[newCapacity];
            }

        }

        public TimeSeriesBase(Value[] values, bool step = false)
        {
            _step = step;
            if ( values != null && values.Length > 0)
            {
                int newCapacity = CalculateCapacity(values.Length, DeltaCapacity);
                _values = new Value[newCapacity];
                Array.Copy(values, _values, values.Length);
                _count = values.Length;
            }
        }


        public abstract TimeSeriesType Type { get; }
        public Value this[DateTime time]
        {
            get
            {
                if (_values != null)
                {
                    var index = FindIndex( _values, _count, time);
                    if (index >= 0)
                    {
                        return _values[index];
                    }
                    else
                    {
                        var nextIndex = ~index;
                        var previousIndex = nextIndex - 1;
                        if(previousIndex >= 0)
                        {
                            if( nextIndex < _count && !Step)
                            {
                                var previousValue = _values[previousIndex];
                                var nextValue = _values[nextIndex];
                                return Interpolate(previousValue, nextValue, time);
                            }
                            else
                            {
                                return _values[previousIndex];
                            }
                        }
                        throw new KeyNotFoundException($"No value found for time {time}");
                    }
                }
                else
                {
                    throw new KeyNotFoundException("No values in time series");
                }
            }
        }

        public Value this[int index]
        {
            get
            {
                if (_values != null && index >= 0 && index < _count)
                {
                    return _values[index];
                }
                throw new ArgumentOutOfRangeException(nameof(index));
            }
        }

        public int Count => _count;
        public int Capacity => _values?.Length ?? 0;

        public Value First
        {   
            get
            {
                if (_values != null && _count > 0)
                {
                    return _values[0];
                }
                throw new InvalidOperationException("Time series is empty");
            }
        }

        public Value Last
        {
            get
            {
                if (_values != null && _count > 0)
                {
                    return _values[_count - 1];
                }
                throw new InvalidOperationException("Time series is empty");
            }
        }

        public bool Step => _step;

        public Range ToRange(Interval interval)
        {
            if (_values != null && _count > 0)
            {
                var start = interval.Start;
                var end = interval.End;
                int startIndex = Common.FindStartIndex(_values, _count, start);
                int endIndex = Common.FindEndIndex(_values, _count, end);
                return new Range(startIndex, endIndex);
            }
            return new Range(0, 0);
        }

        public int FindStartIndex(int beginIndex, DateTime start)
        {
            if (_values != null && _count > 0)
            {
                var startIndex = Common.FindStartIndex(_values, _count, beginIndex, start);
                return startIndex;
            }
            return 0;
        }

        public int FindStartIndex(DateTime start)
        {
            if (_values != null && _count > 0)
            {
                var startIndex = Common.FindStartIndex(_values, _count, 0, start);
                return startIndex;
            }
            return 0;
        }

        public int FindEndIndex(int beginIndex, DateTime end)
        {
            if (_values != null && _count > 0)
            {
                var endIndex = Common.FindEndIndex(_values, _count, beginIndex, end);
                return endIndex;
            }
            return 0;
        }

        public int FindEndIndex(DateTime end)
        {
            if (_values != null && _count > 0)
            {
                var endIndex = Common.FindEndIndex(_values, _count, 0, end);
                return endIndex;
            }
            return 0;
        }




        public Value[] GetValues(Interval interval)
        {
            if (_values != null && _count > 0)
            {
                var firstValue = _values[0];
                if(interval.Start < firstValue.Time)
                {
                    if(interval.End <= firstValue.Time)
                    {
                        return Array.Empty<Value>();
                    }
                    // Clamp start to first value time.
                    interval = new Interval(firstValue.Time, interval.End);
                }
                var range = ToRange(interval);
                var rangeCount = range.Count;
                if (rangeCount > 0)
                {
                    if(!Step)
                    {
                        var remaining = _count - range.Start;
                        if (remaining > 1)
                        {
                            var startValue = _values[range.Start];
                            if (startValue.Time < interval.Start)
                            {
                                // Need to interpolate start value
                                startValue = Interpolate(startValue, _values[range.Start + 1], interval.Start);

                                if (range.End < _count)
                                {
                                    var endValue = _values[range.End];
                                    
                                    if(endValue.Time > interval.End)
                                    {
                                        // Need to interpolate end value
                                        endValue = Interpolate(_values[range.End - 1], endValue, interval.End);
                                    }
                                    var result = new Value[rangeCount + 1];
                                    result[0] = startValue;
                                    var copyCount = rangeCount - 1;
                                    if(copyCount > 0)
                                    {
                                        Array.Copy(_values, range.Start + 1, result, 1, copyCount);
                                    }
                                    result[rangeCount] = endValue;
                                    return result;
                                }
                                else
                                {
                                    // Cannot interpolate end value, just add interpolated start value and copy rest
                                    var result = new Value[rangeCount];
                                    result[0] = new Value(startValue, interval.Start);
                                    Array.Copy(_values, range.Start + 1, result, 1, rangeCount - 1);
                                    return result;
                                }
                            }
                            else
                            {
                                // No need to interpolate start value
                                if (range.End < _count)
                                {
                                    var endValue = _values[range.End];
                                    if (endValue.Time > interval.End)
                                    {
                                        // Need to interpolate end value
                                        endValue = Interpolate(_values[range.End - 1], endValue, interval.End);
                                        var result = new Value[rangeCount + 1];
                                        Array.Copy(_values, range.Start, result, 0, rangeCount);
                                        result[rangeCount] = endValue;
                                        return result;
                                    }
                                }
                                var simpleResult = new Value[rangeCount];
                                Array.Copy(_values, range.Start, simpleResult, 0, rangeCount);
                                return simpleResult;
                            }
                        }
                        else
                        {
                            var startValue = _values[range.Start];
                            return new Value[] { new Value(startValue, interval.Start) };
                        }

                    }
                    else // Pulse == true
                    {
                        var result = new Value[rangeCount];
                        var startValue = _values[range.Start];
                        if ( startValue.Time < interval.Start )
                        {
                            // Need to adjust start value time
                            result[0] = new Value(startValue, interval.Start);
                            if (rangeCount > 1)
                            {
                                Array.Copy(_values, range.Start + 1, result, 1, rangeCount - 1);
                            }
                        }
                        else
                        {
                            Array.Copy(_values, range.Start, result, 0, rangeCount);
                        }
                        return result;
                    }
                        
                }
            }
            return Array.Empty<Value>();
        }


        public Value GetValue(DateTime time, TimeSpan duration, int beginIndex, out int endIndex)
        {
            throw new NotImplementedException();
            if ( beginIndex < 0 || beginIndex >= _count )
            {
                throw new ArgumentOutOfRangeException(nameof(beginIndex));
            }
            if(duration <= TimeSpan.Zero)
            {
                throw new ArgumentOutOfRangeException(nameof(duration));
            }
            if (_values == null || _count == 0 )
            {
                throw new KeyNotFoundException("No values in time series");
            }
            var endTime = time + duration;
            var startIndex = beginIndex;
            var remaining = _count - startIndex;
            var value = _values[startIndex];

            startIndex = Common.FindStartIndex(_values, _count, beginIndex, time);

            
            
            endIndex = Common.FindEndIndex(_values, _count, startIndex, endTime);


        }


        public void Clear()
        {
            _values = null;
            _count = 0;
        }





        public void Add(Value newValue)
        {
            if(_values != null)
            {
                if (_count > 0)
                {
                    if (_values[_count - 1].Time < newValue.Time)
                    {
                        // Append to end
                        if (_count == _values.Length)
                        {
                            // Need to grow array
                            var newCapacity = CalculateCapacity(_values.Length + 1, DeltaCapacity);
                            Array.Resize(ref _values, newCapacity);
                        }
                        _values[_count] = newValue;
                        _count++;
                    }
                    else
                    {
                        if (_values[_count - 1].Time == newValue.Time)
                        {
                            // Replace last value
                            _values[_count - 1] = newValue;
                        }
                        else
                        {
                            var index = FindIndex(_values, _count, newValue.Time);
                            if (index < 0)
                            {
                                // Insert at index
                                var insertIndex = ~index;
                                _values = Insert(_values, ref _count, DeltaCapacity, insertIndex, newValue);
                            }
                            else
                            {
                                // Replace existing value at index
                                _values[index] = newValue;
                            }
                        }
                    }
                }
                else
                {
                    _values[0] = newValue;
                    _count = 1;
                }
            }
            else
            {
                _values = new Value[DeltaCapacity];
                _values[0] = newValue;
                _count = 1;
            }
        }

        public void Add(Value[] newValues)
        {
            if (newValues != null && newValues.Length > 0)
            {
                foreach (var value in newValues)
                {
                    Add(value);
                }
            }
        }

        public void Add(IEnumerable<Value> newValues)
        {
            if (newValues != null)
            {
                foreach (var value in newValues)
                {
                    Add(value);
                }
            }
        }

        public IEnumerator<Value> GetEnumerator()
        {
            return new Enumerator(this);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        /*
        public double GetAvgValue(Interval duration, TimeSpan interval)
        {
            if (_values != null && _count > 0 && duration.End > _values[0].Time)
            {
                if (duration.Start >= _values[_count - 1].Time)
                {
                    return _values[_count - 1].Data;
                }
                var startIndex = FindIndex( _values, _count,duration.Start);
                var endIndex = FindIndex(_values, _count, duration.End);

                double sum = 0.0;
                double totalSeconds = 0.0;

                if (Pulse)
                {
                    if (startIndex < 0)
                    {
                        startIndex = ~startIndex;

                    }
                }
                else
                {
                    
                }
            }
            return 0.0;

        }
        public double GetMinValue(Interval duration, TimeSpan interval)
        {
            if (_values != null && _count > 0)
            {
                var valuesInInterval = GetValues(duration);
                if (valuesInInterval.Length > 0)
                {
                    double min = double.MaxValue;
                    foreach (var value in valuesInInterval)
                    {
                        if (value.Data < min)
                        {
                            min = value.Data;
                        }
                    }
                    return min;
                }
            }
            return double.NaN;
        }
        public double GetMaxValue(Interval duration, TimeSpan interval)
        {
            if (_values != null && _count > 0)
            {
                var valuesInInterval = GetValues(duration);
                if (valuesInInterval.Length > 0)
                {
                    double max = double.MinValue;
                    foreach (var value in valuesInInterval)
                    {
                        if (value.Data > max)
                        {
                            max = value.Data;
                        }
                    }
                    return max;
                }
            }
            return double.NaN;
        }
        */

    }

}
