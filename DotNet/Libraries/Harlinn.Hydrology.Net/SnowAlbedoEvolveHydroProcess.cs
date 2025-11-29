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

using Microsoft.VisualBasic;
using static Harlinn.Hydrology.Constants;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Calculates the evolution of snow albedo
    /// </summary>
    public class SnowAlbedoEvolveHydroProcess : HydroProcess
    {
        /// <summary>
        /// Type of albedo algorithm selected
        /// </summary>
        SnowAlbedoType type;

        public SnowAlbedoEvolveHydroProcess(Model model, SnowAlbedoType snowAlbedoType)
            :base(model, HydroProcessType.SNOW_ALBEDO_EVOLVE)
        {
            type = snowAlbedoType;

            // Used by all snow albedo routines
            int iSnowAlbedo; 
            iSnowAlbedo = Model.GetStateVarIndex(SVType.SNOW_ALBEDO);
            Runtime.ExitGracefullyIf(iSnowAlbedo == DOESNT_EXIST, "SNOW ALBEDO EVOLVE: snow albedo state variable required", ExitCode.BAD_DATA);

            if ((type == SnowAlbedoType.SNOALB_UBCWM) || (type == SnowAlbedoType.SNOALB_CRHM_ESSERY))
            {
                DynamicSpecifyConnections(1);
                FromIndices[0] = iSnowAlbedo; 
                ToIndices[0] = iSnowAlbedo;
            }
            else if (type == SnowAlbedoType.SNOALB_BAKER)
            {
                int iSnowAge = Model.GetStateVarIndex(SVType.SNOW_AGE);
                DynamicSpecifyConnections(2);
                FromIndices[0] = iSnowAlbedo; ToIndices[0] = iSnowAlbedo;
                FromIndices[1] = iSnowAge; ToIndices[1] = iSnowAge;
            }
            else
            {
                Runtime.ExitGracefully("SnowAlbedoEvolveHydroProcess Constructor: undefined snow albedo algorithm", ExitCode.BAD_DATA);
            }
        }


        public override void GetParticipatingParamList(out string[] aP, out ClassType[] aPC)
        {
            if (type == SnowAlbedoType.SNOALB_UBCWM)
            {
                aP = new string[6];
                aPC = new ClassType[6] { ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL };
                aP[0] = "MAX_SNOW_ALBEDO"; 
                aP[1] = "MIN_SNOW_ALBEDO"; 
                aP[2] = "UBC_ALBASE"; 
                aP[3] = "UBC_ALBREC"; 
                aP[4] = "UBC_MAX_CUM_MELT"; 
                aP[5] = "UBC_ALBSNW"; 
            }
            else if (type == SnowAlbedoType.SNOALB_CRHM_ESSERY)
            {
                aP = new string[6];
                aPC = new ClassType[6] { ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL };
                aP[0] = "ALB_DECAY_COLD";
                aP[1] = "ALB_DECAY_MELT";
                aP[2] = "MIN_SNOW_ALBEDO";
                aP[3] = "MAX_SNOW_ALBEDO";
                aP[4] = "BARE_GROUND_ALBEDO"; 
                aP[5] = "SNOWFALL_ALBTHRESH"; 
            }
            else if (type == SnowAlbedoType.SNOALB_BAKER)
            {
                aP = new string[2];
                aPC = new ClassType[2] { ClassType.CLASS_GLOBAL, ClassType.CLASS_GLOBAL };
                aP[0] = "BARE_GROUND_ALBEDO";
                aP[1] = "SNOWFALL_ALBTHRESH";
            }
            else
            {
                aP = new string[0];
                aPC = new ClassType[0];
                Runtime.ExitGracefully("SnowAlbedoEvolveHydroProcess GetParticipatingParamList: undefined snow albedo algorithm", ExitCode.BAD_DATA);
            }
        }

        public static void GetParticipatingStateVarList(SnowAlbedoType snowAlbedoType, out SVType[] aSV, out int[] aLev)
        {

            if (snowAlbedoType == SnowAlbedoType.SNOALB_UBCWM)
            {
                aSV = new SVType[3];
                aLev = [DOESNT_EXIST, DOESNT_EXIST, DOESNT_EXIST ];
                aSV[0] = SVType.SNOW_ALBEDO; 
                aSV[1] = SVType.SNOW; 
                aSV[2] = SVType.CUM_SNOWMELT;
            }
            else if (snowAlbedoType == SnowAlbedoType.SNOALB_CRHM_ESSERY)
            {
                aSV = new SVType[3];
                aLev = [DOESNT_EXIST, DOESNT_EXIST, DOESNT_EXIST];
                aSV[0] = SVType.SNOW_ALBEDO;
                aSV[1] = SVType.SNOW;
                aSV[2] = SVType.SNOW_TEMP;
            }
            else if (snowAlbedoType == SnowAlbedoType.SNOALB_BAKER)
            {
                aSV = new SVType[3];
                aLev = [DOESNT_EXIST, DOESNT_EXIST, DOESNT_EXIST];
                aSV[0] = SVType.SNOW_ALBEDO;
                aSV[1] = SVType.SNOW;
                aSV[2] = SVType.SNOW_AGE;
            }
            else
            {
                aSV = new SVType[1];
                aLev = [DOESNT_EXIST];
                aSV[0] = SVType.SNOW_ALBEDO;
            }
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            var F = hydroUnit.GetForcingFunctions();

            if (type == SnowAlbedoType.SNOALB_UBCWM)
            {
                double snow, albedo, cum_melt, snowfall, old_albedo;

                UBCSnowParameters PP = Model.GetGlobalParams().UBC_snow_params;
                double min_alb = Model.GetGlobalParams().min_snow_albedo;
                double max_alb = Model.GetGlobalParams().max_snow_albedo;

                snow = stateVars[Model.GetStateVarIndex(SVType.SNOW)];
                albedo = stateVars[Model.GetStateVarIndex(SVType.SNOW_ALBEDO)];
                cum_melt = stateVars[Model.GetStateVarIndex(SVType.CUM_SNOWMELT)];
                snowfall = F.precip * F.snow_frac;

                old_albedo = albedo;
                //snow albedo decay
                if (snow > REAL_SMALL || snowfall > REAL_SMALL)
                {
                    albedo = Math.Min(albedo, max_alb);

                    if (albedo > PP.ALBASE)
                    {
                        double albrec_factor = Math.Pow(PP.ALBREC, options.timestep);
                        albedo *= albrec_factor;
                    }

                    else if (albedo < PP.ALBASE)
                    { 
                        //separate if in case the previous change goes below ALBASE
                        albedo = PP.ALBASE * Math.Exp(-cum_melt / PP.MAX_CUM_MELT);
                    }
                    albedo = Math.Max(albedo, min_alb);

                    if (snowfall > 0)//increase in snow albedo
                    {
                        albedo += Math.Min(snowfall * options.timestep / PP.ALBSNW, 1.0) * (max_alb - albedo);
                    }
                }

                rates[0] = (albedo - old_albedo) / options.timestep;
            }
            else if (type == SnowAlbedoType.SNOALB_CRHM_ESSERY)
            { 
                // ported from CRHM (Pomeroy, 2007) routine ClassalbedoRichard::run
                double tstep = options.timestep;

                // Albedo decay time constant for cold snow (~0.008/d)
                double a1 = Model.GetGlobalParams().alb_decay_cold;
                // Albedo decay time constant for melting snow (~0.12/d)
                double a2 = Model.GetGlobalParams().alb_decay_melt;
                double albmin = Model.GetGlobalParams().min_snow_albedo;
                double albmax = Model.GetGlobalParams().max_snow_albedo;
                double albbare = Model.GetGlobalParams().bare_ground_albedo;
                // Minimum snowfall to refresh snow albedo [mm/d] (~10 mm/d)
                double snowfall_th = Model.GetGlobalParams().snowfall_albthresh;

                double albedo = stateVars[Model.GetStateVarIndex(SVType.SNOW_ALBEDO)];
                double SWE = stateVars[Model.GetStateVarIndex(SVType.SNOW)];
                double snow_temp = stateVars[Model.GetStateVarIndex(SVType.SNOW_TEMP)];
                double old_albedo = albedo;

                if (SWE > 1.0) //1mm threshold
                {
                    if (snow_temp < 0) 
                    {
                        // cold snow - 0th order decay
                        albedo -= a1 * tstep; 
                    } 
                    else 
                    {
                        // melting snow -1st order decay
                        albedo = (albedo - albmin) * Math.Exp(-a2 * tstep) + albmin; 
                    } 

                    albedo += (albmax - albedo) * ((F.snow_frac * F.precip) / snowfall_th);

                    albedo = Math.Max(albedo, albmin);
                    albedo = Math.Min(albedo, albmax);
                }
                else
                {
                    albedo = albbare;
                }
                rates[0] = (albedo - old_albedo) / tstep;
            }
            else if (type == SnowAlbedoType.SNOALB_BAKER)
            {
                // albedo decay formulation after Baker, D.G., Ruschy, D.L., Wall, D.B., 1990. The albedo decay of prairie snows. J. Appl. Meteor. 29 _2, 179-187
                double tstep = options.timestep;

                double SWE = stateVars[Model.GetStateVarIndex(SVType.SNOW)];
                double albedo = stateVars[Model.GetStateVarIndex(SVType.SNOW_ALBEDO)];
                double snow_age = stateVars[Model.GetStateVarIndex(SVType.SNOW_AGE)];

                //Minimum snowfall to refresh snow albedo [mm/d] (~10 mm/d)
                double snowfall_th = Model.GetGlobalParams().snowfall_albthresh;
                double albbare = Model.GetGlobalParams().bare_ground_albedo;

                double old_albedo = albedo;
                
                //time [d] since albedo refresh
                double old_snowage = snow_age;

                if (SWE > 1.0)
                {
                    if ((F.snow_frac * F.precip) > snowfall_th) 
                    { 
                        snow_age = 0.0; 
                    }
                    else 
                    { 
                        snow_age += tstep; 
                    }
                    
                    albedo = 0.9 - 0.0473 * Math.Pow(snow_age, 0.1);
                    albedo = Math.Max(albedo, albbare);
                }
                else
                {
                    snow_age = 0.0;
                    albedo = albbare;
                }
                rates[0] = (albedo - old_albedo) / tstep;
                rates[1] = (snow_age - old_snowage) / tstep;
            }
        }

        public override void ApplyConstraints(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            double albedo = stateVars[Model.GetStateVarIndex(SVType.SNOW_ALBEDO)];
            
            rates[0] = Math.Min(rates[0], (1.0 - albedo) / options.timestep);
            rates[0] = Math.Max(rates[0], -albedo / options.timestep);
        }

    }

}
