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
    /// Method of calculating abstraction of rainfall/snowmelt
    /// </summary>
    public enum AbstractionType
    {
        /// <summary>
        /// Abstraction by percentage
        /// </summary>
        ABST_PERCENTAGE,
        /// <summary>
        /// Fill abstraction
        /// </summary>
        ABST_FILL,
        /// <summary>
        /// Abstraction using SCS method
        /// </summary>
        ABST_SCS,
        /// <summary>
        /// Abstraction using PDMROF Method (Mekkonen et al., 2014)
        /// </summary>
        ABST_PDMROF,
        /// <summary>
        /// Abstraction using upscaled wetland fill and spill model (Taheri et al.)
        /// </summary>
        ABST_UWFS
    }




}
