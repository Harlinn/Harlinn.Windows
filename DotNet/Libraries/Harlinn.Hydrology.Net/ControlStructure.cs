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
    /// Reservoir outflow control structure
    /// </summary>
    public class ControlStructure
    {
        /// <summary>
        /// structure name
        /// </summary>
        string _name;
        /// <summary>
        /// subbasin ID
        /// </summary>
        long _SBID;
        /// <summary>
        /// outflow directed to this subbasin ID
        /// </summary>
        long _target_SBID;
        /// <summary>
        /// downstream reference elevation [m] (used in some structures for backwater, limiting flow, etc.)
        /// </summary>
        double _dRefElev;

        /// <summary>
        /// number of flow regimes
        /// </summary>
        int _nRegimes;
        /// <summary>
        /// flow regimes with unique Q=f(h,Q,...)
        /// </summary>
        List<OutflowRegime> _aRegimes;
    }
}
