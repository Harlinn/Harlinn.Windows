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
    /// Type of state variable
    /// </summary>
    public enum SVType
    {
        // Water Storage
        
        /// <summary>
        /// [mm] Streams & rivers: see surface_struct (REQUIRED)
        /// </summary>
        SURFACE_WATER,
        /// <summary>
        /// [mm] atmosphere : recieves water only!! (REQUIRED)
        /// </summary>
        ATMOSPHERE,
        /// <summary>
        /// [mm] atmosphere : provides water only!! (REQUIRED)
        /// </summary>
        ATMOS_PRECIP,
        //[mm] water (melt & precip) waiting to infiltrate/runoff (REQUIRED)
        PONDED_WATER,

        /// <summary>
        /// [mm] Shallow subsurface/vadose zone
        /// </summary>
        SOIL,
        // [mm] Trees & vegetation
        CANOPY,
        /// <summary>
        /// [mm] snow in canopy
        /// </summary>
        CANOPY_SNOW,
        /// <summary>
        /// [mm] water stored in trunks of trees
        /// </summary>
        TRUNK,
        /// <summary>
        /// [mm] water stored in roots
        /// </summary>
        ROOT,
        /// <summary>
        /// [mm] Deep groundwater
        /// </summary>
        GROUNDWATER,
        /// <summary>
        /// [mm] depression/surface storage
        /// </summary>
        DEPRESSION,

        /// <summary>
        /// [mm] frozen snow depth (mm SWE : snow water equivalent)
        /// </summary>
        SNOW,
        /// <summary>
        /// [mm] new snowfall waiting to be handled by snow balance (as SWE)
        /// </summary>
        NEW_SNOW,
        /// <summary>
        /// [mm] liquid water content of snowpack
        /// </summary>
        SNOW_LIQ,
        /// <summary>
        /// [mm] equivalent to SNOW[0]+SNOW[1]+...+SNOW_LIQ[0]..
        /// </summary>
        TOTAL_SWE,
        /// <summary>
        /// [mm] deep wetland depression storage
        /// </summary>
        WETLAND,
        /// <summary>
        /// [mm] Glacier melt/reservoir storage
        /// </summary>
        GLACIER,
        /// <summary>
        /// [mm] Glacier ice - typically assumed to be infinite reservoir.
        /// </summary>
        GLACIER_ICE,
        /// <summary>
        /// [mm] Net lake storage - relative to equilibrium datum - can go negative
        /// </summary>
        LAKE_STORAGE,

        /// <summary>
        /// [mm] Convolution storage - for conceptual models with intermediate convolution steps
        /// </summary>
        CONVOLUTION,
        /// <summary>
        /// [mm] Convolution sub-storage - tracks internal water mass for convolution
        /// </summary>
        CONV_STOR,

        // Distribution tracking variables

        /// <summary>
        /// [mm or -1..0] Minimum depression deficit (describes deficit distribution), =-percent full if negative 
        /// </summary>
        MIN_DEP_DEFICIT,

        // Memory variables

        /// <summary>
        /// [mm] Cumulative infiltration to topsoil
        /// </summary>
        CUM_INFIL,
        /// <summary>
        /// [mm] Initial topsoil moisture content for Green Ampt infiltration
        /// </summary>
        GA_MOISTURE_INIT,
        /// <summary>
        /// [mm] Cumulative snowmelt as SWE
        /// </summary>
        CUM_SNOWMELT,
        /// <summary>
        /// [mm] PET used up in given time step (diagnostic variable)
        /// </summary>
        AET,
        /// <summary>
        /// [mm] net release of water to surface water in given times step (diagnostic variable)
        /// </summary>
        RUNOFF,

        // Temperature/Energy storage [C] or [MJ/m^2]

        /// <summary>
        /// [MJ/m2] general energy losses
        /// </summary>
        ENERGY_LOSSES,

        /// <summary>
        /// [C] Temperature of surface water
        /// </summary>
        SURFACE_WATER_TEMP,
        /// <summary>
        /// [C] Temperature of snow
        /// </summary>
        SNOW_TEMP,
        /// <summary>
        /// [C] Cold content of snowpack
        /// </summary>
        COLD_CONTENT,
        /// <summary>
        /// [C] Temperature of soil
        /// </summary>
        SOIL_TEMP,

        /// <summary>
        /// [C] Temperature fo canopy
        /// </summary>
        CANOPY_TEMP,

        // Snow/Glacier variables

        /// <summary>
        /// [mm] Snow depth - surrogate for density
        /// </summary>
        SNOW_DEPTH,

        /// <summary>
        /// [mm] depth of permafrost
        /// </summary>
        PERMAFROST_DEPTH,
        /// <summary>
        /// [mm] depth of thaw
        /// </summary>
        THAW_DEPTH,

        /// <summary>
        /// log([mm]) Snow depth standard deviation
        /// </summary>
        SNOW_DEPTH_STDDEV,
        /// <summary>
        /// [0..1] fractional snow cover
        /// </summary>
        SNOW_COVER,
        /// <summary>
        /// [mm] cold content of glacier
        /// </summary>
        GLACIER_CC,
        /// <summary>
        /// [mm] remaining holding capacity of snowpack (surrogate for SNOW_LIQ)
        /// </summary>
        SNOW_DEFICIT,
        /// <summary>
        /// [d] snow age, in days
        /// </summary>
        SNOW_AGE,
        /// <summary>
        /// [C] temperature of drifting snow
        /// </summary>
        SNODRIFT_TEMP,
        /// <summary>
        /// [mm as SWE] drifting snow storage
        /// </summary>
        SNOW_DRIFT,
        /// <summary>
        /// [mm as SWE] lake ice thickness
        /// </summary>
        ICE_THICKNESS,

        /// <summary>
        /// [-] Snow Surface albedo
        /// </summary>
        SNOW_ALBEDO,

        // Crop variables

        /// <summary>
        /// [-] cumulative crop heat units
        /// </summary>
        CROP_HEAT_UNITS,

        // Transport variables

        /// <summary>
        /// chemical species [mg/m2], enthalpy [MJ/m2], or tracer [-]
        /// </summary>
        CONSTITUENT,
        /// <summary>
        /// chemical species [mg/m2], enthalpy [MJ/m2], or tracer [-] cumulative source
        /// </summary>
        CONSTITUENT_SRC,
        /// <summary>
        /// chemical species [mg/m2], enthalpy [MJ/m2], or tracer [-] dumped to surface water
        /// </summary>
        CONSTITUENT_SW,
        /// <summary>
        /// chemical species [mg/m2], enthalpy [MJ/m2], or tracer [-] cumulative sink (e.g., decay)
        /// </summary>
        CONSTITUENT_SINK,

        // Energy variables

        /// <summary>
        /// [MJ/m2] cumulative energy lost to evaporative phase change
        /// </summary>
        LATENT_HEAT,

        // Lateral exchange

        /// <summary>
        /// [mm] water storage in transit from HRU awaiting lateral transfer to other HRUs
        /// </summary>
        LATERAL_EXCHANGE,

        // Special/internal flags

        /// <summary>
        /// only used for referencing in data assimilation
        /// </summary>
        STREAMFLOW,
        /// <summary>
        /// only used for referencing in data assimilation
        /// </summary>
        RESERVOIR_STAGE,
        /// <summary>
        /// Unrecognized type of state variable
        /// </summary>
        UNRECOGNIZED_SVTYPE,
        /// <summary>
        /// Multiple State variables (for parsing)
        /// </summary>
        MULTIPLE_SVTYPE,
        /// <summary>
        /// User specified state variable type (for parsing)
        /// </summary>
        USERSPEC_SVTYPE
    }

}
