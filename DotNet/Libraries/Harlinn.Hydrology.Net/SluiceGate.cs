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
    /// Sluice gate
    /// </summary>
    public class SluiceGate : StageDischargeRelation
    {
        /// <summary>
        /// bottom elevation of crest [m]
        /// </summary>
        double _bottom_elev;
        /// <summary>
        /// width of gate [m]
        /// </summary>
        double _gatewidth;
        /// <summary>
        /// height of gate when raised [m]
        /// </summary>
        double _gateheight;
        /// <summary>
        /// gate coefficient [-]
        /// </summary>
        double _gate_coeff;
        /// <summary>
        /// number of parallel (identical) gates [-]
        /// </summary>
        int _num_gates;
    }

}
