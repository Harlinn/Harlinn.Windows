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
    /// Contains information on forcing functions
    /// </summary>
    public class Force
    {
        /// <summary>
        /// precipitaiton rate over time step [mm/d]
        /// </summary>
        public double precip;
        /// <summary>
        /// average precipitaiton over day (0:00-24:00) [mm/d]
        /// </summary>
        public double precip_daily_ave;
        /// <summary>
        /// 5-day precipitation total [mm] (needed for SCS)
        /// </summary>
        public double precip_5day;
        /// <summary>
        /// fraction of precip that is snow [0..1]
        /// </summary>
        public double snow_frac;
        /// <summary>
        /// irrigation rate over time step [mm/d]
        /// </summary>
        public double irrigation;
        /// <summary>
        /// precipitation temperature [C]
        /// </summary>
        public double precip_temp;
        /// <summary>
        /// ///< precipitation concentration [C] (\todo[funct]: should make vector)
        /// </summary>
        public double precip_conc;

        /// <summary>
        /// average air temp over time step [C]
        /// </summary>
        public double temp_ave;
        /// <summary>
        /// minimum air temperature over day (0:00-24:00)[C]
        /// </summary>
        public double temp_daily_min;
        /// <summary>
        /// maximum air temperature over day (0:00-24:00)[C]
        /// </summary>
        public double temp_daily_max;
        /// <summary>
        /// average air temp over day (0:00-24:00) [C]
        /// </summary>
        public double temp_daily_ave;
        /// <summary>
        /// maximum air temp during month [C]
        /// </summary>
        public double temp_month_max;
        /// <summary>
        /// minimum air temp during month [C]
        /// </summary>
        public double temp_month_min;
        /// <summary>
        /// average air temp during month [C]
        /// </summary>
        public double temp_month_ave;
        /// <summary>
        /// uncorrected daily average air temp  [C]
        /// </summary>
        public double temp_ave_unc;
        /// <summary>
        /// uncorrected daily min air temp  [C]
        /// </summary>
        public double temp_min_unc;
        /// <summary>
        /// uncorrected daily max air temp  [C]
        /// </summary>
        public double temp_max_unc;

        /// <summary>
        /// Air density [kg/m3]
        /// </summary>
        public double air_dens;
        /// <summary>
        /// Air pressure [kPa]
        /// </summary>
        public double air_pres;
        /// <summary>
        /// relative humidity [0..1]
        /// </summary>
        public double rel_humidity;

        /// <summary>
        /// Cloud cover [0..1]
        /// </summary>
        public double cloud_cover;
        /// <summary>
        /// uncorrected extraterrestrial shortwave radiation, after slope correction [MJ/m2/d]
        /// </summary>
        public double ET_radia;
        /// <summary>
        /// uncorrected extraterrestrial shortwave radiation on horizontal surface [MJ/m2/d]
        /// </summary>
        public double ET_radia_flat;
        /// <summary>
        /// uncorrected shortwave radiation (before cloud and canopy corrections, after slope)[MJ/m2/d]
        /// </summary>
        public double SW_radia_unc;
        /// <summary>
        /// Incoming shortwave radiation (slope/air mass/horizon/cloud cover/canopy corrections applied, uncorrected for albedo) [MJ/m2/d]
        /// </summary>
        public double SW_radia;
        /// <summary>
        /// Net shortwave radiation at canopy top (albedo corrected) [MJ/m2/d]
        /// </summary>
        public double SW_radia_net;
        /// <summary>
        /// Shortwave incoming radiation at ground beneath canopy [MJ/m2/d]
        /// </summary>
        public double SW_radia_subcan;
        /// <summary>
        /// Net shortwave incoming radiation on ground beneath canopy [MJ/m2/d]
        /// </summary>
        public double SW_subcan_net;
        /// <summary>
        /// Net longwave radiation [MJ/m2/d]
        /// </summary>
        public double LW_radia_net;
        /// <summary>
        /// Incoming longwave radiation [MJ/m2/d]
        /// </summary>
        public double LW_incoming;
        /// <summary>
        /// day length [d]  (e.g., ~0.5 for equinox @ 45lat, 0.0 for the north pole during winter)
        /// </summary>
        public double day_length;
        /// <summary>
        /// day angle [0..2PI] =0 for Jan 1, 2pi for Dec 31
        /// </summary>
        public double day_angle;
        /// <summary>
        /// potential snowmelt rate [mm/d]
        /// </summary>
        public double potential_melt;

        /// <summary>
        /// Wind velocity [m/s]
        /// </summary>
        public double wind_vel;

        /// <summary>
        /// Potential Evapotranspiration [mm/d]
        /// </summary>
        public double PET;
        /// <summary>
        /// Open Water Potential Evapotranspiration [mm/d]
        /// </summary>
        public double OW_PET;
        /// <summary>
        /// average PET during month [mm/d]
        /// </summary>
        public double PET_month_ave;

        /// <summary>
        /// recharge to groundwater (typically from external model) [mm/d]
        /// </summary>
        public double recharge;

        /// <summary>
        /// a subdaily correction factor to re-distribute daily average PET or snowmelt [-]
        /// </summary>
        public double subdaily_corr;
    }

}
