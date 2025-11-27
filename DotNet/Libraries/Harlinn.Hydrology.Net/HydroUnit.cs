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
    /// <summary>
    /// Models a single contiguous portion of watershed with homogeneous 
    /// land use/land type and homogeneous properties
    /// </summary>
    public class HydroUnit
    {
        Model _pModel;

        /// <summary>
        /// Unique HRU identifier
        /// </summary>
        long _ID;
        /// <summary>
        /// Global model index as stored in CModel array (can/will be different from ID)
        /// </summary>
        int _global_k;
        /// <summary>
        /// contributing drainage area for HydroUnit [km^2]
        /// </summary>
        double _Area;
        /// <summary>
        /// global index p (not ID!) of subbasin this HRU is in
        /// </summary>
        int _SubbasinInd;
        /// <summary>
        /// centroid of HRU
        /// </summary>
        Location _Centroid;
        /// <summary>
        /// Standard, Lake, Rock, Glacier, etc...
        /// </summary>
        HRUType _HRUType;
        /// <summary>
        /// true if processes are not simulated for this HRU
        /// </summary>
        bool _Disabled;
        /// <summary>
        /// true if HRU is linked to Reservoir
        /// </summary>
        bool _res_linked;

        // Model State variables:

        /// <summary>
        /// Array of *current value* of state variable i with size CModel::nStateVars [mm] for water storage, permafrost depth, snow depth, [MJ/m^2] for energy storage
        /// </summary>
        double[] _aStateVar;

        // Model Forcing functions:
        /// <summary>
        /// *current values* of forcing functions for time step (precip, temp, etc.)
        /// </summary>
        Force _Forcings;

        // property structures (from soil, veg, aq, surface classes, class-specific)

        /// <summary>
        /// average elevation of HRU [masl]
        /// </summary>
        double _AvgElevation;

        /// <summary>
        /// average terrain aspect [rad counterclockwise from north]
        /// </summary>
        double _AvgAspect;

        /// <summary>
        /// average terrain slope [rad]
        /// </summary>
        double _AvgSlope;

        /// <summary>
        /// latitude of centroid [rad]
        /// </summary>
        double _LatRad;
        /// <summary>
        /// equivalent latitude for slope/aspect  [rad]
        /// </summary>
        double _LatEq;
        /// <summary>
        /// effective solar noon correction for slope [days]
        /// </summary>
        double _SolarNoon;

        /// <summary>
        /// HRU-specific precipitation correction factor
        /// </summary>
        double _PrecipMult;
        /// <summary>
        /// index of met gauge to be used regardless of interpolation scheme (or DOESNT_EXIST, by default)
        /// </summary>
        int _SpecifiedGaugeIdx;

        /// <summary>
        /// array of pointers to structures with profile soil properties
        /// </summary>
        Soil[] _pSoil = new Soil[MAX_SOILLAYERS];

        /// <summary>
        /// vegetation properties
        /// </summary>
        Vegetation _pVeg;
        /// <summary>
        /// land use/land type properties
        /// </summary>
        Surface _pSurface;
        /// <summary>
        /// terrain properties
        /// </summary>
        Terrain _pTerrain;

        // variable property structures (locally stored, HRU-specific)

        /// <summary>
        /// soil layer thicknesses [m]
        /// </summary>
        double[] aThickness = new double[MAX_SOILLAYERS];


        /// <summary>
        /// derived vegetation properties
        /// </summary>
        VegetationVariable _VegVar;

        public long GetHRUID() 
        { 
            return _ID;          
        }
        public int GetGlobalIndex() 
        { 
            return _global_k;    
        }
        public bool IsEnabled => !_Disabled;
        public Location GetCentroid() 
        { 
            return _Centroid;    
        }
        public Location Centroid => _Centroid;
        public double GetArea() 
        { 
            return _Area;        
        }
        public double Area => _Area;
        public int GetSubBasinIndex() 
        { 
            return _SubbasinInd; 
        }
        public int SubBasinIndex => _SubbasinInd;
        public HRUType GetHRUType() 
        { 
            return _HRUType;
        }
        public bool IsLake => (_HRUType== HRUType.HRU_LAKE);
        public bool IsLinkedToReservoir => _res_linked;

        public double GetStateVarValue(int i) 
        { 
            return _aStateVar[i]; 
        }
        public double GetConcentration(int i) 
        { 
            return _pModel.GetConcentration(_global_k, i); 
        }
        public double[] GetStateVarArray()
        {
            return _aStateVar;
        }
        public double[] StateVariables => _aStateVar;

        public double GetElevation()
        {
            return _AvgElevation;
        }
        public double Elevation => _AvgElevation;
        public double GetSlope()
        {
            return _AvgSlope;
        }
        public double Slope => _AvgSlope;

        public double GetAspect()
        {
            return _AvgAspect;
        }
        public double Aspect => _AvgAspect;

        public double GetLatRad()
        {
            return _LatRad;
        }
        public double GetLatEq()
        {
            return _LatEq;
        }
        public double GetSolarNoon()
        {
            return _SolarNoon;
        }

        public double GetPrecipMultiplier()
        {
            return _PrecipMult;
        }
        public int GetSpecifiedGaugeIndex()
        {
            return _SpecifiedGaugeIdx;
        }

        public Soil GetSoilProps(int m)
        {
            return _pSoil[m];
        }
        public double GetSoilThickness(int m)
        {
            return aThickness[m] * MM_PER_METER;
        }
        public double GetSoilCapacity(int m)
        {
            return aThickness[m] * MM_PER_METER * _pSoil[m].CapRatio;
        }
        public double GetSoilTensionStorageCapacity(int m)
        {
            double result = aThickness[m] * MM_PER_METER * _pSoil[m].CapRatio * (_pSoil[m].FieldCapacity - _pSoil[m].WiltingPointSaturation);
            if (result < -REAL_SMALL)
            {
                Runtime.ExitGracefully("Wilting point saturation is greater than field capacity for one or more soil classes, leading to negative tension storage", ExitCode.BAD_DATA);
            }
            return result;
        }

        public Vegetation GetVegetationProps()
        {
            return _pVeg;
        }
        public VegetationVariable GetVegVarProps()
        {
            return _VegVar;
        }
        public Surface GetSurfaceProps()
        {
            return _pSurface;
        }
        public Terrain GetTerrainProps()
        {
            return _pTerrain;
        }


        public Force GetForcingFunctions()
        {
            return _Forcings;
        }
        public double GetForcing(ForcingType forcingType)
        {
            return _Forcings[forcingType];
        }


        public double GetCumulFlux(int i, bool to)
        {
            return _pModel.GetCumulativeFlux(_global_k, i, to);
        }
        public double GetCumulFluxBet(int iFrom, int iTo)
        {
            return _pModel.GetCumulFluxBetween(_global_k, iFrom, iTo);
        }

        public double GetStateVarMax(int i, double[] curr_state_var, Options options, bool ignorevar = false)
        { 
            throw new NotImplementedException();
        }


        // specialized state variable accessors
        public double GetSnowAlbedo()
        {
            int snowAlbedoIndex = _pModel.GetStateVarIndex(SVType.SNOW_ALBEDO);
            
            if (snowAlbedoIndex == DOESNT_EXIST) 
            { 
                return DEFAULT_SNOW_ALBEDO; 
            }
            else 
            { 
                return GetStateVarValue(snowAlbedoIndex); 
            }
        }
        public double GetSnowTemperature()
        {
            int iSnTemp = _pModel.GetStateVarIndex(SVType.SNOW_TEMP);
            if (iSnTemp == DOESNT_EXIST)
            {
                double sntmp = _pModel.GetGlobalParams().snow_temperature;
                if (sntmp == NOT_NEEDED_AUTO)
                {
                    return 0.0;
                }
                return sntmp;
            }
            else
            {
                return GetStateVarValue(iSnTemp);
            }
        }
        public double GetSnowSWE()
        {
            int iSnow = _pModel.GetStateVarIndex(SVType.SNOW);
            if (iSnow == DOESNT_EXIST) 
            { 
                return 0.0; 
            }
            else 
            { 
                return GetStateVarValue(iSnow); 
            }
        }
        public double GetSnowCover()
        {
            var options = _pModel.Options;

            int iSnFrac = _pModel.GetStateVarIndex(SVType.SNOW_COVER);
            int iSnow = _pModel.GetStateVarIndex(SVType.SNOW);

            if (iSnow == DOESNT_EXIST) 
            { 
                return 0.0; 
            }
            double SWE = GetStateVarValue(iSnow);

            if (iSnFrac != DOESNT_EXIST)
            { 
                //snow cover explicitly simulated
                return GetStateVarValue(iSnFrac);
            }
            else  
            {
                //snowcover depletion curves
                if (options.snow_depletion == SnowcovMethod.SNOWCOV_NONE)
                {
                    if (GetSnowSWE() < NEGLIGBLE_SNOW) { return 0.0; }
                    else { return 1.0; }
                }
                else if (options.snow_depletion == SnowcovMethod.SNOWCOV_LINEAR)
                {
                    double snowthresh = 200;
                    return Math.Min(Math.Max(SWE, 0.0) / snowthresh, 1.0);
                }
            }
            return 0.0;
        }
        public double GetSurfaceTemperature()
        {
            double snow_cover = GetSnowCover();
            double snow_temp = GetSnowTemperature();
            double ground_temp = _Forcings.temp_ave; //temp - more proper methods

            if (_HRUType == HRUType.HRU_GLACIER)
            {
                ground_temp = FREEZING_TEMP;
            }

            return (1 - snow_cover) * ground_temp + snow_cover * snow_temp;
        }
        public double GetTotalAlbedo(bool subcanopy)
        {
            double veg_albedo, land_albedo = 0.0;

            double snow_albedo = GetSnowAlbedo();
            double snow_cover = GetSnowCover();
            double svf = _VegVar.skyview_fact;
            double Fc = _pSurface.forest_coverage;

            if (_HRUType == HRUType.HRU_STANDARD)
            {
                int iTopSoil = _pModel.GetStateVarIndex(SVType.SOIL, 0);
                double soil_sat = Math.Max(Math.Min(_aStateVar[iTopSoil] / GetSoilCapacity(0), 1.0), 0.0);
                land_albedo = (soil_sat) * _pSoil[0].albedo_wet + (1.0 - soil_sat) * _pSoil[0].albedo_dry;
            }
            else if (_HRUType == HRUType.HRU_GLACIER)
            {
                land_albedo = 0.4;
            }
            else if (_HRUType == HRUType.HRU_LAKE)
            {
                land_albedo = 0.1;
            }
            else if (_HRUType == HRUType.HRU_WATER)
            {
                land_albedo = 0.1;
            }
            else if (_HRUType == HRUType.HRU_ROCK)
            {
                land_albedo = 0.35;
            }
            else if (_HRUType == HRUType.HRU_WETLAND)
            {
                land_albedo = 0.15;
            }
            land_albedo = (snow_cover) * snow_albedo + (1.0 - snow_cover) * land_albedo;

            if (subcanopy)
            {
                return land_albedo;
            }
            else 
            {
            // above canopy
            veg_albedo = _pVeg.albedo;

                if (veg_albedo < 0) 
                { 
                    veg_albedo = 0.14; 
                }
                if (svf > 1.0) 
                { 
                    svf = 0.0; 
                }
                if (land_albedo < 0) 
                { 
                    land_albedo = 0.3; 
                }

                return (1.0 - svf) * (Fc) * veg_albedo + ((svf) * (Fc) + (1.0 - Fc)) * land_albedo;
            }
        }

        public double GetSnowDepth()
        {
            int iSnow = _pModel.GetStateVarIndex(SVType.SNOW);
            if (iSnow == DOESNT_EXIST) 
            { 
                return 0.0; 
            }

            int iSnowDep = _pModel.GetStateVarIndex(SVType.SNOW_DEPTH);
            if (iSnowDep != DOESNT_EXIST) 
            { 
                return GetStateVarValue(iSnowDep); 
            }

            double SWE = GetStateVarValue(iSnow);
            return (SWE / TYPICAL_SNOW_DENS) * DENSITY_WATER;
        }


        // Manipulator functions
        public void Disable()
        { 
            _Disabled = true; 
        }
        public void Enable()
        { 
            _Disabled = false; 
        }
        public void LinkToReservoir(long SBID)
        { 
            _res_linked = true; 
        }


    }
}
