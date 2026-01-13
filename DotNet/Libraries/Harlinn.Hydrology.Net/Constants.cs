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
    class Constants
    {
        /// <summary>
        /// Largest possible double value to be used
        /// </summary>
        public const double ALMOST_INF = 1e99;
        /// <summary>
        /// useful small tolerance for zero tests
        /// </summary>
        public const double PRETTY_SMALL = 1e-8;
        /// <summary>
        /// Smallest possible double value to be used
        /// </summary>
        public const double REAL_SMALL = 1e-12;
        /// <summary>
        /// Double approximation of pi
        /// </summary>
        public const double PI = double.Pi;

        /// <summary>
        /// Standard acceleration due to gravity [m/s2]
        /// </summary>
        public const double GRAVITY = 9.80616;
        /// <summary>
        /// Zero degrees in Kelvin
        /// </summary>
        public const double ZERO_CELSIUS = 273.16;

        /// <summary>
        /// Universal gas constant [J/K/kmol]
        /// </summary>
        public const double UNIV_GAS_CONST = 8314.47;
        /// <summary>
        /// Specific gas constant for dry air [J/K/kg]
        /// </summary>
        public const double DRY_GAS_CONST = 287.042;
        /// <summary>
        /// Specific gas constant for water vapour [J/K/kmol]
        /// </summary>
        public const double VAP_GAS_CONST = 461.504;
        /// <summary>
        /// Stephan-Boltzmann constant [MJ/m2/d/K4]
        /// </summary>
        public const double STEFAN_BOLTZ = 4.90e-9;
        /// <summary>
        /// Von Karmann constant
        /// </summary>
        public const double VON_KARMAN = 0.42;

        //units conversion constants
        /// <summary>
        /// [in] to [mm]
        /// </summary>
        public const double MM_PER_INCH = 25.4;
        /// <summary>
        /// [m] to [mm]
        /// </summary>
        public const double MM_PER_METER = 1000;
        /// <summary>
        /// [cm] to [mm]
        /// </summary>
        public const double MM_PER_CM = 10;
        /// <summary>
        /// [m] to [cm]
        /// </summary>
        public const double CM_PER_METER = 100;
        /// <summary>
        /// [m3] to [ccm]
        /// </summary>
        public const double CM3_PER_METER3 = 1e6;
        /// <summary>
        /// [cm] to [m]
        /// </summary>
        public const double METER_PER_CM = 0.01;
        /// <summary>
        /// [km2] to [m2]
        /// </summary>
        public const double M2_PER_KM2 = 1e6;
        /// <summary>
        /// [m2] to [mm2]
        /// </summary>
        public const double MM2_PER_M2 = 1e6;
        /// <summary>
        /// [km] to [m]
        /// </summary>
        public const double M_PER_KM = 1000;
        /// <summary>
        /// [kg] to [g]
        /// </summary>
        public const double GRAMS_PER_KG = 1000;
        /// <summary>
        /// [kg] to [mg]
        /// </summary>
        public const double MG_PER_KG = 1000000;
        /// <summary>
        /// [m3] to [l]
        /// </summary>
        public const double LITER_PER_M3 = 1000;
        /// <summary>
        /// [kg/m3] to [g/ccm]
        /// </summary>
        public const double GPCM3_PER_KGPM3 = 0.001;
        /// <summary>
        /// [J] to [MJ]
        /// </summary>
        public const double MJ_PER_J = 1e-6;
        /// <summary>
        /// [MPa] to [KPa]
        /// </summary>
        public const double KPA_PER_MPA = 1000;
        /// <summary>
        /// [kPa] to [Pa]
        /// </summary>
        public const double PA_PER_KPA = 1000;
        /// <summary>
        /// [kPa] to [hPa]
        /// </summary>
        public const double HPA_PER_KPA = 10;
        /// <summary>
        /// [KPa] to [millibars]
        /// </summary>
        public const double MB_PER_KPA = 10;
        /// <summary>
        /// [atm] to [KPa]
        /// </summary>
        public const double KPA_PER_ATM = 101.325;
        /// <summary>
        /// days to seconds
        /// </summary>
        public const double SEC_PER_DAY = 86400;
        /// <summary>
        /// days to minutes
        /// </summary>
        public const double MIN_PER_DAY = 1440;
        /// <summary>
        /// hours to seconds
        /// </summary>
        public const double SEC_PER_HR = 3600;
        /// <summary>
        /// years to days
        /// </summary>
        public const double DAYS_PER_YEAR = 365.25;
        /// <summary>
        /// days to hours
        /// </summary>
        public const double HR_PER_DAY = 24;
        /// <summary>
        /// [MJ/d] to [W]
        /// </summary>
        public const double MJ_PER_D_TO_WATT = 11.574;
        /// <summary>
        /// [W] to [MJ/d]
        /// </summary>
        public const double WATT_TO_MJ_PER_D = 0.0864;
        /// <summary>
        /// Langley to [MJ/m2]
        /// </summary>
        public const double MJ_PER_M2_LANGLEY = 0.04184;
        /// <summary>
        /// [m] to [in]
        /// </summary>
        public const double INCH_PER_METER = 39.37;
        /// <summary>
        /// [m] to [ft]
        /// </summary>
        public const double FEET_PER_METER = 3.28;
        /// <summary>
        /// [acre-ft/d] to [m3/s]
        /// </summary>
        public const double ACREFTD_PER_CMS = 70.0456;
        /// <summary>
        /// [acre-ft] to [m3]
        /// </summary>
        public const double ACREFT_PER_M3 = 0.000810714;
        /// <summary>
        /// [ft3/s] to [m3 / s]
        /// </summary>
        public const double CFS_PER_CMS = 0.0283168;
        /// <summary>
        /// [cdm/day] to [m3/s]
        /// </summary>
        public const double CDM_PER_DAY_PER_CMS = 86.4;
        /// <summary>
        /// [kph] to [mph]
        /// </summary>
        public const double MPH_PER_KPH = 1.609;
        /// <summary>
        /// [m/s] to [mph]
        /// </summary>
        public const double MPH_PER_MPS = 2.237;
        /// <summary>
        /// [rad] to [deg]
        /// </summary>
        public const double RADIANS_TO_DEGREES = 57.29578951;
        /// <summary>
        /// [deg] to [rad]
        /// </summary>
        public const double DEGREES_TO_RADIANS = 0.017453293;
        /// <summary>
        /// Allows rational method to be applied
        /// 
        /// 0.278*(24hr/d)*(1000^2m^2/km)*(0.001m/mm)*(1/86400s/day)
        /// runoff=RATIONAL_CONV*C_R*rainfall intensity
        /// [mm/d] = [mm/d]
        /// </summary>
        public const double RATIONAL_CONV = 0.7722;
        /// <summary>
        /// Array of doubles containing the number of days in each month
        /// </summary>
        public static readonly double[] DAYS_PER_MONTH = { 31.0, 28.0, 31.0, 30.0, 31.0, 30.0, 31.0, 31.0, 30.0, 31.0, 30.0, 31.0 };

        /// <summary>
        /// [C] Freezing temperature of water
        /// </summary>
        public const double FREEZING_TEMP = 0.0;

        /// <summary>
        /// [kg/m3] Ambient Air Density (@ 10 C)
        /// </summary>
        public const double DENSITY_AIR = 1.2466;
        /// <summary>
        /// [kg/m3] Water Density
        /// </summary>
        public const double DENSITY_WATER = 1.000e3;
        /// <summary>
        /// [kg/m3] Ice Density
        /// </summary>
        public const double DENSITY_ICE = 0.917e3;
        /// <summary>
        /// [kg/m3] Sand Density
        /// </summary>
        public const double DENSITY_SAND = 2.650e3;
        /// <summary>
        /// [kg/m3] Clay Density
        /// </summary>
        public const double DENSITY_CLAY = 2.650e3;
        /// <summary>
        /// [kg/m3] Organic Matter Density
        /// </summary>
        public const double DENSITY_OM = 1.300e3;
        /// <summary>
        /// [kg/m3] maximum dry density of snowpack (GAWSER)
        /// </summary>
        public const double MAX_SNOW_DENS = 0.350e3;
        /// <summary>
        /// [kg/m3] fresh snow density @ 0 deg. C
        /// </summary>
        public const double FRESH_SNOW_DENS = 0.119e3;
        /// <summary>
        /// [kg/m3] "typical" snow density
        /// </summary>
        public const double TYPICAL_SNOW_DENS = 0.250e3;

        /// <summary>
        /// [MJ/m/d/K] Thermal conductivity of Water (0.57 W/m/k)
        /// </summary>
        public const double TC_WATER = 0.0492;
        /// <summary>
        /// [MJ/m/d/K] Thermal conductivity of Ice (2.24 W/m/K)
        /// </summary>
        public const double TC_ICE = 0.194;
        /// <summary>
        /// [MJ/m/d/K] Thermal conductivity of sand (8.0 W/m/K vs 8.8 in CLM)
        /// </summary>
        public const double TC_SAND = 0.691;
        /// <summary>
        /// [MJ/m/d/K] Thermal conductivity of clay (2.5 W/m/K vs 2.92 in CLM)
        /// </summary>
        public const double TC_CLAY = 0.216;
        /// <summary>
        /// [MJ/m/d/K] Thermal conductivity of organic matter (0.25 W/m/K)
        /// </summary>
        public const double TC_ORGANIC = 0.0216;
        /// <summary>
        /// [MJ/m/d/K] Thermal conductivity of air (0.023 W/m/K)
        /// </summary>
        public const double TC_AIR = 0.00199;

        /// <summary>
        /// [1/Pa] Compressiblity of Water
        /// </summary>
        public const double COM_WATER = 4.58e-10;
        /// <summary>
        /// [1/Pa] Compressiblity of Ice
        /// </summary>
        public const double COM_ICE = 4.58e-10;
        /// <summary>
        /// [MJ/m3/K] Volumetric Heat Capacity of Water
        /// </summary>
        public const double HCP_WATER = 4.186;
        /// <summary>
        /// [MJ/m3/K] Volumetric Heat Capacity of Ice
        /// </summary>
        public const double HCP_ICE = 1.938;
        /// <summary>
        /// [MJ/m3/K] Volumetric Heat Capacity of Clay
        /// </summary>
        public const double HCP_CLAY = 2.380;
        /// <summary>
        /// [MJ/m3/K] Volumetric Heat Capacity of Sand
        /// </summary>
        public const double HCP_SAND = 2.130;
        /// <summary>
        /// [MJ/m3/K] Volumetric Heat Capacity of Organic Matter
        /// </summary>
        public const double HCP_ORGANIC = 2.500;
        /// <summary>
        /// [MJ/m3/K] Volumetric Heat capacity of air
        /// </summary>
        public const double HCP_AIR = 0.00124;

        /// <summary>
        /// [MJ/kg/K] Specific heat capacity of ice
        /// </summary>
        public const double SPH_ICE = 2.100e-3;
        /// <summary>
        /// [MJ/kg/K] Specific heat capacity of water
        /// </summary>
        public const double SPH_WATER = 4.186e-3;
        /// <summary>
        /// [MJ/kg/K] Specific heat capacity of water
        /// </summary>
        public const double SPH_SAND = 0.835e-3;
        /// <summary>
        /// [MJ/kg/K] Specific heat capacity of vegetation
        /// </summary>
        public const double SPH_VEGETATION = 2.700e-3;
        /// <summary>
        /// [MJ/kg/K] Specific heat capacity of air
        /// </summary>
        public const double SPH_AIR = 1.012e-3;

        /// <summary>
        /// [MJ/kg]  Latent heat of fusion
        /// </summary>
        public const double LH_FUSION = 0.334;
        /// <summary>
        /// [MJ/kg]  Latent heat of vaporization
        /// </summary>
        public const double LH_VAPOR = 2.501;
        /// <summary>
        /// [MJ/kg]  Latent heat of sublimation
        /// </summary>
        public const double LH_SUBLIM = 2.845;

        /// <summary>
        /// [-] emissivity of the atmosphere and snowpack
        /// </summary>
        public const double EMISS_ATM = 0.985;
        /// <summary>
        /// [-] emissivity of the canopy
        /// </summary>
        public const double EMISS_CANOPY = 0.96;
        /// <summary>
        /// [-] emissivity of open water
        /// </summary>
        public const double EMISS_WATER = 0.97;

        /// <summary>
        /// ratio of molecular weight of air to that of water
        /// </summary>
        public const double AIR_H20_MW_RAT = 0.622;
        /// <summary>
        /// [g/mol] molecular weight of H2O
        /// </summary>
        public const double MOLWT_WATER = 18.01528;
        /// <summary>
        /// [kPa]
        /// </summary>
        public const double AMBIENT_AIR_PRESSURE = 101.3;

        /// <summary>
        /// [m]
        /// </summary>
        public const double EARTH_RADIUS = 6.3712e6;
        /// <summary>
        /// Earth's angular velocity [rad/d]
        /// </summary>
        public const double EARTH_ANG_VEL = 6.283185;
        /// <summary>
        /// The fraction of a day at which solar noon occurs (12:00 PM)
        /// </summary>
        public const double SOLAR_NOON = 0.5;
        /// <summary>
        /// [MJ/m2/d]
        /// </summary>
        public const double SOLAR_CONSTANT = 118.1;
        /// <summary>
        /// Global Albedo used to calculate the backscattered radiation according to Dingman (Dingman 2008, E-20)
        /// </summary>
        public const double GLOBAL_ALBEDO = 0.3;
        /// <summary>
        /// if =3, 3:00 PM is time of max temperature, 3:00 AM is time of min temp
        /// </summary>
        public const double PEAK_TEMP_HR = 3;
        /// <summary>
        /// Dec 21 as day angle
        /// </summary>
        public const double WINTER_SOLSTICE_ANG = 6.111043;

        //Hard-coded Empirical parameters

        /// <summary>
        /// [0..1] cutoff saturation for parabolic calculation of phi in clapp-hornberger soil characteristics
        /// </summary>
        public const double SAT_INF = 0.92;

        /// <summary>
        /// [-mm] minimum matric potential in soil
        /// </summary>
        public const double MIN_PRESSURE = 1e10;

        /// <summary>
        /// [0..1]  default snow albedo used for all snow, if not tracked explicitly
        /// </summary>
        public const double DEFAULT_SNOW_ALBEDO = 0.8;
        /// <summary>
        /// [mm]    SWE at which snow cover no longer impacts albedo/evap calculations (i.e., snow cover~0)
        /// </summary>
        public const double NEGLIGBLE_SNOW = 0.1;
        /// <summary>
        /// [0..1]  ratio of roughness to height for smooth closed canopies (from Brook90)
        /// </summary>
        public const double CZS = 0.13;
        /// <summary>
        /// [m]     height below which CZS applies
        /// </summary>
        public const double CZS_HEIGHT = 1.0;
        /// <summary>
        /// [0..1]  ratio of roughness to height for rough closed canopies
        /// </summary>
        public const double CZR = 0.05;
        /// <summary>
        /// [m]     height above which czr applies
        /// </summary>
        public const double CZR_HEIGHT = 10.0;
        /// <summary>
        /// [m2/m2] minimum LAI defining a closed canopy (Shuttleworth and Wallace (1985))
        /// </summary>
        public const double CLOSED_LAI = 4.0;
        /// <summary>
        /// [m]     reference height for weather data above canopy height
        /// </summary>
        public const double Z_REF_ADJUST = 2.0;
        /// <summary>
        /// [-]     wind/diffusivity extinction coefficient
        /// </summary>
        public const double WIND_EXTINCT = 2.5;
        /// <summary>
        /// [m2/m2] ratio of total leaf area to projected area.
        /// </summary>
        /// <remarks> 
        /// This is always 2 for broadleaves, and ranges from 2 for flat needles to pi for cylindrical needles.
        /// </remarks>
        public const double LEAF_PROJ_RAT = 2.2;

        /// <summary>
        /// [masl]  (zref in HBV)
        /// </summary>
        public const double HBV_REFERENCE_ELEV = 1000;
        /// <summary>
        /// [mm/m-d] PET lapse rate (ECALT in HBV-EC)
        /// </summary>
        public const double HBV_PET_ELEV_CORR = 0.0005;
        /// <summary>
        /// [-]     (ETF in HBV-EC)
        /// </summary>
        public const double HBV_PET_TEMP_CORR = 0.5;
        /// <summary>
        /// [-]     (ECORR in HBV-EC)
        /// </summary>
        public const double GLOBAL_PET_CORR = 1.0;

        //Flag variables
        /// <summary>
        /// return value for nonexistent index
        /// </summary>
        public const int DOESNT_EXIST = -1;
        /// <summary>
        /// return value for index not found
        /// </summary>
        public const int INDEX_NOT_FOUND = -2;

        /// <summary>
        /// arbitrary value indicating that a parameter is to be autocalculated
        /// </summary>
        public const double AUTO_COMPUTE = -11111.1;
        /// <summary>
        /// arbitrary value indicating that a parameter is to be autocalculated
        /// </summary>
        public const long AUTO_COMPUTE_LONG = -11111;
        /// <summary>
        /// arbitrary value indicating that a parameter has not been specified
        /// </summary>
        public const double NOT_SPECIFIED = -33333.3;
        /// <summary>
        /// arbitrary value indicating that a parameter should be set to the template value
        /// </summary>
        public const double USE_TEMPLATE_VALUE = -55555.5;
        /// <summary>
        /// arbitrary value indicating that a non-auto parameter is not needed for the current model configuration
        /// </summary>
        public const double NOT_NEEDED = -66666.6;
        /// <summary>
        /// arbitrary value indicating that a autogeneratable parameter is not needed for the current model configuration
        /// </summary>
        public const double NOT_NEEDED_AUTO = -77777.7;
        /// <summary>
        /// NetCDF flag for blank value
        /// </summary>
        public const double NETCDF_BLANK_VALUE = -9999.0;
        /// <summary>
        /// double corresponding to blank/void data item (also used in input files)
        /// </summary>
        public const double BLANK_DATA = -1.2345;
        /// <summary>
        /// dirichlet concentration flag corresponding to air temperature
        /// </summary>
        public const double DIRICHLET_TEMP = -9999.0;
        /// <summary>
        /// special flag indicating that NetCDF indices should be looked up from station attribute table
        /// </summary>
        public const int FROM_STATION_VAR = -55;

        //Decision constants
        /// <summary>
        /// [d/mm]   essentially infinite resistance
        /// </summary>
        public const double HUGE_RESIST = 1e20;
        /// <summary>
        /// [mm/mm3] essentially negligible root density
        /// </summary>
        public const double SMALL_ROOT_DENS = 0.00001;
        /// <summary>
        /// [m]      essentially negligible root length
        /// </summary>
        public const double SMALL_ROOT_LENGTH = 0.1;
        /// <summary>
        /// [m3/s]   essentially negligible flow rate
        /// </summary>
        public const double SMALL_FLOWRATE = 0.0001;
        /// <summary>
        /// [d]      offset for time series min/max functions
        /// </summary>
        public static readonly TimeSpan TIME_CORRECTION = TimeSpan.FromDays(0.0001);
        /// <summary>
        /// [km]     very large maximum reach length (defaults to single segment per reach)
        /// </summary>
        public const double DEFAULT_MAX_REACHLENGTH = 10000.0;

        //Special symbols
        /// <summary>
        /// degree symbol, (or \0xB0)
        /// </summary>
        public const char DEG_SYMBOL = 'o';


        /// <summary>
        /// if true, screen output is generated when destructor is called
        /// </summary>
        public const bool DESTRUCTOR_DEBUG = false;
        /// <summary>
        /// Max number of layers per state variable (greater than MAX_SOILLAYERS)
        /// </summary>
        public const int MAX_SV_LAYERS = 160;
        /// <summary>
        /// Max number of soil layers in profile
        /// </summary>
        public const int MAX_SOILLAYERS = 50;
        /// <summary>
        /// Max number of *types* of state variables in model
        /// </summary>
        public const int MAX_STATE_VAR_TYPES = 100;
        /// <summary>
        /// Max number of simulated state variables manipulable by one process (CAdvection worst offender)
        /// </summary>
        public const int MAX_STATE_VARS = 500;
        /// <summary>
        /// Max number of to/from connections in any single process (CAdvection worst offender)
        /// </summary>
        public const int MAX_CONNECTIONS = 650;
        /// <summary>
        /// Max number of lateral HRU flow connections
        /// </summary>
        public const int MAX_LAT_CONNECTIONS = 4000;
        /// <summary>
        /// Max number of soil profiles
        /// </summary>
        public const int MAX_SOIL_PROFILES = 200;
        /// <summary>
        /// Max number of vegetation classes
        /// </summary>
        public const int MAX_VEG_CLASSES = 200;
        /// <summary>
        /// Max number of lult classes
        /// </summary>
        public const int MAX_LULT_CLASSES = 200;
        /// <summary>
        /// Max number of terrain classes
        /// </summary>
        public const int MAX_TERRAIN_CLASSES = 50;
        /// <summary>
        /// Max number of survey points
        /// </summary>
        public const int MAX_SURVEY_PTS = 50;
        /// <summary>
        /// Max number of transported constituents
        /// </summary>
        public const int MAX_CONSTITUENTS = 10;
        /// <summary>
        /// Max number of river segments
        /// </summary>
        public const int MAX_RIVER_SEGS = 50;
        /// <summary>
        /// Max filename length
        /// </summary>
        public const int MAX_FILENAME_LENGTH = 256;
        /// <summary>
        /// Max multidata length
        /// </summary>
        public const int MAX_MULTIDATA = 10;


        public const int MAX_FORCING_TYPES = 50;


        /// <summary>
        /// Maximum allowable number of histogram bins
        /// </summary>
        public const int MAX_HISTOGRAM_BINS = 40;

        

    }
}
