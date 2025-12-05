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
using Harlinn.Hydrology;
using System;
using System.Diagnostics.Metrics;
using System.Formats.Asn1;
using System.Linq;
using System.Reflection.Emit;
using System.Threading;
using static Harlinn.Hydrology.Common;
using static Harlinn.Hydrology.Constants;
using static Harlinn.Mathematics.Net.Common;
using static System.Math;
using static System.Net.Mime.MediaTypeNames;

namespace Harlinn.Hydrology
{

    public class Model
    {
        // Model attributes

        /// <summary>
        /// total area of all subbasins [km^2]
        /// </summary>
        double _WatershedArea;

        /// <summary>
        /// number of HRUs in model
        /// </summary>
        int _nHydroUnits;
        /// <summary>
        /// Hydro units
        /// </summary>
        readonly List<HydroUnit> _pHydroUnits = new();

        /// <summary>
        /// number of HRU groups in model
        /// </summary>
        int _nHRUGroups;
        readonly List<HRUGroup> _pHRUGroups = new();

        /// <summary>
        /// number of Subbasin groups in model
        /// </summary>
        int _nSBGroups;
        readonly List<SubbasinGroup> _pSBGroups = new();

        /// <summary>
        /// number of subbasins
        /// </summary>
        int _nSubBasins;
        readonly List<SubBasin> _pSubBasins = new();
        /// <summary>
        /// stores order of subbasin for routing [size:_nSubBasins] (may be relegated to local variable in InitializeRoutingNetwork)
        /// </summary>
        int[] _aSubBasinOrder;
        /// <summary>
        /// stores maximum subasin order for routing (may be relegated to local variable in InitializeRoutingNetwork)
        /// </summary>
        int _maxSubBasinOrder;
        /// <summary>
        /// stores list of subbasin indices ordered upstream to downstream [size:_nSubBasins]
        /// </summary>
        int[] _aOrderedSBind;
        /// <summary>
        /// stores list of downstream indices of basins (for speed) [size:_nSubBasins]
        /// </summary>
        int[] _aDownstreamInds;

        /// <summary>
        /// number of state variables: water and energy storage units, snow density, etc.
        /// </summary>
        int _nStateVars;
        /// <summary>
        /// type of state variable in unit i  [size:_nStateVars] 
        /// </summary>
        SVType[] _aStateVarType;
        /// <summary>
        /// index of state variable for multilayer variables (e.g., SOIL); [size:_nStateVars] value=DOESNT_EXIST(-1) for unique variables (e.g. SURFACE_WATER)
        /// </summary>
        int[] _aStateVarLayer;
        /// <summary>
        /// lookup table for state variable indices; the index of SOIL[1] in a state_var[] array may be returned by aStateVarIndices[(int)(SOIL)][1]
        /// </summary>
        int[,] _aStateVarIndices = new int[MAX_STATE_VAR_TYPES,MAX_SV_LAYERS];

        /// <summary>
        /// number of soil layer storage units
        /// </summary>
        int _nSoilVars;

        int _nProcesses;  ///< number of hydrological processes that move water, mass, or energy from one storage unit to another
        /// hydrological processes
        readonly List<HydroProcess> _pProcesses = new();
        /// <summary>
        /// array of flags for whether or not each process applies to each HRU [_nProcesses][_nHydroUnits]
        /// </summary>
        bool[] _aShouldApplyProcess;
        /// <summary>
        /// Number of convolution variables (a.k.a. processes) in model
        /// </summary>
        int _nConvVariables;

        /// <summary>
        /// number of precip/temp gauges for forcing interpolation
        /// </summary>
        int _nGauges;
        /// <summary>
        /// gauges which store time series info [size:_nGauges]
        /// </summary>
        readonly List<Gauge> _pGauges = new();
        /// <summary>
        /// array of weights for each gauge/HRU pair[_nHydroUnits,_nGauges]
        /// </summary>
        double[,] _aGaugeWeights;  
        double[,] _aGaugeWtTemp;
        double[,] _aGaugeWtPrecip;

        /// <summary>
        /// number of gridded forcing input data
        /// </summary>
        int _nForcingGrids;
        /// <summary>
        /// gridded input data [size: _nForcingGrids]
        /// </summary>
        readonly List<ForcingGrid> _pForcingGrids = new();

        /// <summary>
        /// model-wide UTM zone used for interpolation
        /// </summary>
        int _UTM_zone;

        /// <summary>
        /// index of storage variable for lakes/wetlands (TMP?)
        /// </summary>
        int _lake_sv;

        /// <summary>
        /// global parameters  (used to be global, static)
        /// </summary>
        ModelParameters _pGlobalParams = new();

        /// <summary>
        /// number of transient parameters
        /// </summary>
        int _nTransParams;
        /// <summary>
        /// Transient parameters with time series
        /// </summary>
        readonly List<TransientParam> _pTransParams = new();
        /// <summary>
        /// number of HRU Group class changes
        /// </summary>
        int _nClassChanges;  
        readonly List<ClassChange> _pClassChanges = new();
        /// <summary>
        /// number of local parameter overrides
        /// </summary>
        int _nParamOverrides;
        /// <summary>
        /// local parameter overrides
        /// </summary>
        readonly List<ParameterOverride> _pParamOverrides = new();

        /// <summary>
        /// corresponding groundwater model
        /// </summary>
        GroundwaterModel _pGWModel = new();
        /// <summary>
        /// corresponding transport model
        /// </summary>
        TransportModel _pTransModel;
        /// <summary>
        /// model ensemble
        /// </summary>
        Ensemble _pEnsemble;
        /// <summary>
        /// demand optimizer (NULL w/o optimization)
        /// </summary>
        DemandOptimizer _pDO;

        // For Diagnostics Calculation

        /// <summary>
        /// observation time series [size: _nObservedTS]
        /// </summary>
        readonly List<TimeSeries> _pObservedTS = new();
        /// <summary>
        /// modeled time series corresponding to observations [size: _nObservedTS]
        /// </summary>
        readonly List<TimeSeries> _pModeledTS = new();
        /// <summary>
        /// number of observation time series
        /// </summary>
        int _nObservedTS;
        /// <summary>
        /// index of the next unprocessed observation
        /// </summary>
        int[] _aObsIndex;

        /// <summary>
        /// observation weight time series [size: _nObsWeightTS]
        /// </summary>
        readonly List<TimeSeries> _pObsWeightTS = new();
        /// <summary>
        /// number of observation weight time series
        /// </summary>
        int _nObsWeightTS;

        /// <summary>
        /// diagnostics to be calculated [size: _nDiagnostics]
        /// </summary>
        readonly List<Diagnostic> _pDiagnostics = new();
        /// <summary>
        /// number of diagnostics to be calculated comparing obs. vs modeled
        /// </summary>
        int _nDiagnostics;
        /// <summary>
        /// diagnostic periods [size _nDiagPeriods]
        /// </summary>
        readonly List<DiagPeriod> _pDiagPeriods = new();
        /// <summary>
        /// number of diagnostic periods
        /// </summary>
        int _nDiagPeriods;
        /// <summary>
        /// aggregate diagnostic structures [size: _nAggDiagnostics]
        /// </summary>
        readonly List<AggDiag> _pAggDiagnostics = new();
        /// <summary>
        /// number of aggregated diagnostics
        /// </summary>
        int _nAggDiagnostics;

        // Data Assimilation

        /// <summary>
        /// data assimilation flow scaling parameters [size: _nSubBasins] (NULL w/o DA)
        /// </summary>
        double[] _aDAscale;
        /// <summary>
        /// downstream distance to nearest DA observation [m] [size: _nSubBasins] (NULL w/o DA)
        /// </summary>
        double[] _aDAlength;
        /// <summary>
        /// flow adjustments [m3/s] [size: _nSubBasins]
        /// </summary>
        double[] _aDAQadjust;
        /// <summary>
        /// sum of assimilated drainage areas upstream of a subbasin outlet [km2] [size: _nSubBasins]
        /// </summary>
        double[] _aDADrainSum;
        /// <summary>
        /// the drainage area of the nearest downstream assimilated flow observation [km2] [size: _nSubBasins]
        /// </summary>
        double[] _aDADownSum;
        /// <summary>
        /// downstream time since most recent downstream DA observation [size: _nSubBasins] (NULL w/o DA)
        /// </summary>
        double[] _aDAtimesince;
        /// <summary>
        /// array of booleans indicating if observation data is available for assimilation at basin p's outlet [size: _nSubBasins] (NULL w/o DA)
        /// </summary>
        bool[] _aDAoverride;
        /// <summary>
        /// array of observed flow values in basins [size: _nSubBasins]  (NULL w/o DA)
        /// </summary>
        double[] _aDAobsQ;
        /// <summary>
        /// array of scale factors from previous time step  [size: _nSubBasins]  (NULL w/o DA)
        /// </summary>
        double[] _aDAscale_last;

        /// <summary>
        /// perturbation data; defines which forcing functions to perturb and how [size: _nPerturbations]
        /// </summary>
        readonly List<ForcePerturb> _pPerturbations = new();
        /// <summary>
        /// number of forcing functions to perturb
        /// </summary>
        int _nPerturbations;

        // Water/Energy Balance information

        /// <summary>
        /// cumulative amount of flowthrough [mm or MJ/m2 or mg/m2] for each process connection, each HRU [k][j*]
        /// </summary>
        double[,] _aCumulativeBal;
        /// <summary>
        /// current time step flowthrough [mm or MJ/m2 or mg/m2] for each process connection, each HRU [k][j*]
        /// </summary>
        double[,] _aFlowBal;
        /// <summary>
        /// total number of in-HRU connections in model
        /// </summary>
        int _nTotalConnections;
        /// <summary>
        /// cumulative amount of flowthrough [mm-m2 or MJ or mg] for each lateral process connection [j**]
        /// </summary>
        double[] _aCumulativeLatBal;
        /// <summary>
        /// current time step flowthrough [mm-m2 or MJ or mg] for each lateral process connection [j**]
        /// </summary>
        double[] _aFlowLatBal;
        /// <summary>
        /// total number of between-HRU connections in model
        /// </summary>
        int _nTotalLatConnections;
        /// <summary>
        /// cumulative water added to watershed (precipitation, basin inflows, etc.) [mm]
        /// </summary>
        double _CumulInput;
        /// <summary>
        /// cumulative outflow of water from system [mm]
        /// </summary>
        double _CumulOutput;
        /// <summary>
        /// initial water in system [mm]
        /// </summary>
        double _initWater;

        // Output

