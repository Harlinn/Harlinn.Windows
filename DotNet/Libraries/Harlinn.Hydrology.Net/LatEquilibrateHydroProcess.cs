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
    /// Claculates the complete dump of water from one storage
    /// compartment in one HRU to another in another HRU
    /// </summary>
    public class LatEquilibrateHydroProcess : LateralExchangeHydroProcess
    {
        /// <summary>
        /// global state variable index of state var
        /// </summary>
        int _iSV;
        /// <summary>
        /// HRU group index (or DOESNT_EXIST, if all HRUs should be equlibrated)
        /// </summary>
        int _kk;
        /// <summary>
        /// sum of areas of HRUs in HRU group within subbasin  [size: nSubBasins]
        /// </summary>
        double[] _Asum;
        /// <summary>
        /// 1/2 number of connections in basin b (=nHRUs in kk within basin-1) [size: nSubBasins]
        /// </summary>
        int[] _halfconn;
        /// <summary>
        /// all transfer is within one sub-basin; otherwise, requires only one recipient HRU in model
        /// </summary>
        bool _constrain_to_SBs;
        /// <summary>
        /// [0..1] % of water mixed per day
        /// </summary>
        double _mixing_rate;
    }
}
