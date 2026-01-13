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
    /// Methods used for routing water (lateral flow) to catchment outlet
    /// </summary>
    public enum CatchmentRoute
    {
        /// <summary>
        /// dumps all surface water directly in channel
        /// </summary>
        ROUTE_DUMP,
        /// <summary>
        /// Linear Unit Hydrograph with lag time
        /// </summary>
        ROUTE_DELAYED_FIRST_ORDER,
        /// <summary>
        /// Gamma Unit Hydrograph
        /// </summary>
        ROUTE_GAMMA_CONVOLUTION,
        /// <summary>
        /// Triangular Unit Hydrograph
        /// </summary>
        ROUTE_TRI_CONVOLUTION,
        /// <summary>
        /// Series of linear reservoirs (Nash Hydrograph)
        /// </summary>
        ROUTE_RESERVOIR_SERIES
    };
}
