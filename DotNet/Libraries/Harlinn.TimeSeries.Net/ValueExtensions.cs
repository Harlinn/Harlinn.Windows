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

namespace Harlinn.TimeSeries.Net
{


    public static class ValueExtensions
    {


        /*
        public static int IndexOf(this Value[] values, DateTime time)
        {
            if (values == null || values.Length == 0)
            {
                return -1;
            }

            int lo = 0;
            int hi = values.Length - 1;

            while (lo <= hi)
            {
                int mid = lo + ((hi - lo) >> 1);
                int cmp = DateTime.Compare( values[mid].Time, time);

                if (cmp == 0)
                {
                    // If multiple entries share the same time, return the first occurrence.
                    // Walk left to find the earliest index with matching time.
                    while (mid > 0 && DateTime.Compare(values[mid].Time, time) == 0)
                    {
                        mid--;
                    }
                    return mid;
                }

                if (cmp < 0)
                {
                    lo = mid + 1;
                }
                else
                {
                    hi = mid - 1;
                }
            }
            return -1;
        }
        */

        public static int IndexOf(this Value[] values, DateTime time)
        {
            if (values == null || values.Length == 0)
            {
                // Not found; insertion point is 0
                return ~0;
            }

            int lo = 0;
            int hi = values.Length - 1;

            while (lo <= hi)
            {
                int mid = lo + ((hi - lo) >> 1);
                int cmp = DateTime.Compare(values[mid].Time, time);

                if (cmp == 0)
                {
                    // Return first occurrence if duplicates exist
                    while (mid > 0 && DateTime.Compare(values[mid - 1].Time, time) == 0)
                    {
                        mid--;
                    }
                    return mid;
                }

                if (cmp < 0)
                {
                    lo = mid + 1;
                }
                else
                {
                    hi = mid - 1;
                }
            }

            // Not found: return one's complement of insertion point
            // Insertion point is 'lo' where 'time' would be inserted to keep the array sorted by Time.
            return ~lo;
        }

        public static int LowerBound(this Value[] values, DateTime time)
        {
            if (values == null || values.Length == 0)
            {
                throw new ArgumentException("Array is null or empty", nameof(values));
            }

            int lo = 0;
            int hi = values.Length - 1;

            while (lo <= hi)
            {
                int mid = lo + ((hi - lo) >> 1);
                int cmp = DateTime.Compare(values[mid].Time, time);

                if (cmp == 0)
                {
                    // If we found an exact match, walk left to find the lower bound.
                    while (mid > 0 && DateTime.Compare(values[mid - 1].Time, time) == 0)
                    {
                        mid--;
                    }
                    return mid;
                }

                if (cmp < 0)
                {
                    lo = mid + 1;
                }
                else
                {
                    hi = mid - 1;
                }
            }
            return lo;
        }

        public static int UpperBound(this Value[] values, DateTime time)
        {   
            if (values == null || values.Length == 0)
            {
                throw new ArgumentException("Array is null or empty", nameof(values));
            }
            int lo = 0;
            int hi = values.Length - 1;
            while (lo <= hi)
            {
                int mid = lo + ((hi - lo) >> 1);
                int cmp = DateTime.Compare(values[mid].Time, time);
                if (cmp == 0)
                {
                    // If we found an exact match, walk right to find the upper bound.
                    while (mid < values.Length - 1 && DateTime.Compare(values[mid + 1].Time, time) == 0)
                    {
                        mid++;
                    }
                    return mid + 1;
                }
                if (cmp < 0)
                {
                    lo = mid + 1;
                }
                else
                {
                    hi = mid - 1;
                }
            }
            return lo;
        }


        public static bool IsMissing(this Value value)
        {
            return (value.Flags & ValueFlags.Missing) == ValueFlags.Missing;
        }
        public static bool IsEstimated(this Value value)
        {
            return (value.Flags & ValueFlags.Estimated) == ValueFlags.Estimated;
        }
    }


}
