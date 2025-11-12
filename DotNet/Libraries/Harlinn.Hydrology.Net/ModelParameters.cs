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
    /// Global model parameters
    /// </summary>
    public class ModelParameters
    {
        /// <summary>
        /// [degC/km]
        /// </summary>
        double adiabatic_lapse;
        /// <summary>
        /// [degC/km]
        /// </summary>
        double wet_adiabatic_lapse;
        /// <summary>
        /// [mm/d/km] precipitation lapse rate for orographic correction
        /// </summary>
        double precip_lapse;

        /// <summary>
        /// [degC] rain/snow halfway transition temperature  (-0.15 for dingman, 0.0 for HBV, ~1 for UBC)
        /// </summary>
        double rainsnow_temp;
        /// <summary>
        /// [degC] range of rain-snow transition zone (around rainsnow_temp) (4.0 for HBV, 2.0 for UBC)
        /// </summary>
        double rainsnow_delta;
        /// <summary>
        /// [0..1] ~0.05, 0.07 irreducible water saturation fraction of snow
        /// </summary>
        double snow_SWI;

        //   =WHC in HBV-EC, WATCAP in UBCWM, SWI in GAWSER

        /// <summary>
        /// [0..1] minimum irreducible sat fraction
        /// </summary>
        double snow_SWI_min;
        /// <summary>
        /// [0..1] maximum irreducible sat fraction
        /// </summary>
        double snow_SWI_max;
        /// <summary>
        /// [1/mm] SWI reduction factor with cumulative snowmelt
        /// </summary>
        double SWI_reduct_coeff;
        /// <summary>
        /// [degC]   default snow temperature if not explicitly modelled
        /// </summary>
        double snow_temperature;
        /// <summary>
        /// [m]  roughness height of snow
        /// </summary>
        double snow_roughness;
        /// <summary>
        /// [0..1] very old snow/glacier albedo (~0.3)
        /// </summary>
        double min_snow_albedo;
        /// <summary>
        /// [0..1] albedo of fresh snow  (~0.95)
        /// </summary>
        double max_snow_albedo;
        /// <summary>
        /// [1/d] 1st order albedo decay rate for cold conditions (~0.008/d)
        /// </summary>
        double alb_decay_cold;
        /// <summary>
        /// [1/d] albedo decay rate for melt conditions (~0.12/d)
        /// </summary>
        double alb_decay_melt;
        /// <summary>
        /// [0..1] bare ground albedo (~0.1-0.4)
        /// </summary>
        double bare_ground_albedo;
        /// <summary>
        /// [mm/d] threshold snowfall rate to refresh albedo to fresh snow (~10 mm/d)
        /// </summary>
        double snowfall_albthresh;

        /// <summary>
        /// [mm] avg annual snow as SWE
        /// </summary>
        double avg_annual_snow;
        /// <summary>
        /// [mm] avg annual runoff from basin
        /// </summary>
        double avg_annual_runoff;
        /// <summary>
        /// [-] multiplier for reference flow relative to annual mean flow (10 for flood modelling, 0.5 for low-flow conditions)
        /// </summary>
        double reference_flow_mult;

        /// <summary>
        /// [km] maximum reach segment length
        /// </summary>
        double max_reach_seglength;
        /// <summary>
        /// [mm] maximum SWE in surface snow layer
        /// </summary>
        double max_SWE_surface;

        /// <summary>
        /// parameters for orographic corrections
        /// </summary>
        UBCLapse UBC_lapse_params;
        /// <summary>
        /// UBC snow parameters
        /// </summary>
        UBCSnowParameters UBC_snow_params;
        /// <summary>
        /// UBC solar radiation corrections
        /// </summary>
        readonly double[] UBC_s_corr = new double[12];
        readonly double[] UBC_n_corr = new double[12];

        /// <summary>
        /// UBC GW Split parameter [0..1]
        /// </summary>
        double UBC_GW_split;
        /// <summary>
        /// UBC Sun exposure factor of forested areas (F0ERGY) [0..1]
        /// </summary>
        double UBC_exposure_fact;
        /// <summary>
        /// UBC Fraction of solar radiation penetrating cloud cover [0..1]
        /// </summary>
        double UBC_cloud_penet;
        /// <summary>
        /// UBC mulitplier of temperature to estimate LW radiation in forests (P0BLUE*P0LWVF) [mm/d/K]
        /// </summary>
        double UBC_LW_forest_fact;
        /// <summary>
        /// UBC ponding threshold for flash factor (V0FLAS) [mm]
        /// </summary>
        double UBC_flash_ponding;

        /// <summary>
        /// HBV-EC precipitation lapse rate below HBVEC_lapse_elev [mm/d/km] (PCALT*1000 in HBV, PGRADL*1000 in HBV-EC)
        /// </summary>
        double HBVEC_lapse_rate;
        /// <summary>
        /// HBV-EC precipitation lapse rate above HBVEC_lapse_elev [mm/d/km] (PCALTUP*1000 in HBV, PGRADH*1000 in HBV-EC)
        /// </summary>
        double HBVEC_lapse_upper;
        /// <summary>
        /// HBV-EC precipitation lapse rate shift elevation [m]  (PCALTL/EMID in HBV-EC)
        /// </summary>
        double HBVEC_lapse_elev;

        /// <summary>
        /// [1/d] air/snow heat transfer coefficient
        /// </summary>
        double airsnow_coeff;

        /// <summary>
        /// [mm/d] MOHYSE PET constant (PET @ equinox when temperature is 10 degC)
        /// </summary>
        double MOHYSE_PET_coeff;

        /// <summary>
        /// [0..1] numerical relaxation parameter for overridden reservoir outflows/target stage [~0.4]
        /// </summary>
        double reservoir_relax;
        /// <summary>
        /// [mm] time of concentration multiplier
        /// </summary>
        double TOC_multiplier;
        /// <summary>
        /// [0..1+] time to peak multiplier
        /// </summary>
        double TIME_TO_PEAK_multiplier;
        /// <summary>
        /// [0..1+] Gamma shape multiplier
        /// </summary>
        double GAMMA_SHAPE_multiplier;
        /// <summary>
        /// [0..1+] Gamma scale multiplier
        /// </summary>
        double GAMMA_SCALE_multiplier;
        /// <summary>
        /// [0..1] assimilation factor (0=no assimilation to 1= full replacement)
        /// </summary>
        double assimilation_fact;
        /// <summary>
        /// [1/km] assimilation upstream decay factor (0= overrides everything upstream, large- observation influence decays quickly with distance from gauge) [~0.01]
        /// </summary>
        double assim_upstream_decay;
        /// <summary>
        /// [1/d] assimilation temporal decay factor (0=diminishes in future, 0.1 - diminshes in  3 days) [0.2]
        /// </summary>
        double assim_time_decay;

        /// <summary>
        /// [0..1+] multiplier of irrigation demand to be met by upstream reservoirs
        /// </summary>
        double reservoir_demand_mult;

        /// <summary>
        /// [C] intial stream temperature
        /// </summary>
        double init_stream_temp;

        /// <summary>
        /// [m/s] intercept parameter for regression between wind vel. and F(T_max-T_min)
        /// </summary>
        double windvel_icept;
        /// <summary>
        /// [changes] slope parameter for regression between wind vel. and F(T_max-T_min)
        /// </summary>
        double windvel_scale;
    }

}
