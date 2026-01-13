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
    /// UBC Watershed model snow parameters
    /// </summary>
    public struct UBCSnowParameters
    {
        /// <summary>
        /// albedo exponential decay threshold value (0.65)
        /// </summary>
        public double ALBASE;
        /// <summary>
        /// recession constant (0.9/day)
        /// </summary>
        public double ALBREC;
        /// <summary>
        /// "max annual melt" (~4000mm)
        /// </summary>
        public double MAX_CUM_MELT;
        /// <summary>
        /// total daily snowfall required to bring albedo to that of new snow [mm/d] ,  15
        /// </summary>
        public double ALBSNW;
    };

}
