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
    /// Methods used for converting total precipitation to rain/snow
    /// </summary>
    public enum RainsnowMethod
    {
        /// <summary>
        /// Use data instead of calculating rain/snow partition
        /// </summary>
        RAINSNOW_DATA,
        /// <summary>
        /// from Dingman - based upon min & max daily temperatures
        /// </summary>
        RAINSNOW_DINGMAN,
        /// <summary>
        /// Linear variation between two temperatures - corrects only rain portion
        /// </summary>
        RAINSNOW_HBV,
        /// <summary>
        /// HSPF approach - variable transition temperature
        /// </summary>
        RAINSNOW_HSPF,
        /// <summary>
        /// Linear variation between two temperatures
        /// </summary>
        RAINSNOW_UBCWM,
        /// <summary>
        /// Harder & Pomeroy (2013) method ported over from CRHM (Pomeroy et al 2007)
        /// </summary>
        RAINSNOW_HARDER,
        /// <summary>
        /// Wang et al. (2019) sigmoid function
        /// </summary>
        RAINSNOW_WANG,
        /// <summary>
        /// Jordan et al (1991) fixed function used in SNTHERM.89 model and Noah-MP3.6
        /// </summary>
        RAINSNOW_SNTHERM89,
        RAINSNOW_THRESHOLD
    }






}
