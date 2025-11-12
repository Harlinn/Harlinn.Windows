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
    /// Methods used for subdaily temporal downscaling of daily average PET and snowmelt
    /// </summary>
    public enum SubdailyMethod
    {
        /// <summary>
        /// no correction for daily average values used
        /// </summary>
        SUBDAILY_NONE,
        /// <summary>
        /// Use half-sine wave pulse from dawn to dusk
        /// </summary>
        SUBDAILY_SIMPLE,
        /// <summary>
        /// from UBCWM - based upon cumulative temperature hours above zero Celsius
        /// </summary>
        SUBDAILY_UBC,
    }
}