        /// <summary>
        /// custom output objects [size:_nCustomOutputs]
        /// </summary>
        readonly List<CustomOutput> _pCustomOutputs = new();
        /// <summary>
        /// Nuber of custom output objects
        /// </summary>
        int _nCustomOutputs;
        /// <summary>
        /// custom table objects [size:_nCustomTables]
        /// </summary>
        readonly List<CustomTable> _pCustomTables = new();
        /// <summary>
        /// Number of custom tables
        /// </summary>
        int _nCustomTables;
        /// <summary>
        /// output file stream for Hydrographs.csv
        /// </summary>
        TextWriter _HYDRO;
        /// <summary>
        /// output file stream for WatershedStorage.csv
        /// </summary>
        TextWriter _STORAGE;
        /// <summary>
        /// output file stream for ForcingFunctions.csv
        /// </summary>
        TextWriter _FORCINGS;
        /// <summary>
        /// output file stream for ReservoirStages.csv
        /// </summary>
        TextWriter _RESSTAGE;
        /// <summary>
        /// output file stream for Demands.csv
        /// </summary>
        TextWriter _DEMANDS;
        /// <summary>
        /// output file stream for WaterLevels.csv
        /// </summary>
        TextWriter _LEVELS;
        /// <summary>
        /// output file ID for Hydrographs.nc
        /// </summary>
        int _HYDRO_ncid;
        /// <summary>
        /// output file ID for ReservoirStages.nc
        /// </summary>
        int _RESSTAGE_ncid;
        /// <summary>
        /// output file ID for WatershedStorage.nc
        /// </summary>
        int _STORAGE_ncid;
        /// <summary>
        /// output file ID for ForcingFunctions.nc
        /// </summary>
        int _FORCINGS_ncid;
        /// <summary>
        /// output file ID for ReservoirMassBalance.nc
        /// </summary>
        int _RESMB_ncid;

        /// <summary>
        /// Set of model major output times (LOCAL times at which full solution is written)
        /// </summary>
        readonly SortedSet<TimeSpan> _outputTimes = new();
        /// <summary>
        /// index of current output time
        /// </summary>
        int _currOutputTimeInd;
        /// <summary>
        /// HRU group for which storage histories are written to file (or NULL)
        /// </summary>
        HRUGroup _pOutputGroup;

        /// <summary>
        /// model options information
        /// </summary>
        Options _pOptStruct; 

        // Blended PET/potential melt members
        int _PETBlends_N;
        EvapMethod[] _PETBlends_type;
        double[] _PETBlends_wts;
        int _PotMeltBlends_N;
        PotmeltMethod[] _PotMeltBlends_type;
        double[] _PotMeltBlends_wts;

        //Parameter classes

        /// <summary>
        /// land use classes
        /// </summary>
        List<LandUseClass> _pLandUseClasses;
        /// <summary>
        /// number of land use classes
        /// </summary>
        int _nLandUseClasses;
        readonly List<SoilClass> _pAllSoilClasses = new List<SoilClass>();
        int _nAllSoilClasses;
        readonly List<VegetationClass> _pAllVegClasses = [];
        int _numVegClasses;
        /// <summary>
        /// all terrain classes that have been created
        /// </summary>
        List<TerrainClass> _pAllTerrainClasses;
        /// <summary>
        /// Number of terrain classes that have been created length of pAllTerrainClasses
        /// </summary>
        int _nAllTerrainClasses;
        /// <summary>
        /// Reference to array of all soil profiles in model
        /// </summary>
        List<SoilProfile> _pAllSoilProfiles;
        /// <summary>
        /// Number of soil profiles in model (size of pAllSoilProfiles)
        /// </summary>
        int _nAllSoilProfiles;
        List<ChannelXSect> _pAllChannelXSects;
        int _nAllChannelXSects;

        /// <summary>
        /// pointer to state variable information object
        /// </summary>
        List<StateVariable> _pStateVar;
        /// <summary>
        /// number of lateral flow processes
        /// </summary>
        int _nLatFlowProcesses;

        public Options Options => _pOptStruct;

        // Variable used for search optimizations

        int _lastHruIndex = 0;
        int _lastSubBasinIndex = 0;

        bool[]? isUpstr;

        // Derived counters kept for compatibility with C++ API
        public int NumSubBasins => _pSubBasins.Count;
        public int NumHRUs => _pHydroUnits.Count;
        public int NumHRUGroups => _pHRUGroups.Count;
        public int NumSBGroups => _pSBGroups.Count;
        public int NumGauges => _pGauges.Count;
        public int NumForcingGrids => _pForcingGrids.Count;
        public int NumProcesses => _pProcesses.Count;
        public int NumObservedTS => _pObservedTS.Count;
        public double WatershedArea => _WatershedArea;

        // --- Constructor ---
        public Model(int nSoilLayers, Options options)
        {
            if (nSoilLayers < 1)
            {
                throw new ArgumentException("Model constructor: improper number of soil layers.", nameof(nSoilLayers));
            }
            _pOptStruct = options ?? throw new ArgumentNullException(nameof(options));

            _pGlobalParams = new ModelParameters();

            _HYDRO_ncid = -9;
            _STORAGE_ncid = -9;
            _FORCINGS_ncid = -9;
            _RESSTAGE_ncid = -9;
            _RESMB_ncid = -9;

            // initialize state variable index table with DOESNT_EXIST sentinel
            const int MAX_STATE_VAR_TYPES = 64;  // should match project constant
            const int MAX_SV_LAYERS = 64;        // should match project constant
            _aStateVarIndices = new int[MAX_STATE_VAR_TYPES, MAX_SV_LAYERS];
            for (int i = 0; i < MAX_STATE_VAR_TYPES; i++)
            {
                for (int j = 0; j < MAX_SV_LAYERS; j++)
                {
                    _aStateVarIndices[i, j] = Constants.DOESNT_EXIST;
                }
            }

            //determine first group of state variables based upon soil model
            //SW, atmosphere, atmos_precip always present, one for each soil layer, and 1 for GW (unless lumped)
            _nStateVars = 5 + nSoilLayers;

            _aStateVarType = new SVType[_nStateVars];
            _aStateVarLayer = new int[_nStateVars];
            _nSoilVars = nSoilLayers;

            _aStateVarType[0] = SVType.SURFACE_WATER; _aStateVarLayer[0] = DOESNT_EXIST; _aStateVarIndices[(int)(SVType.SURFACE_WATER),0] = 0;
            _aStateVarType[1] = SVType.ATMOSPHERE; _aStateVarLayer[1] = DOESNT_EXIST; _aStateVarIndices[(int)(SVType.ATMOSPHERE),0] = 1;
            _aStateVarType[2] = SVType.ATMOS_PRECIP; _aStateVarLayer[2] = DOESNT_EXIST; _aStateVarIndices[(int)(SVType.ATMOS_PRECIP),0] = 2;
            _aStateVarType[3] = SVType.PONDED_WATER; _aStateVarLayer[3] = DOESNT_EXIST; _aStateVarIndices[(int)(SVType.PONDED_WATER),0] = 3;
            _aStateVarType[4] = SVType.RUNOFF; _aStateVarLayer[4] = (int)SVType.RUNOFF; _aStateVarIndices[(int)(SVType.RUNOFF),0] = 4;

            int count = 0;
            for (int i = 5; i < 5 + _nSoilVars; i++)
            {
                _aStateVarType[i] = SVType.SOIL;
                _aStateVarLayer[i] = count;
                _aStateVarIndices[(int)(SVType.SOIL),count] = i;
                count++;
            }
            _UTM_zone = -1;

            _pTransModel = new TransportModel(this);
            
        }


        // --- Basic accessors translated from C++ ---
        public ModelParameters GetGlobalParams() => _pGlobalParams;
        public int GetNumSubBasins() => _pSubBasins.Count;
        public int GetNumHRUs() => _pHydroUnits.Count;
        public int GetNumHRUGroups() => _pHRUGroups.Count;
        public int GetNumForcingGrids() => _pForcingGrids.Count;
        public int GetNumProcesses() => _pProcesses.Count;
        public double GetWatershedArea() => _WatershedArea;
        public int GetNumObservedTS() => _pObservedTS.Count;

        public TimeSeriesBase GetObservedTS(int i) => _pObservedTS[i];
        public TimeSeriesBase GetSimulatedTS(int i) => _pModeledTS[i];

        public HydroProcess GetProcess(int j)
        {
            if (j < 0 || j >= _pProcesses.Count) throw new IndexOutOfRangeException("GetProcess: improper index");
            return _pProcesses[j];
        }

        public Gauge GetGauge(int g)
        {
            if (g < 0 || g >= _pGauges.Count) throw new IndexOutOfRangeException("GetGauge: improper index");
            return _pGauges[g];
        }

        public ForcingGrid GetForcingGrid(ForcingType ftype)
        {
            var f = _pForcingGrids.FindIndex(x => x.GetForcingType() == ftype);
            if (f < 0)
            {
                throw new InvalidOperationException("GetForcingGrid: no forcing grid of requested type");
            }
            return _pForcingGrids[f];
        }

        public HydroUnit GetHydroUnit(int k)
        {
            if (k < 0 || k >= _pHydroUnits.Count)
            {
                throw new IndexOutOfRangeException("GetHydroUnit: improper index");
            }
            return _pHydroUnits[k];
        }

        public HydroUnit? GetHRUByID(long hruId)
        {
            for (int i = 0; i < _nHydroUnits; i++)
            {
                int k = NearSearchIndex(i, _lastHruIndex, _nHydroUnits);
                if (hruId == _pHydroUnits[k].GetHRUID()) 
                {
                    _lastHruIndex = k; 
                    return _pHydroUnits[k]; 
                }
            }
            return null;
        }

        /// <summary>
        /// Returns specific HRU group denoted by parameter kk
        /// </summary>
        /// <param name="kk">
        /// Index of the HRU group to retrieve.
        /// </param>
        /// <returns>
        /// The HRU group corresponding to the specified index.
        /// </returns>
        /// <exception cref="ArgumentOutOfRangeException">
        /// Thrown when the specified index is out of range.
        /// </exception>
        public HRUGroup GetHRUGroup(int kk)
        {
            if (kk < 0 || kk >= _pHRUGroups.Count)
            {
                throw new ArgumentOutOfRangeException("GetHRUGroup: improper index");
            }
            return _pHRUGroups[kk];
        }


        /// <summary>
        /// Returns specific HRU group denoted by string parameter
        /// </summary>
        /// <param name="name">
        /// Name of the HRU group to retrieve.
        /// </param>
        /// <returns>
        /// The HRU group corresponding to the specified name.
        /// </returns>
        public HRUGroup? GetHRUGroup(string name)
        {
            for (int kk=0;kk<_nHRUGroups;kk++)
            {
                if (_pHRUGroups[kk].GetName() == name)
                {
                    return _pHRUGroups[kk];
                }
            }
            return null;
        }

        /// <summary>
        /// Returns true if HRU with global index k is in specified HRU Group
        /// </summary>
        /// <param name="k">
        /// HRU global index
        /// </param>
        /// <param name="HRUGroupName">
        /// The name of the HRU group
        /// </param>
        /// <returns>
        /// true if HRU k is in HRU Group specified by HRUGroupName.
        /// </returns>
        public bool IsInHRUGroup(int k, string HRUGroupName)
        {
            HRUGroup? pGrp = GetHRUGroup(HRUGroupName);
            if (pGrp == null) 
            { 
                return false; 
            }
            return pGrp.IsInGroup(k);
        }


