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
    /// Methods of calculating wind velocity
    /// </summary>
    public enum WindvelMethod
    {
        /// <summary>
        /// naive: constant wind velocity of 3 m/s
        /// </summary>
        WINDVEL_CONSTANT,
        /// <summary>
        /// wind velocity specfied as time series at gauge
        /// </summary>
        WINDVEL_DATA,
        /// <summary>
        /// from UBC Watershed model: daily temperature range-based
        /// </summary>
        WINDVEL_UBCWM,
        /// <summary>
        /// simplified version of UBCWM algorithm (linear relationship with T_max-T_min)
        /// </summary>
        WINDVEL_UBC_MOD,
        /// <summary>
        /// linear relationshipw with sqrt(T_max-T_min)
        /// </summary>
        WINDVEL_SQRT,
        /// <summary>
        /// linear relationship with ln(T_max-T_min)
        /// </summary>
        WINDVEL_LOG,
    }






}
