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
        List<HydroUnit> _pHydroUnits;

        /// <summary>
        /// number of HRU groups in model
        /// </summary>
        int _nHRUGroups;
        List<HRUGroup> _pHRUGroups;

        /// <summary>
        /// number of Subbasin groups in model
        /// </summary>
        int _nSBGroups;
        List<SubbasinGroup> _pSBGroups;

        /// <summary>
        /// number of subbasins
        /// </summary>
        int _nSubBasins;
        List<SubBasin> _pSubBasins;
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
        List<HydroProcess> _pProcesses;
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
        List<Gauge> _pGauges;
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
        List<ForcingGrid> _pForcingGrids;

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
        ModelParameters _pGlobalParams;

        /// <summary>
        /// number of transient parameters
        /// </summary>
        int _nTransParams;
        /// <summary>
        /// Transient parameters with time series
        /// </summary>
        TransientParam[] _pTransParams;
        /// <summary>
        /// number of HRU Group class changes
        /// </summary>
        int _nClassChanges;  
        List<ClassChange> _pClassChanges;
        /// <summary>
        /// number of local parameter overrides
        /// </summary>
        int _nParamOverrides;
        /// <summary>
        /// local parameter overrides
        /// </summary>
        List<ParameterOverride> _pParamOverrides;

        /// <summary>
        /// corresponding groundwater model
        /// </summary>
        GroundwaterModel _pGWModel;
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
        List<TimeSeries> _pObservedTS;
        /// <summary>
        /// modeled time series corresponding to observations [size: _nObservedTS]
        /// </summary>
        List<TimeSeries> _pModeledTS;
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
        List<TimeSeries> _pObsWeightTS;
        /// <summary>
        /// number of observation weight time series
        /// </summary>
        int _nObsWeightTS;

        /// <summary>
        /// diagnostics to be calculated [size: _nDiagnostics]
        /// </summary>
        List<DiagnosticType> _pDiagnostics;
        /// <summary>
        /// number of diagnostics to be calculated comparing obs. vs modeled
        /// </summary>
        int _nDiagnostics;
        /// <summary>
        /// diagnostic periods [size _nDiagPeriods]
        /// </summary>
        DiagPeriod[] _pDiagPeriods;
        /// <summary>
        /// number of diagnostic periods
        /// </summary>
        int _nDiagPeriods;
        /// <summary>
        /// aggregate diagnostic structures [size: _nAggDiagnostics]
        /// </summary>
        AggDiag[] _pAggDiagnostics;
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
        List<ForcePerturb> _pPerturbations;
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
        List<CustomOutput> _pCustomOutputs;
        /// <summary>
        /// Nuber of custom output objects
        /// </summary>
        int _nCustomOutputs;
        /// <summary>
        /// custom table objects [size:_nCustomTables]
        /// </summary>
        List<CustomTable> _pCustomTables;
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
        /// array of model major output times (LOCAL times at which full solution is written)
        /// </summary>
        double[] _aOutputTimes;
        /// <summary>
        /// size of array of model major output times
        /// </summary>
        int _nOutputTimes;
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
        List<SoilClass> _pAllSoilClasses;
        int _nAllSoilClasses;
        List<VegetationClass> _pAllVegClasses;
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
    }




}
