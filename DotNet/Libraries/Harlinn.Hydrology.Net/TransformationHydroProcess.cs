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
    /// Calculates the decay of a substance in a particular water store
    /// </summary>
    public class TransformationHydroProcess : HydroProcess
    {
        TransportModel _pTransModel;

        /// <summary>
        /// transformation algorithm type
        /// </summary>
        TransformationType _ttype;
        /// <summary>
        /// index of reactant constituent
        /// </summary>
        int _constit_ind1;
        /// <summary>
        /// index of product constituent
        /// </summary>
        int _constit_ind2;
        /// <summary>
        /// index of transport process name
        /// </summary>
        int _process_ind;
        /// <summary>
        /// index of water store (or DOESNT_EXIST if this should occur in all water compartments)
        /// </summary>
        int _iWaterStore;
    }

}