        /// <summary>
        /// Returns specific Sub basin denoted by index parameter.
        /// </summary>
        /// <param name="subBasinIndex">
        /// Index of the sub basin to retrieve.
        /// </param>
        /// <returns>
        /// The sub basin corresponding to the specified index.
        /// </returns>
        /// <exception cref="ArgumentOutOfRangeException">
        /// Thrown when the specified index is out of range.
        /// </exception>
        public SubBasin GetSubBasin(int subBasinIndex)
        {
            if (subBasinIndex < 0 || subBasinIndex >= _pSubBasins.Count)
            {
                throw new ArgumentOutOfRangeException(nameof(subBasinIndex));
            }
            return _pSubBasins[subBasinIndex];
        }

        /// <summary>
        /// Returns index of subbasin downstream from subbasin referred to by index.
        /// </summary>
        /// <param name="subBasinIndex">The downstream index of the sub basin</param>
        /// <returns>
        /// The downstream subbasin index.
        /// </returns>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public int GetDownstreamBasin(int subBasinIndex)
        {
            if (subBasinIndex < 0 || subBasinIndex >= _aDownstreamInds.Length )
            {
                throw new ArgumentOutOfRangeException(nameof(subBasinIndex));
            }
            return _aDownstreamInds[subBasinIndex];
        }

        /// <summary>
        /// Returns subbasin object corresponding to passed subbasin ID
        /// </summary>
        /// <param name="subBasinId">The sub basin ID</param>
        /// <returns>The subbasin object corresponding to passed subbasin ID.</returns>
        public SubBasin? GetSubBasinByID(long subBasinId)
        {
            if (subBasinId < 0)
            {
                return null;
            }
            int n = _pSubBasins.Count;
            for (int i = 0; i < n; i++)
            {
                int index = NearSearchIndex(i, _lastSubBasinIndex, n);
                var subBasin = _pSubBasins[index];
                if (subBasin.Id == subBasinId) 
                { 
                    _lastSubBasinIndex = index; 
                    return subBasin; 
                }
            }
            return null;
        }

        /// <summary>
        /// Returns sub basin index corresponding to passed subbasin ID
        /// </summary>
        /// <param name="subBasinId">The sub basin ID</param>
        /// <returns>The sub basin index corresponding to passed subbasin ID</returns>
        public int GetSubBasinIndex(long subBasinId)
        {
            if (subBasinId < 0)
            {
                return DOESNT_EXIST;
            }
            int n = _pSubBasins.Count;
            for (int i = 0; i < n; i++)
            {
                int index = NearSearchIndex(i, _lastSubBasinIndex, n);
                var subBasin = _pSubBasins[index];
                if (subBasin.Id == subBasinId)
                {
                    _lastSubBasinIndex = index;
                    return index;
                }
            }
            return INDEX_NOT_FOUND;
        }

        /// <summary>
        /// Returns array of subbasins upstream of subbasin SBID, including that subbasin
        /// </summary>
        /// <param name="SBID">
        /// subbasin ID
        /// </param>
        /// <returns>
        /// An array of subbasins upstream of subbasin SBID, including that subbasin.
        /// </returns>
        /// <exception cref="ArgumentException"></exception>
        public SubBasin[] GetUpstreamSubbasins(long SBID)
        {
            if((isUpstr?.Length ?? 0) != _pSubBasins.Count)
            {
                isUpstr = new bool[_nSubBasins];
            }

            Array.Fill(isUpstr!, false);

            int p = GetSubBasinIndex(SBID);
            if((p==DOESNT_EXIST) || (p==INDEX_NOT_FOUND)) 
            {
                throw new ArgumentException(nameof(SBID));
            }
            isUpstr![p] = true;
            int upstrCount = 1;
            const int MAX_ITER = 1000;
            int numUpstr = 0;
            int numUpstrOld = 1;
            int iter = 0;
            int down_p;
            do
            {
                numUpstrOld = numUpstr;
                for (p = 0; p < _nSubBasins; p++)
                {
                    down_p = GetSubBasinIndex(_pSubBasins[p].GetDownstreamID());
                    if (down_p != DOESNT_EXIST)
                    {
                        if (isUpstr[down_p] == true) 
                        {
                            if (!isUpstr[p])
                            {
                                isUpstr[p] = true;
                                upstrCount++;
                            }
                        }
                    }
                }
                numUpstr = 0;
                for (p = 0; p < _nSubBasins; p++)
                {
                    if (isUpstr[p] == true) 
                    { 
                        numUpstr++; 
                    }
                }
                iter++;
            } while ((iter < MAX_ITER) && (numUpstr != numUpstrOld));

            var pSBs = new SubBasin[upstrCount];
            int count = 0;
            for (p = 0; p < _nSubBasins; p++)
            {
                if (isUpstr[p] == true) 
                { 
                    pSBs[count] = _pSubBasins[p]; count++; 
                }
            }
            return pSBs;
        }


        /// <summary>
        /// Returns true if subbasin with ID SBID is upstream of (or is) basin with subbasin SBIDdown
        /// </summary>
        /// <remarks>
        /// Recursive call, keeps marching downstream until outlet or SBIDdown is encounterd
        /// </remarks>
        /// <param name="SBID">
        /// ID of subbasin being queried
        /// </param>
        /// <param name="SBIDdown">
        /// subbasin ID basis of query
        /// </param>
        /// <returns>
        /// true if subbasin with ID SBID is upstream of (or is) basin with subbasin SBIDdown
        /// </returns>
        public bool IsSubBasinUpstream(long SBID, long SBIDdown)
        {
            if (SBID == DOESNT_EXIST) 
            {
                //end of the recursion line
                return false; 
            } 
            else if (SBIDdown == SBID) 
            {
                //a subbasin is upstream of itself (even handles loops on bad networks)
                return true; 
            } 
            else if (SBIDdown == DOESNT_EXIST) 
            {
                //everything is upstream of an outlet
                return true; 
            } 
            else if (GetSubBasinByID(SBID)!.GetDownstreamID() == SBIDdown) 
            {
                //directly upstream
                return true; 
            } 
            else 
            {
                return IsSubBasinUpstream(GetSubBasinByID(SBID)!.GetDownstreamID(), SBIDdown);
            }
        }

        /// <summary>
        /// Returns specific subbasin group at index subBasinGroupIndex.
        /// </summary>
        /// <param name="subBasinGroupIndex">
        /// subbasin group index
        /// </param>
        /// <returns>
        /// The subbasin group corresponding to passed index (subBasinGroupIndex).
        /// </returns>
        public SubbasinGroup GetSubBasinGroup(int subBasinGroupIndex)
        {
            return _pSBGroups[subBasinGroupIndex];
        }

        /// <summary>
        /// Returns specific subbasin group denoted by string parameter
        /// </summary>
        /// <param name="name">
        /// The name of the subbasin group
        /// </param>
        /// <returns>
        /// The subbasin group corresponding to passed name, or null if this group doesn't exist.
        /// </returns>
        public SubbasinGroup? GetSubBasinGroup(string name)
        {
            for(int i=0;i<_nSBGroups;i++) 
            {
                var subbasinGroup = _pSBGroups[i];
                if (subbasinGroup.GetName() == name) 
                {
                    return subbasinGroup;
                }
            }
            return null;
        }

        /// <summary>
        /// Returns true if subbasin with subbasin ID SBID is in specified subbasin Group
        /// </summary>
        /// <param name="SBID">
        /// subbasin identifier
        /// </param>
        /// <param name="SBGroupName">
        /// The name of the subbasin group.
        /// </param>
        /// <returns>
        /// true if subbasin SBID is in subbasin Group specified by SBGroupName.
        /// </returns>
        public bool IsInSubBasinGroup(long SBID, string SBGroupName)
        {
            var pGrp = GetSubBasinGroup(SBGroupName);
            if(pGrp == null) 
            { 
                return false; 
            }

            int pp = pGrp.GetGlobalIndex();
            for(int p_loc=0; p_loc<_pSBGroups[pp].GetNumSubbasins(); p_loc++)
            {
                if(_pSBGroups[pp].GetSubBasin(p_loc)!.GetID()==SBID) 
                { 
                    return true; 
                }
            }
            return false;
        }

        /// <summary>
        /// Returns hydrologic process type corresponding to passed index
        /// </summary>
        /// <param name="index">
        /// Index of the hydro process type to retrieve.
        /// </param>
        /// <returns>
        /// Hydrologic process type corresponding to passed index.
        /// </returns>
        public HydroProcessType GetProcessType(int index)
        { 
            return _pProcesses[index].GetProcessType();
        }

        /// <summary>
        /// Returns number of connections of hydrological process associated with passed index.
        /// </summary>
        /// <param name="index">
        /// index corresponding to the hydrological process.
        /// </param>
        /// <returns>
        /// The number of connections associated with hydrological process symbolized by index.
        /// </returns>
        public int GetNumConnections(int index)
        {
            return _pProcesses[index].GetNumConnections();
        }

        /// <summary>
        /// Returns number of forcing perturbations in the model.
        /// </summary>
        /// <returns>
        /// The number of forcing perturbations in the model.
        /// </returns>
        public int GetNumForcingPerturbations() => _nPerturbations;

        /// <summary>
        /// Returns state variable type corresponding to passed state variable array index.
        /// </summary>
        /// <param name="stateVariableIndex">
        /// State variable array index.
        /// </param>
        /// <returns>
        /// State variable type corresponding to passed state variable array index.
        /// </returns>
        public SVType GetStateVarType(int stateVariableIndex)
        {
            return _aStateVarType[stateVariableIndex];
        }

        /// <summary>
        /// Returns index of state variable type passed
        /// </summary>
        /// <remarks>
        /// Should only be used for state variable types without multiple levels.
        /// </remarks>
        /// <param name="type">
        /// State variable type.
        /// </param>
        /// <returns>
        /// Index which corresponds to the state variable type passed, if it exists; DOESNT_EXIST (-1) otherwise
        /// </returns>
        public int GetStateVarIndex(SVType type)
        {
            return _aStateVarIndices[(int)(type),0];
        }

        /// <summary>
        /// Returns index of state variable type passed (for repeated state variables)
        /// </summary>
        /// <param name="type">
        /// State variable type
        /// </param>
        /// <param name="layer">
        /// Identifies the layer of interest.
        /// </param>
        /// <returns>
        /// Index which corresponds to the state variable type passed, if it exists; DOESNT_EXIST (-1) otherwise.
        /// </returns>
        public int GetStateVarIndex(SVType type, int layer)
        {
            if (layer == DOESNT_EXIST) 
            { 
                return _aStateVarIndices[(int)(type),0]; 
            }
            else 
            { 
                return _aStateVarIndices[(int)(type),layer]; 
            }
        }

        /// <summary>
        /// Uses state variable type index to access index of layer to which it corresponds
        /// </summary>
        /// <param name="ii">
        /// Index referencing a type of state variable
        /// </param>
        /// <returns>
        /// Index which corresponds to soil layer, or 0 for a non-layered state variable
        /// </returns>
        public int GetStateVarLayer(int ii)
        {
            int count = 0;
            for (int i = 0; i < ii; i++)
            {
                if (_aStateVarType[i] == _aStateVarType[ii]) 
                { 
                    count++; 
                }
            }
            return count;
        }

