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
    /// Calculates the advection of a substance
    /// </summary>
    public class LatAdvectionHydroProcess : LateralExchangeHydroProcess
    {
        TransportModel pTransModel;
        /// <summary>
        /// index of constituent being advected
        /// </summary>
        int _constit_ind;

        /// <summary>
        /// number of Dirichlet source compartments
        /// </summary>
        int _nSources;
        /// <summary>
        /// state variable indices of Dirichlet source compartments [size: nSources]
        /// </summary>
        int[] _iSource;
        /// <summary>
        /// array of source concentrations for Dirichlet sources [size: nSources]
        /// </summary>
        double[] _aSourceConcs;
    }
}
