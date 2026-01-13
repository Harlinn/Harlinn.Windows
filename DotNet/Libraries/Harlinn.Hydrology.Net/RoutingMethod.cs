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
    /// The methods which can be used to route water along channel between basins
    /// </summary>
    public enum RoutingMethod
    {
        /// <summary>
        /// No routing to be simulated
        /// </summary>
        ROUTE_NONE,
        /// <summary>
        /// Plug flow routing - no dissipation of wave travelling at reach celerity
        /// </summary>
        ROUTE_PLUG_FLOW,
        /// <summary>
        /// standard Muskingum algorithm
        /// </summary>
        ROUTE_MUSKINGUM,
        /// <summary>
        /// Muskingum-Cunge algorithm
        /// </summary>
        ROUTE_MUSKINGUM_CUNGE,
        /// <summary>
        /// Storage coefficient approach
        /// </summary>
        ROUTE_STORAGECOEFF,
        /// <summary>
        /// diffusive wave approximation
        /// </summary>
        ROUTE_DIFFUSIVE_WAVE,
        /// <summary>
        /// variable celerity/diffusivity diffusive wave approach
        /// </summary>
        ROUTE_DIFFUSIVE_VARY,
        /// <summary>
        /// simple iterative mass balance approach dS/dt=I-O
        /// </summary>
        ROUTE_HYDROLOGIC,
        /// <summary>
        /// Total variation diminishing approach of Schwanenberg and Montero, 2016
        /// </summary>
        ROUTE_TVD,
        /// <summary>
        /// routing handled via external script/live file support
        /// </summary>
        ROUTE_EXTERNAL
    }

}
