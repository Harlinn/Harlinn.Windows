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
    /// Methods of estimating potential melt
    /// </summary>
    public enum PotmeltMethod
    {
        /// <summary>
        /// simple degree day method
        /// </summary>
        POTMELT_DEGREE_DAY,
        /// <summary>
        /// energy balance approach
        /// </summary>
        POTMELT_EB,
        /// <summary>
        /// restricted degree-day method
        /// </summary>
        POTMELT_RESTRICTED,
        /// <summary>
        /// degree day with rain-on-snow
        /// </summary>
        POTMELT_DD_RAIN,
        /// <summary>
        /// UBC watershed model approach
        /// </summary>
        POTMELT_UBCWM,
        /// <summary>
        /// custom degree day model used in HBV-EC
        /// </summary>
        POTMELT_HBV,
        /// <summary>
        /// HBV-EC degree day model with rain-on-snow
        /// </summary>
        POTMELT_HBV_ROS,
        /// <summary>
        /// user-specified potential melt forcing
        /// </summary>
        POTMELT_DATA,
        /// <summary>
        /// US Army Corps of Engineers Snow Melt
        /// </summary>
        POTMELT_USACE,
        /// <summary>
        /// Energy balance snow model from the Cold Regions Hydrology Model (CRHM) (Pomeroy, 2007)
        /// </summary>
        POTMELT_CRHM_EBSM,
        /// <summary>
        /// From HMETS model (Martel et al., 2017)
        /// </summary>
        POTMELT_HMETS,
        /// <summary>
        /// From Riley et al., 1972, as reported in HYDROTEL 2.1 manual
        /// </summary>
        POTMELT_RILEY,
        /// <summary>
        /// weighted average of multiple methods
        /// </summary>
        POTMELT_BLENDED,
        /// <summary>
        /// simple degree day with refreeze coefficient in winter
        /// </summary>
        POTMELT_DD_FREEZE,
        /// <summary>
        /// Potential melt not calculated
        /// </summary>
        POTMELT_NONE,
        /// <summary>
        /// special case - can't recognize melt method in input
        /// </summary>
        POTMELT_UNKNOWN
    }






}
