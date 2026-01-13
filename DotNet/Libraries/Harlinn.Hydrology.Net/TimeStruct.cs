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
namespace Harlinn.Hydrology
{
    /// <summary>
    /// Stores information describing a specific instance in time
    /// </summary>
    public class TimeStruct
    {
        DateTime _start;
        TimeSpan _elapsed;

        public TimeStruct()
        {
            _start = DateTime.UtcNow;
        }

        public TimeStruct(DateTime value)
        {
            _start = value;
        }

        public TimeStruct(DateTime start, TimeSpan elapsed)
        {
            _start = start;
            _elapsed = elapsed;
        }

        public DateTime Start { get => _start; set => _start = value; }
        public TimeSpan Elapsed { get => _elapsed; set => _elapsed = value; }


        /// <summary>
        /// [d] time elapsed since model start time
        /// </summary>
        public double model_time
        {
            get
            {
                return _elapsed.TotalDays;
            }
        }

        /// <summary>
        /// String date
        /// </summary>
        public string date_string
        {
            get
            {
                return _start.Add(_elapsed).ToString("yyyy-MM-dd HH:mm:ss");
            }
        }

        /// <summary>
        /// [d] Julian-format decimal date (time in days since 0:00 Jan 1 of current year)
        /// </summary>
        public double julian_day
        {
            get
            {
                var current = _start.Add(_elapsed);
                var startOfYear = new DateTime(current.Year, 1, 1, 0, 0, 0, DateTimeKind.Utc);
                return (current - startOfYear).TotalDays;
            }
        }

        /// <summary>
        /// Day of month
        /// </summary>
        public int day_of_month
        {
            get
            {
                var current = _start.Add(_elapsed);
                return current.Day;
            }
        }

        /// <summary>
        /// [1..12] month of year
        /// </summary>
        public int month
        {
            get
            {
                var current = _start.Add(_elapsed);
                return current.Month;
            }
        }

        /// <summary>
        /// year
        /// </summary>
        public int year
        {
            get
            {
                var current = _start.Add(_elapsed);
                return current.Year;
            }
        }

        /// <summary>
        /// Boolean flag that indicates leap year
        /// </summary>
        public bool leap_yr
        {
            get
            {
                var current = _start.Add(_elapsed);
                return DateTime.IsLeapYear(current.Year);
            }
        }

        /// <summary>
        /// Boolean flag indicating change of day for subdaily time steps
        /// </summary>
        public bool day_changed
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        
    }
}
