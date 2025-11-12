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
    /// Methods used for estimating net longwave radiation
    /// </summary>
    public enum LWMethod
    {
        /// <summary>
        /// Longwave radiation specified in time series files
        /// </summary>
        LW_RAD_DATA,
        /// <summary>
        /// Longwave radiation not simulated (equal to zero)
        /// </summary>
        LW_RAD_NONE,
        /// <summary>
        /// from Dingman text: uses Kustas (1994) approach for effective emissivity \cite Moran1994WRR
        /// </summary>
        LW_RAD_DEFAULT,
        /// <summary>
        /// UBCWM approach
        /// </summary>
        LW_RAD_UBCWM,
        /// <summary>
        /// HSPF approach (U.S. Corps of Engineers, 1956)
        /// </summary>
        LW_RAD_HSPF,
        /// <summary>
        /// From Valiantzas, 2006 via Doorenbos and Pruit (1977) and Shuttleworth and Wallace (1952)
        /// </summary>
        LW_RAD_VALIANTZAS
    }
}
