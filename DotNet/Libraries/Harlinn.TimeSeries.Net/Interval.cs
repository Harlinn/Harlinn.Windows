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
    public readonly struct Interval
    {
        readonly DateTime _start;
        readonly DateTime _end;

        public Interval(DateTime start, DateTime end)
        {
            if (end < start)
            {
                throw new ArgumentOutOfRangeException(nameof(end), "End time must be greater than or equal to start time.");
            }
            _start = start;
            _end = end;
        }

        public DateTime Start => _start;
        public DateTime End => _end;

        public TimeSpan Duration => _end - _start;

        override public string ToString()
        {
            return $"[{_start:O}, {_end:O})";
        }
    }


}
