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

using static Harlinn.Hydrology.Constants;
using static Harlinn.Mathematics.Net.Common;
using static Harlinn.Hydrology.Common;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Model for a contiguous watershed section with a primary channel, contains a collection of HRUs, used primarily to route water
    /// </summary>
    public class SubBasin
    {
        /// <summary>
        /// unique ID of subbasin (must be positive)
        /// </summary>
        long _ID;
        /// <summary>
        /// name
        /// </summary>
        string _name;
        /// <summary>
        /// true if disabled
        /// </summary>
        bool _disabled = false;
        /// <summary>
        /// p index in _pModel subbasin array
        /// </summary>
        int _global_p = DOESNT_EXIST;

        Model _pModel;

        // basin properties


        /// <summary>
        /// contributing surface area for subbasin [km2]
        /// </summary>
        double _basin_area = 0.0;
        /// <summary>
        /// total upstream drainage area [km2] (includes subbasin area)
        /// </summary>
        double _drainage_area = 0.0;
        /// <summary>
        /// ID of downstream subbasin; if <0, then this outflows outside the model domain
        /// </summary>
        long _downstream_ID;
        /// <summary>
        /// if true, hydrographs are generated for downstream flows
        /// </summary>
        bool _gauged;
        /// <summary>
        /// true if no subbasins drain into this one and _pInflowHydro==NULL
        /// </summary>
        bool _is_headwater = true;
        /// <summary>
        /// true if basin is 'conduit' basin, and shouldn't have HRUs
        /// </summary>
        bool _is_conduit;
        /// <summary>
        /// true if observed data in this basin should be assimilated.
        /// </summary>
        bool _assimilate = false;
        /// <summary>
        /// downstream subbasin instance
        /// </summary>
        SubBasin? _pDownSB = null;

        // catchment routing properties

        /// <summary>
        /// basin time of concentration [d]
        /// </summary>
        double _t_conc = AUTO_COMPUTE;
        /// <summary>
        /// basin time to peak [d] (<=_t_conc)
        /// </summary>
        double _t_peak = AUTO_COMPUTE;
        /// <summary>
        /// basin time lag [d]
        /// </summary>
        double _t_lag = AUTO_COMPUTE;
        /// <summary>
        /// linear basin/catchment routing constant [1/d]
        /// </summary>
        double _reservoir_constant = AUTO_COMPUTE;
        /// <summary>
        /// number of linear reservoirs used for in-catchment routing
        /// </summary>
        int _num_reservoirs = 1;
        /// <summary>
        /// shape parameter of gamma unit hydrograph
        /// </summary>
        double _gamma_shape = 3.0;
        /// <summary>
        /// scale parameter of gamma unit hydrograph
        /// </summary>
        double _gamma_scale = 1.0;
        /// <summary>
        /// HRU *index* k (not ID) associated with reach. Used for reach-specific forcings.
        /// </summary>
        int _reach_HRUindex = DOESNT_EXIST;
        /// <summary>
        /// in-catchment sensible exchange coefficient [1/d]
        /// </summary>
        double _sens_exch_coeff = 0.0;
        /// <summary>
        /// in-catchment groundwater temperature exchange coefficient [1/d]
        /// </summary>
        double _GW_exch_coeff = 0.0;

        /// <summary>
        /// gross exchange flux with groundwater [m/d]
        /// </summary>
        double _hyporheic_flux = 0.0;
        /// <summary>
        /// convection coefficient [MJ/m2/d/K]
        /// </summary>
        double _convect_coeff = 2.0;
        /// <summary>
        /// bed thermal conductivity [MJ/m/d/K]
        /// </summary>
        double _bed_conductivity = 0.0;
        /// <summary>
        /// mean thickness of stream bed [m]
        /// </summary>
        double _bed_thickness = 0.5;

        //River/stream  channel data:

        /// <summary>
        /// Main channel
        /// </summary>
        ChannelXSect? _pChannel;

        /// <summary>
        /// length of subbasin reach [m]
        /// </summary>
        double _reach_length;
        /// <summary>
        /// reference flow rate [m3/s]
        /// </summary>
        double _Q_ref;
        /// <summary>
        /// celerity at reference flow rate (if ==AUTO_COMPUTE, or user-specified otherwiae)[m/s]
        /// </summary>
        double _c_ref = AUTO_COMPUTE;
        /// <summary>
        /// channel top width at reference flow rate [m]
        /// </summary>
        double _w_ref = AUTO_COMPUTE;
        /// <summary>
        /// manning's n for channel (or uses channel one, if =AUTO_COMPUTE)
        /// </summary>
        double _mannings_n = AUTO_COMPUTE;
        /// <summary>
        /// channel slope (rise over run) (or uses channel one, if =AUTO_COMPUTE)
        /// </summary>
        double _slope = AUTO_COMPUTE;
        /// <summary>
        /// channel diffusivity (specified or calculated, if =AUTO_COMPUTE) [m2/s]
        /// </summary>
        double _diffusivity = AUTO_COMPUTE;

        //Other params

        /// <summary>
        /// correction factor for rainfall [-]
        /// </summary>
        double _rain_corr = 1.0;
        /// <summary>
        /// correction factor for snowfall [-]
        /// </summary>
        double _snow_corr = 1.0;
        /// <summary>
        /// correction factor (additive) for temperature [-]
        /// </summary>
        double _temperature_corr = 0.0;

        /// <summary>
        /// Number of river segments used in routing(>=1)
        /// </summary>
        int _nSegments;

        // Reservoir


        /// <summary>
        /// Reservoir object (or NULL, if no reservoir)
        /// </summary>
        Reservoir? _pReservoir = null;
        /// <summary>
        /// true if lake or reservoir should be disabled/never created
        /// </summary>
        bool _res_disabled = false;
        /// <summary>
        /// corrected reach length [m] if reservoir/lake is disabled
        /// </summary>
        double _reach_length2;

        // state variables:

        /// <summary>
        /// downstream river (out)flow [m3/s] at start of time step at end of each channel segment [size=_nSegments]
        /// </summary>
        double[]? _aQout;
        /// <summary>
        /// history of lateral runoff into surface water [m3/s][size:_nQlatHist] - uniform (time-averaged) over timesteps
        /// if Ql=Ql(t), aQlatHist[0]=Qlat(t to t+dt), aQlatHist[1]=Qlat(t-dt to t)...
        /// </summary>
        double[]? _aQlatHist = null;

        /// <summary>
        /// size of _aQlatHist array
        /// </summary>
        int _nQlatHist = 0;
        /// <summary>
        /// water storage in channel [m3]
        /// </summary>
        double _channel_storage = 0.0;
        /// <summary>
        /// water storage in rivulets [m3]
        /// </summary>
        double _rivulet_storage = 0.0;
        /// <summary>
        /// Qout from downstream channel segment [m3/s] at start of previous timestep- needed for reporting integrated outflow
        /// </summary>
        double _QoutLast = AUTO_COMPUTE;
        /// <summary>
        /// Qlat (after convolution) at start of previous timestep [m3/s]
        /// </summary>
        double _QlatLast = AUTO_COMPUTE;
        /// <summary>
        /// local contribution to current subbasin outflow [m3/s] (just from in-catchment routing)
        /// </summary>
        double _Qlocal = 0;
        /// <summary>
        /// last local contribution [m3/s]
        /// </summary>
        double _QlocLast = 0;

        /// <summary>
        /// Qirr (delivered water demand) at end of timestep [m3/s] (for MB accounting)
        /// </summary>
        double _Qirr = 0.0;
        /// <summary>
        /// Qirr (delivered water demand) at start of timestep [m3/s] (for MB accounting)
        /// </summary>
        double _QirrLast = 0.0;
        /// <summary>
        /// diverted flow at start of timestep [m3/s] (for MB accounting)
        /// </summary>
        double _QdivLast = 0.0;
        /// <summary>
        /// diverted flow at end of timestep [m3/s] (for MB accounting)
        /// </summary>
        double _Qdiverted = 0;
        /// <summary>
        /// delivered flow at end of time step if management optimization is used [m3/s]
        /// </summary>
        double _Qdelivered = 0.0;
        /// <summary>
        /// delivered flow at end of time step for each water demand [m3/s] [size: _nIrrigDemands]
        /// </summary>
        double[]? _aQdelivered = null;
        /// <summary>
        /// return flow associated with deliveries (may be redirected to other basin) [m3/s]
        /// </summary>
        double[]? _aQreturned = null;
        /// <summary>
        /// return flow at end of time step if management optimization is used [m3/s] (may be sourced from other basin)
        /// </summary>
        double _Qreturn = 0.0;

        // Hydrograph Memory
        /// <summary>
        /// history of inflow from upstream into primary channel [m3/s][size:nQinHist] (aQinHist[n] = Qin(t-ndt))
        ///   _aQinHist[0]=Qin(t), _aQinHist[1]=Qin(t-dt), _aQinHist[2]=Qin(t-2dt)...
        /// </summary>
        double[]? _aQinHist = null;

        /// <summary>
        /// size of _aQinHist array
        /// </summary>
        int _nQinHist = 0;
        /// <summary>
        /// reach celerity history [size: _nQinHist] (used for ROUTE_DIFFUSIVE_VARY only)
        /// </summary>
        double[]? _c_hist = null;

        // characteristic weighted hydrographs

        /// <summary>
        /// [size:_nQlatHist] catchment unit hydrograph (time step-dependent). area under = 1.0.
        /// </summary>
        double[]? _aUnitHydro = null;
        /// <summary>
        /// [size:_nQinHist ] routing unit hydrograph. area under = 1.0.
        /// </summary>
        double[]? _aRouteHydro = null;

        // HRUs

        /// <summary>
        /// constituent HRUs with different hydrological characteristics
        /// </summary>
        int _nHydroUnits = 0;

        /// <summary>
        /// [size:nHydroUnits] Array of pointers to constituent HRUs
        /// </summary>
        HydroUnit[]? _pHydroUnits = null;

        // Treatment Plant/Irrigation/Other incoming hydrograph

        /// <summary>
        /// time series of inflows; NULL if no specified input - Inflow at upstream entrance of basin
        /// </summary>
        TimeSeries? _pInflowHydro = null;
        /// <summary>
        /// time series of inflows/extractions ; at downstream end of basin reach
        /// </summary>
        TimeSeries? _pInflowHydro2 = null;
        /// <summary>
        /// time series of environmental minimum flow targets that force reduced irrigation demand (=0 by default)
        /// </summary>
        TimeSeries? _pEnviroMinFlow = null;

        /// <summary>
        /// number of water demand objects
        /// </summary>
        int _nWaterDemands = 0;
        /// <summary>
        /// array of demand objects; demand applied at downstream end of basin reach [size: _nIrrigDemand]
        /// </summary>
        Demand[]? _pWaterDemands = null;

        /// <summary>
        /// number of flow diversions from basin
        /// </summary>
        int _nDiversions = 0;
        /// <summary>
        /// array of pointers to flow diversion structures
        /// </summary>
        Diversion[]? _pDiversions = null;
        /// <summary>
        /// for irrigation, fraction of flow above enviro min. flow that is not allowed to be used [0..1] (0 default)
        /// </summary>
        double _unusable_flow_pct = 0.0;

        public SubBasin(Model pMod, long Identifier, string Name, long down_ID, ChannelXSect? pChan, double reach_len, double Qreference, bool gaged, bool is_conduit)
        {
            ArgumentNullException.ThrowIfNull(pMod);
            if ((Qreference <= 0.0) && (Qreference != AUTO_COMPUTE))
            {
                throw new ArgumentException("CSubBasin::Constructor: Reference flow must be non-zero and positive (or _AUTO)");
            }

            _pModel = pMod;
            _ID = Identifier;
            _name = Name;
            _is_conduit = is_conduit;

            _reach_length = reach_len;
            _reach_length2 = reach_len;
            
            // estimate reach length and _nSegments if needed
            //-----------------------------------------------------------------------
            double max_len = _pModel.GetGlobalParams().max_reach_seglength * M_PER_KM;

            if((_reach_length==AUTO_COMPUTE) && (max_len/M_PER_KM<0.99*DEFAULT_MAX_REACHLENGTH))
            {
                string warningMessage = $"Basin {_ID} with _AUTO reach length will be assigned a single reach segment; to override, specify a specific reach length";
                Runtime.WriteWarning(warningMessage, ExitCode.BAD_DATA_WARN);
                _nSegments = 1;
            }
            else
            {
                _nSegments = Max((int)(Ceiling(_reach_length/max_len)),1);
            }

            
            if (_nSegments > MAX_RIVER_SEGS) 
            {
                string warn = $"CSubBasin:Constructor: exceeded maximum river segments in basin {_ID}: MAX_REACH_SEGLENGTH may be too small";
                Runtime.WriteWarning(warn, true); 
                _nSegments = MAX_RIVER_SEGS - 1; 
            }

            _downstream_ID = down_ID;
            if (_downstream_ID < 0) 
            {
                //outflow basin
                _downstream_ID = DOESNT_EXIST; 
            }
            _gauged = gaged;
            _pChannel = pChan; //Can be NULL
            
            //Initialized in Initialize
            _aQout = new double[_nSegments];
            Array.Fill(_aQout, AUTO_COMPUTE);

            _Q_ref = Qreference;
            
            if (pChan != null)
            {
                _mannings_n = pChan.GetMinMannings();
                _slope = pChan.GetBedslope();
            }
        }

        /// <summary>
        /// Returns subbasin ID
        /// </summary>
        /// <returns></returns>
        public long GetID() 
        {
            return _ID; 
        }

        /// <summary>
        /// Subbasin ID
        /// </summary>
        public long Id => _ID;

        public int GetGlobalIndex() => _global_p;
        public string GetName() => _name;
        public double GetBasinArea() => _basin_area;
        public double GetDrainageArea() => _drainage_area;
        public long GetDownstreamID() => _downstream_ID;
        public double GetReachLength() => _reach_length;
        public bool IsGauged() => _gauged;
        public bool IsHeadwater() => _is_headwater;
        public int GetNumSegments() => _nSegments;
        public bool IsEnabled() => !_disabled;
        public double GetRainCorrection() => _rain_corr;
        public double GetSnowCorrection() => _snow_corr;
        public double GetTemperatureCorrection() => _temperature_corr;
        public double[] GetUnitHydrograph() => _aUnitHydro;
        public double[] GetRoutingHydrograph() => _aRouteHydro;
        public double[] GetInflowHistory() => _aQinHist;
        public double[] GetOutflowArray() => _aQout;
        public double[] GetLatHistory() => _aQlatHist;
        public int GetLatHistorySize() => _nQlatHist;
        public int GetInflowHistorySize() => _nQinHist;
        public int GetOutflowArraySize() => _nSegments;
        public bool UseInFlowAssimilation() => _assimilate;
        public int GetNumHRUs() => _nHydroUnits;
        public HydroUnit GetHRU(int ks)
        {
#if STRICT_CHECK
        if (ks < 0 || ks >= _nHydroUnits) throw new IndexOutOfRangeException("CSubBasin:GetHRU::improper index");
#endif
            return _pHydroUnits[ks];
        }

        public Reservoir GetReservoir() => _pReservoir;

        public double GetAvgStateVar(int i)
        {
#if STRICT_CHECK
        if (i < 0 || i >= _pModel.GetNumStateVars()) throw new ArgumentOutOfRangeException(nameof(i));
#endif
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += _pHydroUnits[k].GetStateVarValue(i) * _pHydroUnits[k].GetArea();
                }
            }
            if (_basin_area == 0.0) return 0.0;
            return sum / _basin_area;
        }

        public double GetAvgConcentration(int i)
        {
#if STRICT_CHECK
        if (i < 0 || i >= _pModel.GetNumStateVars()) throw new ArgumentOutOfRangeException(nameof(i));
#endif
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += _pHydroUnits[k].GetConcentration(i) * _pHydroUnits[k].GetArea();
                }
            }
            if (_basin_area == 0.0) return 0.0;
            return sum / _basin_area;
        }

        public double GetAvgForcing(ForcingType ftype)
        {
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += _pHydroUnits[k].GetForcing(ftype) * _pHydroUnits[k].GetArea();
                }
            }
            if (_basin_area == 0.0) return 0.0;
            return sum / _basin_area;
        }

        public double GetAvgCumulFlux(int i, bool to)
        {
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += _pHydroUnits[k].GetCumulFlux(i, to) * _pHydroUnits[k].GetArea();
                }
            }
            if (_basin_area == 0.0) return 0.0;
            return sum / _basin_area;
        }

        public double GetAvgCumulFluxBet(int iFrom, int iTo)
        {
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += _pHydroUnits[k].GetCumulFluxBet(iFrom, iTo) * _pHydroUnits[k].GetArea();
                }
            }
            if (_basin_area == 0.0) return 0.0;
            return sum / _basin_area;
        }

        public double GetSpecifiedInflow(double t)
        {
            if (_pInflowHydro == null) return 0.0;
            return _pInflowHydro.GetValue(t);
        }

        public double GetDownstreamInflow(double t)
        {
            if (_pInflowHydro2 == null) return 0.0;
            return _pInflowHydro2.GetValue(t);
        }

        public double GetTotalWaterDemand()
        {
            double sum = 0.0;
            for (int ii = 0; ii < _nWaterDemands; ii++)
            {
                sum += _pWaterDemands[ii].GetDemand();
            }
            return sum;
        }

        public double GetWaterDemand(int ii)
        {
#if STRICT_CHECK
        if (ii < 0 || ii >= _nWaterDemands) throw new IndexOutOfRangeException("CSubBasin::GetWaterDemand: invalid index");
#endif
            return _pWaterDemands[ii].GetDemand();
        }

        public double GetDemandDelivery()
        {
            double sum = 0;
            for (int ii = 0; ii < _nWaterDemands; ii++) sum += _aQdelivered[ii];
            return sum;
        }

        public double GetTotalReturnFlow() => _Qreturn;

        public double GetDemandDelivery(int ii)
        {
#if STRICT_CHECK
        if (ii < 0 || ii >= _nWaterDemands) throw new IndexOutOfRangeException("CSubBasin::GetDemandDelivery: invalid demand index");
#endif
            return _aQdelivered[ii];
        }

        public double GetReturnFlow(int ii)
        {
#if STRICT_CHECK
        if (ii < 0 || ii >= _nWaterDemands) throw new IndexOutOfRangeException("CSubBasin::GetReturnFlow: invalid demand index");
#endif
            return _aQreturned[ii];
        }

        public double GetDownstreamIrrDemand(double t)
        {
            double Qirr = GetTotalWaterDemand();

            if (_downstream_ID == Constants.DOESNT_EXIST) return Qirr;
            return _pDownSB.GetDownstreamIrrDemand(t) + Qirr;
        }

        public double GetEnviroMinFlow(double t)
        {
            if (_pEnviroMinFlow == null) return 0.0;
            double Qmin = _pEnviroMinFlow.GetValue(t);
            if (Qmin == Constants.RAV_BLANK_DATA) Qmin = 0;
            return Qmin;
        }

        public int GetDiversionTargetIndex(int i)
        {
#if STRICT_CHECK
        if (i < 0 || i >= _nDiversions) throw new IndexOutOfRangeException("GetDiversionTargetIndex: bad index");
#endif
            return _pDiversions[i].target_p;
        }

        public bool HasIrrigationDemand()
        {
            int nResDemands = 0;
            if (_pReservoir != null) nResDemands = _pReservoir.GetNumWaterDemands();
            return ((_nWaterDemands + nResDemands) > 0);
        }

        public bool HasEnviroMinFlow() => _pEnviroMinFlow != null;

        public double ApplyIrrigationDemand(double t, double Q, bool optimized)
        {
            if (_nWaterDemands == 0) return 0.0;

            if (optimized)
            {
                return Math.Min(Q, _Qdelivered);
            }

            double Qdemand = GetTotalWaterDemand();
            double Qmin = GetEnviroMinFlow(t);
            double Qdelivered = Math.Min(Math.Max((1.0 - _unusable_flow_pct) * (Q - Qmin), 0.0), Qdemand);
            return Qdelivered;
        }

        public int GetNumDiversions() => _nDiversions;

        public double GetDiversionFlow(int i, double Q, OptStruct Options, TimeStruct tt, out int p_Divert)
        {
            p_Divert = Constants.DOESNT_EXIST;
            if (i < 0 || i >= _nDiversions) throw new InvalidOperationException("CSubBasin::GetDiversionFlow");
            if (_pDiversions[i] == null) { p_Divert = Constants.DOESNT_EXIST; return 0.0; }

            p_Divert = _pDiversions[i].target_p;
            if (Utils.IsInDateRange(tt.julian_day, _pDiversions[i].julian_start, _pDiversions[i].julian_end))
            {
                if (_pDiversions[i].aQdivert == null)
                {
                    if (Q > _pDiversions[i].min_flow)
                    {
                        return (Q - _pDiversions[i].min_flow) * _pDiversions[i].percentage;
                    }
                }
                else
                {
                    return Utils.InterpolateCurve(Q, _pDiversions[i].aQsource, _pDiversions[i].aQdivert, _pDiversions[i].nPoints, false);
                }
            }
            return 0.0;
        }

        public void AddFlowDiversion(int jul_start, int jul_end, int target_p, double min_flow, double pct)
        {
            if (jul_start < 0 || jul_start > 366) Utils.ExitGracefully("CSubBasin::AddFlowDiversion: invalid julian start date. must be between 0 and 366", Constants.BAD_DATA_WARN);
            if (jul_end < 0 || jul_end > 366) Utils.ExitGracefully("CSubBasin::AddFlowDiversion: invalid julian start date. must be between 0 and 366", Constants.BAD_DATA_WARN);
            if (min_flow < 0) Utils.WriteWarning("CSubBasin::AddFlowDiversion: negative minimum flow. will be corrected to 0.0", true);
            if (pct < 0 || pct > 100) Utils.WriteWarning("CSubBasin::AddFlowDiversion: invalid diversion fraction. Must be between 0.0 (0%) and 1.0 (100%)", true);
            if (jul_start > jul_end) Utils.WriteWarning("CSubBasin::AddFlowDiversion: julian start date after julian end date. No diversion will occur", true);
            if (target_p == Constants.DOESNT_EXIST) Utils.WriteWarning("CSubBasin::AddFlowDiversion: target diversion subbasin is -1. Watershed mass balance reporting does not yet incorporate this loss, and will incorrectly indicate a mass balance error.", true);

            var div = new Diversion
            {
                julian_end = jul_end,
                julian_start = jul_start,
                min_flow = Math.Max(min_flow, 0.0),
                percentage = Math.Min(Math.Max(pct, 0.0), 1.0),
                target_p = target_p
            };

            Utils.DynArrayAppend(ref _pDiversions, div, ref _nDiversions);
        }

        public void AddFlowDiversion(int jul_start, int jul_end, int target_p, double[] aQ1, double[] aQ2, int NQ)
        {
            if (jul_start < 0 || jul_start > 366) Utils.ExitGracefully("CSubBasin::AddFlowDiversion: invalid julian start date. must be between 0 and 366", Constants.BAD_DATA_WARN);
            if (jul_end < 0 || jul_end > 366) Utils.ExitGracefully("CSubBasin::AddFlowDiversion: invalid julian start date. must be between 0 and 366", Constants.BAD_DATA_WARN);
            if (jul_start > jul_end) Utils.WriteWarning("CSubBasin::AddFlowDiversion: julian start date after julian end date. No diversion will occur", true);
            if (target_p == Constants.DOESNT_EXIST) Utils.WriteWarning("CSubBasin::AddFlowDiversion: target diversion subbasin is -1. Watershed mass balance reporting does not yet incorporate this loss, and will incorrectly indicate a mass balance error.", true);

            var div = new Diversion
            {
                julian_end = jul_end,
                julian_start = jul_start,
                target_p = target_p,
                min_flow = Constants.RAV_BLANK_DATA,
                percentage = Constants.RAV_BLANK_DATA,
                nPoints = NQ,
                aQsource = new double[NQ],
                aQdivert = new double[NQ]
            };

            for (int i = 0; i < NQ; i++)
            {
                div.aQsource[i] = aQ1[i];
                div.aQdivert[i] = aQ2[i];
            }

            Utils.DynArrayAppend(ref _pDiversions, div, ref _nDiversions);
        }

        public int GetReachHRUIndex() => _reach_HRUindex;
        public double GetConvectionCoeff() => _convect_coeff;
        public double GetHyporheicFlux() => _hyporheic_flux;
        public double GetRiverbedConductivity() => _bed_conductivity;
        public double GetRiverbedThickness() => _bed_thickness;
        public double GetChannelStorage() => _channel_storage;
        public double GetReservoirStorage() => _pReservoir == null ? 0.0 : _pReservoir.GetStorage();
        public double GetRivuletStorage() => _rivulet_storage;
        public int GetNumWaterDemands() => _nWaterDemands;
        public Demand GetWaterDemandObj(int ii)
        {
#if STRICT_CHECK
        if (ii < 0 || ii >= _nWaterDemands) throw new IndexOutOfRangeException("CSubBasin::GetWaterDemandObj: invalid index");
#endif
            return _pWaterDemands[ii];
        }

        public double GetOutflowRate()
        {
            if (_pReservoir != null) return _pReservoir.GetOutflowRate();
            return _aQout[_nSegments - 1];
        }

        public double GetChannelOutflowRate() => _aQout[_nSegments - 1] + _Qdiverted;
        public double GetLastChannelOutflowRate() => _QoutLast + _QdivLast;
        public double GetLastOutflowRate() => _QoutLast;
        public double GetLocalOutflowRate() => _Qlocal;
        public double GetReservoirInflow() => _pReservoir == null ? 0.0 : _aQout[_nSegments - 1];

        public double GetReservoirLosses(double tstep) => _pReservoir == null ? 0.0 : _pReservoir.GetReservoirLosses(tstep);

        public double GetIrrigationLosses(double tstep) => 0.5 * (_QirrLast + _Qirr) * tstep * Constants.SEC_PER_DAY;
        public double GetDiversionLosses(double tstep) => 0.5 * (_Qdiverted + _QdivLast) * tstep * Constants.SEC_PER_DAY;

        public double GetIntegratedOutflow(double tstep)
        {
            if (_pReservoir != null) return _pReservoir.GetIntegratedOutflow(tstep);
            return 0.5 * (_aQout[_nSegments - 1] + _QoutLast) * (tstep * Constants.SEC_PER_DAY);
        }

        public double GetIntegratedReservoirInflow(double tstep)
        {
            if (_pReservoir == null) return 0.0;
            return 0.5 * (_aQout[_nSegments - 1] + _QoutLast) * (tstep * Constants.SEC_PER_DAY);
        }

        public double GetIntegratedSpecInflow(double t, double tstep)
        {
            double sum = 0.0;
            sum += 0.5 * (GetSpecifiedInflow(t) + GetSpecifiedInflow(t + tstep)) * (tstep * Constants.SEC_PER_DAY);
            sum += GetDownstreamInflow(t) * (tstep * Constants.SEC_PER_DAY);
            return sum;
        }

        public double GetIntegratedLocalOutflow(double tstep) => 0.5 * (_Qlocal + _QlocLast) * (tstep * Constants.SEC_PER_DAY);

        public double GetReferenceFlow() => _Q_ref;
        public double GetTimeOfConc() => _t_conc;

        public double GetReferenceXSectArea()
        {
            if (_Q_ref == Constants.AUTO_COMPUTE) return Constants.AUTO_COMPUTE;
            if (_pChannel == null) return Constants.ALMOST_INF;
            return _pChannel.GetArea(_Q_ref, _slope, _mannings_n);
        }

        public double GetReferenceCelerity() => _c_ref;

        public double GetCelerity()
        {
            if (_pChannel != null) return _pChannel.GetCelerity(_aQout[_nSegments - 1], _slope, _mannings_n);
            return 0.0;
        }

        public double GetDiffusivity()
        {
            if ((_pChannel != null) && (_diffusivity == Constants.AUTO_COMPUTE))
                return _pChannel.GetDiffusivity(_Q_ref, _slope, _mannings_n);
            return _diffusivity;
        }

        public double GetRiverDepth()
        {
            if (_pChannel == null) return Constants.ALMOST_INF;
            const double MIN_CHANNEL_DEPTH = 0.01;
            return Math.Max(_pChannel.GetDepth(_aQout[_nSegments - 1], _slope, _mannings_n), MIN_CHANNEL_DEPTH);
        }

        public double GetXSectArea()
        {
            if (_pChannel == null) return Constants.ALMOST_INF;
            const double MIN_CHANNEL_AREA = 0.01;
            return Math.Max(_pChannel.GetArea(_aQout[_nSegments - 1], _slope, _mannings_n), MIN_CHANNEL_AREA);
        }

        public double GetWaterLevel()
        {
            if (_pChannel == null) return Constants.ALMOST_INF;
            return _pChannel.GetStageElev(_aQout[_nSegments - 1], _slope, _mannings_n);
        }

        public double GetBedslope()
        {
            if (_pChannel == null) return 0.0;
            return _pChannel.GetBedslope();
        }

        public double GetWettedPerimeter()
        {
            if (_pChannel == null) return Constants.ALMOST_INF;
            return _pChannel.GetWettedPerim(_aQout[_nSegments - 1], _slope, _mannings_n);
        }

        public double GetTopWidth()
        {
            if (_pChannel == null) return Constants.ALMOST_INF;
            return _pChannel.GetTopWidth(_aQout[_nSegments - 1], _slope, _mannings_n);
        }

        public double GetUnusableFlowPercentage() => _unusable_flow_pct;

        // --- Manipulators ---
        public void AddHRU(HydroUnit pHRU)
        {
            if (!Utils.DynArrayAppend(ref _pHydroUnits, pHRU, ref _nHydroUnits))
                Utils.ExitGracefully("CSubBasin::AddHRU: adding NULL HRU", Constants.BAD_DATA);
        }

        public void AddReservoir(Reservoir pRes)
        {
            if (_pReservoir != null) Utils.ExitGracefully("CSubBasin::AddReservoir: only one reservoir may be specified per basin", Constants.BAD_DATA);
            if (_res_disabled)
            {
                pRes.DisposeIfNeeded();
                _reach_length = _reach_length2;
                return;
            }
            _pReservoir = pRes;
        }

        public void SetGlobalIndex(int p) { _global_p = p; }

        public bool SetBasinProperties(string label, double value)
        {
            var label_n = label.ToUpperInvariant();
            switch (label_n)
            {
                case "TIME_CONC": _t_conc = value; break;
                case "TIME_TO_PEAK": _t_peak = value; break;
                case "TIME_LAG": _t_lag = value; break;
                case "RES_CONSTANT": _reservoir_constant = value; break;
                case "NUM_RESERVOIRS": _num_reservoirs = (int)value; break;
                case "GAMMA_SHAPE": _gamma_shape = value; break;
                case "GAMMA_SCALE": _gamma_scale = value; break;
                case "Q_REFERENCE": _Q_ref = value; break;
                case "MANNINGS_N": _mannings_n = value; break;
                case "SLOPE": _slope = value; break;
                case "DIFFUSIVITY": _diffusivity = value; break;
                case "CELERITY": _c_ref = value; break;
                case "RAIN_CORR": _rain_corr = value; break;
                case "SNOW_CORR": _snow_corr = value; break;
                case "TEMP_CORR": _temperature_corr = value; break;
                case "REACH_HRU_ID": _reach_HRUindex = (int)value; break;
                case "HYPORHEIC_FLUX": _hyporheic_flux = value; break;
                case "CONVECT_COEFF": _convect_coeff = value; break;
                case "SENS_EXCH_COEFF": _sens_exch_coeff = value; break;
                case "GW_EXCH_COEFF": _GW_exch_coeff = value; break;
                case "RIVERBED_CONDUCTIVITY": _bed_conductivity = value; break;
                case "RIVERBED_THICKNESS": _bed_thickness = value; break;
                case "RESERVOIR_DISABLED": _res_disabled = Convert.ToBoolean(value); break;
                case "CORR_REACH_LENGTH": _reach_length2 = value; break;
                case "LAKEBED_CONDUCTIVITY":
                    if (_pReservoir != null) _pReservoir.SetLakebedConductivity(value);
                    break;
                case "LAKEBED_THICKNESS":
                    if (_pReservoir != null) _pReservoir.SetLakebedThickness(value);
                    break;
                case "LAKE_CONVECT_COEFF":
                    if (_pReservoir != null) _pReservoir.SetLakeConvectionCoeff(value);
                    break;
                case "RESERVOIR_CREST_WIDTH":
                    if (_pReservoir != null) _pReservoir.SetCrestWidth(value);
                    break;
                default:
                    return false;
            }
            return true;
        }

        public double GetBasinProperties(string label)
        {
            var label_n = label.ToUpperInvariant();
            switch (label_n)
            {
                case "TIME_CONC": return _t_conc;
                case "TIME_TO_PEAK": return _t_peak;
                case "TIME_LAG": return _t_lag;
                case "RES_CONSTANT": return _reservoir_constant;
                case "NUM_RESERVOIRS": return (double)_num_reservoirs;
                case "GAMMA_SHAPE": return _gamma_shape;
                case "GAMMA_SCALE": return _gamma_scale;
                case "Q_REFERENCE": return _Q_ref;
                case "MANNINGS_N": return _mannings_n;
                case "SLOPE": return _slope;
                case "DIFFUSIVITY": return _diffusivity;
                case "CELERITY": return _c_ref;
                case "RAIN_CORR": return _rain_corr;
                case "SNOW_CORR": return _snow_corr;
                case "TEMP_CORR": return _temperature_corr;
                case "REACH_HRU_ID": return (double)_reach_HRUindex;
                case "HYPORHEIC_FLUX": return _hyporheic_flux;
                case "CONVECT_COEFF": return _convect_coeff;
                case "SENS_EXCH_COEFF": return _sens_exch_coeff;
                case "GW_EXCH_COEFF": return _GW_exch_coeff;
                case "RESERVOIR_DISABLED": return _res_disabled ? 1.0 : 0.0;
                case "CORR_REACH_LENGTH": return _reach_length2;
                case "RESERVOIR_CREST_WIDTH":
                    if (_pReservoir != null) return _pReservoir.GetCrestWidth();
                    return 0.0;
                default:
                    return Constants.INDEX_NOT_FOUND;
            }
        }

        public void SetAsNonHeadwater() => _is_headwater = false;

        public void AddInflowHydrograph(TimeSeries pInflow)
        {
            if (_pInflowHydro != null && Globals.g_current_e == Constants.DOESNT_EXIST)
                Utils.ExitGracefully("CSubBasin::AddInflowHydrograph: only one inflow hydrograph may be specified per basin", Constants.BAD_DATA);
            _pInflowHydro?.DisposeIfNeeded();
            _pInflowHydro = pInflow;
        }

        public void AddDownstreamInflow(TimeSeries pInflow)
        {
            if (_pInflowHydro2 != null && Globals.g_current_e == Constants.DOESNT_EXIST)
                Utils.ExitGracefully("CSubBasin::AddDownstreamInflow: only one inflow hydrograph may be specified per basin", Constants.BAD_DATA);
            _pInflowHydro?.DisposeIfNeeded();
            _pInflowHydro2 = pInflow;
        }

        public void AddWaterDemand(Demand pDemand)
        {
            if (!Utils.DynArrayAppend(ref _pWaterDemands, pDemand, ref _nWaterDemands))
                Utils.ExitGracefully("CSubBasin::AddIrrigationDemand: trying to add NULL regime", Constants.BAD_DATA);
        }

        public void AddEnviroMinFlow(TimeSeries pMinFlow)
        {
            if (_pEnviroMinFlow != null) Utils.ExitGracefully("CSubBasin::AddEnviroMinFlow: only one environmental minimum flow time series may be specified per basin", Constants.BAD_DATA);
            _pEnviroMinFlow = pMinFlow;
        }

        public void SetChannelStorage(double V) => _channel_storage = V;
        public void SetRivuletStorage(double V) => _rivulet_storage = V;

        public void SetQoutArray(int N, double[] aQo, double QoLast)
        {
            if (N != _nSegments)
            {
                string warn = $"Number of reach segments in state file and input file are inconsistent in basin {_ID}. Unable to read in-reach flow initial conditions";
                Utils.WriteWarning(warn, false);
            }
            else
            {
                for (int i = 0; i < _nSegments; i++) _aQout[i] = aQo[i];
                _QoutLast = QoLast;
            }
        }

        public void SetQout(double Q)
        {
            for (int i = 0; i < _nSegments; i++) _aQout[i] = Q;
            _QoutLast = Q;
        }

        public void SetQlatHist(int N, double[] aQl, double QlLast)
        {
            if (N != _nQlatHist)
                Utils.WriteWarning("CSubBasin::SetQlatHist: size of lateral flow history differs between current model and initial conditions file. Array will be truncated", false);
            if (N == 0) return;
            int len = Math.Min(_nQlatHist, N);
            for (int i = 0; i < len; i++) _aQlatHist[i] = aQl[i];
            _QlatLast = QlLast;
        }

        public void SetQinHist(int N, double[] aQi)
        {
            if (N != _nQinHist) Utils.WriteWarning("CSubBasin::SetQinHist: size of inflow history differs between current model and initial conditions file. Array will be truncated", false);
            if (N == 0) return;
            int len = Math.Min(_nQinHist, N);
            for (int i = 0; i < len; i++) _aQinHist[i] = aQi[i];
        }

        public void UpdateInflow(double Qin)
        {
            for (int n = _nQinHist - 1; n > 0; n--) _aQinHist[n] = _aQinHist[n - 1];
            _aQinHist[0] = Qin;
        }

        public void UpdateLateralInflow(double Qlat)
        {
            for (int n = _nQlatHist - 1; n > 0; n--) _aQlatHist[n] = _aQlatHist[n - 1];
            _aQlatHist[0] = Qlat;
        }

        public void SetUnusableFlowPercentage(double val)
        {
            if (val < 0 || val > 1.0)
                Utils.ExitGracefully("CSubBasin:SetUnusableFlowPercentage: invalid value for :UnusableFlowPercentage (must be between zero and one).", Constants.BAD_DATA_WARN);
            _unusable_flow_pct = val;
        }

        public double ScaleAllFlows(double scale, bool overriding, double tstep, double t)
        {
            double va = 0.0;
            double sf = (scale - 1.0) / scale;

            if (!overriding)
            {
                for (int n = 0; n < _nQlatHist; n++)
                {
                    _aQlatHist[n] *= scale;
                    Utils.UpperSwap(ref _aQlatHist[n], 0.0);
                    va += _aQlatHist[n] * sf * tstep * Constants.SEC_PER_DAY;
                }
                for (int n = 0; n < _nQinHist; n++)
                {
                    _aQinHist[n] *= scale;
                    Utils.UpperSwap(ref _aQinHist[n], 0.0);
                    va += _aQinHist[n] * sf * tstep * Constants.SEC_PER_DAY;
                }
                for (int i = 0; i < _nSegments; i++)
                {
                    _aQout[i] *= scale;
                    Utils.UpperSwap(ref _aQout[i], 0.0);
                    // careful accessing i+1 in original; guard to original semantics if necessary
                    double next = (i + 1 < _aQout.Length) ? _aQout[i + 1] : _aQout[i];
                    va += 0.5 * (_aQout[i] + next) * sf * tstep * Constants.SEC_PER_DAY;
                }
            }

            if (overriding && (_pReservoir == null))
            {
                for (int i = 0; i < _nSegments; i++)
                {
                    _aQout[i] *= scale;
                    Utils.UpperSwap(ref _aQout[i], 0.0);
                    double next = (i + 1 < _aQout.Length) ? _aQout[i + 1] : _aQout[i];
                    va += 0.5 * (_aQout[i] + next) * sf * tstep * Constants.SEC_PER_DAY;
                }
            }

            if (_pReservoir != null) va += _pReservoir.ScaleFlow(scale, overriding, tstep, t);

            _channel_storage *= scale; va += _channel_storage * sf;
            _rivulet_storage *= scale; va += _rivulet_storage * sf;
            return va;
        }

        public double AdjustAllFlows(double adjust, bool overriding, double tstep, double t)
        {
            double va = 0.0;

            if (!overriding)
            {
                for (int n = 0; n < _nQinHist; n++)
                {
                    _aQinHist[n] += adjust;
                    Utils.UpperSwap(ref _aQinHist[n], 0.0);
                    va += adjust * tstep * Constants.SEC_PER_DAY;
                }
                for (int i = 0; i < _nSegments; i++)
                {
                    _aQout[i] += adjust;
                    Utils.UpperSwap(ref _aQout[i], 0.0);
                    va += adjust * tstep * Constants.SEC_PER_DAY;
                }
            }

            if (overriding && (_pReservoir == null))
            {
                for (int i = 0; i < _nSegments; i++)
                {
                    _aQout[i] += adjust;
                    Utils.UpperSwap(ref _aQout[i], 0.0);
                    va += adjust * tstep * Constants.SEC_PER_DAY;
                }
            }

            // reservoir scaling not used in original AdjustAllFlows

            return va;
        }

        public void SetDownstreamID(long down_SBID) => _downstream_ID = down_SBID;

        public void SetDownstreamBasin(SubBasin pSB)
        {
            _pDownSB = pSB;
            if (_pReservoir != null) _pReservoir.SetDownstreamBasin(pSB);
        }

        public void AddToDeliveredDemand(int ii, double Qdel)
        {
#if STRICT_CHECK
        if (ii < 0 || ii >= _nWaterDemands) throw new IndexOutOfRangeException("CSubBasin::AddToDeliveredDemand: invalid demand index");
#endif
            _aQdelivered[ii] = Qdel;
            _Qdelivered += Qdel;
        }

        public void UpdateDemands(OptStruct Options, TimeStruct tt)
        {
            for (int ii = 0; ii < _nWaterDemands; ii++) _pWaterDemands[ii].UpdateDemand(Options, tt);
            _pReservoir?.UpdateDemands(Options, tt);
        }

        public void AddToReturnFlow(double Qret) => _Qreturn += Qret;

        public void RecordReturnFlow(int ii, double Qret)
        {
#if STRICT_CHECK
        if (ii < 0 || ii >= _nWaterDemands) throw new IndexOutOfRangeException("CSubBasin::RecordReturnFlow: invalid demand index");
#endif
            _aQreturned[ii] = Qret;
        }

        public void SetGauged(bool isgauged) => _gauged = isgauged;

        public void Disable()
        {
            _disabled = true;
            for (int k = 0; k < _nHydroUnits; k++) _pHydroUnits[k].Disable();
        }

        public void Enable()
        {
            _disabled = false;
            for (int k = 0; k < _nHydroUnits; k++) _pHydroUnits[k].Enable();
        }

        public void IncludeInAssimilation() => _assimilate = true;

        public double CalculateBasinArea()
        {
            _basin_area = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].GetArea() <= 0.0)
                    Utils.ExitGracefully("CSubBasin::CalculateBasinArea: one or more HRUs has a negative or zero area", Constants.BAD_DATA);
                if (_pHydroUnits[k].IsEnabled()) _basin_area += _pHydroUnits[k].GetArea();
            }
            if (_basin_area < 0.0) Utils.ExitGracefully("CSubBasin::CalculateBasinArea: negative subbasin area!", Constants.BAD_DATA);
            return _basin_area;
        }

        public void Initialize(double Qin_avg, double Qlat_avg, double total_drain_area, OptStruct Options)
        {
            string warn;
            if ((_nHydroUnits == 0) && (!_is_conduit))
            {
                warn = $"CSubBasin::Initialize: subbasin {_ID} has no constituent HRUs and therefore zero area";
                Utils.ExitGracefully(warn, Constants.BAD_DATA_WARN);
            }
            if ((_nHydroUnits > 0) && (_is_conduit))
            {
                warn = $"CSubBasin::Initialize: conduit {_ID} has constituent HRUs. HRUs should not be linked to conduits";
                Utils.ExitGracefully(warn, Constants.BAD_DATA_WARN);
            }
            if ((_pChannel == null) && (Options.routing != RoutingMethod.ROUTE_NONE) && (Options.routing != RoutingMethod.ROUTE_EXTERNAL))
            {
                warn = $"CSubBasin::Initialize: channel profile for basin {_ID} may only be 'NONE' if Routing=ROUTE_NONE or ROUTE_EXTERNAL";
                Utils.ExitGracefully(warn, Constants.BAD_DATA);
            }
            if (_pInflowHydro != null) _is_headwater = false;

            _drainage_area = total_drain_area;

            if (!_disabled)
            {
                if (_Q_ref == Constants.AUTO_COMPUTE)
                {
                    if ((Qin_avg + Qlat_avg <= 0) && (!_is_headwater) && (!_disabled))
                    {
                        warn = $"CSubBasin::Initialize: negative or zero average flow specified in initialization (basin {_ID})";
                        Utils.ExitGracefully(warn, Constants.BAD_DATA);
                    }
                    double mult = _pModel.GetGlobalParams().GetParams().reference_flow_mult;
                    ResetReferenceFlow(mult * (Qin_avg + Qlat_avg));
                }
                else
                {
                    ResetReferenceFlow(_Q_ref);
                }

                _pChannel?.CheckReferenceFlow(_Q_ref, _slope, _mannings_n, _ID);

                if (_reach_length == Constants.AUTO_COMPUTE)
                {
                    _reach_length = Math.Pow(_basin_area, 0.67) * Constants.M_PER_KM;
                }

                if (_t_conc == Constants.AUTO_COMPUTE)
                {
                    _t_conc = 0.76 * Math.Pow(Math.Max(_basin_area, 0.001), 0.38) / Constants.HR_PER_DAY;
                    _t_conc *= _pModel.GetGlobalParams().GetParams().TOC_multiplier;
                }
                if (Options.catchment_routing == RoutingMethod.ROUTE_GAMMA_CONVOLUTION) _t_peak = Constants.AUTO_COMPUTE;
                if (Options.catchment_routing == RoutingMethod.ROUTE_DUMP) _t_peak = Constants.AUTO_COMPUTE;

                if (_t_peak == Constants.AUTO_COMPUTE)
                {
                    _t_peak = 0.3 * _t_conc;
                    _t_peak *= _pModel.GetGlobalParams().GetParams().TIME_TO_PEAK_multiplier;
                }
                if (_t_lag == Constants.AUTO_COMPUTE) _t_lag = 0.0;
                if (_gamma_shape == Constants.AUTO_COMPUTE)
                {
                    _gamma_shape = 3.0;
                    _gamma_shape *= _pModel.GetGlobalParams().GetParams().GAMMA_SHAPE_multiplier;
                }
                if (_gamma_scale == Constants.AUTO_COMPUTE)
                {
                    _gamma_scale = Math.Max((_gamma_shape - 1.0) / _t_peak, 0.01);
                    _gamma_scale *= _pModel.GetGlobalParams().GetParams().GAMMA_SCALE_multiplier;
                }

                if (_reservoir_constant == Constants.AUTO_COMPUTE)
                {
                    _reservoir_constant = -Math.Log(_t_conc / (1 + _t_conc));
                }

                Utils.ExitGracefullyIf(_t_conc < _t_peak, "CSubBasin::Initialize: time of concentration must be greater than time to peak", Constants.BAD_DATA);
                Utils.ExitGracefullyIf(_t_peak <= 0, "CSubBasin::Initialize: time to peak must be greater than zero", Constants.BAD_DATA);
                Utils.ExitGracefullyIf(_t_conc <= 0, "CSubBasin::Initialize: time of concentration must be greater than zero", Constants.BAD_DATA);
                Utils.ExitGracefullyIf(_gamma_shape <= 0, "CSubBasin::Initialize: gamma shape parameter must be greater than zero", Constants.BAD_DATA);
                Utils.ExitGracefullyIf(_gamma_scale <= 0, "CSubBasin::Initialize: gamma scale parameter must be greater than zero", Constants.BAD_DATA);

                _diffusivity = GetDiffusivity();

                GenerateCatchmentHydrograph(Qlat_avg, Options);
                GenerateRoutingHydrograph(Qin_avg, Options);
                InitializeFlowStates(Qin_avg, Qlat_avg, Options);
            }

            if (_pReservoir != null) _pReservoir.Initialize(Options);
            if (_pInflowHydro != null) _pInflowHydro.Initialize(Options.julian_start_day, Options.julian_start_year, Options.duration, Options.timestep, false, Options.calendar);
            if (_pInflowHydro2 != null) _pInflowHydro2.Initialize(Options.julian_start_day, Options.julian_start_year, Options.duration, Options.timestep, false, Options.calendar);
            if (_pEnviroMinFlow != null) _pEnviroMinFlow.Initialize(Options.julian_start_day, Options.julian_start_year, Options.duration, Options.timestep, false, Options.calendar);

            if ((Options.routing == RoutingMethod.ROUTE_MUSKINGUM) || (Options.routing == RoutingMethod.ROUTE_MUSKINGUM_CUNGE))
            {
                double dx = _reach_length / (double)_nSegments;
                double K = GetMuskingumK(dx);
                double X = GetMuskingumX(dx);
                if ((Options.timestep < 2 * K * X) || (Options.timestep > 2 * K * (1 - X)))
                {
                    string w;
                    if (Options.timestep < 2 * K * X)
                        w = $"CSubBasin::Initialize: inappropriate global time step for Muskingum routing in subbasin {_name} timestep too small, must decrease size of reach segments";
                    else
                        w = $"CSubBasin::Initialize: inappropriate global time step for Muskingum routing in subbasin {_name}: local timestepping will be used";
                    Utils.WriteWarning(w, Options.noisy);
                    if (Options.noisy)
                    {
                        Console.WriteLine(w);
                        Console.WriteLine($"   For Muskingum stability, the following condition should hold:");
                        Console.WriteLine($"   2KX < dt < 2K(1-X): {2 * K * X} < {Options.timestep} < {2 * K * (1 - X)}");
                        Console.WriteLine($"   where K={K} X={X} dt={Options.timestep}");
                    }
                }
            }
        }

        public void InitializePostRVM(OptStruct Options)
        {
            if (_nWaterDemands > 0)
            {
                _aQdelivered = new double[_nWaterDemands];
                _aQreturned = new double[_nWaterDemands];
                for (int ii = 0; ii < _nWaterDemands; ii++)
                {
                    _pWaterDemands[ii].Initialize(Options);
                    _aQdelivered[ii] = 0.0;
                    _aQreturned[ii] = 0.0;
                }
            }
            _pReservoir?.InitializePostRVM(Options);
        }

        public void InitializeFlowStates(double Qin_avg, double Qlat_avg, OptStruct Options)
        {
            if (!_disabled)
            {
                for (int seg = 0; seg < _nSegments; seg++)
                {
                    _aQout[seg] = Qin_avg + Qlat_avg * (double)(seg + 1) / (double)(_nSegments);
                }
                _QoutLast = _aQout[_nSegments - 1];
                _QlatLast = Qlat_avg;

                _channel_storage = 0.0;
                if ((Options.routing != RoutingMethod.ROUTE_NONE) && (Options.routing != RoutingMethod.ROUTE_EXTERNAL))
                {
                    for (int seg = 0; seg < _nSegments; seg++)
                    {
                        _channel_storage += _pChannel.GetArea(_aQout[seg], _slope, _mannings_n) * (_reach_length / _nSegments);
                    }
                }

                double sum = 0.0;
                for (int n = 0; n < _nQlatHist; n++) sum += (n + 1) * _aUnitHydro[n];
                _rivulet_storage = sum * Qlat_avg * (Options.timestep * Constants.SEC_PER_DAY);
            }
        }

        public void ResetReferenceFlow(double Qreference)
        {
            _Q_ref = Qreference;
            if ((_Q_ref != Constants.AUTO_COMPUTE) && (_pChannel != null))
            {
                if ((_Q_ref <= 0.0) && (!_is_headwater))
                {
                    Console.WriteLine("_Q_ref=" + _Q_ref);
                    Utils.ExitGracefully("CSubBasin::ResetReferenceFlow: invalid (negative or zero) reference flow rate in non-headwater basin", Constants.BAD_DATA);
                }
                if (_c_ref == Constants.AUTO_COMPUTE)
                {
                    _c_ref = _pChannel.GetCelerity(_Q_ref, _slope, _mannings_n);
                    if (_c_ref <= 0.0) Utils.ExitGracefully("CSubBasin::ResetReferenceFlow: negative or zero celerity", Constants.RUNTIME_ERR);
                }
                _w_ref = _pChannel.GetTopWidth(_Q_ref, _slope, _mannings_n);
            }
            else
            {
                _c_ref = Constants.AUTO_COMPUTE;
                _w_ref = Constants.AUTO_COMPUTE;
            }
        }

        public void GenerateRoutingHydrograph(double Qin_avg, OptStruct Options)
        {
            double tstep = Options.timestep;
            double travel_time = _reach_length / _c_ref / Constants.SEC_PER_DAY;

            if (Options.routing == RoutingMethod.ROUTE_PLUG_FLOW)
                _nQinHist = (int)Math.Ceiling(travel_time / tstep) + 2;
            else if (Options.routing == RoutingMethod.ROUTE_DIFFUSIVE_WAVE)
                _nQinHist = (int)Math.Ceiling(2 * travel_time / tstep) + 2;
            else if (Options.routing == RoutingMethod.ROUTE_DIFFUSIVE_VARY)
                _nQinHist = (int)Math.Ceiling(2.5 * travel_time / tstep) + 2;
            else if ((Options.routing == RoutingMethod.ROUTE_HYDROLOGIC) || (Options.routing == RoutingMethod.ROUTE_TVD))
                _nQinHist = 2;
            else
                _nQinHist = 20;

            _aQinHist = new double[_nQinHist + 1];
            for (int n = 0; n < _nQinHist; n++) _aQinHist[n] = Qin_avg;

            _aRouteHydro = new double[_nQinHist + 1];
            for (int n = 0; n < _nQinHist; n++) _aRouteHydro[n] = 0.0;

            if (Options.routing == RoutingMethod.ROUTE_PLUG_FLOW)
            {
                for (int n = 0; n < _nQinHist - 1; n++)
                {
                    double ts = (travel_time - n * tstep) / tstep;
                    if (ts >= 0.0 && ts < 1.0)
                    {
                        _aRouteHydro[n] = 1 - ts;
                        _aRouteHydro[n + 1] = ts;
                    }
                }
            }
            else if (Options.routing == RoutingMethod.ROUTE_DIFFUSIVE_WAVE)
            {
                Utils.ExitGracefullyIf(_nSegments > 1, "ROUTE_DIFFUSIVE_WAVE only valid for single-segment rivers", Constants.BAD_DATA);
                double sum = 0.0;
                double cc = _c_ref * Constants.SEC_PER_DAY;
                double diffusivity = _diffusivity * Constants.SEC_PER_DAY;
                for (int n = 0; n < _nQinHist; n++)
                {
                    _aRouteHydro[n] = Math.Max(Utils.ADRCumDist(n * tstep, _reach_length, cc, diffusivity) - sum, 0.0);
                    sum += _aRouteHydro[n];
                }
                _aRouteHydro[_nQinHist - 1] = 0.0;
                if (travel_time < tstep)
                {
                    _aRouteHydro[0] = 1.0 - travel_time / tstep;
                    _aRouteHydro[1] = travel_time / tstep;
                    for (int n = 2; n < _nQinHist; n++) _aRouteHydro[n] = 0.0;
                }
            }
            else if (Options.routing == RoutingMethod.ROUTE_DIFFUSIVE_VARY)
            {
                for (int n = 0; n < _nQinHist; n++) _aRouteHydro[n] = 0.0;
                _aRouteHydro[0] = 1.0;
                double cc = _c_ref * Constants.SEC_PER_DAY;
                _c_hist = new double[_nQinHist];
                for (int n = 0; n < _nQinHist; n++) _c_hist[n] = cc;
            }
            else
            {
                for (int n = 0; n < _nQinHist; n++) _aRouteHydro[n] = 0.0;
                _aRouteHydro[0] = 1.0;
            }

            double total = 0.0;
            for (int n = 0; n < _nQinHist; n++) total += _aRouteHydro[n];
            if (total < 0.2)
            {
                Console.WriteLine("diff: " + _pChannel.GetDiffusivity(_Q_ref, _slope, _mannings_n) + " cel " + _c_ref);
                Console.Write("---");
                for (int n = 0; n < _nQinHist; n++) Console.Write($"{_aRouteHydro[n]} ");
                Console.WriteLine(" SUM: " + total);
                Utils.ExitGracefully($"CSubBasin::GenerateRoutingHydrograph: bad routing hydrograph constructed in subbasin {_ID}", Constants.RUNTIME_ERR);
            }
            for (int n = 0; n < _nQinHist; n++) _aRouteHydro[n] /= total;
        }

        public void GenerateCatchmentHydrograph(double Qlat_avg, OptStruct Options)
        {
            double tstep = Options.timestep;
            int OldnQlatHist = _nQlatHist;

            if (Options.catchment_routing == RoutingMethod.ROUTE_TRI_CONVOLUTION)
                _nQlatHist = (int)Math.Ceiling((_t_conc) / tstep) + 3;
            else if (Options.catchment_routing == RoutingMethod.ROUTE_GAMMA_CONVOLUTION)
                _nQlatHist = (int)Math.Ceiling(4.5 * Math.Pow(_gamma_shape, 0.6) / _gamma_scale / tstep) + 1;
            else if (Options.catchment_routing == RoutingMethod.ROUTE_DELAYED_FIRST_ORDER)
                _nQlatHist = 2;
            else if (Options.catchment_routing == RoutingMethod.ROUTE_DUMP)
                _nQlatHist = 3;
            else if (Options.catchment_routing == RoutingMethod.ROUTE_RESERVOIR_SERIES)
                _nQlatHist = (int)Math.Ceiling((4.0 / _reservoir_constant) / tstep) * _num_reservoirs + 2;

            _nQlatHist += (int)Math.Ceiling(_t_lag / tstep);

            if (_nQlatHist <= 0) Utils.ExitGracefully($"GenerateCatchmentHydrograph: negative or zero inflow history. Something is wrong with catchment routing parameters in basin {_ID}", Constants.RUNTIME_ERR);

            _aQlatHist = new double[_nQlatHist];
            for (int n = 0; n < _nQlatHist; n++) _aQlatHist[n] = Qlat_avg;

            _aUnitHydro = new double[_nQlatHist];
            for (int n = 0; n < _nQlatHist; n++) _aUnitHydro[n] = 0.0;

            double sum;

            if (Options.catchment_routing == RoutingMethod.ROUTE_GAMMA_CONVOLUTION)
            {
                sum = 0;
                double alpha = _gamma_shape;
                double beta = _gamma_scale;
                for (int n = 0; n < _nQlatHist; n++)
                {
                    double t = n * tstep - _t_lag;
                    _aUnitHydro[n] = Utils.GammaCumDist(t + tstep, alpha, beta) - sum;
                    Utils.ExitGracefullyIf(_aUnitHydro[n] > Constants.ALMOST_INF, "GenerateCatchmentHydrograph: issues with gamma distribution. Time to peak may be too small relative to timestep", Constants.RUNTIME_ERR);
                    sum += _aUnitHydro[n];
                }
                _aUnitHydro[_nQlatHist - 1] = 0.0;
            }
            else if (Options.catchment_routing == RoutingMethod.ROUTE_TRI_CONVOLUTION)
            {
                sum = 0.0;
                for (int n = 0; n < _nQlatHist; n++)
                {
                    double t = n * tstep - _t_lag;
                    _aUnitHydro[n] = Utils.TriCumDist(t + tstep, _t_conc, _t_peak) - sum;
                    sum += _aUnitHydro[n];
                }
            }
            else if (Options.catchment_routing == RoutingMethod.ROUTE_RESERVOIR_SERIES)
            {
                sum = 0.0;
                for (int n = 0; n < _nQlatHist; n++)
                {
                    double t = n * tstep - _t_lag;
                    _aUnitHydro[n] = Utils.NashCumDist(t + tstep, _reservoir_constant, _num_reservoirs) - sum;
                    sum += _aUnitHydro[n];
                }
            }
            else if (Options.catchment_routing == RoutingMethod.ROUTE_DUMP)
            {
                for (int n = 0; n < _nQlatHist; n++) _aUnitHydro[n] = 0.0;
                _aUnitHydro[0] = 1.0;
            }

            sum = 0.0;
            for (int n = 0; n < _nQlatHist; n++) sum += _aUnitHydro[n];
            Utils.ExitGracefullyIf(sum == 0.0, "CSubBasin::GenerateCatchmentHydrograph: bad unit hydrograph constructed", Constants.RUNTIME_ERR);
            if (Math.Abs(sum - 1.0) > 0.05) Utils.WriteWarning("CSubBasin::GenerateCatchmentHydrograph: unit hydrograph truncated", Options.noisy);
            for (int n = 0; n < _nQlatHist; n++) _aUnitHydro[n] /= sum;
        }

        public void UpdateSubBasin(TimeStruct tt, OptStruct Options)
        {
            _Qdelivered = 0;
            for (int ii = 0; ii < _nWaterDemands; ii++)
            {
                _aQdelivered[ii] = 0.0;
                _aQreturned[ii] = 0.0;
            }
            _Qreturn = 0;
            if (Options.routing == RoutingMethod.ROUTE_DIFFUSIVE_VARY) UpdateRoutingHydro(Options.timestep);
            _pReservoir?.UpdateReservoir(tt, Options);
        }

        public void UpdateOutflows(double[] aQo, double irr_Q, double Qdiv, double res_ht, double res_outflow,
                                   ResConstraint constraint, double[] res_Qstruct, OptStruct Options, TimeStruct tt, bool initialize)
        {
            double tstep = Options.timestep;
            _QoutLast = _aQout[_nSegments - 1];
            for (int seg = 0; seg < _nSegments; seg++) _aQout[seg] = aQo[seg];

            double irrQ_act = Math.Min(irr_Q, _aQout[_nSegments - 1]);
            _aQout[_nSegments - 1] -= irrQ_act;

            double divQ_act = Math.Min(Qdiv, _aQout[_nSegments - 1]);
            _aQout[_nSegments - 1] -= divQ_act;

            _QdivLast = _Qdiverted;
            _Qdiverted = divQ_act;
            _QirrLast = _Qirr;
            _Qirr = irrQ_act;

            if (!Options.management_optimization)
            {
                double total = GetTotalWaterDemand();
                for (int ii = 0; ii < _nWaterDemands; ii++)
                {
                    double demand = _pWaterDemands[ii].GetDemand();
                    _aQdelivered[ii] = _Qirr * (demand / total);
                    _aQreturned[ii] = 0.0;
                }
            }

            if (_pReservoir != null)
            {
                _pReservoir.UpdateStage(res_ht, res_outflow, constraint, res_Qstruct, Options, tt);
                _pReservoir.UpdateMassBalance(tt, Options.timestep, Options);
            }

            if (initialize) return;

            double dt = tstep * Constants.SEC_PER_DAY;
            double dV = 0.0;
            double Qlat_new = 0.0;
            for (int n = 0; n < _nQlatHist; n++) Qlat_new += _aUnitHydro[n] * _aQlatHist[n];
            _QlocLast = _Qlocal;
            _Qlocal = Qlat_new;

            dV += 0.5 * (_aQinHist[0] + _aQinHist[1]) * dt;
            dV -= 0.5 * (_aQout[_nSegments - 1] + _QoutLast) * dt;
            dV += 0.5 * (Qlat_new + _QlatLast) * dt;
            dV -= 0.5 * (_Qirr + _QirrLast) * dt;
            dV -= 0.5 * (_Qdiverted + _QdivLast) * dt;

            _channel_storage += dV;

            dV = 0.0;
            dV += _aQlatHist[0] * dt;
            dV -= 0.5 * (Qlat_new + _QlatLast) * dt;
            _rivulet_storage += dV;

            _QlatLast = Qlat_new;
        }

        public double GetMuskingumK(double dx) => dx / (_c_ref * Constants.SEC_PER_DAY);

        public double GetMuskingumX(double dx)
        {
            Utils.ExitGracefullyIf(_pChannel == null, "CSubBasin::GetMuskingumX", Constants.BAD_DATA);
            double bedslope = _slope;
            if (_slope == Constants.AUTO_COMPUTE) bedslope = _pChannel.GetBedslope();
            return Math.Max(0.0, 0.5 * (1.0 - _Q_ref / bedslope / _w_ref / _c_ref / dx));
        }

        public double GetReachSegVolume(double Qin, double Qout, double dx)
        {
            double bedslope = _slope;
            if (_slope == Constants.AUTO_COMPUTE) bedslope = _pChannel.GetBedslope();

            double c_in = _pChannel.GetCelerity(Qin, _slope, _mannings_n);
            double w_in = _pChannel.GetTopWidth(Qin, _slope, _mannings_n);
            double c_out = _pChannel.GetCelerity(Qout, _slope, _mannings_n);
            double w_out = _pChannel.GetTopWidth(Qout, _slope, _mannings_n);

            double Kin = dx / (c_in * Constants.SEC_PER_DAY);
            double Kout = dx / (c_out * Constants.SEC_PER_DAY);
            double Xin = Math.Max(0.0, 0.5 * (1.0 - Qin / bedslope / w_in / c_in / dx));
            double Xout = Math.Max(0.0, 0.5 * (1.0 - Qout / bedslope / w_out / c_out / dx));

            return (Kin * Xin * Qin + Kout * (1 - Xout) * Qout) * Constants.SEC_PER_DAY;
        }

        public double thQ(double In_old, double In_new, double Out_old, double Out_new, double th_in, double dx, double tstep)
        {
            if (Math.Abs(Out_old - Out_new) < Constants.REAL_SMALL) return 0.5;
            double thQ = (GetReachSegVolume(In_new, Out_new, dx) - GetReachSegVolume(In_old, Out_old, dx)) / tstep / Constants.SEC_PER_DAY / (Out_old - Out_new);
            thQ += (-(1.0 - th_in) * In_old - (th_in) * In_new + Out_old) / (Out_old - Out_new);
            return thQ;
        }

        public double TVDTheta(double In_old, double In_new, double Out_old, double Out_new, double th_in, double dx, double tstep)
        {
            double th;
            if (In_new > Out_old)
            {
                th = thQ(In_old, In_new, Out_old, Math.Min(In_new, In_old), th_in, dx, tstep);
                return Math.Min(1.0, Math.Max(0.5, th));
            }
            else if (In_new < Out_old)
            {
                th = thQ(In_old, In_new, Out_old, Math.Max(In_new, In_old), th_in, dx, tstep);
                return Math.Min(1.0, Math.Max(0.5, th));
            }
            return 0.5;
        }

        public void UpdateRoutingHydro(double tstep)
        {
            double Q = _aQinHist[0];
            double sum = 0, sumwt = 0, sum2 = 0;
            for (int n = 0; n < _nQinHist; n++)
            {
                sumwt += _aRouteHydro[n];
                sum += _aQinHist[n] * (1.0 - sumwt);
                sum2 += (1.0 - sumwt);
            }

            double cc = _pChannel.GetCelerity(Q, _slope, _mannings_n) * Constants.SEC_PER_DAY;
            double D_ref = _pChannel.GetDiffusivity(_Q_ref, _slope, _mannings_n) * Constants.SEC_PER_DAY;

            for (int n = _nQinHist; n > 0; n--) if (n < _c_hist.Length) _c_hist[n] = _c_hist[n - 1];
            _c_hist[0] = cc;

            sum = 0;
            double alpha = D_ref / 2;
            for (int n = 0; n < _nQinHist; n++)
            {
                _aRouteHydro[n] = Math.Max(Utils.TimeVaryingADRCumDist((n) * tstep, _reach_length, _c_hist, _nQinHist, alpha, tstep) - sum, 0.0);
                sum += _aRouteHydro[n];
            }
            for (int n = 0; n < _nQinHist; n++) _aRouteHydro[n] /= sum;

            double travel_time = _reach_length / _c_ref;
            if (travel_time < tstep)
            {
                _aRouteHydro[0] = 1.0 - travel_time / tstep;
                _aRouteHydro[1] = travel_time / tstep;
                for (int n = 2; n < _nQinHist; n++) _aRouteHydro[n] = 0.0;
            }
        }

        public void RouteWater(double[] aQout_new, OptStruct Options, TimeStruct tt)
        {
            int seg, n;
            double tstep = Options.timestep;
            double dx = _reach_length / (double)(_nSegments);
            double Qlat_new = 0.0;
            double seg_fraction = 1.0 / (double)(_nSegments);

            for (n = 0; n < _nQlatHist; n++) Qlat_new += _aUnitHydro[n] * _aQlatHist[n];

            var route_method = Options.routing;
            if ((_is_headwater) && (route_method != RoutingMethod.ROUTE_EXTERNAL)) route_method = RoutingMethod.ROUTE_NONE;

            if (route_method == RoutingMethod.ROUTE_MUSKINGUM || route_method == RoutingMethod.ROUTE_MUSKINGUM_CUNGE)
            {
                double K = GetMuskingumK(dx);
                double X = GetMuskingumX(dx);

                double dt = Math.Min(K, tstep);
                double Qin = 0, Qin_new = 0;
                double[] aQoutStored = new double[_nSegments];
                for (seg = 0; seg < _nSegments; seg++) aQoutStored[seg] = _aQout[seg];

                for (double t = 0; t < tstep; t += dt)
                {
                    if (dt > (tstep - t)) dt = tstep - t;
                    double cunge = 0;
                    if (route_method == RoutingMethod.ROUTE_MUSKINGUM_CUNGE) cunge = 1;

                    double denom = (2 * K * (1.0 - X) + dt);
                    double c1 = (dt - 2 * K * (X)) / denom;
                    double c2 = (dt + 2 * K * (X)) / denom;
                    double c3 = (-dt + 2 * K * (1 - X)) / denom;
                    double c4 = (dt) / denom;

                    Qin = _aQinHist[1] + ((t) / tstep) * (_aQinHist[0] - _aQinHist[1]);
                    Qin_new = _aQinHist[1] + ((t + dt) / tstep) * (_aQinHist[0] - _aQinHist[1]);

                    for (seg = 0; seg < _nSegments; seg++)
                    {
                        aQout_new[seg] = c1 * Qin_new + c2 * Qin + c3 * _aQout[seg] + cunge * c4 * (Qlat_new * seg_fraction);
                        Qin = _aQout[seg];
                        Qin_new = aQout_new[seg];
                        _aQout[seg] = aQout_new[seg];
                    }
                }
                for (seg = 0; seg < _nSegments; seg++) _aQout[seg] = aQoutStored[seg];
            }
            else if (route_method == RoutingMethod.ROUTE_STORAGECOEFF)
            {
                double Qin_new = _aQinHist[0];
                double Qin = _aQinHist[1];
                for (seg = 0; seg < _nSegments; seg++)
                {
                    double ttime = GetMuskingumK(dx) * seg_fraction;
                    double storage_coeff = Math.Min(1.0 / (ttime / tstep + 0.5), 1.0);
                    double c1 = storage_coeff / 2;
                    double c2 = storage_coeff / 2;
                    double c3 = (1.0 - storage_coeff);
                    double corr = 1.0;
                    aQout_new[seg] = c1 * Qin + c2 * Qin_new + c3 * (_aQout[seg] - corr * _Qlocal);
                    Qin = _aQout[seg];
                    Qin_new = aQout_new[seg];
                }
            }
            else if (route_method == RoutingMethod.ROUTE_HYDROLOGIC)
            {
                const double ROUTE_MAXITER = 20;
                const double ROUTE_TOLERANCE = 0.0001;
                double Qout_old = _aQout[_nSegments - 1] - _Qlocal;
                double Qin_new = _aQinHist[0];
                double Qin_old = _aQinHist[1];
                double V_old = _pChannel.GetArea(Qout_old, _slope, _mannings_n) * _reach_length;

                int iter = 0;
                double change = 0;
                double gamma = V_old + (Qin_old + Qin_new - Qout_old) / 2.0 * (tstep * Constants.SEC_PER_DAY);

                double dQ = 0.1;
                double f = 0, dfdQ = 0;
                double Q_guess = Qout_old;
                double relax = 1.0;

                do
                {
                    f = (_pChannel.GetArea(Q_guess, _slope, _mannings_n) * _reach_length + (Q_guess) / 2.0 * (tstep * Constants.SEC_PER_DAY));
                    dfdQ = (_pChannel.GetArea(Q_guess + dQ, _slope, _mannings_n) * _reach_length + (Q_guess + dQ) / 2.0 * (tstep * Constants.SEC_PER_DAY) - f) / dQ;
                    change = -(f - gamma) / dfdQ;
                    if (dfdQ == 0.0) change = 1e-7;
                    Q_guess += relax * change;
                    if (Q_guess < 0) { Q_guess = 0; change = 0.0; }
                    iter++;
                    if (iter > 3) relax = 0.9;
                    if (iter > 10) relax = 0.7;
                } while ((iter < ROUTE_MAXITER) && (Math.Abs(change) > ROUTE_TOLERANCE));

                aQout_new[_nSegments - 1] = Q_guess;
                if (Q_guess < 0) Console.WriteLine($"Negative flow in basin {_ID} Qoutold: {Qout_old} Qin: {Qin_new} {Qin_old}");
                if (iter == ROUTE_MAXITER)
                {
                    string warn = $"CSubBasin::RouteWater did not converge after {ROUTE_MAXITER} iterations for basin {_ID} flow: {Q_guess} stage: {_pChannel.GetStageElev(Q_guess, _slope, _mannings_n)}";
                    Utils.WriteWarning(warn, false);
                }
            }
            else if (route_method == RoutingMethod.ROUTE_TVD)
            {
                const double ROUTE_MAXITER = 20;
                const double ROUTE_TOLERANCE = 0.0001;
                double Qout_old = _aQout[_nSegments - 1] - _Qlocal;
                double Qin_new = _aQinHist[0];
                double Qin_old = _aQinHist[1];

                int iter = 0;
                double change = 0;
                double f = 0, df = 0;
                double Q_guess = Qin_new;
                double relax = 1.0;
                double th_in = 0.5;
                double th_out = 0;
                double dxLocal = _reach_length;
                double dQ = 0.0001;
                do
                {
                    th_out = TVDTheta(Qin_old, Qin_new, Qout_old, Q_guess, th_in, dxLocal, tstep);
                    Console.WriteLine($"th_out: {th_out} {Qin_old} {Qin_new} {Qout_old} {Q_guess}");
                    f = (GetReachSegVolume(Qin_new, Q_guess, dxLocal) - GetReachSegVolume(Qin_old, Qout_old, dxLocal)) / (tstep * Constants.SEC_PER_DAY);
                    f -= (1.0 - th_in) * Qin_old + (th_in) * Qin_new;
                    f += (1.0 - th_out) * Qout_old + (th_out) * Q_guess;

                    th_out = TVDTheta(Qin_old, Qin_new, Qout_old, Q_guess + dQ, th_in, dxLocal, tstep);
                    df = (GetReachSegVolume(Qin_new, Q_guess + dQ, dxLocal) - GetReachSegVolume(Qin_old, Qout_old, dxLocal)) / (tstep * Constants.SEC_PER_DAY);
                    df -= (1.0 - th_in) * Qin_old + (th_in) * Qin_new;
                    df += (1.0 - th_out) * Qout_old + (th_out) * (Q_guess + dQ);
                    df -= f;

                    change = -f / (df / dQ);
                    if (df == 0.0) change = 1e-7;
                    Q_guess += relax * change;
                    Console.WriteLine($"Q_guess [{iter}]: {Q_guess} {f}");
                    if (Q_guess < 0) { Q_guess = Constants.REAL_SMALL; change = 0.0; }

                    iter++;
                    if (iter > 3) relax = 0.9;
                    if (iter > 10) relax = 0.7;
                } while ((iter < ROUTE_MAXITER) && (Math.Abs(change) > ROUTE_TOLERANCE));

                aQout_new[_nSegments - 1] = Q_guess;
                if (Q_guess < 0) Console.WriteLine($"Negative flow in basin {_ID} Qoutold: {Qout_old} Qin: {Qin_new} {Qin_old}");
                if (iter == ROUTE_MAXITER)
                {
                    string warn = $"CSubBasin::RouteWater:TVD did not converge after {ROUTE_MAXITER} iterations for basin {_ID} flow: {Q_guess} stage: {_pChannel.GetStageElev(Q_guess, _slope, _mannings_n)}";
                    Utils.WriteWarning(warn, false);
                }
            }
            else if (route_method == RoutingMethod.ROUTE_PLUG_FLOW || route_method == RoutingMethod.ROUTE_DIFFUSIVE_WAVE)
            {
                aQout_new[_nSegments - 1] = 0.0;
                for (n = 0; n < _nQinHist; n++) aQout_new[_nSegments - 1] += _aRouteHydro[n] * _aQinHist[n];
            }
            else if (route_method == RoutingMethod.ROUTE_DIFFUSIVE_VARY)
            {
                aQout_new[_nSegments - 1] = 0.0;
                for (n = 0; n < _nQinHist; n++) aQout_new[_nSegments - 1] += _aRouteHydro[n] * _aQinHist[n];
            }
            else if (route_method == RoutingMethod.ROUTE_EXTERNAL)
            {
                for (seg = 0; seg < _nSegments; seg++) aQout_new[seg] = 0.0;
                aQout_new[_nSegments - 1] = _aQout[_nSegments - 1];
            }
            else if (route_method == RoutingMethod.ROUTE_NONE)
            {
                for (seg = 0; seg < _nSegments; seg++) aQout_new[seg] = 0.0;
                aQout_new[_nSegments - 1] = _aQinHist[0];
            }
            else
            {
                Utils.ExitGracefully("Unrecognized routing method", Constants.STUB);
            }

            aQout_new[_nSegments - 1] += Qlat_new;
        }

        public void WriteToSolutionFile(StreamWriter RVC)
        {
            RVC.WriteLine(_name);
            RVC.WriteLine($"    :ChannelStorage, {_channel_storage}");
            RVC.WriteLine($"    :RivuletStorage, {_rivulet_storage}");
            RVC.Write($"    :Qout,{_nSegments}");
            for (int i = 0; i < _nSegments; i++)
            {
                RVC.Write($",{_aQout[i]}");
                if (i % 200 == 199) RVC.WriteLine("\n    ");
            }
            RVC.WriteLine($",{_QoutLast}");
            RVC.Write($"    :Qlat,{_nQlatHist}");
            for (int i = 0; i < _nQlatHist; i++)
            {
                RVC.Write($",{_aQlatHist[i]}");
                if (i % 200 == 199) RVC.WriteLine("\n    ");
            }
            RVC.WriteLine($",{_QlatLast}");
            RVC.Write($"    :Qin ,{_nQinHist}");
            for (int i = 0; i < _nQinHist; i++)
            {
                RVC.Write($",{_aQinHist[i]}");
                if (i % 200 == 199) RVC.WriteLine("\n    ");
            }
            RVC.WriteLine();
            _pReservoir?.WriteToSolutionFile(RVC);
        }

        public void ClearTimeSeriesData(OptStruct Options)
        {
            _pInflowHydro?.DisposeIfNeeded(); _pInflowHydro = null;
            _pInflowHydro2?.DisposeIfNeeded(); _pInflowHydro2 = null;
            _pEnviroMinFlow?.DisposeIfNeeded(); _pEnviroMinFlow = null;
            _pReservoir?.ClearTimeSeriesData(Options);
        }

        // --- Helper nested types for diversion etc. (kept minimal) ---
        private class Diversion
        {
            public int julian_end;
            public int julian_start;
            public double min_flow;
            public double percentage;
            public int target_p;
            public int nPoints;
            public double[] aQsource;
            public double[] aQdivert;
        }

    }

}
