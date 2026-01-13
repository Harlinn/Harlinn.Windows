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
    /// Methods used for estimating clear sky and extraterrestrial shortwave radiation
    /// </summary>
    public enum SWMethod
    {
        SW_RAD_NONE,
        /// <summary>
        /// Shortwave radiation specified in time series files
        /// </summary>
        SW_RAD_DATA,
        /// <summary>
        /// from Dingman text
        /// </summary>
        SW_RAD_DEFAULT,
        /// <summary>
        /// UBCWM approach
        /// </summary>
        SW_RAD_UBCWM,
        /// <summary>
        /// From Valiantzas, 2006
        /// </summary>
        SW_RAD_VALIANTZAS
    }

}
