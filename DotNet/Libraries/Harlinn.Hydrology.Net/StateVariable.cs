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
    /// Methods class for related state variable parsing and querying routines
    /// </summary>
    public class StateVariable
    {
        /// <summary>
        /// total number of aliases
        /// </summary>
        int _nAliases;
        /// <summary>
        /// Array of alias values [size: nAliases]
        /// </summary>
        string[] _aAliases;
        /// <summary>
        /// Array of strings referenced by aliases [size: nAliases]
        /// </summary>
        string[] _aAliasReferences;
        
        TransportModel _pTransportModel;



        public static string GetStateVarLongName(SVType typ,
                                            int layerIndex,
                                            TransportModel transportModel)
        {
            string name;
            switch (typ)
            {
                // Water Storage [mm]
                case (SVType.SURFACE_WATER): 
                { 
                    name = "Surface Water"; 
                }
                break;
                case (SVType.ATMOSPHERE): 
                { 
                    name = "Cum. Losses to Atmosphere"; 
                }
                break;
                case (SVType.ATMOS_PRECIP): 
                { 
                    name = "Cum. Precipitation"; 
                }
                break;
                case (SVType.PONDED_WATER): 
                { 
                    name = "Ponded Water";  
                }
                break;
                case (SVType.SOIL): 
                { 
                    name = "Soil Water";  
                }
                break;
                case (SVType.CANOPY): 
                { 
                    name = "Canopy";  
                }
                break;
                case (SVType.CANOPY_SNOW): 
                { 
                    name = "Canopy Snow";  
                }
                break;
                case (SVType.TRUNK): 
                { 
                    name = "Trunks of trees";  
                }
                break;
                case (SVType.ROOT): 
                { 
                    name = "Root Storage";  
                }
                break;
                case (SVType.GROUNDWATER): 
                { 
                    name = "Deep Groundwater";  
                }
                break;
                case (SVType.DEPRESSION): 
                { 
                    name = "Depression";  
                }
                break;
                case (SVType.SNOW): 
                { 
                    name = "Snow";  
                }
                break;
                case (SVType.NEW_SNOW): 
                { 
                    name = "New Snow";  
                }
                break;
                case (SVType.SNOW_LIQ): 
                { 
                    name = "Snow Melt (Liquid)";  
                }
                break;
                case (SVType.TOTAL_SWE): 
                { 
                    name = "Total SWE";  
                }
                break;
                case (SVType.WETLAND): 
                { 
                    name = "Wetlands";  
                }
                break;
                case (SVType.CUM_INFIL): 
                { 
                    name = "Cumulative infiltration";  
                }
                break;
                case (SVType.GA_MOISTURE_INIT): 
                { 
                    name = "Green Ampt initial soil Water";  
                }
                break;
                case (SVType.LATERAL_EXCHANGE): 
                { 
                    name = "Lateral exchange storage";  
                }
                break;
                case (SVType.SNOW_DRIFT): 
                { 
                    name = "Blowing Snow";  
                }
                break;
                case (SVType.LAKE_STORAGE): 
                { 
                    name = "Net Lake Storage";  
                }
                break;
                case (SVType.MIN_DEP_DEFICIT): 
                { 
                    name = "Minimum depression deficit";  
                }
                break;

                // Temperature/Energy storage

                case (SVType.ENERGY_LOSSES): 
                { 
                    name = "Energy Losses";  
                }
                break;
                case (SVType.SURFACE_WATER_TEMP): 
                { 
                    name = "Surface Water Temperature";  
                }
                break;
                case (SVType.SNOW_TEMP): 
                { 
                    name = "Temperature of snow";  
                }
                break;
                case (SVType.COLD_CONTENT): 
                { 
                    name = "Cold Content";  
                }
                break;
                case (SVType.SOIL_TEMP): 
                { 
                    name = "Temperature of soil";  
                }
                break;
                case (SVType.CANOPY_TEMP): 
                { 
                    name = "Temperature of canopy";  
                }
                break;

                // Snow variables

                case (SVType.SNOW_DEPTH): 
                { 
                    name = "Snow depth";  
                }
                break;
                case (SVType.PERMAFROST_DEPTH): 
                { 
                    name = "Permafrost depth";  
                }
                break;
                case (SVType.THAW_DEPTH): 
                { 
                    name = "Ground thaw depth"; 
                }
                break;
                case (SVType.SNOW_DEPTH_STDDEV): 
                { 
                    name = "Snow depth sigma"; 
                }
                break;
                case (SVType.SNOW_COVER): 
                { 
                    name = "Fractional Snow Cover"; 
                }
                break;
                case (SVType.CUM_SNOWMELT): 
                { 
                    name = "Cumulative Snowmelt"; 
                }
                break;
                case (SVType.SNOW_DEFICIT): 
                { 
                    name = "Snow Deficit"; 
                }
                break;
                case (SVType.ICE_THICKNESS): 
                { 
                    name = "Ice Thickness";  
                }
                break;
                case (SVType.SNOW_AGE): 
                { 
                    name = "Snow Age";  
                }
                break;
                case (SVType.SNODRIFT_TEMP): 
                { 
                    name = "Blowing Snow Temperature";  
                }
                break;
                case (SVType.GLACIER): 
                { 
                    name = "Glacier Liquid Storage"; break; 
                }
                case (SVType.GLACIER_ICE): 
                { 
                    name = "Glacier Ice"; 
                }
                break;
                case (SVType.GLACIER_CC): 
                { 
                    name = "Glacier Cold Content";
                }
                break;
                case (SVType.SNOW_ALBEDO): 
                { 
                    name = "Snow Albedo"; 
                }
                break;
                case (SVType.CROP_HEAT_UNITS): 
                { 
                    name = "Crop Heat Units";
                }
                break;
                case (SVType.CONVOLUTION): 
                { 
                    name = "Convolution Storage"; 
                }
                break;
                case (SVType.CONV_STOR): 
                { 
                    name = "Convolution Substorage"; 
                }
                break;
                case (SVType.AET): 
                { 
                    name = "Actual Evapotranspiration"; 
                }
                break;
                case (SVType.RUNOFF): 
                { 
                    name = "Runoff"; 
                }
                break;
                case (SVType.STREAMFLOW): 
                { 
                    name = "Streamflow"; 
                }
                break;
                case (SVType.RESERVOIR_STAGE): { name = "Reservoir Stage"; break; }

                // Transport variables
                case (SVType.CONSTITUENT): 
                { 
                    name = "Constituent"; 
                }
                break;
                case (SVType.CONSTITUENT_SRC): 
                { 
                    name = "Constituent Source"; 
                }
                break;
                case (SVType.CONSTITUENT_SINK): 
                { 
                    name = "Constituent Sink";
                }
                break;
                case (SVType.CONSTITUENT_SW): 
                { 
                    name = "Constituent in Surface Water"; 
                }
                break;
                default:
                {
                    throw new ArgumentException($"{typ}: Unknown State Variable Type");
                }
                
            }
            if ((typ == SVType.SOIL) || (typ == SVType.SOIL_TEMP) ||
                (typ == SVType.CONVOLUTION) || (typ == SVType.CONV_STOR) || (typ == SVType.LATERAL_EXCHANGE))
            {
                name = $"{name}[{layerIndex}]";
            }
            if (((typ == SVType.SNOW) || (typ == SVType.GROUNDWATER)) && (layerIndex >= 0))
            {
                name = $"{name}[{layerIndex}]";
            }
            if (typ == SVType.CONSTITUENT)
            {
                name = transportModel.GetConstituentLongName(layerIndex);
            }
            else if (typ == SVType.CONSTITUENT_SRC)
            {
                name = "Source of " + transportModel.GetConstituentTypeName2(layerIndex);
            }
            else if (typ == SVType.CONSTITUENT_SINK)
            {
                name = "Sink of " + transportModel.GetConstituentTypeName2(layerIndex);
            }
            else if (typ == SVType.CONSTITUENT_SW)
            {
                name = "SW Sink of " + transportModel.GetConstituentTypeName2(layerIndex);
            }
            return name;
        }

    }
}
