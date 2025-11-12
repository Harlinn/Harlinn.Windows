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
    /// Calculates the complete dump of water from one storage compartment 
    /// in one HRU to another in another HRU
    /// </summary>
    public class LatFlushHydroProcess : LateralExchangeHydroProcess
    {
        /// <summary>
        /// global state variable index of source state var
        /// </summary>
        int _iFlushFrom;
        /// <summary>
        /// global state variable index of target state var
        /// </summary>
        int _iFlushTo;
        /// <summary>
        /// HRU group index of source HRUs
        /// </summary>
        int _kk_from;
        /// <summary>
        /// HRU group index of target HRUs
        /// </summary>
        int _kk_to;
        /// <summary>
        /// all transfer is within one sub-basin; otherwise, requires only one recipient HRU in model
        /// </summary>
        bool _constrain_to_SBs;
    }
}
