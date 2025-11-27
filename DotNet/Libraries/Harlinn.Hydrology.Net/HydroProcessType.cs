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
    /// Hydrological process types
    /// </summary>
    public enum HydroProcessType
    {
        
        RICHARDS,

        
        PRECIPITATION,

        
        INFILTRATION,

        
        BASEFLOW, SOIL_EVAPORATION, INTERFLOW, PERCOLATION, CAPILLARY_RISE, RECHARGE, SOIL_BALANCE,

        
        CANOPY_EVAPORATION, CANOPY_SNOW_EVAPORATION, CANOPY_DRIP,
        OPEN_WATER_EVAPORATION, LAKE_EVAPORATION,

        
        SNOWMELT, REFREEZE, SUBLIMATION, SNOW_BALANCE, SNOWSQUEEZE, SNOWTEMP_EVOLVE,

        
        GLACIER_MELT, GLACIER_RELEASE, GLACIER_INFIL,

        
        FLUSH, SPLIT, OVERFLOW_PROC, CONVOLVE, EXCHANGE_FLOW,

        
        LAT_FLUSH, LAT_EQUIL,

        
        SNOW_ALBEDO_EVOLVE,

        
        BLOWING_SNOW,

        
        CROP_HEAT_UNIT_EVOLVE,

        
        ABSTRACTION, DEPRESSION_OVERFLOW, SEEPAGE, LAKE_RELEASE,

        
        ADVECTION, LAT_ADVECTION, MASS_LOADING,

        
        DECAY, TRANSFORMATION,

        
        PARTITION_ENERGY,

        
        HEATCONDUCTION,

        
        GROUND_FREEZING,

        
        LAKE_FREEZING,

        
        PROCESS_GROUP,

        
        DRAIN, GWRECHARGE,

        
        RF_PROCESS,

        NULL_PROCESS_TYPE
    }

}
