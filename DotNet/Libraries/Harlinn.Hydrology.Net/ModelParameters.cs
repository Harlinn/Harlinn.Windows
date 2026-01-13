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

using static Harlinn.Hydrology.Constants;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Global model parameters
    /// </summary>
    public class ModelParameters
    {
        /// <summary>
        /// [degC/km]
        /// </summary>
        public double adiabatic_lapse;
        /// <summary>
        /// [degC/km]
        /// </summary>
        public double wet_adiabatic_lapse;
        /// <summary>
        /// [mm/d/km] precipitation lapse rate for orographic correction
        /// </summary>
        public double precip_lapse;

        /// <summary>
        /// [degC] rain/snow halfway transition temperature  (-0.15 for dingman, 0.0 for HBV, ~1 for UBC)
        /// </summary>
        public double rainsnow_temp;
        /// <summary>
        /// [degC] range of rain-snow transition zone (around rainsnow_temp) (4.0 for HBV, 2.0 for UBC)
        /// </summary>
        public double rainsnow_delta;
        /// <summary>
        /// [0..1] ~0.05, 0.07 irreducible water saturation fraction of snow
        /// </summary>
        public double snow_SWI;

        //   =WHC in HBV-EC, WATCAP in UBCWM, SWI in GAWSER

        /// <summary>
        /// [0..1] minimum irreducible sat fraction
        /// </summary>
        public double snow_SWI_min;
        /// <summary>
        /// [0..1] maximum irreducible sat fraction
        /// </summary>
        public double snow_SWI_max;
        /// <summary>
        /// [1/mm] SWI reduction factor with cumulative snowmelt
        /// </summary>
        public double SWI_reduct_coeff;
        /// <summary>
        /// [degC]   default snow temperature if not explicitly modelled
        /// </summary>
        public double snow_temperature;
        /// <summary>
        /// [m]  roughness height of snow
        /// </summary>
        public double snow_roughness;
        /// <summary>
        /// [0..1] very old snow/glacier albedo (~0.3)
        /// </summary>
        public double min_snow_albedo;
        /// <summary>
        /// [0..1] albedo of fresh snow  (~0.95)
        /// </summary>
        public double max_snow_albedo;
        /// <summary>
        /// [1/d] 1st order albedo decay rate for cold conditions (~0.008/d)
        /// </summary>
        public double alb_decay_cold;
        /// <summary>
        /// [1/d] albedo decay rate for melt conditions (~0.12/d)
        /// </summary>
        public double alb_decay_melt;
        /// <summary>
        /// [0..1] bare ground albedo (~0.1-0.4)
        /// </summary>
        public double bare_ground_albedo;
        /// <summary>
        /// [mm/d] threshold snowfall rate to refresh albedo to fresh snow (~10 mm/d)
        /// </summary>
        public double snowfall_albthresh;

        /// <summary>
        /// [mm] avg annual snow as SWE
        /// </summary>
        public double avg_annual_snow;
        /// <summary>
        /// [mm] avg annual runoff from basin
        /// </summary>
        public double avg_annual_runoff;
        /// <summary>
        /// [-] multiplier for reference flow relative to annual mean flow (10 for flood modelling, 0.5 for low-flow conditions)
        /// </summary>
        public double reference_flow_mult;

        /// <summary>
        /// [km] maximum reach segment length
        /// </summary>
        public double max_reach_seglength;
        /// <summary>
        /// [mm] maximum SWE in surface snow layer
        /// </summary>
        public double max_SWE_surface;

        /// <summary>
        /// parameters for orographic corrections
        /// </summary>
        public UBCLapse UBC_lapse_params;
        /// <summary>
        /// UBC snow parameters
        /// </summary>
        public UBCSnowParameters UBC_snow_params;
        /// <summary>
        /// UBC solar radiation corrections
        /// </summary>
        public readonly double[] UBC_s_corr = new double[12];
        public readonly double[] UBC_n_corr = new double[12];

        /// <summary>
        /// UBC GW Split parameter [0..1]
        /// </summary>
        public double UBC_GW_split;
        /// <summary>
        /// UBC Sun exposure factor of forested areas (F0ERGY) [0..1]
        /// </summary>
        public double UBC_exposure_fact;
        /// <summary>
        /// UBC Fraction of solar radiation penetrating cloud cover [0..1]
        /// </summary>
        public double UBC_cloud_penet;
        /// <summary>
        /// UBC mulitplier of temperature to estimate LW radiation in forests (P0BLUE*P0LWVF) [mm/d/K]
        /// </summary>
        public double UBC_LW_forest_fact;
        /// <summary>
        /// UBC ponding threshold for flash factor (V0FLAS) [mm]
        /// </summary>
        public double UBC_flash_ponding;

        /// <summary>
        /// HBV-EC precipitation lapse rate below HBVEC_lapse_elev [mm/d/km] (PCALT*1000 in HBV, PGRADL*1000 in HBV-EC)
        /// </summary>
        public double HBVEC_lapse_rate;
        /// <summary>
        /// HBV-EC precipitation lapse rate above HBVEC_lapse_elev [mm/d/km] (PCALTUP*1000 in HBV, PGRADH*1000 in HBV-EC)
        /// </summary>
        public double HBVEC_lapse_upper;
        /// <summary>
        /// HBV-EC precipitation lapse rate shift elevation [m]  (PCALTL/EMID in HBV-EC)
        /// </summary>
        public double HBVEC_lapse_elev;

        /// <summary>
        /// [1/d] air/snow heat transfer coefficient
        /// </summary>
        public double airsnow_coeff;

        /// <summary>
        /// [mm/d] MOHYSE PET constant (PET @ equinox when temperature is 10 degC)
        /// </summary>
        public double MOHYSE_PET_coeff;

        /// <summary>
        /// [0..1] numerical relaxation parameter for overridden reservoir outflows/target stage [~0.4]
        /// </summary>
        public double reservoir_relax;
        /// <summary>
        /// [mm] time of concentration multiplier
        /// </summary>
        public double TOC_multiplier;
        /// <summary>
        /// [0..1+] time to peak multiplier
        /// </summary>
        public double TIME_TO_PEAK_multiplier;
        /// <summary>
        /// [0..1+] Gamma shape multiplier
        /// </summary>
        public double GAMMA_SHAPE_multiplier;
        /// <summary>
        /// [0..1+] Gamma scale multiplier
        /// </summary>
        public double GAMMA_SCALE_multiplier;
        /// <summary>
        /// [0..1] assimilation factor (0=no assimilation to 1= full replacement)
        /// </summary>
        public double assimilation_fact;
        /// <summary>
        /// [1/km] assimilation upstream decay factor (0= overrides everything upstream, large- observation influence decays quickly with distance from gauge) [~0.01]
        /// </summary>
        public double assim_upstream_decay;
        /// <summary>
        /// [1/d] assimilation temporal decay factor (0=diminishes in future, 0.1 - diminshes in  3 days) [0.2]
        /// </summary>
        public double assim_time_decay;

        /// <summary>
        /// [0..1+] multiplier of irrigation demand to be met by upstream reservoirs
        /// </summary>
        public double reservoir_demand_mult;

        /// <summary>
        /// [C] intial stream temperature
        /// </summary>
        public double init_stream_temp;

        /// <summary>
        /// [m/s] intercept parameter for regression between wind vel. and F(T_max-T_min)
        /// </summary>
        public double windvel_icept;
        /// <summary>
        /// [changes] slope parameter for regression between wind vel. and F(T_max-T_min)
        /// </summary>
        public double windvel_scale;


        public static ModelParameters Default()
        {
            var G = new ModelParameters();
            G.snow_SWI = 0.05;
            G.snow_SWI_min = 0.05;
            G.snow_SWI_max = 0.05;
            G.snow_temperature = FREEZING_TEMP;
            G.snow_roughness = 0.0002;
            G.rainsnow_temp = 0.15;
            G.rainsnow_delta = 2.0;
            G.max_SWE_surface = 100.0;
            G.TOC_multiplier = 1.0;
            G.TIME_TO_PEAK_multiplier = 1.0;
            G.GAMMA_SHAPE_multiplier = 1.0;
            G.GAMMA_SCALE_multiplier = 1.0;
            G.reference_flow_mult = 10;
            G.adiabatic_lapse = 6.4;
            G.wet_adiabatic_lapse = 6.4;
            G.precip_lapse = 0.0;

            for (int i = 0; i < 12; i++)
            {
                G.UBC_s_corr[i] = 1.0;
                G.UBC_n_corr[i] = 1.0;
            }
            G.max_snow_albedo = 0.95;
            G.min_snow_albedo = 0.3;
            G.alb_decay_cold = 0.008;
            G.alb_decay_melt = 0.12;
            G.bare_ground_albedo = 0.25;
            G.snowfall_albthresh = 10;
            G.UBC_exposure_fact = 0.01;
            G.UBC_cloud_penet = 0.25;
            G.UBC_LW_forest_fact = 0.76;
            G.UBC_flash_ponding = 36;
            G.max_reach_seglength = DEFAULT_MAX_REACHLENGTH;
            G.reservoir_relax = 0.4;
            G.assimilation_fact = 1.0;
            G.assim_upstream_decay = 0.01;
            G.assim_time_decay = 0.2;
            G.reservoir_demand_mult = 1.0;
            G.HBVEC_lapse_rate = 0.08;
            G.HBVEC_lapse_upper = 0.0;
            G.HBVEC_lapse_elev = 5000.0;


            return G;
        }


    }

}