        /// <summary>
        /// Determines whether a state variable of the specified type exists in the model.
        /// </summary>
        /// <param name="typ">The type of the state variable to check for existence.</param>
        /// <returns>true if a state variable of the specified type exists; otherwise, false.</returns>
        public bool StateVarExists(SVType typ)
        {
            return (GetStateVarIndex(typ) != DOESNT_EXIST);
        }

        /// <summary>
        /// Returns lake storage variable index
        /// </summary>
        /// <returns>The index of lake storage variable.</returns>
        public int GetLakeStorageIndex() 
        { 
            return _lake_sv; 
        }

        /// <summary>
        /// Returns gauge index of gauge with specified name
        /// </summary>
        /// <param name="name">
        /// The specified name.
        /// </param>
        /// <returns>
        /// The index of the gauge.
        /// </returns>
        public int GetGaugeIndexFromName(string name)
        {
            for (int i = 0; i < _nGauges; i++)
            {
                if (name == _pGauges[i].GetName()) 
                { 
                    return i; 
                }
            }
            return DOESNT_EXIST;
        }

        /// <summary>
        /// Returns forcing grid index of forcing grid with specified type
        /// </summary>
        /// <param name="typ">
        /// specified type
        /// </param>
        /// <returns>
        /// The index of the forcing grid
        /// </returns>
        public int GetForcingGridIndexFromType(ForcingType typ)
        {
            for (int f = 0; f < _nForcingGrids; f++)
            {
                if (typ == _pForcingGrids[f].GetForcingType()) 
                { 
                    return f; 
                }
            }
            return DOESNT_EXIST;
        }

        /// <summary>
        /// Returns current mass/energy flux (mm/d, MJ/m2/d, mg/m2/d) between two storage compartments FromIndices and ToIndices
        /// </summary>
        /// <param name="k">
        /// HRU index
        /// </param>
        /// <param name="js">
        /// index of process connection (i.e., j*)
        /// </param>
        /// <param name="options">
        /// Global model options information
        /// </param>
        /// <returns></returns>
        public double GetFlux(int k, int js, Options options)
        {
            return _aFlowBal[k, js] / options.timestep;
        }

        /// <summary>
        /// returns concentration or temperature within hru k with storage index i
        /// </summary>
        /// <param name="k">
        /// HRU index
        /// </param>
        /// <param name="i">
        /// mass/energy state variable index
        /// </param>
        /// <returns></returns>
        public double GetConcentration(int k, int i)
        {
            return _pTransModel.GetConcentration(k, i);
        }

        /// <summary>
        /// Returns current mass/energy flow (mm-m2/d, MJ/d, mg/d) between two storage compartments FromIndices and ToIndices
        /// </summary>
        /// <remarks>Used by advective transport processes.</remarks>
        /// <param name="qs">
        /// global index of process connection (i.e., q*)
        /// </param>
        /// <param name="options">
        /// Global model options information
        /// </param>
        /// <returns></returns>
        public double GetLatFlow(int qs,Options options)
        {
            return _aFlowLatBal[qs] / options.timestep;
        }

        /// <summary>
        /// Returns cumulative flux to/from storage unit i
        /// </summary>
        /// <param name="k">
        /// index of HRU
        /// </param>
        /// <param name="i">
        /// index of storage compartment
        /// </param>
        /// <param name="to">
        /// true if evaluating cumulative flux to storage compartment, false for 'from'
        /// </param>
        /// <returns>
        /// cumulative flux to storage compartment i in hru K
        /// </returns>
        public double GetCumulativeFlux(int k, int i, bool to)
        {
            int js = 0;
            double sum = 0;
            double area = _pHydroUnits[k].GetArea();
            int jss = 0;
            for(int j = 0; j<_nProcesses; j++)
            {
                // Each process may have multiple connections
                for(int q = 0; q<_pProcesses[j].GetNumConnections(); q++)
                {
                    
                    if ((to) && (_pProcesses[j].GetToIndices()[q]   == i))
                    { 
                        sum+=_aCumulativeBal[k,js]; 
                    }
                    if((!to) && (_pProcesses[j].GetFromIndices()[q] == i))
                    { 
                        sum+=_aCumulativeBal[k,js]; 
                    }
                    js++;
                }

                if (_pProcesses[j].GetNumLatConnections() > 0)
                {
                    var pProc = (LateralExchangeHydroProcess)_pProcesses[j];
                    // Each process may have multiple connections
                    for (int q = 0; q < _pProcesses[j].GetNumLatConnections(); q++)
                    {
                        if ((to) && (pProc.GetToHRUIndices()[q] == k) && (pProc.GetLateralToIndices()[q] == i)) 
                        { 
                            sum += _aCumulativeLatBal[jss] / area; 
                        }
                        if ((!to) && (pProc.GetFromHRUIndices()[q] == k) && (pProc.GetLateralFromIndices()[q] == i)) 
                        { 
                            sum += _aCumulativeLatBal[jss] / area; 
                        }
                        jss++;
                    }
                }
            }
            return sum;
        }

        /// <summary>
        /// Returns cumulative gross flux between unit iFrom and iTo in HRU k
        /// </summary>
        /// <param name="k">
        /// index of HRU
        /// </param>
        /// <param name="iFrom">
        /// index of storage compartment
        /// </param>
        /// <param name="iTo">
        /// index of storage compartment
        /// </param>
        /// <returns>
        /// cumulative gross flux between unit iFrom and iTo in HRU k
        /// </returns>
        public double GetCumulFluxBetween(int k, int iFrom, int iTo)
        {
            int q, js = 0;
            double sum = 0;
            for(int j = 0; j<_nProcesses; j++)
            {
                var hydroProcess = _pProcesses[j];
                var iFromp = hydroProcess.GetFromIndices();
                var iTop  = hydroProcess.GetToIndices();
                var nConn = hydroProcess.GetNumConnections();
                // Each process may have multiple connections
                for (q = 0; q<nConn; q++)
                {
                    if((iTop[q]== iTo) && (iFromp[q]== iFrom))
                    { 
                        sum += _aCumulativeBal[k,js]; 
                    }
                    if((iFromp[q]== iTo) && (iTop[q]== iFrom))
                    { 
                        sum -= _aCumulativeBal[k,js]; 
                    }
                    js++;
                }
            }

            return sum;
        }

