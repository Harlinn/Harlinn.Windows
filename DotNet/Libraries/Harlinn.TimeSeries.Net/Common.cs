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

using System.Runtime.CompilerServices;

namespace Harlinn.TimeSeries.Net
{
    public class Common
    {


        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int CalculateCapacity( int requestedSize, int deltaCapacity )
        {
            return requestedSize % deltaCapacity == 0
                ? requestedSize
                : ((requestedSize / deltaCapacity) + 1) * deltaCapacity;
        }

        public static Value[] Insert(Value[]? values, ref int currentSize, int deltaCapacity, int index, Value newValue)
        {
            if (index < 0 || index > currentSize)
            {
                throw new ArgumentOutOfRangeException(nameof(index));
            }
            if (values != null)
            {
                if (index < currentSize)
                {
                    if (values[index].Time == newValue.Time)
                    {
                        // If the times are equal, we can replace the value
                        values[index] = newValue;
                        return values;
                    }
                    else
                    {
                        if (values.Length == currentSize)
                        {
                            int newCapacity = CalculateCapacity(currentSize + 1, deltaCapacity);
                            Value[] newValues = new Value[newCapacity];
                            Array.Copy(values, newValues, index);
                            newValues[index] = newValue;
                            Array.Copy(values, index, newValues, index + 1, currentSize - index);
                            currentSize++;
                            return newValues;
                        }
                        else
                        {
                            Array.Copy(values, index, values, index + 1, currentSize - index);
                            values[index] = newValue;
                            currentSize++;
                            return values;
                        }
                    }
                }
                else
                {
                    if (values.Length == currentSize)
                    {
                        int newCapacity = CalculateCapacity(currentSize + 1, deltaCapacity);
                        Value[] newValues = new Value[newCapacity];
                        Array.Copy(values, newValues, currentSize);
                        newValues[currentSize] = newValue;
                        currentSize++;
                        return newValues;
                    }
                    else
                    {
                        values[currentSize] = newValue;
                        currentSize++;
                        return values;
                    }
                }
            }
            else
            {
                int newCapacity = CalculateCapacity(1, deltaCapacity);
                Value[] newValues = new Value[newCapacity];
                newValues[0] = newValue;
                currentSize = 1;
                return newValues;
            }
        }



        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int FindIndex(Value[] values, int count, DateTime time)
        {
            int low = 0;
            int high = count - 1;
            while (low <= high)
            {
                int mid = (low + high) / 2;
                DateTime midTime = values[mid].Time;
                if (midTime == time)
                {
                    return mid;
                }
                else if (midTime < time)
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
            // Not found, return bitwise complement of the insertion point
            return ~low; 
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int FindStartIndex(Value[] values, int count, DateTime time)
        {
            int low = 0;
            int high = count - 1;
            while (low <= high)
            {
                int mid = (low + high) / 2;
                DateTime midTime = values[mid].Time;
                if (midTime == time)
                {
                    return mid;
                }
                else if (midTime < time)
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
            return Math.Max(0, high);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int FindEndIndex(Value[] values, int count, DateTime time)
        {
            if (values[count - 1].Time < time)
            {
                return count;
            }
            int low = 0;
            int high = count - 1;
            while (low <= high)
            {
                int mid = (low + high) / 2;
                DateTime midTime = values[mid].Time;
                if (midTime == time)
                {
                    return mid;
                }
                else if (midTime < time)
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
            return Math.Min(low, count);
        }











        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int CodeOf(in Value first, in Value second)
        {
            if( first.Code != 0)
            {
                return first.Code;
            }
            return second.Code;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ValueFlags FlagsOf(in Value first, in Value second)
        {
            return first.Flags | second.Flags;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Value Interpolate(in Value first, in Value second, DateTime time)
        {
            var totalTicks = second.Time.Ticks - first.Time.Ticks;
            var elapsedTicks = time.Ticks - first.Time.Ticks;
            var ratio = (double)elapsedTicks / totalTicks;
            var interpolatedValue = first.Data + (second.Data - first.Data) * ratio;
            var flags = first.Flags | second.Flags | ValueFlags.Interpolated;
            var code = CodeOf(first, second);
            return new Value(time, flags, code, interpolatedValue);
        }


        public static Value[] Generate(DateTime start, TimeSpan interval, int count, Func<DateTime, Value> valueFactory)
        {
            if (count <= 0) throw new ArgumentOutOfRangeException(nameof(count));
            if (valueFactory == null) throw new ArgumentNullException(nameof(valueFactory));

            var values = new Value[count];
            for (int i = 0; i < count; i++)
            {
                var time = start + TimeSpan.FromTicks(interval.Ticks * i);
                values[i] = valueFactory(time);
            }
            return values;
        }

        public static Value[] Generate(DateTime start, TimeSpan interval, int count)
        {
            int i = 0;
            return Generate(start, interval, count, time => new Value(time, (double)i++));
        }

        public static void Shuffle<T>(T[] array, Random? rng = null)
        {
            if (array == null || array.Length <= 1)
            {
                return;
            }
            rng ??= new Random();

            for (int i = array.Length - 1; i > 0; i--)
            {
                int j = rng.Next(i + 1); 
                (array[i], array[j]) = (array[j], array[i]); 
            }
        }


    }
}
