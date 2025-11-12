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
namespace Harlinn.Hydrology
{
    /// <summary>
    /// Stores information describing a specific instance in time
    /// </summary>
    public class TimeStruct
    {
        /// <summary>
        /// String date
        /// </summary>
        public string date_string;
        /// <summary>
        /// [d] time elapsed since model start time
        /// </summary>
        public double model_time;
        /// <summary>
        /// [d] Julian-format decimal date (time in days since 0:00 Jan 1 of current year)
        /// </summary>
        public double julian_day;
        /// <summary>
        /// Day of month
        /// </summary>
        public int day_of_month;
        /// <summary>
        /// [1..12] month of year
        /// </summary>
        public int month;
        /// <summary>
        /// year
        /// </summary>
        public int year;
        /// <summary>
        /// Boolean flag that indicates leap year
        /// </summary>
        public bool leap_yr;
        /// <summary>
        /// Boolean flag indicating change of day for subdaily time steps
        /// </summary>
        public bool day_changed;
    }
}
