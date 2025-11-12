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
    /// Irrigation or other water demand
    /// </summary>
    public class Demand
    {
        /// <summary>
        /// unique long identifier
        /// </summary>
        long _ID;
        /// <summary>
        /// unique name/alias identifier
        /// </summary>
        string _name;

        /// <summary>
        /// model object
        /// </summary>
        Model _pModel;

        /// <summary>
        /// subbasin ID
        /// </summary>
        long _SBID;
        /// <summary>
        /// local demand index ii (counter in each subbasin or reservoir)
        /// </summary>
        int _loc_index;
        /// <summary>
        /// global demand index d (from list of all demands in water management model)
        /// </summary>
        int _global_index;
        /// <summary>
        /// true if withdrawal is from reservoir
        /// </summary>
        bool _is_reservoir;

        /// <summary>
        /// penalty for not satisfying demand [s/m3]
        /// </summary>
        double _penalty;

        /// <summary>
        /// true if demand is unrestricted by downstream flow regulations [default: false]
        /// </summary>
        bool _unrestricted;

        /// <summary>
        /// julian date to calculate cumulative deliveries from {default: Jan 1}
        /// </summary>
        int _cumDelivDate;

        // Demand characterization

        /// <summary>
        /// demand type
        /// </summary>
        DemandType _demType;

        /// <summary>
        /// multiplies time series or any other means of calculating demand
        /// </summary>
        double _multiplier;
        /// <summary>
        /// pointer to time series of demands (or NULL, if calculated elsewise)
        /// </summary>
        TimeSeries _pDemandTS;

        /// <summary>
        /// return expression (or null, if calculated elsewise)
        /// </summary>
        Expression _pDemandExp;

        /// <summary>
        /// [0..1] percentage of flow demanded
        /// </summary>
        double _demandFract;

        // Return flow variables

        /// <summary>
        /// return type
        /// </summary>
        ReturnType _retType;

        /// <summary>
        /// subbasin id of return destination (defaults to _SBID, is -1 for irrigation to HRU group)
        /// </summary>
        long _targetSBID;
        /// <summary>
        /// index kk of HRU group on which withdrawn water is applied
        /// </summary>
        int _irrigHRUGroup;
        /// <summary>
        /// percentage of delivered demand which returns to stream or land
        /// </summary>
        double _returnPct;
        /// <summary>
        /// time series of target return flows (or NULL, if calculated elsewise)
        /// </summary>
        TimeSeries _pReturnTS;
        /// <summary>
        /// return expression (or NULL, if calculated elsewise)
        /// </summary>
        Expression _pReturnExp;

        /// <summary>
        /// (time-variable) demand in current time step [m3/s]
        /// </summary>
        double _currentDemand;
        /// <summary>
        /// (time-variable) return flow target in current time step [m3/s]
        /// </summary>
        double _currentRetTarget;
    }
}
