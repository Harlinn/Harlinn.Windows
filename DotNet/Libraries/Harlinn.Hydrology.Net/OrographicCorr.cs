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
    /// Methods used for correcting forcing functions with elevation
    /// </summary>
    public enum OrographicCorr
    {
        /// <summary>
        /// no orographic corrections
        /// </summary>
        OROCORR_NONE,
        /// <summary>
        /// simple linear adiabatic lapse
        /// </summary>
        OROCORR_SIMPLELAPSE,
        /// <summary>
        /// HBV-EC style orographic corrections
        /// </summary>
        OROCORR_HBV,
        /// <summary>
        /// UBCWM-style orographic corrections
        /// </summary>
        OROCORR_UBCWM,
        /// <summary>
        /// UBCWM-style orographic corrections (simpler)
        /// </summary>
        OROCORR_UBCWM2,
        /// <summary>
        /// PRMS-style orographic corrections
        /// </summary>
        OROCORR_PRMS
    }

}
