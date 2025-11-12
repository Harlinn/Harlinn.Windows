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
        bool _disabled;
        /// <summary>
        /// p index in _pModel subbasin array
        /// </summary>
        int _global_p;

        Model _pModel;

        // basin properties


        /// <summary>
        /// contributing surface area for subbasin [km2]
        /// </summary>
        double _basin_area;
        /// <summary>
        /// total upstream drainage area [km2] (includes subbasin area)
        /// </summary>
        double _drainage_area;
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
        bool _is_headwater;
        /// <summary>
        /// true if basin is 'conduit' basin, and shouldn't have HRUs
        /// </summary>
        bool _is_conduit;
        /// <summary>
        /// true if observed data in this basin should be assimilated.
        /// </summary>
        bool _assimilate;
        /// <summary>
        /// downstream subbasin instance
        /// </summary>
        SubBasin _pDownSB;

        // catchment routing properties

        /// <summary>
        /// basin time of concentration [d]
        /// </summary>
        double _t_conc;
        /// <summary>
        /// basin time to peak [d] (<=_t_conc)
        /// </summary>
        double _t_peak;
        /// <summary>
        /// basin time lag [d]
        /// </summary>
        double _t_lag;
        /// <summary>
        /// linear basin/catchment routing constant [1/d]
        /// </summary>
        double _reservoir_constant;
        /// <summary>
        /// number of linear reservoirs used for in-catchment routing
        /// </summary>
        int _num_reservoirs;
        /// <summary>
        /// shape parameter of gamma unit hydrograph
        /// </summary>
        double _gamma_shape;
        /// <summary>
        /// scale parameter of gamma unit hydrograph
        /// </summary>
        double _gamma_scale;
        /// <summary>
        /// HRU *index* k (not ID) associated with reach. Used for reach-specific forcings.
        /// </summary>
        int _reach_HRUindex;
        /// <summary>
        /// in-catchment sensible exchange coefficient [1/d]
        /// </summary>
        double _sens_exch_coeff;
        /// <summary>
        /// in-catchment groundwater temperature exchange coefficient [1/d]
        /// </summary>
        double _GW_exch_coeff;

        /// <summary>
        /// gross exchange flux with groundwater [m/d]
        /// </summary>
        double _hyporheic_flux;
        /// <summary>
        /// convection coefficient [MJ/m2/d/K]
        /// </summary>
        double _convect_coeff;
        /// <summary>
        /// bed thermal conductivity [MJ/m/d/K]
        /// </summary>
        double _bed_conductivity;
        /// <summary>
        /// mean thickness of stream bed [m]
        /// </summary>
        double _bed_thickness;

        //River/stream  channel data:

        /// <summary>
        /// Main channel
        /// </summary>
        ChannelXSect _pChannel;

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
        double _c_ref;
        /// <summary>
        /// channel top width at reference flow rate [m]
        /// </summary>
        double _w_ref;
        /// <summary>
        /// manning's n for channel (or uses channel one, if =AUTO_COMPUTE)
        /// </summary>
        double _mannings_n;
        /// <summary>
        /// channel slope (rise over run) (or uses channel one, if =AUTO_COMPUTE)
        /// </summary>
        double _slope;
        /// <summary>
        /// channel diffusivity (specified or calculated, if =AUTO_COMPUTE) [m2/s]
        /// </summary>
        double _diffusivity;

        //Other params

        /// <summary>
        /// correction factor for rainfall [-]
        /// </summary>
        double _rain_corr;
        /// <summary>
        /// correction factor for snowfall [-]
        /// </summary>
        double _snow_corr;
        /// <summary>
        /// correction factor (additive) for temperature [-]
        /// </summary>
        double _temperature_corr;

        /// <summary>
        /// Number of river segments used in routing(>=1)
        /// </summary>
        int _nSegments;

        // Reservoir


        /// <summary>
        /// Reservoir object (or NULL, if no reservoir)
        /// </summary>
        Reservoir _pReservoir;
        /// <summary>
        /// true if lake or reservoir should be disabled/never created
        /// </summary>
        bool _res_disabled;
        /// <summary>
        /// corrected reach length [m] if reservoir/lake is disabled
        /// </summary>
        double _reach_length2;

        // state variables:

        /// <summary>
        /// downstream river (out)flow [m3/s] at start of time step at end of each channel segment [size=_nSegments]
        /// </summary>
        double[] _aQout;
        /// <summary>
        /// history of lateral runoff into surface water [m3/s][size:_nQlatHist] - uniform (time-averaged) over timesteps
        /// if Ql=Ql(t), aQlatHist[0]=Qlat(t to t+dt), aQlatHist[1]=Qlat(t-dt to t)...
        /// </summary>
        double[] _aQlatHist;

        /// <summary>
        /// size of _aQlatHist array
        /// </summary>
        int _nQlatHist;
        /// <summary>
        /// water storage in channel [m3]
        /// </summary>
        double _channel_storage;
        /// <summary>
        /// water storage in rivulets [m3]
        /// </summary>
        double _rivulet_storage;
        /// <summary>
        /// Qout from downstream channel segment [m3/s] at start of previous timestep- needed for reporting integrated outflow
        /// </summary>
        double _QoutLast;
        /// <summary>
        /// Qlat (after convolution) at start of previous timestep [m3/s]
        /// </summary>
        double _QlatLast;
        /// <summary>
        /// local contribution to current subbasin outflow [m3/s] (just from in-catchment routing)
        /// </summary>
        double _Qlocal;
        /// <summary>
        /// last local contribution [m3/s]
        /// </summary>
        double _QlocLast;

        /// <summary>
        /// Qirr (delivered water demand) at end of timestep [m3/s] (for MB accounting)
        /// </summary>
        double _Qirr;
        /// <summary>
        /// Qirr (delivered water demand) at start of timestep [m3/s] (for MB accounting)
        /// </summary>
        double _QirrLast;
        /// <summary>
        /// diverted flow at start of timestep [m3/s] (for MB accounting)
        /// </summary>
        double _QdivLast;
        /// <summary>
        /// diverted flow at end of timestep [m3/s] (for MB accounting)
        /// </summary>
        double _Qdiverted;
        /// <summary>
        /// delivered flow at end of time step if management optimization is used [m3/s]
        /// </summary>
        double _Qdelivered;
        /// <summary>
        /// delivered flow at end of time step for each water demand [m3/s] [size: _nIrrigDemands]
        /// </summary>
        double[] _aQdelivered;
        /// <summary>
        /// return flow associated with deliveries (may be redirected to other basin) [m3/s]
        /// </summary>
        double[] _aQreturned;
        /// <summary>
        /// return flow at end of time step if management optimization is used [m3/s] (may be sourced from other basin)
        /// </summary>
        double _Qreturn;

        // Hydrograph Memory
        /// <summary>
        /// history of inflow from upstream into primary channel [m3/s][size:nQinHist] (aQinHist[n] = Qin(t-ndt))
        ///   _aQinHist[0]=Qin(t), _aQinHist[1]=Qin(t-dt), _aQinHist[2]=Qin(t-2dt)...
        /// </summary>
        double[] _aQinHist;

        /// <summary>
        /// size of _aQinHist array
        /// </summary>
        int _nQinHist;
        /// <summary>
        /// reach celerity history [size: _nQinHist] (used for ROUTE_DIFFUSIVE_VARY only)
        /// </summary>
        double[] _c_hist;

        // characteristic weighted hydrographs

        /// <summary>
        /// [size:_nQlatHist] catchment unit hydrograph (time step-dependent). area under = 1.0.
        /// </summary>
        double[] _aUnitHydro;
        /// <summary>
        /// [size:_nQinHist ] routing unit hydrograph. area under = 1.0.
        /// </summary>
        double[] _aRouteHydro;

        // HRUs

        /// <summary>
        /// constituent HRUs with different hydrological characteristics
        /// </summary>
        int _nHydroUnits;

        /// <summary>
        /// [size:nHydroUnits] Array of pointers to constituent HRUs
        /// </summary>
        HydroUnit[] _pHydroUnits;

        // Treatment Plant/Irrigation/Other incoming hydrograph

        /// <summary>
        /// time series of inflows; NULL if no specified input - Inflow at upstream entrance of basin
        /// </summary>
        TimeSeries _pInflowHydro;
        /// <summary>
        /// time series of inflows/extractions ; at downstream end of basin reach
        /// </summary>
        TimeSeries _pInflowHydro2;
        /// <summary>
        /// time series of environmental minimum flow targets that force reduced irrigation demand (=0 by default)
        /// </summary>
        TimeSeries _pEnviroMinFlow;

        /// <summary>
        /// number of water demand objects
        /// </summary>
        int _nWaterDemands;
        /// <summary>
        /// array of demand objects; demand applied at downstream end of basin reach [size: _nIrrigDemand]
        /// </summary>
        Demand[] _pWaterDemands;

        /// <summary>
        /// number of flow diversions from basin
        /// </summary>
        int _nDiversions;
        /// <summary>
        /// array of pointers to flow diversion structures
        /// </summary>
        Diversion[] _pDiversions;
        /// <summary>
        /// for irrigation, fraction of flow above enviro min. flow that is not allowed to be used [0..1] (0 default)
        /// </summary>
        double _unusable_flow_pct;


    }

}
