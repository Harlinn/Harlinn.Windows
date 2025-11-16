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
    public class GlobalParams
    {
        ModelParameters _parameters;

        public GlobalParams()
        {
            _parameters = new ModelParameters();
        }

        public ModelParameters GetParams()
        {
            return _parameters;
        }

        public double GetParameter(string paramName)
        {
            return GetGlobalProperty(_parameters, paramName);
        }


        static public void AutoCalculateGlobalParams(ModelParameters Gtmp, ModelParameters Gtemplate)
        {

        }

        static public double GetGlobalProperty(ModelParameters modelParameters, string param_name, bool strict = true)
        {
            string name = param_name.ToUpper();

            if (name.Equals("RAINSNOW_TEMP")) { return modelParameters.rainsnow_temp; }
            else if (name.Equals("SNOW_SWI")) { return modelParameters.snow_SWI; }
            else if (name.Equals("SNOW_SWI_MIN")) { return modelParameters.snow_SWI_min; }
            else if (name.Equals("SNOW_SWI_MAX")) { return modelParameters.snow_SWI_max; }
            else if (name.Equals("SWI_REDUCT_COEFF")) { return modelParameters.SWI_reduct_coeff; }
            else if (name.Equals("SNOW_TEMPERATURE")) { return modelParameters.snow_temperature; }
            else if (name.Equals("SNOW_ROUGHNESS")) { return modelParameters.snow_roughness; }
            else if (name.Equals("RAINSNOW_DELTA")) { return modelParameters.rainsnow_delta; }
            else if (name.Equals("ADIABATIC_LAPSE")) { return modelParameters.adiabatic_lapse; }
            else if (name.Equals("REFERENCE_FLOW_MULT")) { return modelParameters.reference_flow_mult; }
            else if (name.Equals("WET_ADIABATIC_LAPSE")) { return modelParameters.wet_adiabatic_lapse; }
            else if (name.Equals("PRECIP_LAPSE")) { return modelParameters.precip_lapse; }

            else if (name.Equals("TOC_MULTIPLIER")) { return modelParameters.TOC_multiplier; }
            else if (name.Equals("TIME_TO_PEAK_MULTIPLIER")) { return modelParameters.TIME_TO_PEAK_multiplier; }
            else if (name.Equals("GAMMA_SHAPE_MULTIPLIER")) { return modelParameters.GAMMA_SHAPE_multiplier; }
            else if (name.Equals("GAMMA_SCALE_MULTIPLIER")) { return modelParameters.GAMMA_SCALE_multiplier; }

            //WARNING: this get only returns the first (zero-index) element of the 12 SW correction parameters
            else if (name.Equals("UBC_SW_N_CORR")) { return modelParameters.UBC_n_corr[0]; }
            else if (name.Equals("UBC_SW_S_CORR")) { return modelParameters.UBC_s_corr[0]; }

            else if (name.Equals("MAX_SNOW_ALBEDO")) { return modelParameters.max_snow_albedo; }
            else if (name.Equals("MIN_SNOW_ALBEDO")) { return modelParameters.min_snow_albedo; }
            else if (name.Equals("ALB_DECAY_COLD")) { return modelParameters.alb_decay_cold; }
            else if (name.Equals("ALB_DECAY_MELT")) { return modelParameters.alb_decay_melt; }
            else if (name.Equals("BARE_GROUND_ALBEDO")) { return modelParameters.bare_ground_albedo; }
            else if (name.Equals("SNOWFALL_ALBTHRESH")) { return modelParameters.snowfall_albthresh; }
            else if (name.Equals("UBC_ALBASE")) { return modelParameters.UBC_snow_params.ALBASE; }
            else if (name.Equals("UBC_ALBREC")) { return modelParameters.UBC_snow_params.ALBREC; }
            else if (name.Equals("UBC_ALBSNW")) { return modelParameters.UBC_snow_params.ALBSNW; }
            else if (name.Equals("UBC_MAX_CUM_MELT")) { return modelParameters.UBC_snow_params.MAX_CUM_MELT; }
            else if (name.Equals("UBC_GW_SPLIT")) { return modelParameters.UBC_GW_split; }
            else if (name.Equals("UBC_FLASH_PONDING")) { return modelParameters.UBC_flash_ponding; }
            else if (name.Equals("UBC_EXPOSURE_FACT")) { return modelParameters.UBC_exposure_fact; }
            else if (name.Equals("UBC_CLOUD_PENET")) { return modelParameters.UBC_cloud_penet; }
            else if (name.Equals("UBC_LW_FOREST_FACT")) { return modelParameters.UBC_LW_forest_fact; }

            else if (name.Equals("UBC_A0PELA")) { return modelParameters.UBC_lapse_params.A0PELA; }
            else if (name.Equals("UBC_A0PPTP")) { return modelParameters.UBC_lapse_params.A0PPTP; }
            else if (name.Equals("UBC_A0STAB")) { return modelParameters.UBC_lapse_params.A0STAB; }
            else if (name.Equals("UBC_A0TLXM")) { return modelParameters.UBC_lapse_params.A0TLXM; }
            else if (name.Equals("UBC_A0TLNH")) { return modelParameters.UBC_lapse_params.A0TLNH; }
            else if (name.Equals("UBC_A0TLNM")) { return modelParameters.UBC_lapse_params.A0TLNM; }
            else if (name.Equals("UBC_A0TLXH")) { return modelParameters.UBC_lapse_params.A0TLXH; }
            else if (name.Equals("UBC_E0LHI")) { return modelParameters.UBC_lapse_params.E0LHI; }
            else if (name.Equals("UBC_E0LLOW")) { return modelParameters.UBC_lapse_params.E0LLOW; }
            else if (name.Equals("UBC_E0LMID")) { return modelParameters.UBC_lapse_params.E0LMID; }
            else if (name.Equals("UBC_P0GRADL")) { return modelParameters.UBC_lapse_params.P0GRADL; }
            else if (name.Equals("UBC_P0GRADM")) { return modelParameters.UBC_lapse_params.P0GRADM; }
            else if (name.Equals("UBC_P0GRADU")) { return modelParameters.UBC_lapse_params.P0GRADU; }
            else if (name.Equals("UBC_P0TEDL")) { return modelParameters.UBC_lapse_params.P0TEDL; }
            else if (name.Equals("UBC_P0TEDU")) { return modelParameters.UBC_lapse_params.P0TEDU; }
            else if (name.Equals("UBC_MAX_RANGE_TEMP")) { return modelParameters.UBC_lapse_params.max_range_temp; }

            else if (name.Equals("AIRSNOW_COEFF")) { return modelParameters.airsnow_coeff; }
            else if (name.Equals("AVG_ANNUAL_SNOW")) { return modelParameters.avg_annual_snow; }
            else if (name.Equals("AVG_ANNUAL_RUNOFF")) { return modelParameters.avg_annual_runoff; }
            else if (name.Equals("INIT_STREAM_TEMP")) { return modelParameters.init_stream_temp; }
            else if (name.Equals("MAX_SWE_SURFACE")) { return modelParameters.max_SWE_surface; }
            else if (name.Equals("MOHYSE_PET_COEFF")) { return modelParameters.MOHYSE_PET_coeff; }
            else if (name.Equals("MAX_REACH_SEGLENGTH")) { return modelParameters.max_reach_seglength; }
            else if (name.Equals("RESERVOIR_RELAX")) { return modelParameters.reservoir_relax; }
            else if (name.Equals("ASSIMILATION_FACT")) { return modelParameters.assimilation_fact; }
            else if (name.Equals("ASSIM_UPSTREAM_DECAY")) { return modelParameters.assim_upstream_decay; }
            else if (name.Equals("ASSIM_TIME_DECAY")) { return modelParameters.assim_time_decay; }
            else if (name.Equals("RESERVOIR_DEMAND_MULT")) { return modelParameters.reservoir_demand_mult; }
            else if (name.Equals("WINDVEL_ICEPT")) { return modelParameters.windvel_icept; }
            else if (name.Equals("WINDVEL_SCALE")) { return modelParameters.windvel_scale; }
            else if (name.Equals("HBVEC_LAPSE_RATE")) { return modelParameters.HBVEC_lapse_rate; }
            else if (name.Equals("HBVEC_LAPSE_UPPER")) { return modelParameters.HBVEC_lapse_upper; }
            else if (name.Equals("HBVEC_LAPSE_ELEV")) { return modelParameters.HBVEC_lapse_elev; }
            else
            {
                if (strict)
                {
                    throw new ArgumentException($"Unrecognized/invalid global parameter name:\"{name}\".", nameof(param_name));
                }
                else
                {
                    return INDEX_NOT_FOUND;
                }
            }
        }


    }
}
