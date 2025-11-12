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
    /// Base class for lateral exchange processes
    /// </summary>
    public class LateralExchangeHydroProcess : HydroProcess
    {
        /// <summary>
        /// number of HRU lateral connections
        /// </summary>
        int _nLatConnections;
        /// <summary>
        /// array of HRU from indices [size: nLatConnections] (JRC: Usually 1?)
        /// </summary>
        int[] _kFrom;
        /// <summary>
        /// array of HRU to indices [size: nLatConnections]
        /// </summary>
        int[] _kTo;
        /// <summary>
        /// array of 'From' state variable indices [size: nLatConnections]
        /// </summary>
        int[] _iFromLat;
        /// <summary>
        /// array of 'To' state variable indices [size: nLatConnections]
        /// </summary>
        int[] _iToLat;

        /// <summary>
        /// global index of lateral flow process
        /// </summary>
        int _LatFlowIndex;

        Model _pModel;
    }
}
