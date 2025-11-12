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
    enum CurveFunction
    {
        CURVE_LINEAR,      ///< y =a*x
        CURVE_POWERLAW,    ///< y=a*x^b
        CURVE_DATA,        ///< y=interp(xi,yi)
        CURVE_VARYING,     ///< y=interp(xi,yi,t)
        CURVE_LAKE         ///< y=interp(xi,yi) (curve from weir)
    }

    /// <summary>
    /// Dynamically zoned target release model structure
    /// </summary>
    class DZTRmodel 
    {
        /// <summary>
        /// maximum channel capacity [m3/s]
        /// </summary>
        double Qmc;
        /// <summary>
        /// maximum reservoir storage [m3]
        /// </summary>
        double Vmax;
        /// <summary>
        /// critical release target [m3/s]
        /// </summary>
        double[] Qci = new double[12];
        /// <summary>
        /// normal release target [m3/s]
        /// </summary>
        double[] Qni = new double[12];
        /// <summary>
        /// maximum release target [m3/s]
        /// </summary>
        double[] Qmi = new double[12];
        /// <summary>
        /// critical release storage [m3]
        /// </summary>
        double[] Vci = new double[12];
        /// <summary>
        /// normal release storage [m3]
        /// </summary>
        double[] Vni = new double[12];
        /// <summary>
        /// critical release storage [m3]
        /// </summary>
        double[] Vmi = new double[12];
    }

    class DownDemand
    {
        /// <summary>
        /// subbasin of downstream demand location
        /// </summary>
        SubBasin pDownSB;
        /// <summary>
        /// percentage of demand met by reservoir
        /// </summary>
        double percent;
        /// <summary>
        /// julian start day for commencement of demand (beginning @ 0)
        /// </summary>
        int julian_start;
        /// <summary>
        /// julian end day of demand (wraps, such that if julian_end < julian_start, demand in winter)
        /// </summary>
        int julian_end;
    }


    public class Reservoir
    {
        /// <summary>
        /// reservoir name
        /// </summary>
        string _name;
        /// <summary>
        /// subbasin ID
        /// </summary>
        long _SBID;
        /// <summary>
        /// maximum reservoir capacity [m3]
        /// </summary>
        double _max_capacity;

        /// <summary>
        /// lakebed thickness [m]
        /// </summary>
        double _lakebed_thick;
        /// <summary>
        /// lakebed thermal conductivity [MJ/m/K/d]
        /// </summary>
        double _lakebed_cond;
        /// <summary>
        /// lake surface thermal convection coefficient [MJ/m2/d/K]
        /// </summary>
        double _lake_convcoeff;

        /// <summary>
        /// (potentially zero-area) HRU used for Precip/ET calculation (or NULL for no ET)
        /// </summary>
        HydroUnit _pHRU;

        /// <summary>
        /// number of reservoir demand time series
        /// </summary>
        int _nWaterDemands;
        /// <summary>
        /// array of pointers to demand objects [size:_nDemands]
        /// </summary>
        Demand[] _pWaterDemands;

        /// <summary>
        /// Time series of weir heights [m] (or NULL for fixed weir height)
        /// </summary>
        TimeSeries _pWeirHeightTS;
        /// <summary>
        /// Time series of rule curve upper stage constraint [m] (or NULL for no maximum stage)
        /// </summary>
        TimeSeries _pMaxStageTS;
        /// <summary>
        /// Time series of overrride flows [m3/s] (or NULL for no override)
        /// </summary>
        TimeSeries _pOverrideQ;
        /// <summary>
        /// Time series of minimum stage [m] (or NULL for no minimum)
        /// </summary>
        TimeSeries _pMinStageTS;
        /// <summary>
        /// Time series of flows when below minimum stage [m3/s] (or NULL for no minimum)
        /// </summary>
        TimeSeries _pMinStageFlowTS;
        /// <summary>
        /// Time series of target stage [m] (or NULL for no target)
        /// </summary>
        TimeSeries _pTargetStageTS;
        /// <summary>
        /// Time series maximum rate of flow increase [m3/s/d] (or NULL for no maximum)
        /// </summary>
        TimeSeries _pMaxQIncreaseTS;
        /// <summary>
        /// Time series maximum rate of flow decrease [m3/s/d] (or NULL for no maximum)
        /// </summary>
        TimeSeries _pMaxQDecreaseTS;
        /// <summary>
        /// Time series of drought line stage [m] (or NULL if none exists)
        /// </summary>
        TimeSeries _pDroughtLineTS;
        /// <summary>
        /// Time series of maximum flow constraint [m3/s] (or NULL for no maximum)
        /// </summary>
        TimeSeries _pQmaxTS;
        /// <summary>
        /// Time series of minimum flow constraint [m3/s] (or NULL for no minimum)
        /// </summary>
        TimeSeries _pQminTS;
        /// <summary>
        /// Time series of downstream flow soft target [m3/s] (or NULL for none)
        /// </summary>
        TimeSeries _pQdownTS;
        /// <summary>
        /// range of acceptable target flows from Qdown [m3/s] (or zero for hard target)
        /// </summary>
        double _QdownRange;

        /// <summary>
        /// proscribed outflow provided by management optimization routine [m3/s] (or RAV_BLANK_DATA for none)
        /// </summary>
        double _Qoptimized;

        /// <summary>
        /// downstream SubBasin for diversions (or NULL for none)
        /// </summary>
        SubBasin _pQdownSB;
        /// <summary>
        /// downstream subbasin
        /// </summary>
        SubBasin _pDownSB;

        /// <summary>
        /// array of downstream demand information used to determine Qmin [size:_nDemands]
        /// </summary>
        DownDemand[] _aDownDemands;
        /// <summary>
        /// size of downstream demand location array
        /// </summary>
        int _nDownDemands;

        /// <summary>
        /// DZTR model, if used (default=null)
        /// </summary>
        DZTRmodel _pDZTR;

        /// <summary>
        /// true if minimum stage dominates minflow/overrideflow constraints (false by default)
        /// </summary>
        bool _minStageDominant;
        /// <summary>
        /// reservoir demand multiplier that indicates percentage of requested downstream 
        /// irrigation demand satisfied from this reservoir.
        /// </summary>
        double _demand_mult;

        /// <summary>
        /// true if assimilating lake stage for this reservoir
        /// </summary>
        bool _assimilate_stage;
        /// <summary>
        /// observed lake stage
        /// </summary>
        TimeSeries _pObsStage;
        /// <summary>
        /// true if observed stage is blank this time step
        /// </summary>
        bool _assim_blank;

        /// <summary>
        /// outflow scale factor - used for reporting overriden flows
        /// </summary>
        double _DAscale;
        /// <summary>
        /// outflow scale factor for previous time step
        /// </summary>
        double _DAscale_last;

        /// <summary>
        /// number of time steps this reservoir dried out  during simulation
        /// </summary>
        int _dry_timesteps;

        // state variables :

        /// <summary>
        /// current stage [m] (actual state variable)
        /// </summary>
        double _stage;
        /// <summary>
        /// stage at beginning of current time step [m]
        /// </summary>
        double _stage_last;
        /// <summary>
        /// outflow corresponding to current stage [m3/s]
        /// </summary>
        double _Qout;
        /// <summary>
        /// outflow at beginning of current time step [m3/s]
        /// </summary>
        double _Qout_last;
        /// <summary>
        /// losses over current time step [m3]
        /// </summary>
        double _MB_losses;
        /// <summary>
        /// losses through AET only [m3]
        /// </summary>
        double _AET;
        /// <summary>
        /// gains through precipitation [m3]
        /// </summary>
        double _Precip;
        /// <summary>
        /// losses to GW only [m3] (negative for GW gains)
        /// </summary>
        double _GW_seepage;
        /// <summary>
        /// array of flows from control structures at end of time step [m3/s]
        /// </summary>
        double[] _aQstruct;
        /// <summary>
        /// array of flows from control structures at start of time step [m3/s]
        /// </summary>
        double[] _aQstruct_last;
        /// <summary>
        /// amount of water demand delivered for each demand [m3/s] (for management optimization)
        /// </summary>
        double[] _aQdelivered;
        /// <summary>
        /// amount of water returned for each demand [m3/s]
        /// </summary>
        double[] _aQreturned;

        /// <summary>
        /// current constraint type
        /// </summary>
        ResConstraint _constraint;

        // rating curve characteristics :

        /// <summary>
        /// reference elevation [m] (below which, no volume; flow can be zero)
        /// </summary>
        double _min_stage;
        /// <summary>
        /// maximum reference elevation [m]
        /// </summary>
        double _max_stage;

        /// <summary>
        /// absolute crest height, m.a.s.l (0 by default)
        /// </summary>
        double _crest_ht;
        /// <summary>
        ///          ///< crest width [m]
        /// </summary>
        double _crest_width;

        /// <summary>
        /// number of points on rating curves
        /// </summary>
        int _Np;
        /// <summary>
        /// Rating curve for stage elevation [m]
        /// </summary>
        double[] _aStage;
        /// <summary>
        /// Rating curve for overflow (e.g., weir) flow rates [m3/s]
        /// </summary>
        double[] _aQ;
        /// <summary>
        /// Rating curve for underflow/orifice flow (if specified; 0 by default) [m3/s]
        /// </summary>
        double[] _aQunder;
        /// <summary>
        /// Rating curve for surface area [m2]
        /// </summary>
        double[] _aArea;
        /// <summary>
        /// Rating curve for storage volume [m3]
        /// </summary>
        double[] _aVolume;

        /// <summary>
        /// Rating curve for flow rates for different times [m3/s]
        /// </summary>
        double[,] _aQ_back;
        /// <summary>
        /// Array of Julian days at which aQ changes [days after Jan 1]
        /// </summary>
        int[] _aDates;
        /// <summary>
        /// size of aDates
        /// </summary>
        int _nDates;

        /// <summary>
        /// number of outflow control structures
        /// </summary>
        int _nControlStructures;
        /// <summary>
        /// Array of pointer to outflow control structures
        /// </summary>
        ControlStructure[] _pControlStructures;

        // GW information :

        /// <summary>
        /// seepage constant [m3/s/m] for groundwater losses Q=k*(h-h_loc)
        /// </summary>
        double _seepage_const;

        /// <summary>
        /// local head [m] (same  for groundwater losses Q=k*(h-h_loc)
        /// </summary>
        double _local_GW_head;
    }






}
