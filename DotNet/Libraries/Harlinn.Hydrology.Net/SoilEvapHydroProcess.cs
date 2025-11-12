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
    /// Calculates of loss of water from multiple soil layers to atmosphere using the root-weighting method
    /// </summary>
    public class SoilEvapHydroProcess : HydroProcess
    {
        /// <summary>
        /// Model of soil evaporation selected
        /// </summary>
        SoilEvapType type;
        /// <summary>
        /// array of soil indices
        /// </summary>
        int[] soil_ind;
        /// <summary>
        /// number of soil layers subject to evaporation
        /// </summary>
        int nSoilLayers;
    }
}