        /// <summary>
        /// Returns area-weighted average of specified cumulative flux over watershed
        /// </summary>
        /// <param name="i">
        /// index of storage compartment
        /// </param>
        /// <param name="to">
        /// true if evaluating cumulative flux to storage compartment, false for 'from'
        /// </param>
        /// <returns>
        /// Area-weighted average of cumulative flux to storage compartment i
        /// </returns>
        public double GetAvgCumulFlux(int i,bool to)
        {
            //Area-weighted average
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += GetCumulativeFlux(k, i, to) * _pHydroUnits[k].GetArea();
                }
            }
            return sum / _WatershedArea;
        }

        /// <summary>
        /// Returns area-weighted average of  cumulative flux between two compartments over watershed
        /// </summary>
        /// <param name="iFrom">
        /// index of 'from' storage compartment
        /// </param>
        /// <param name="iTo">
        /// index of 'to' storage compartment
        /// </param>
        /// <returns>
        /// Area-weighted average of cumulative flux between two compartments over watershed
        /// </returns>
        public double GetAvgCumulFluxBet(int iFrom, int iTo)
        {
            // Area-weighted average
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += GetCumulFluxBetween(k, iFrom, iTo) * _pHydroUnits[k].GetArea();
                }
            }
            return sum / _WatershedArea;
        }

        /// <summary>
        /// Returns options structure model
        /// </summary>
        public Options GetOptStruct() 
        { 
            return _pOptStruct; 
        }

        /// <summary>
        /// Returns transport model
        /// </summary>
        public TransportModel GetTransportModel() 
        {
            return _pTransModel;
        }

        /// <summary>
        /// Returns groundwater model
        /// </summary>
        public GroundwaterModel GetGroundwaterModel() 
        {
            return _pGWModel;
        }

        /// <summary>
        /// Returns ensemble setup
        /// </summary>
        public Ensemble GetEnsemble() 
        { 
            return _pEnsemble; 
        }

        /// <summary>
        /// Returns demand optimizer
        /// </summary>
        public DemandOptimizer GetManagementOptimizer() 
        { 
            return _pDO; 
        }

        /// <summary>
        /// Returns area-weighted average total precipitation + irrigation rate at all HRUs [mm/d]
        /// </summary>
        /// <returns>Area-weighted average of total precipitation rate [mm/d] over all HRUs</returns>
        public double GetAveragePrecip()
        {
            double sum = 0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += (_pHydroUnits[k].GetForcingFunctions().precip + _pHydroUnits[k].GetForcingFunctions().irrigation) * _pHydroUnits[k].GetArea();
                }
            }
            return sum / _WatershedArea;
        }

        /// <summary>
        /// Returns current area-weighted average snowfall rate [mm/d] at all HRUs
        /// </summary>
        /// <returns>
        /// Current area-weighted average snowfall rate [mm/d] at all HRUs
        /// </returns>
        public double GetAverageSnowfall()
        {
            double sum = 0;

            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    var f = _pHydroUnits[k].GetForcingFunctions();
                    sum += (f.precip * f.snow_frac) * _pHydroUnits[k].GetArea();
                }
            }
            return sum / _WatershedArea;
        }

        /// <summary>
        /// Returns current area-weighted average forcing functions at all HRUs
        /// </summary>
        /// <returns>
        /// Current area-weighted average forcing functions at all HRUs
        /// </returns>
        public Force GetAverageForcings()
        {
            Force Fave = new Force();
            double area_wt;
            Fave.ZeroOutForcings();



            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    var pF_hru = _pHydroUnits[k].GetForcingFunctions();
                    area_wt = _pHydroUnits[k].GetArea() / _WatershedArea;

                    Fave.precip += area_wt * pF_hru.precip;
                    Fave.precip_daily_ave += area_wt * pF_hru.precip_daily_ave;
                    Fave.precip_5day += area_wt * pF_hru.precip_5day;
                    Fave.snow_frac += area_wt * pF_hru.snow_frac;

                    Fave.temp_ave += area_wt * pF_hru.temp_ave;
                    Fave.temp_daily_min += area_wt * pF_hru.temp_daily_min;
                    Fave.temp_daily_max += area_wt * pF_hru.temp_daily_max;
                    Fave.temp_daily_ave += area_wt * pF_hru.temp_daily_ave;
                    Fave.temp_month_max += area_wt * pF_hru.temp_month_max;
                    Fave.temp_month_min += area_wt * pF_hru.temp_month_min;
                    Fave.temp_month_ave += area_wt * pF_hru.temp_month_ave;

                    Fave.temp_ave_unc += area_wt * pF_hru.temp_ave_unc;
                    Fave.temp_min_unc += area_wt * pF_hru.temp_min_unc;
                    Fave.temp_max_unc += area_wt * pF_hru.temp_max_unc;

                    Fave.air_dens += area_wt * pF_hru.air_dens;
                    Fave.air_pres += area_wt * pF_hru.air_pres;
                    Fave.rel_humidity += area_wt * pF_hru.rel_humidity;

                    Fave.cloud_cover += area_wt * pF_hru.cloud_cover;
                    Fave.ET_radia += area_wt * pF_hru.ET_radia;
                    Fave.ET_radia_flat += area_wt * pF_hru.ET_radia_flat;
                    Fave.SW_radia += area_wt * pF_hru.SW_radia;
                    Fave.SW_radia_unc += area_wt * pF_hru.SW_radia_unc;
                    Fave.SW_radia_net += area_wt * pF_hru.SW_radia_net;
                    Fave.SW_radia_subcan += area_wt * pF_hru.SW_radia_subcan;
                    Fave.SW_subcan_net += area_wt * pF_hru.SW_subcan_net;
                    Fave.LW_incoming += area_wt * pF_hru.LW_incoming;
                    Fave.LW_radia_net += area_wt * pF_hru.LW_radia_net;
                    Fave.day_length += area_wt * pF_hru.day_length;
                    Fave.day_angle += area_wt * pF_hru.day_angle;   //not really necc.

                    Fave.wind_vel += area_wt * pF_hru.wind_vel;

                    Fave.PET += area_wt * pF_hru.PET;
                    Fave.OW_PET += area_wt * pF_hru.OW_PET;
                    Fave.PET_month_ave += area_wt * pF_hru.PET_month_ave;

                    Fave.potential_melt += area_wt * pF_hru.potential_melt;

                    Fave.recharge += area_wt * pF_hru.recharge;
                    Fave.precip_temp += area_wt * pF_hru.precip_temp;
                    Fave.precip_conc += area_wt * pF_hru.precip_conc;

                    Fave.subdaily_corr += area_wt * pF_hru.subdaily_corr;
                }
            }
            return Fave;
        }

        /// <summary>
        /// Returns area weighted average of state variables across all modeled HRUs
        /// </summary>
        /// <param name="i">
        /// State variable index
        /// </param>
        /// <returns>
        /// Area weighted average of state variables across all modeled HRUs
        /// </returns>
        public double GetAvgStateVar(int i)
        {
            //Area-weighted average
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += (_pHydroUnits[k].GetStateVarValue(i) * _pHydroUnits[k].GetArea());
                }
            }
            return sum / _WatershedArea;
        }

        /// <summary>
        /// Returns area weighted average of concentrations across all modeled HRUs
        /// </summary>
        /// <param name="i">
        /// State variable index
        /// </param>
        /// <returns>
        /// Area weighted average of concentrations across all modeled HRUs
        /// </returns>
        public double GetAvgConcentration(int i)
        {
            //Area-weighted average
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += (_pTransModel.GetConcentration(k, i) * _pHydroUnits[k].GetArea());
                }
            }
            return sum / _WatershedArea;
        }

        /// <summary>
        /// Returns area-weighted average of specified forcing function over watershed
        /// </summary>
        /// <param name="ftype">
        /// identifier of forcing function to assess
        /// </param>
        /// <returns>
        /// Area-weighted average of specified forcing function
        /// </returns>
        public double GetAvgForcing(ForcingType ftype)
        {
            //Area-weighted average
            double sum = 0.0;
            for (int k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k].IsEnabled)
                {
                    sum += (_pHydroUnits[k].GetForcing(ftype) * _pHydroUnits[k].GetArea());
                }
            }
            return sum / _WatershedArea;
        }

        /// <summary>
        /// Returns total channel storage [mm]
        /// </summary>
        /// <returns>
        /// Total channel storage in all of watershed [mm]
        /// </returns>
        public double GetTotalChannelStorage()
        {
            double sum = 0;

            for (int p = 0; p < _nSubBasins; p++)
            {
                sum += _pSubBasins[p].GetChannelStorage();
            }
            return sum / (_WatershedArea * M2_PER_KM2) * MM_PER_METER;
        }


        /// <summary>
        /// Returns total reservoir storage [mm]
        /// </summary>
        /// <returns>
        /// Total reservoir storage in all of watershed [mm]
        /// </returns>
        public double GetTotalReservoirStorage()
        {
            double sum = 0;

            for (int p = 0; p < _nSubBasins; p++)
            {
                sum += _pSubBasins[p].GetReservoirStorage();
            }
            return sum / (_WatershedArea * M2_PER_KM2) * MM_PER_METER;
        }

        /// <summary>
        /// Returns total rivulet storage distributed over watershed [mm]
        /// </summary>
        /// <returns>
        /// Total rivulet storage distributed over watershed [mm]
        /// </returns>
        public double GetTotalRivuletStorage()
        {
            double sum = 0;

            for (int p = 0; p < _nSubBasins; p++)
            {
                sum += _pSubBasins[p].GetRivuletStorage();
            }

            return sum / (_WatershedArea * M2_PER_KM2) * MM_PER_METER;
        }

        /// <summary>
        /// Adds additional HRU to model
        /// </summary>
        /// <param name="hydroUnit">
        /// HydroUnit to add
        /// </param>
        public void AddHRU(HydroUnit hydroUnit)
        {
            _pHydroUnits.Add(hydroUnit);
            _nHydroUnits++;
        }


        /// <summary>
        /// Adds the specified HRU group to the model.
        /// </summary>
        /// <param name="pHRUGroup">The HRU group to add. Cannot be null and must have a unique name within the model.</param>
        /// <exception cref="ArgumentException">Thrown if an HRU group with the same name already exists in the model.</exception>
        public void AddHRUGroup(HRUGroup pHRUGroup)
        {
            if ( GetHRUGroup(pHRUGroup.GetName()) != null)
            {
                throw new ArgumentException("HRU Group with name "+ pHRUGroup.GetName() + " already exists in model.");
            }
            _pHRUGroups.Add(pHRUGroup);
            _nHRUGroups++;
        }

        /// <summary>
        /// Adds a sub-basin to the collection of sub-basins managed by this instance.
        /// </summary>
        /// <param name="subBasin">The sub-basin to add to the collection. Cannot be null.</param>
        public void AddSubBasin(SubBasin subBasin)
        {
            _pSubBasins.Add(subBasin);
            _nSubBasins++;
        }

        /// <summary>
        /// Adds a sub-basin group to the model.
        /// </summary>
        /// <param name="subBasinGroup">The sub-basin group to add. Cannot be null. The group's name must be unique within the model.</param>
        /// <exception cref="ArgumentException">Thrown if a sub-basin group with the same name already exists in the model.</exception>
        public void AddSubBasinGroup(SubbasinGroup subBasinGroup)
        {
            if (GetSubBasinGroup(subBasinGroup.GetName()) != null)
            {
                throw new ArgumentException("Sub-basin Group with name " + subBasinGroup.GetName() + " already exists in model.");
            }
            _pSBGroups.Add(subBasinGroup);
            _nSBGroups++;
        }


        /// <summary>
        /// Adds the specified gauge to the collection of gauges managed by this instance.  
        /// </summary>
        /// <param name="gauge">The gauge to add to the collection. Cannot be null.</param>
        public void AddGauge(Gauge gauge)
        {
            _pGauges.Add(gauge);
            _nGauges++;
        }

        /// <summary>
        /// Adds gridded forcing to model
        /// </summary>
        /// <param name="forcingGrid">
        /// The forcing grid to add.
        /// </param>
        /// <param name="typ">
        /// The type of forcing.
        /// </param>
        public void AddForcingGrid(ForcingGrid forcingGrid, ForcingType typ)
        {
            int f = GetForcingGridIndexFromType(typ);
            if (f == DOESNT_EXIST)
            {
                _pForcingGrids.Add(forcingGrid);
                _nForcingGrids++;
            }
            else
            {
                // Overwrite grid
                _pForcingGrids[f] = forcingGrid;
            }
        }

        /// <summary>
        /// Adds transient parameter to model
        /// </summary>
        /// <param name="transientParameter">
        /// Transient parameter to be added to model
        /// </param>
        public void AddTransientParameter(TransientParam transientParameter)
        {
            _pTransParams.Add(transientParameter);
            _nTransParams++;
        }


        /// <summary>
        /// Adds parameter override to model
        /// </summary>
        /// <param name="parameterOverride">
        /// Parameter override to be added to model
        /// </param>
        public void AddParameterOverride(ParameterOverride parameterOverride)
        {
            _pParamOverrides.Add(parameterOverride);
            _nParamOverrides++;
        }

        /// <summary>
        /// Adds class change to model
        /// </summary>
        /// <param name="HRUgroup">
        /// The name of the HRU group to change.
        /// </param>
        /// <param name="tclass">
        /// The class type to change.
        /// </param>
        /// <param name="new_class">
        /// The new class to assign to the HRU group.
        /// </param>
        /// <param name="tt">
        /// The time struct representing the time of the change.
        /// </param>
        /// <param name="options">
        /// The options for the change.
        /// </param>
        /// <exception cref="ArgumentException"></exception>
        public void AddPropertyClassChange(string HRUgroup, ClassType tclass, string new_class, TimeStruct tt, Options options)
        {

            var pCC = new ClassChange();
            pCC.HRU_groupID = DOESNT_EXIST;
            for (int kk = 0; kk < _nHRUGroups; kk++)
            {
                if (_pHRUGroups[kk].GetName() == HRUgroup)
                {
                    pCC.HRU_groupID = kk;
                }
            }
            if (pCC.HRU_groupID == DOESNT_EXIST)
            {
                throw new ArgumentException("Invalid HRU Group name: " + HRUgroup + ". HRU group names should be defined in .rvi file using :DefineHRUGroups command. ", nameof(HRUgroup));
            }
            pCC.newclass = new_class;
            if ((tclass == ClassType.CLASS_LANDUSE) && (StringToLUClass(new_class) == null))
            {
                throw new ArgumentException("Invalid land use class specified: " + new_class, nameof(new_class));
            }
            if ((tclass == ClassType.CLASS_VEGETATION) && (StringToVegClass(new_class) == null))
            {
                throw new ArgumentException("Invalid vegetation class specified: " + new_class, nameof(new_class));
            }
            if ((tclass == ClassType.CLASS_HRUTYPE) && (StringToHRUType(new_class) == HRUType.HRU_INVALID_TYPE))
            {
                throw new ArgumentException("Invalid HRU type specified: " + new_class, nameof(new_class));
            }

            pCC.tclass = tclass;
            if ((tclass != ClassType.CLASS_VEGETATION) && (tclass != ClassType.CLASS_LANDUSE) && (tclass != ClassType.CLASS_HRUTYPE))
            {
                throw new ArgumentException("Only vegetation, land use, and HRU type classes may be changed during the course of simulation", nameof(tclass));
            }

            //convert time to model time
            pCC.modeltime = tt.Elapsed;

            if (pCC.modeltime > options.duration)
            {
                string warn;
                warn = "Property Class change dated " + tt.date_string + " occurs after model simulation is done; it will not effect results.";
                Runtime.WriteWarning(warn, Options.noisy);
            }
            if (pCC.modeltime.Ticks < 0)
            {
                string warn;
                warn = "Property Class change dated " + tt.date_string + " occurs before model simulation. All such changes will be processed before time zero, and these changes MUST be input in chronological order.";
                Runtime.WriteAdvisory(warn, Options.noisy);
            }

            _pClassChanges.Add(pCC);
            _nClassChanges++;
        }


        /// <summary>
        /// Adds observed time series to model
        /// </summary>
        /// <param name="timeSeries">
        /// The observed time series to be added to model.
        /// </param>
        public void AddObservedTimeSeries(TimeSeries timeSeries)
        {
            _pObservedTS.Add(timeSeries);
            _nObservedTS++;
        }

        /// <summary>
        /// Adds observation weighting time series to model
        /// </summary>
        /// <param name="timeSeries">
        /// The observation weights time series to be added to model.
        /// </param>
        public void AddObservedWeightsTS(TimeSeries timeSeries)
        {
            _pObsWeightTS.Add(timeSeries);
            _nObsWeightTS++;
        }


        /// <summary>
        /// Adds diagnostic to model
        /// </summary>
        /// <param name="diagnostic">
        /// The diagnostic to be added to model
        /// </param>
        public void AddDiagnostic(Diagnostic diagnostic)
        {
            _pDiagnostics.Add(diagnostic);
            _nDiagnostics++;
        }


        /// <summary>
        /// Adds aggregate diagnostic to model
        /// </summary>
        /// <param name="stat">
        /// The aggregation statistic to be used
        /// </param>
        /// <param name="datatype">
        /// The observation datatype string e.g., "HYDROGRAPH"
        /// </param>
        /// <param name="group_ind">
        /// The group index (or DOESNT_EXIST, if applied to all)
        /// </param>
        public void AddAggregateDiagnostic(AggStat stat, string datatype, int group_ind)
        {
            var agg = new AggDiag(stat, datatype, group_ind);
            _pAggDiagnostics.Add(agg);
            _nAggDiagnostics++;
        }

        /// <summary>
        /// Adds diagnostic period to model
        /// </summary>
        /// <param name="diagPeriod">
        /// The diagnostic period to be added to model.
        /// </param>
        public void AddDiagnosticPeriod(DiagPeriod diagPeriod)
        {   
            _pDiagPeriods.Add(diagPeriod);
            _nDiagPeriods++;
        }

        /// <summary>
        /// Adds model output time to model
        /// </summary>
        /// <param name="outputTime">The output time to add</param>
        public void AddModelOutputTime(TimeSpan outputTime)
        {
            _outputTimes.Add(outputTime);
        }

        /// <summary>
        /// Adds a hydrological process to system.
        /// </summary>
        /// <remarks>
        /// Adds a hydrological process that moves water or energy from state
        /// variable (e.g., an array of storage units) i[] to state variables j[]
        /// </remarks>
        /// <param name="hydroProcess">The Hydrological process to be added</param>
        /// <exception cref="ArgumentException"></exception>
        public void AddProcess(HydroProcess hydroProcess)
        {
            ArgumentNullException.ThrowIfNull(hydroProcess);
            var numConnections = hydroProcess.GetNumConnections();
            for (int i = 0; i < numConnections; i++)
            {
                int fi = hydroProcess.FromIndices[i];
                if(fi < 0 && fi >= _nStateVars)
                {
                    throw new ArgumentException($"Invalid from storage index:{fi}");
                }
                int ti = hydroProcess.ToIndices[i];
                if (ti < 0 && ti >= _nStateVars)
                {
                    throw new ArgumentException($"Invalid to storage index:{ti}");
                }
            }
            _pProcesses.Add(hydroProcess);
        }

        /// <summary>
        /// Adds state variables during model construction
        /// </summary>
        /// <remarks>
        /// Called during model construction (only from parse of RVI file) to dynamically
        /// generate a list of state variables in the model.
        /// </remarks>
        /// <param name="aSV">
        /// array of state variables types to be added
        /// </param>
        /// <param name="aLev">
        /// array of state variable levels to be added
        /// </param>
        /// <exception cref="ArgumentException"></exception>
        public void AddStateVariables( SVType[] aSV, int[] aLev)
        {
            
            if(aSV.Length != aLev.Length)
            {
                throw new ArgumentException("State variable type and layer arrays must have the same length");
            }
            if(aSV.Length > MAX_STATE_VARS)
            {
                throw new ArgumentException("Exceeded maximum number of state variables manipulable by one process");
            }
            int nSV = aSV.Length;
            bool found;
            for (int ii=0;ii<nSV;ii++)
            {
                found=false;
                for (int i=0;i<_nStateVars;i++)
                {
                    if ((_aStateVarType[i]==aSV[ii]) && (_aStateVarLayer[i]==aLev[ii]))
                    {
                        found=true;
                    }
                }
        
                if (!found)
                {
                    var tmpSV = new SVType[_nStateVars + 1];
                    var tmpLy = new int[_nStateVars + 1];
                    
                    for (int i = 0; i < _nStateVars; i++)//copy old arrays
                    {
                        tmpSV[i] = _aStateVarType[i];
                        tmpLy[i] = _aStateVarLayer[i];
                    }
                    // set values of new array items
                    tmpSV[_nStateVars] = aSV[ii];
                    tmpLy[_nStateVars] = aLev[ii];
                    
                    //add index to state variable lookup table
                    if((int)(aSV[ii]) > MAX_STATE_VAR_TYPES)
                    {
                        throw new ArgumentException("bad type specified");
                    }
                    if((aLev[ii] < -1) || (aLev[ii] >= MAX_SV_LAYERS) )
                    {
                        throw new ArgumentException("bad layer index specified");
                    }

                    if (aLev[ii] == DOESNT_EXIST) 
                    { 
                        _aStateVarIndices[(int)(aSV[ii]),0] = _nStateVars; 
                    }
                    else 
                    { 
                        _aStateVarIndices[(int)(aSV[ii]),aLev[ii]] = _nStateVars; 
                    }
                    // replace old arrays
                    _aStateVarType = tmpSV;
                    _aStateVarLayer = tmpLy;
                    _nStateVars++;
                }
            }
        }

        /// <summary>
        /// Adds custom output object
        /// </summary>
        /// <param name="customOutput">
        /// The custom output object to be added
        /// </param>
        public void AddCustomOutput(CustomOutput customOutput)
        {
            _pCustomOutputs.Add(customOutput);
            _nCustomOutputs++;
        }

        /// <summary>
        /// Adds custom table object
        /// </summary>
        /// <param name="customTable">
        /// The custom table object to be added.
        /// </param>
        public void AddCustomTable(CustomTable customTable)
        {
            _pCustomTables.Add(customTable);
            _nCustomTables++;
        }


        /// <summary>
        /// Adds additional forcing perturbation
        /// </summary>
        /// <param name="type">
        /// forcing type to be perturbed
        /// </param>
        /// <param name="distrib">
        /// sampling distribution type
        /// </param>
        /// <param name="distpars">
        /// array of distribution parameters
        /// </param>
        /// <param name="group_index">
        /// HRU group ID (or DOESNT_EXIST if all HRUs should be perturbed)
        /// </param>
        /// <param name="adj">
        /// type of perturbation (e.g., additive or multiplicative)
        /// </param>
        /// <param name="nStepsPerDay">
        /// Number of simulation steps per day
        /// </param>
        /// <exception cref="ArgumentException"></exception>
        public void AddForcingPerturbation(ForcingType type, DistType distrib, double[] distpars, int group_index, Adjustment adj, int nStepsPerDay)
        {
            if (!((type == ForcingType.F_PRECIP) || (type == ForcingType.F_SNOWFALL) || (type == ForcingType.F_RAINFALL) || (type == ForcingType.F_TEMP_AVE)))
            {
                throw new ArgumentException("Only PRECIP, RAINFALL, SNOWFALL, and TEMP_AVE are supported for forcing perturbation.");
            }

            ForcePerturb pFP = new ForcePerturb();
            pFP.forcing = type;
            pFP.distribution = distrib;
            pFP.kk = group_index;
            pFP.adj_type = adj;
            for (int i = 0; i < 3; i++)
            {
                pFP.distpar[i] = distpars[i];
            }
            pFP.eps = new double[nStepsPerDay];
            for (int n = 0; n < nStepsPerDay; n++)
            {
                pFP.eps[n] = 0;
            }
            _pPerturbations.Add(pFP);
            _nPerturbations++;
        }

        /// <summary>
        /// Sets lake storage state variable index based on SV type and layer
        /// </summary>
        /// <param name="lak_sv">
        /// Lake storage state variable type.
        /// </param>
        /// <param name="lev">
        /// Layer of interest.
        /// </param>
        /// <exception cref="Exception"></exception>
        public void SetLakeStorage(SVType lak_sv, int lev)
        {
            var lake_sv = GetStateVarIndex(lak_sv, lev);
            if (lake_sv == DOESNT_EXIST)
            {
                throw new Exception("non-existent state variable");
            }
            _lake_sv = lake_sv;
        }

        /// <summary>
        /// Sets HRU group for which storage output files are generated
        /// </summary>
        /// <param name="outputGroup">
        /// The HRU group for which storage output files are generated.
        /// </param>
        public void SetOutputGroup(HRUGroup outputGroup)
        {
            _pOutputGroup = outputGroup;
        }

        /// <summary>
        /// Sets Ensemble mode for model
        /// </summary>
        /// <param name="ensemble">
        /// The Ensemble instance.
        /// </param>
        public void SetEnsembleMode(Ensemble ensemble)
        {
            _pEnsemble = ensemble;
        }

        /// <summary>
        /// Sets demand optimizer
        /// </summary>
        /// <param name="demandOptimizer">
        /// The DemandOptimizer instance.
        /// </param>
        public void AddDemandOptimization(DemandOptimizer demandOptimizer)
        {
            _pDO = demandOptimizer;
        }

        /// <summary>
        /// Sets the PET blend values.
        /// </summary>
        /// <param name="aEv">The array of evaporation methods.</param>
        /// <param name="wts">The array of weights corresponding to the evaporation methods.</param>
        /// <exception cref="ArgumentException">Thrown when the lengths of the input arrays do not match.</exception>
        public void SetPETBlendValues(EvapMethod[] aEv, double[] wts) 
        {
            if(aEv.Length != wts.Length) 
            {
                throw new ArgumentException("PET evaporation method and weight arrays must have same length");
            }
            _PETBlends_type = (EvapMethod[])aEv.Clone();
            _PETBlends_wts = (double[])wts.Clone();
        }

        /// <summary>
        /// Sets the blend types and corresponding weights for the pot melt process.
        /// </summary>
        /// <param name="aPM">An array of blend types to be used in the pot melt process. Each element specifies a blend method for the
        /// corresponding weight.</param>
        /// <param name="wts">An array of weights associated with each blend type. The length must match the number of blend types in
        /// <paramref name="aPM"/>.</param>
        /// <exception cref="ArgumentException">Thrown if <paramref name="aPM"/> and <paramref name="wts"/> do not have the same length.</exception>
        public void SetPotMeltBlendValues(PotmeltMethod[] aPM, double[] wts)
        {
            if (aPM.Length != wts.Length)
            {
                throw new ArgumentException("PET blend type and weight arrays must have same length");
            }
            _PotMeltBlends_type = (PotmeltMethod[])aPM.Clone();
            _PotMeltBlends_wts = (double[])wts.Clone();
        }

        /// <summary>
        /// Gets basin blended forcing number of weighted groups.
        /// </summary>
        /// <param name="label">
        /// property identifier.
        /// </param>
        /// <returns>
        /// number of blended weights of basin corresponding to label.
        /// </returns>
        /// <exception cref="ArgumentException"></exception>
        public int GetBlendedForcingsNumWeights(string label)
        {
            string label_n = label.ToUpperInvariant();
            if(label_n == "PET_BLEND_WTS") 
            { 
                return _PETBlends_wts?.Length ?? 0; 
            }
            else if (label_n == "POTMELT_BLEND_WTS") 
            { 
                return _PotMeltBlends_wts?.Length ?? 0; 
            }
            else
            {
                throw new ArgumentException("unrecognized blend type");
            }
        }

        /// <summary>
        /// Removes all custom outputs (For FEWS override)
        /// </summary>
        public void DeleteCustomOutputs()
        {
            _pCustomOutputs.Clear();
            _nCustomOutputs = 0;
        }

        /// <summary>
        /// Sets number of layers used to simulate snowpack.
        /// </summary>
        /// <param name="nLayers">The number of snow layers to set. Must be zero or greater.</param>
        /// <exception cref="ArgumentOutOfRangeException">Thrown when <paramref name="nLayers"/> is less than zero.</exception>
        public void SetNumSnowLayers(int nLayers)
        {
            if (nLayers < 0)
            {
                throw new ArgumentOutOfRangeException(nameof(nLayers), "Number of snow layers cannot be negative");
            }
  
            var aSV = new SVType[nLayers];
            var aLev = new int[nLayers];
            for (int m=0;m<nLayers;m++)
            {
                aSV[m]=SVType.SNOW;
                aLev[m]=m;
            }
            AddStateVariables(aSV, aLev);
        }

        /// <summary>
        /// overrides streamflow with observed streamflow
        /// </summary>
        /// <param name="SBID">
        /// Subbasin identifier of basin with observations at outflow
        /// </param>
        public void OverrideStreamflow(long SBID)
        {
            for (int i = 0; i < _nObservedTS; i++)
            {
                if (IsContinuousFlowObs(_pObservedTS[i], SBID))
                {
                    //check for blanks in observation TS
                    bool bad = false;
                    for (int n = 0; n < _pObservedTS[i].GetNumValues(); n++)
                    {
                        if (_pObservedTS[i].GetValue(n) == RAV_BLANK_DATA) { bad = true; break; }
                    }
                    if (bad)
                    {
                        Runtime.WriteWarning("CModel::OverrideStreamflow::cannot override streamflow if there are blanks in observation data", Options.noisy);
                        return;
                    }

                    long downID = GetSubBasinByID(SBID)!.GetDownstreamID();
                    if (downID != DOESNT_EXIST)
                    {
                        //Copy time series of observed flows to new time series
                        string name = $"Inflow_Hydrograph_{SBID}";
                        TimeSeries pObs = _pObservedTS[i];
                        TimeSeries pTS = new TimeSeries(name, pObs);
                        pTS.SetLocID(SBID);

                        //need to shift everything by one interval, since HYDROGRAPHS are stored as period-ending
                        pTS.ShiftInTime(-(pTS.GetInterval()), Options);

                        //add as inflow hydrograph to downstream
                        GetSubBasinByID(downID).AddInflowHydrograph(pTS);
                        GetSubBasinByID(SBID).SetDownstreamID(DOESNT_EXIST);
                        GetSubBasinByID(SBID).SetDownstreamBasin(null);
                        return;
                    }
                    else
                    {
                        Runtime.WriteWarning("CModel::OverrideStreamflow: overriding streamflow at an outlet subbasin has no impact on model operation", Options.noisy);
                    }
                }
            }
        }




        /// <summary>
        /// Returns the LU class corresponding to passed string
        /// </summary>
        /// <remarks>
        /// Converts string (e.g., "AGRICULTURAL" in HRU file) to LU class
        ///  can accept either lultclass index or lultclass tag
        ///  if string is invalid, returns null.
        /// </remarks>
        /// <param name="s">
        /// LU class identifier (tag or index)
        /// </param>
        /// <returns>
        /// LU class corresponding to the passed string, or null if invalid.
        /// </returns>
        public LandUseClass? StringToLUClass(string s)
        {
            int value = -1;
            if (!int.TryParse(s, out value))
            {
                value = -1;
            }
            string s_sup = s.ToUpperInvariant();
            for (int c = 0; c < _nLandUseClasses; c++)
            {
                if (s_sup == _pLandUseClasses[c].GetLanduseName())
                {
                    return this._pLandUseClasses[c];
                }
                else if (value == (c + 1))
                {
                    return this._pLandUseClasses[c];
                }
            }

            return null;
        }

        /// <summary>
        /// Returns the land use  class corresponding to the passed index
        /// </summary>
        /// <param name="index">
        /// LandUse class index
        /// </param>
        /// <returns>
        /// Reference to land use class corresponding to the index.
        /// </returns>
        public LandUseClass GetLanduseClass(int index)
        {
            return _pLandUseClasses[index];
        }

        /// <summary>
        /// Summarize LU class information to screen
        /// </summary>
        public void SummarizeLUClassesToScreen()
        {
            Console.WriteLine("===================");
            Console.WriteLine($"Land Use Class Summary: {_nLandUseClasses} LU/LT classes in database");
            for (int c = 0; c < _nLandUseClasses; c++)
            {
                Console.WriteLine($"-LULT. class \"{_pLandUseClasses[c].GetLanduseName()}\" ");
                Console.WriteLine($"    impermeable: {_pLandUseClasses[c].GetSurfaceStruct().impermeable_frac * 100} %");
                Console.WriteLine($"       forested: {_pLandUseClasses[c].GetSurfaceStruct().forest_coverage * 100} %");
            }
        }


        /// <summary>
        /// Destroy all LU classes
        /// </summary>
        public void DestroyAllLanduseClasses()
        {
            _pLandUseClasses.Clear();
            _nLandUseClasses = 0;
        }


        /// <summary>
        /// Returns the soil class corresponding to passed string
        /// </summary>
        /// <remarks>
        /// Converts string (e.g., "SILT" in HRU file) to soilclass
        /// can accept either soilclass index or soilclass _tag
        /// if string is invalid, returns NULL
        /// </remarks>
        /// <param name="s">Soil class identifier (_tag or index)</param>
        /// <returns>Reference to soil class corresponding to identifier s</returns>
        public SoilClass StringToSoilClass(string s)
        {
            int value = -1;
            if (!int.TryParse(s, out value))
            {
                value = -1;
            }
            string sup = s.ToUpperInvariant();
            for (int c = 0; c < _nAllSoilClasses; c++)
            {
                if (sup == _pAllSoilClasses[c].Tag.ToUpperInvariant())
                {
                    return _pAllSoilClasses[c];
                }
                else if (value == (c + 1)) { return _pAllSoilClasses[c]; }
            }
            return null;
        }

        /// <summary>
        /// Returns the soil class corresponding to the passed index
        /// </summary>
        /// <param name="index">
        /// Soil class index
        /// </param>
        /// <returns>
        /// Reference to soil class corresponding to index
        /// </returns>
        public SoilClass? GetSoilClass(int index)
        {
            if ((index < 0) || (index >= _pAllSoilClasses.Count)) 
            { 
                return null; 
            }
            return _pAllSoilClasses[index];
        }

        /// <summary>
        /// Return number of soil classes
        /// </summary>
        /// <returns>The number of soil classes</returns>
        public int GetNumSoilClasses()
        {
            return _pAllSoilClasses.Count;
        }

        /// <summary>
        /// Adds a soil class to the model
        /// </summary>
        /// <param name="soilClass">
        /// The soil class to be added to the model. 
        /// </param>
        public void AddSoilClass(SoilClass soilClass)
        {
            _pAllSoilClasses.Add(soilClass);
            _nAllSoilClasses++;
        }

        public void SummarizeSoilClassesToScreen()
        {
            Console.WriteLine( "===================" );
            Console.WriteLine($"Soil Class Summary:{_nAllSoilClasses} soils in database");
            for (int c = 0; c < _nAllSoilClasses; c++)
            {
                Console.WriteLine($"-Soil class \"{_pAllSoilClasses[c].Tag}\" ");
                Console.WriteLine($"       %sand: {_pAllSoilClasses[c].Soil._sandContent}");
                Console.WriteLine($"       %clay: {_pAllSoilClasses[c].Soil._clayContent}");
                Console.WriteLine($"    %organic: {_pAllSoilClasses[c].Soil._organicContent}");
            }
        }


        /// <summary>
        /// Remove all soil classes from the model.
        /// </summary>
        public void DestroyAllSoilClasses()
        {
            _pAllSoilClasses.Clear();
            _nAllSoilClasses = 0;
        }


        /// <summary>
        /// Returns the vegetation class corresponding to passed string
        /// </summary>
        /// <param name="s">
        /// Vegetation class identifier (tag or index)
        /// </param>
        /// <returns>
        /// Reference to vegetation class corresponding to identifier s
        /// </returns>
        public VegetationClass? StringToVegClass(string s)
        {
            int value = -1;
            if (!int.TryParse(s, out value))
            {
                value = -1;
            }
            string sup = s.ToUpperInvariant();
            var count = _pAllVegClasses.Count;
            for (int c = 0; c < count; c++)
            {
                if (sup == _pAllVegClasses[c].GetVegetationName())
                {
                    return _pAllVegClasses[c];
                }
                else if (value == (c + 1))
                {
                    return _pAllVegClasses[c];
                }
            }
            return null;
        }

        /// <summary>
        /// Returns the vegetation class corresponding to the passed index
        /// </summary>
        /// <param name="index"></param>
        /// <returns>
        /// Reference to vegetation class corresponding to index.
        /// </returns>
        public VegetationClass? GetVegClass(int index)
        {
            if ((index < 0) || (index >= _numVegClasses)) 
            { 
                return null; 
            }
            return _pAllVegClasses[index];
        }

        /// <summary>
        /// Return the number of vegetation classes.
        /// </summary>
        /// <returns>
        /// The number of vegetation classes.
        /// </returns>
        public int GetNumVegClasses()
        {
            return _pAllVegClasses.Count;
        }

        /// <summary>
        /// Adds a vegetation to the model.
        /// </summary>
        /// <param name="vegetationClass">
        /// The vegetation class to add.
        /// </param>
        public void AddVegClass(VegetationClass vegetationClass)
        {
            _pAllVegClasses.Add(vegetationClass);
            _numVegClasses++;
        }

        /// <summary>
        /// Summarize vegetation class information to screen
        /// </summary>
        public void SummarizeVegClassesToScreen()
        {
            Console.WriteLine("===================");
            Console.WriteLine($"Vegetation Class Summary: {_numVegClasses} vegetation classes in database");
            for (int c = 0; c < _numVegClasses; c++)
            {
                Console.WriteLine($"-Veg. class \"{_pAllVegClasses[c].GetVegetationName()}\" ");
                Console.WriteLine($"    max. height: {_pAllVegClasses[c].GetVegetationStruct().max_height} m");
                Console.WriteLine($"       max. LAI: {_pAllVegClasses[c].GetVegetationStruct().max_LAI}");
                Console.WriteLine($"   max. conduct: {_pAllVegClasses[c].GetVegetationStruct().max_leaf_cond} mm/s");
                Console.WriteLine($"         albedo: {_pAllVegClasses[c].GetVegetationStruct().albedo}");
            }
        }

        /// <summary>
        /// Removes all vegetation class entries and resets the vegetation class count to zero.
        /// </summary>
        public void DestroyAllVegClasses()
        {
            _pAllVegClasses.Clear();
            _numVegClasses = 0;
        }


        /// <summary>
        /// Returns the terrain class corresponding to passed string.
        /// </summary>
        /// <remarks>
        /// Converts string (e.g., "HUMMOCKY" in HRU file) to Terrain class
        ///  can accept either terrainclass index or terrainclass tag
        ///  if string is invalid, returns NULL
        /// </remarks>
        /// <param name="s">
        /// The terrain class identifier (tag or index).
        /// </param>
        /// <returns>
        /// Reference to terrain class corresponding to identifier s.
        /// </returns>
        public TerrainClass? StringToTerrainClass(string s)
        {
            int value = -1;
            if (!int.TryParse(s, out value))
            {
                value = -1;
            }
            string sup = s.ToUpperInvariant();
            var count = _pAllTerrainClasses.Count;
            for (int c = 0; c < count; c++)
            {
                if (sup == _pAllTerrainClasses[c].Tag)
                {
                    return _pAllTerrainClasses[c];
                }
                else if (value == (c + 1))
                {
                    return _pAllTerrainClasses[c];
                }
            }
            return null;
        }

        /// <summary>
        /// Gets the total number of terrain classes currently available.
        /// </summary>
        /// <returns>The number of terrain classes. Returns 0 if no terrain classes are present.</returns>
        public int GetNumTerrainClasses()
        {
            return _pAllTerrainClasses.Count;
        }

        /// <summary>
        /// Retrieves the terrain class at the specified index, if available.
        /// </summary>
        /// <param name="index">The zero-based index of the terrain class to retrieve. Must be greater than or equal to 0 and less than the
        /// total number of terrain classes.</param>
        /// <returns>The terrain class at the specified index, or null if the index is out of range.</returns>
        public TerrainClass? GetTerrainClass(int index)
        {
            if ((index < 0) || (index >= _pAllTerrainClasses.Count))
            {
                return null;
            }
            return _pAllTerrainClasses[index];
        }

        /// <summary>
        /// Adds a terrain class to the collection of available terrain classes.
        /// </summary>
        /// <param name="terrainClass">The terrain class to add to the collection. Cannot be null.</param>
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="terrainClass"/> is null.</exception>
        public void AddTerrainClass(TerrainClass terrainClass)
        {
            if (terrainClass == null)
            {
                throw new ArgumentNullException(nameof(terrainClass), "Terrain class cannot be null");
            }
            _pAllTerrainClasses.Add(terrainClass);
        }

        /// <summary>
        /// Summarize terrain class information to screen
        /// </summary>
        public void SummarizeTerrainClassesToScreen()
        {
            Console.WriteLine("===================");
            Console.WriteLine($"Terrain Class Summary: {_pAllTerrainClasses.Count} terrain classes in database");
            foreach (var terrainClass in _pAllTerrainClasses)
            {
                Console.WriteLine($"-Terrain. class \"{terrainClass.Tag}\" ");
                Console.WriteLine($"    drainage density: {terrainClass.Terrain.drainage_density}");
            }
        }

        /// <summary>
        /// Removes all terrain class entries from the collection, resetting its state.
        /// </summary>
        public void DestroyAllTerrainClasses()
        {
            _pAllTerrainClasses.Clear();
            _nAllTerrainClasses = 0;
        }

        /// <summary>
        /// Adds a soil profile to the collection of managed soil profiles.
        /// </summary>
        /// <param name="soilProfile">The soil profile to add to the collection. Cannot be null.</param>
        public void AddSoilProfile(SoilProfile soilProfile)
        {
            ArgumentNullException.ThrowIfNull(soilProfile);
            _pAllSoilProfiles.Add(soilProfile);
            _nAllSoilProfiles++;
        }

        /// <summary>
        /// Writes a summary of all soil profiles to the standard output.
        /// </summary>
        public void SummarizeSoilProfilesToScreen()
        {
            Console.WriteLine("===================");
            Console.WriteLine($"Soil Profile Summary: {_nAllSoilProfiles} soils in database");
            for (int p = 0; p < _nAllSoilProfiles; p++)
            {
                Console.WriteLine($"-Soil profile \"{_pAllSoilProfiles[p].Tag}\" ");
                Console.WriteLine($"    #horizons: {_pAllSoilProfiles[p].GetNumHorizons()}");
                for (int m = 0; m < _pAllSoilProfiles[p].GetNumHorizons(); m++)
                {
                    Console.WriteLine($"      -layer #{m + 1}: {_pAllSoilProfiles[p].GetSoilTag(m)} (thickness: {_pAllSoilProfiles[p].GetThickness(m)} m)");
                }
            }
        }

        /// <summary>
        /// Converts the specified string to a corresponding soil profile, if a match is found.
        /// </summary>
        /// <remarks>The method attempts to match the input string to a soil profile by comparing it to
        /// profile tags (case-insensitive) or by interpreting it as a 1-based index into the list of available
        /// profiles.</remarks>
        /// <param name="s">The string representation of the soil profile to convert. This can be a profile tag (case-insensitive) or a
        /// 1-based index as a string.</param>
        /// <returns>A <see cref="SoilProfile"/> object that matches the specified string, or <see langword="null"/> if no
        /// matching profile is found.</returns>
        public SoilProfile? StringToSoilProfile(string s)
        {
            int value = -1;
            if (!int.TryParse(s, out value))
            {
                value = -1;
            }
            string sup = s.ToUpperInvariant();
            var count = _pAllSoilProfiles.Count;
            for (int c = 0; c < count; c++)
            {
                if (sup == _pAllSoilProfiles[c].Tag)
                {
                    return _pAllSoilProfiles[c];
                }
                else if (value == (c + 1))
                {
                    return _pAllSoilProfiles[c];
                }
            }
            return null;
        }

        
        /// <summary>
        /// Gets the number of soil profiles currently available.
        /// </summary>
        /// <returns>The total number of soil profiles. Returns 0 if no soil profiles are present.</returns>
        public int GetNumSoilProfiles()
        {
            return _pAllSoilProfiles.Count;
        }

        /// <summary>
        /// Removes all soil profiles from the model.
        /// </summary>
        public void DestroyAllSoilProfiles()
        {
            _pAllSoilProfiles.Clear();
            _nAllSoilProfiles = 0;
        }

        /// <summary>
        /// Converts string (e.g., "X2305" in Basin file) to channel profile
        /// </summary>
        /// <param name="s">The string representation of the channel cross-section to convert. This can be a profile tag (case-insensitive) or a 1-based index as a string.</param>
        /// <returns>A <see cref="ChannelXSect"/> object that matches the specified string, or <see langword="null"/> if no matching profile is found.</returns>
        public ChannelXSect? StringToChannelXSect(string s)
        {
            int value = -1;
            if (!int.TryParse(s, out value))
            {
                value = -1;
            }
            string sup = s.ToUpperInvariant();
            var count = _pAllChannelXSects.Count;
            for (int c = 0; c < count; c++)
            {
                if (sup == _pAllChannelXSects[c].Name)
                {
                    return _pAllChannelXSects[c];
                }
                else if (value == (c + 1))
                {
                    return _pAllChannelXSects[c];
                }
            }
            return null;
        }

        /// <summary>
        /// Returns the number of channel cross-sections currently available.
        /// </summary>
        /// <returns>The total count of channel cross-sections. The value is zero if no cross-sections are present.</returns>
        public int GetNumChannelXSects()
        {
            return _pAllChannelXSects.Count;
        }

        /// <summary>
        /// Adds a channel cross-section to the collection of channel cross-sections managed by this instance.
        /// </summary>
        /// <param name="pXSect">The channel cross-section to add. Cannot be null.</param>
        public void AddChannelXSect(ChannelXSect pXSect)
        {
            ArgumentNullException.ThrowIfNull(pXSect);
            _pAllChannelXSects.Add(pXSect);
            _nAllChannelXSects++;
        }

        /// <summary>
        /// Summarize profile information to screen
        /// </summary>
        public void SummarizeChannelXSectToScreen()
        {
            Console.WriteLine("===================");
            Console.WriteLine("Channel Profile Summary:" + this._nAllChannelXSects + " profiles in database");
            for (int p = 0; p < _pAllChannelXSects.Count; p++)
            {
                Console.WriteLine("-Channel profile \"" + this._pAllChannelXSects[p].Name + "\" ");
                Console.WriteLine("           slope: " + this._pAllChannelXSects[p].Bedslope);
            }
        }

        /// <summary>
        /// Removes all channel cross-section entries from the collection and resets the count to zero.
        /// </summary>
        /// <remarks>After calling this method, the collection of channel cross-sections will be empty and
        /// the count will be reset. This operation is irreversible; any previously stored channel cross-section data
        /// will be lost.</remarks>
        public void DestroyAllChannelXSections()
        {
            _pAllChannelXSects.Clear();
            _nAllChannelXSects = 0;
        }

        /// <summary>
        /// Checks for duplicate channel cross-section names and issues a warning if any duplicates are found.
        /// </summary>
        /// <remarks>This method scans the collection of channel cross-sections and writes a warning for
        /// each pair of items that share the same name. No exceptions are thrown; duplicates are reported via the
        /// runtime warning mechanism.</remarks>
        public void CheckForChannelXSectsDuplicates()
        {
            var count = _pAllChannelXSects.Count;
            for (int p = 0; p < count; p++)
            {
                for (int pp = 0; pp < p; pp++)
                {
                    if (_pAllChannelXSects[p].Name == _pAllChannelXSects[pp].Name)
                    {
                        string warn = "CheckForChannelXSectsDuplicates: found duplicated channel name: " + _pAllChannelXSects[p].Name;
                        Runtime.WriteWarning(warn, Options.noisy);
                    }
                }
            }
        }





    }




}


