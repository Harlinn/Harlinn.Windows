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
    /// Base class for physical hydrological processes
    /// </summary>
    public class HydroProcess
    {
        Model pModel;

        /// <summary>
        /// Hydrological proccess, e.g., sublimation, infiltration, etc.
        /// </summary>
        ProcessType _process;
        /// <summary>
        /// indices of state variables/storage units that (typically) lose water/energy/mass (size: nConnections)
        /// </summary>
        int[] iFrom;
        /// <summary>
        /// indices of state variables/storage units that (typically) gain water/energy/mass (size: nConnections) (==iFrom if no mass/energy is exchanged in change of state variable)
        /// </summary>
        int[] iTo;
        /// <summary>
        /// usually 1, number of transfer routes between state variables/storage units
        /// </summary>
        int _nConnections;

        /// <summary>
        /// array of conditions for process to occur (ALL must be satisfied)
        /// </summary>
        Condition[] _pConditions;
        /// <summary>
        /// number of conditions
        /// </summary>
        int _nConditions;
        
    }
}
