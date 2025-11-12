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
    /// Methods used for estimating incoming longwave radiation
    /// </summary>
    public enum LWincMethod
    {
        /// <summary>
        /// default implementation - reverts to Dingman 2014 if LW_RAD_DEFAULT is used (for backward compatibility)
        /// </summary>
        LW_INC_DEFAULT,
        /// <summary>
        /// specified in time series files
        /// </summary>
        LW_INC_DATA,
        /// <summary>
        /// From Sicart et al. (2005) as ported over from CRHM
        /// </summary>
        LW_INC_SICART,
        /// <summary>
        /// simple sky view factor approach for stream temperature modelling, Using Prata 1996 clear sky emissivity
        /// </summary>
        LW_INC_SKYVIEW,
        /// <summary>
        /// from Dingman (2014), using Brutsaert 1975 clear sky emissivity
        /// </summary>
        LW_INC_DINGMAN
    }

}
