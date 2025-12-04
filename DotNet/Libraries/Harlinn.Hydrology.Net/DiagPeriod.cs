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
    public class DiagPeriod
    {
        string _name;
        TimeSpan _start;
        TimeSpan _end;
        Comparison _comp;
        double _thresh;

        public DiagPeriod(string name, TimeSpan start, TimeSpan end, Comparison comp, double thresh)
        {
            _name = name;
            _start = start;
            _end = end;
            _comp = comp;
            _thresh = thresh;
        }

        /// <summary>
        /// period name (e.g., "CALIBRATION")
        /// </summary>
        public string Name { get => _name; set => _name = value; }
        /// <summary>
        /// starttime (in local model time)
        /// </summary>
        public TimeSpan Start { get => _start; set => _start = value; }
        /// <summary>
        /// endtime (in local model time)
        /// </summary>
        public TimeSpan End { get => _end; set => _end = value; }
        /// <summary>
        /// comparison criterion (> or <)
        /// </summary>
        public Comparison Comp { get => _comp; set => _comp = value; }
        /// <summary>
        /// threshold percentage
        /// </summary>
        public double Thresh { get => _thresh; set => _thresh = value; }
    }
}
