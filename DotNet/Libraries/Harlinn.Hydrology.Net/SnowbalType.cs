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
    /// Methods of balancing energy based on melt/refreeze
    /// </summary>
    public enum SnowbalType
    {
        /// <summary>
        /// melt rate = potential melt, only SWE modified
        /// </summary>
        SNOBAL_SIMPLE_MELT,
        /// <summary>
        /// Cold content-based
        /// </summary>
        SNOBAL_COLD_CONTENT,
        /// <summary>
        /// HBV method
        /// </summary>
        SNOBAL_HBV,
        /// <summary>
        /// UBCWM method
        /// </summary>
        SNOBAL_UBCWM,
        /// <summary>
        /// Cema Neige method
        /// </summary>
        SNOBAL_CEMA_NEIGE,
        /// <summary>
        /// Two layer cold content (converted from GJ C# code)
        /// </summary>
        SNOBAL_TWO_LAYER,
        /// <summary>
        /// GAWSER snow melt model (modified from Object GAWSER to replicate behavior)
        /// </summary>
        SNOBAL_GAWSER,
        /// <summary>
        /// CRHM's energy balance snow model (from Marks, 1997)
        /// </summary>
        SNOBAL_CRHM_EBSM,
        /// <summary>
        /// HMETS single layer snow balance routine (Martel et al., 2017)
        /// </summary>
        SNOBAL_HMETS
    }

}
