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
    /// Calculates the decay of a constituent
    /// </summary>
    public class DecayHydroProcess : HydroProcess
    {
        TransportModel _pTransModel;

        /// <summary>
        /// decay algorithm type
        /// </summary>
        DecayType _dtype;
        /// <summary>
        /// index, c, of constituent which is decaying
        /// </summary>
        int _constit_ind;

        /// <summary>
        /// index of transport process name
        /// </summary>
        int _process_ind;
        /// <summary>
        /// index ii of water store (or DOESNT_EXIST if this should occur in all water compartments)
        /// </summary>
        int _iWaterStore;
    }
}
