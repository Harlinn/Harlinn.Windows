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
    /// The method of determining the amount of flux exchange crossing between SW and GW
    /// </summary>
    public enum FluxMethod
    {
        /// <summary>
        /// Regular process calculations
        /// </summary>
        FLUX_EX_STANDARD,
        /// <summary>
        /// All fluxes are determined using rating curves
        /// </summary>
        FLUX_EX_UFR,
    }
}
