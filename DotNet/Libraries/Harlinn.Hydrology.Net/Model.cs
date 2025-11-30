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
using Serilog;
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

        /// <summary>
        /// Returns index of state variable type passed
        /// </summary>
        /// <param name="type">
        /// State variable type
        /// </param>
        /// <returns>
        /// Index which corresponds to the state variable type passed, if it exists; DOESNT_EXIST (-1) otherwise.
        /// </returns>
        /// <remarks>
        /// should only be used for state variable types without multiple levels; issues for soils, e.g.
        /// </remarks>
        public int GetStateVarIndex(SVType type)
        {
            return _aStateVarIndices[(int)(type),0];
        }

        /// <summary>
        /// Checks if state variable passed exists in model
        /// </summary>
        /// <param name="type">
        /// State variable type
        /// </param>
        /// <returns>
        /// bool indicating whether state variable exists in model
        /// </returns>
        public bool StateVarExists(SVType type)
        {
            return (GetStateVarIndex(type) != DOESNT_EXIST);
        }


        int GetForcingGridIndexFromType(ForcingType typ)
        {
            for (int f=0;f<_nForcingGrids;f++)
            {
                if (typ==_pForcingGrids[f].GetForcingType())
                {
                    return f;
                }
            }
            return DOESNT_EXIST;
        }

        public bool ForcingGridIsAvailable(ForcingType ftype)
        {
            return (GetForcingGridIndexFromType(ftype) != DOESNT_EXIST);
        }

        ///

        void GenerateGaugeWeights(ForcingType forcing, Options options, out double[,] aWts)
        {
            int k, g;
            bool[] has_data = new bool[_nGauges];
            Location xyh, xyg;

            // allocate memory

            aWts = new double[_nHydroUnits, _nGauges];

            int nGaugesWithData = 0;
            for (g = 0; g < _nGauges; g++)
            {
                has_data[g] = _pGauges[g].TimeSeriesExists(forcing);
                if (has_data[g])
                {
                    nGaugesWithData++;
                }
            }

            //handle the case that weights are allowed to sum to zero -netCDF is available
            //still need to allocate all zeros
            if (ForcingGridIsAvailable(forcing))
            {
                return;
            }
            if ((forcing == ForcingType.F_TEMP_AVE) && (ForcingGridIsAvailable(ForcingType.F_TEMP_DAILY_MIN)))
            {
                //this is also acceptable
                return;
            }
            if ((forcing == ForcingType.F_TEMP_AVE) && (ForcingGridIsAvailable(ForcingType.F_TEMP_DAILY_AVE)))
            {
                //this is also acceptable
                return;
            }
            if ((forcing == ForcingType.F_PRECIP) && (ForcingGridIsAvailable(ForcingType.F_RAINFALL)))
            {
                //this is also acceptable
                return;
            }

            if (nGaugesWithData == 0)
            {
                Log.Warning("GenerateGaugeWeights: no gauges present with the following data: {:Forcing}", forcing);
                string message = "GenerateGaugeWeights: no gauges present with the following data: " + forcing;
                throw new InvalidOperationException(message);
            }

            switch (options.interpolation)
            {
                case (InterpMethod.INTERP_NEAREST_NEIGHBOR):
                {
                    //w=1.0 for nearest gauge, 0.0 for all others
                    double distmin, dist;
                    int g_min = 0;
                    for (k = 0; k < _nHydroUnits; k++)
                    {
                        xyh = _pHydroUnits[k].GetCentroid();
                        g_min = 0;
                        distmin = ALMOST_INF;
                        for (g = 0; g < _nGauges; g++)
                        {
                            if (has_data[g])
                            {
                                xyg = _pGauges[g].GetLocation();
                                dist = Math.Pow(xyh.UTM_x - xyg.UTM_x, 2) + Math.Pow(xyh.UTM_y - xyg.UTM_y, 2);
                                if (dist < distmin) 
                                { 
                                    distmin = dist; g_min = g; 
                                }
                            }
                            aWts[k,g] = 0.0;
                        }
                        aWts[k,g_min] = 1.0;

                    }
                }
                break;
                case (InterpMethod.INTERP_AVERAGE_ALL):
                {
                    for (k = 0; k < _nHydroUnits; k++)
                    {
                        for (g = 0; g < _nGauges; g++)
                        {
                            if (has_data[g]) 
                            { 
                                aWts[k,g] = 1.0 / (double)(nGaugesWithData); 
                            }
                            else 
                            { 
                                aWts[k,g] = 0.0; 
                            }
                        }
                    }
                }
                break;
                case (InterpMethod.INTERP_INVERSE_DISTANCE):
                {
                    //wt_i = (1/r_i^2) / (sum{1/r_j^2})
                    double dist;
                    double denomsum;
                    const double IDW_POWER = 2.0;
                    int atop_gauge = DOESNT_EXIST;
                    for (k = 0; k < _nHydroUnits; k++)
                    {
                        xyh = _pHydroUnits[k].GetCentroid();
                        atop_gauge = DOESNT_EXIST;
                        denomsum = 0;
                        for (g = 0; g < _nGauges; g++)
                        {
                            if (has_data[g])
                            {
                                xyg = _pGauges[g].GetLocation();
                                dist = Math.Sqrt(Math.Pow(xyh.UTM_x - xyg.UTM_x, 2) + Math.Pow(xyh.UTM_y - xyg.UTM_y, 2));
                                denomsum += Math.Pow(dist, -IDW_POWER);
                                if (dist < REAL_SMALL) 
                                {
                                    //handles limiting case where weight= large number/large number
                                    atop_gauge = g; 
                                }
                            }
                        }

                        for (g = 0; g < _nGauges; g++)
                        {
                            aWts[k,g] = 0.0;
                            if (has_data[g])
                            {
                                xyg = _pGauges[g].GetLocation();
                                dist = Math.Sqrt(Math.Pow(xyh.UTM_x - xyg.UTM_x, 2) + Math.Pow(xyh.UTM_y - xyg.UTM_y, 2));

                                if (atop_gauge != DOESNT_EXIST) 
                                { 
                                    aWts[k,g] = 0.0; 
                                    aWts[k,atop_gauge] = 1.0; 
                                }
                                else 
                                { 
                                    aWts[k,g] = Math.Pow(dist, -IDW_POWER) / denomsum; 
                                }
                            }
                        }
                    }
                }
                break;
                case (InterpMethod.INTERP_INVERSE_DISTANCE_ELEVATION):
                {
                    double dist;
                    double elevh, elevg;
                    double denomsum;
                    const double IDW_POWER = 2.0;
                    int atop_gauge = DOESNT_EXIST;
                    for (k = 0; k < _nHydroUnits; k++)
                    {
                        elevh = _pHydroUnits[k].GetElevation();
                        atop_gauge = DOESNT_EXIST;
                        denomsum = 0;
                        for (g = 0; g < _nGauges; g++)
                        {
                            if (has_data[g])
                            {
                                elevg = _pGauges[g].GetElevation();
                                dist = Math.Abs(elevh - elevg);
                                denomsum += Math.Pow(dist, -IDW_POWER);
                                if (dist < REAL_SMALL) 
                                {
                                    //handles limiting case where weight= large number/large number
                                    atop_gauge = g; 
                                }
                            }
                        }

                        for (g = 0; g < _nGauges; g++)
                        {
                            aWts[k,g] = 0.0;
                            if (has_data[g])
                            {
                                elevg = _pGauges[g].GetElevation();
                                dist = Math.Abs(elevh - elevg);
                                if (atop_gauge != DOESNT_EXIST) 
                                { 
                                    aWts[k,g] = 0.0; 
                                    aWts[k,atop_gauge] = 1.0; 
                                }
                                else 
                                { 
                                    aWts[k,g] = Math.Pow(dist, -IDW_POWER) / denomsum; 
                                }
                            }
                        }
                    }
                }
                break;
                case (InterpMethod.INTERP_FROM_FILE):
                {
                    //format:
                    //:GaugeWeightTable
                    //  nGauges nHydroUnits
                    //  v11 v12 v13 v14 ... v_1,nGauges
                    //  ...
                    //  vN1 vN2 vN3 vN4 ... v_N,nGauges
                    //:EndGaugeWeightTable
                    //ExitGracefullyIf no gauge file

                    /*
                    int Len, line = 0 ;
                    char* s[MAXINPUTITEMS];
                    ifstream INPUT;
                    INPUT.open(Options.interp_file.c_str());
                    if (INPUT.fail())
                    {
                        INPUT.close();
                        string errString = "GenerateGaugeWeights:: Cannot find gauge weighting file " + Options.interp_file;
                        ExitGracefully(errString.c_str(), BAD_DATA);
                    }
                    else
                    {
                        CParser* p = new CParser(INPUT, Options.interp_file, line);
                        bool done(false);
                        while (!done)
                        {
                            p->Tokenize(s, Len);
                            if (IsComment(s[0], Len)) { }
                            else if (!strcmp(s[0], ":GaugeWeightTable")) { }
                            else if (Len >= 2)
                            {
                                ExitGracefullyIf(s_to_i(s[0]) != _nGauges,
                                                 "GenerateGaugeWeights: the gauge weighting file has an improper number of gauges specified", BAD_DATA);
                                ExitGracefullyIf(s_to_i(s[1]) != _nHydroUnits,
                                                 "GenerateGaugeWeights: the gauge weighting file has an improper number of HRUs specified", BAD_DATA);
                                done = true;
                            }
                        }
                        int junk;
                        p->Parse2DArray_dbl(aWts, _nHydroUnits, _nGauges, junk);

                        for (k = 0; k < _nHydroUnits; k++)
                        {
                            double sum = 0;
                            for (g = 0; g < _nGauges; g++)
                            {
                                sum += aWts[k][g];
                            }
                            if (fabs(sum - 1.0) > 1e-4)
                            {
                                ExitGracefully("GenerateGaugeWeights: INTERP_FROM_FILE: user-specified weights for gauge don't add up to 1.0", BAD_DATA);
                            }
                        }
                        INPUT.close();
                        delete p;
                    }
                    */
                    
                }
                break;
                default:
                {
                    throw new InvalidOperationException("Invalid interpolation method");
                }
                break;
            }
            /*
            //Override weights where specified
            for (k = 0; k < _nHydroUnits; k++)
            {
                if (_pHydroUnits[k]->GetSpecifiedGaugeIndex() != DOESNT_EXIST)
                {
                    for (g = 0; g < _nGauges; g++)
                    {
                        aWts[k][g] = 0.0;
                    }
                    g = _pHydroUnits[k]->GetSpecifiedGaugeIndex();
                    aWts[k][g] = 1.0;
                }
            }

            //check quality - weights for each HRU should add to 1
            double sum;
            for (k = 0; k < _nHydroUnits; k++)
            {
                sum = 0.0;
                for (g = 0; g < _nGauges; g++) { sum += aWts[k][g]; }

                ExitGracefullyIf((fabs(sum - 1.0) > REAL_SMALL) && (INTERP_FROM_FILE) && (_nGauges > 1),
                                 "GenerateGaugeWeights: Bad weighting scheme- weights for each HRU must sum to 1", BAD_DATA);
                ExitGracefullyIf((fabs(sum - 1.0) > REAL_SMALL) && !(INTERP_FROM_FILE) && (_nGauges > 1),
                                 "GenerateGaugeWeights: Bad weighting scheme- weights for each HRU must sum to 1", RUNTIME_ERR);
            }

            if (Options.write_interp_wts)
            {
                ofstream WTS;
                string tmpFilename = FilenamePrepare("InterpolationWeights.csv", Options);
                WTS.open(tmpFilename.c_str(), ios::app);
                WTS << "Weights for " << ForcingToString(forcing) << "--------------------------------------" << endl;
                WTS << "HRU index (k), HRU ID";
                for (g = 0; g < _nGauges; g++) { WTS << "," << _pGauges[g]->GetName(); }
                WTS << endl;
                for (k = 0; k < _nHydroUnits; k++)
                {
                    WTS << k << "," << _pHydroUnits[k]->GetHRUID();

                    for (g = 0; g < _nGauges; g++) { WTS << "," << aWts[k][g]; }
                    WTS << endl;
                }
                WTS.close();
            }

            has_data;
            */
        }

        internal int GetNumSubBasins()
        {
            throw new NotImplementedException();
        }

        internal double GetConcentration(int global_k, int i)
        {
            throw new NotImplementedException();
        }

        internal double GetCumulativeFlux(int global_k, int i, bool to)
        {
            throw new NotImplementedException();
        }

        internal double GetCumulFluxBetween(int global_k, int iFrom, int iTo)
        {
            throw new NotImplementedException();
        }

        public ModelParameters GetGlobalParams()
        {
            return _pGlobalParams;
        }

        public Options GetOptions()
        {
            return _pOptStruct;
        }

        internal int GetStateVarIndex(SVType sOIL, int v)
        {
            throw new NotImplementedException();
        }

        internal SVType GetStateVarType(int v)
        {
            throw new NotImplementedException();
        }

        internal int GetStateVarLayer(int v)
        {
            throw new NotImplementedException();
        }

        internal int GetLakeStorageIndex()
        {
            throw new NotImplementedException();
        }

        public Options Options => _pOptStruct;

    }




}
