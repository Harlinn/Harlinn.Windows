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

namespace Harlinn.TimeSeries.Net
{
    public readonly struct Range
    {
        readonly int _start;
        readonly int _end;

        public Range(int start, int end)
        {
            if (end < start)
            {
                throw new ArgumentOutOfRangeException(nameof(end), "End must be greater than or equal to start.");
            }
            _start = start;
            _end = end;
        }

        public int Start => _start;
        public int End => _end;

        public int Count => _end - _start;

        override public string ToString()
        {
            return $"[{_start}, {_end})";
        }
    }


}
