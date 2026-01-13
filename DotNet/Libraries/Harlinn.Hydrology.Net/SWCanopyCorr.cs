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
    /// Methods used for estimating canopy transmittance of shortwave radiation
    /// </summary>
    public enum SWCanopyCorr
    {
        /// <summary>
        /// Applies no canopy correction for shortwave radiation
        /// </summary>
        SW_CANOPY_CORR_NONE,
        /// <summary>
        /// Bulk shortwave canopy transmittance (no hourly or seasonal variation)
        /// </summary>
        SW_CANOPY_CORR_STATIC,
        /// <summary>
        /// Dynamic (varies hourly and seasonal) shortwave canopy transmittance
        /// </summary>
        SW_CANOPY_CORR_DYNAMIC,
        /// <summary>
        /// shortwave canopy transmittance according to UBCWM  (simple factor)
        /// </summary>
        SW_CANOPY_CORR_UBCWM
    }

}
