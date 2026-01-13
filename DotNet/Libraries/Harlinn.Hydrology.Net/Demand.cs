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


        public Demand(long id, string name, long SBID, bool isReservoir, Model pMod)
        {
            _ID = id;
            _name = name ?? string.Empty;
            _SBID = SBID;
            _is_reservoir = isReservoir;

            _demType = DemandType.DEMAND_TIME_SERIES;
            _retType = ReturnType.RETURN_MAX;

            _loc_index = Constants.DOESNT_EXIST;
            _global_index = Constants.DOESNT_EXIST;
            _unrestricted = false;
            _cumDelivDate = 0;

            _penalty = 1.0;
            _multiplier = 1.0;
            _demandFract = 0.0;

            _pDemandTS = null;
            _pReturnTS = null;
            _pDemandExp = null;
            _pReturnExp = null;
            _targetSBID = _SBID;
            _irrigHRUGroup = Constants.DOESNT_EXIST;
            _returnPct = 0.0;

            _currentDemand = 0.0;
            _currentRetTarget = 0.0;

            _pModel = pMod ?? throw new ArgumentNullException(nameof(pMod));
        }

        // Convenience ctor that attaches time series immediately
        public Demand(long id, string name, long SBID, bool isReservoir, TimeSeries pTS, Model pMod)
            : this(id, name, SBID, isReservoir, pMod)
        {
            _pDemandTS = pTS;
            _demType = DemandType.DEMAND_TIME_SERIES;
        }


        // --- Accessors ---
        public long GetDemandID() => _ID;
        public string GetName() => _name;
        public int GetGlobalIndex()
        {
            if (_global_index == Constants.DOESNT_EXIST)
            {
                throw new InvalidOperationException("GetGlobalIndex(): didnt set global index");
            }
            return _global_index;
        }
        public int GetLocalIndex()
        {
            if (_loc_index == Constants.DOESNT_EXIST)
            {
                throw new InvalidOperationException("GetLocalIndex(): didnt set local index");
            }
            return _loc_index;
        }
        public long GetSubBasinID() => _SBID;
        public double GetPenalty() => _penalty;
        public bool IsUnrestricted() => _unrestricted;
        public int GetCumulDeliveryDate() => _cumDelivDate;
        public bool IsReservoirDemand() => _is_reservoir;
        public double GetDemand() => _currentDemand;
        public double GetReturnFlowTarget() => _currentRetTarget;
        public double GetReturnFlowFraction() => _returnPct;
        public bool HasReturnFlow() => (_returnPct * _multiplier > 0.0);
        public long GetTargetSBID() => _targetSBID;

        // --- Manipulators ---
        public void SetLocalIndex(int ii) => _loc_index = ii;
        public void SetGlobalIndex(int d) => _global_index = d;
        public void SetDemandPenalty(double P) => _penalty = P;
        public void SetCumulDeliveryDate(int date) => _cumDelivDate = date;
        public void SetAsUnrestricted() => _unrestricted = true;
        public void SetMultiplier(double M) => _multiplier *= M; // allow multiple calls
        public void SetDemandTimeSeries(TimeSeries pTS)
        {
            _demType = DemandType.DEMAND_TIME_SERIES;
            _pDemandTS = pTS;
        }
        public void SetReturnTimeSeries(TimeSeries pTS)
        {
            if (_returnPct == 0.0) _returnPct = 1.0; // mirror C++ behaviour (note caveat in original)
            _retType = ReturnType.RETURN_TIME_SERIES;
            _pReturnTS = pTS;
        }
        public void SetReturnFraction(double val)
        {
            if (val > 1.0 || val < 0.0)
            {
                throw new ArgumentOutOfRangeException(nameof(val), "CDemand::SetReturnFraction: demand must be set between 0 and 1");
            }
            _returnPct = val;
        }
        public void SetDemandFraction(double val)
        {
            if (val > 1.0 || val < 0.0)
            {
                throw new ArgumentOutOfRangeException(nameof(val), "CDemand::SetDemandFraction: demand must be set between 0 and 1");
            }
            _demType = DemandType.DEMAND_PCT;
            _demandFract = val;
        }
        public void SetDemandExpression(Expression expression)
        {
            _demType = DemandType.DEMAND_EXPRESSION;
            _pDemandExp = expression;
        }
        public void SetReturnExpression(Expression expression)
        {
            _retType = ReturnType.RETURN_EXPRESSION;
            _pReturnExp = expression;
        }
        public void SetTargetSBID(long ID) => _targetSBID = ID;
        public void SetIrrigationGroup(int kk)
        {
            _targetSBID = Constants.DOESNT_EXIST;
            _irrigHRUGroup = kk;
        }

        // Initialize time series prior to simulation
        public void Initialize(Options Options)
        {
            _pDemandTS?.Initialize(Options.julian_start_day, Options.julian_start_year, Options.duration, Options.timestep, false, Options.calendar);
            _pReturnTS?.Initialize(Options.julian_start_day, Options.julian_start_year, Options.duration, Options.timestep, false, Options.calendar);
        }

        // Re-calculates _currentDemand and _currentRetTarget at start of time step
        public void UpdateDemand(Options Options, TimeStruct tt)
        {
            // Demand
            if (_demType == DemandType.DEMAND_TIME_SERIES)
            {
                int nn = (int)((tt.model_time + Constants.TIME_CORRECTION) / Options.timestep);
                double Qirr = _pDemandTS?.GetSampledValue(nn) ?? Constants.RAV_BLANK_DATA;
                if (Qirr == Constants.RAV_BLANK_DATA) Qirr = 0.0;
                _currentDemand = _multiplier * Qirr;
            }
            else if (_demType == DemandType.DEMAND_PCT)
            {
                double Q = _pModel.GetSubBasinByID(_SBID).GetOutflowRate();
                _currentDemand = _demandFract * Q;
            }
            else if (_demType == DemandType.DEMAND_EXPRESSION)
            {
                double val = _pModel.GetManagementOptimizer().EvaluateExpression(_pDemandExp, tt.model_time, true);
                if (Math.Abs(val - Constants.RAV_BLANK_DATA) < Constants.REAL_SMALL) _currentDemand = 0.0;
                else _currentDemand = val;
            }

            // Return target
            _currentRetTarget = 0.0;
            if (HasReturnFlow())
            {
                if (_retType == ReturnType.RETURN_TIME_SERIES)
                {
                    int nn = (int)((tt.model_time + Constants.TIME_CORRECTION) / Options.timestep);
                    double Qret = _pReturnTS?.GetSampledValue(nn) ?? Constants.RAV_BLANK_DATA;
                    if (Qret == Constants.RAV_BLANK_DATA) Qret = 0.0;
                    _currentRetTarget = _multiplier * Qret;
                }
                else if (_retType == ReturnType.RETURN_MAX)
                {
                    _currentRetTarget = 1e8;
                }
                else if (_retType == ReturnType.RETURN_EXPRESSION)
                {
                    Utils.ExitGracefully("UpdateDemand::RETURN_EXPRESSION not implemented", Constants.STUB);
                }
                _currentRetTarget = Math.Min(_currentRetTarget, _currentDemand);
            }
        }

    }
}
