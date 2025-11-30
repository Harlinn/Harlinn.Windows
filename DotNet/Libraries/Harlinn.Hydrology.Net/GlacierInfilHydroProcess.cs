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
using static Harlinn.Hydrology.Common;
using static Harlinn.Mathematics.Net.Common;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Calculates glacier water infiltration to deep groundwater
    /// </summary>
    public class GlacierInfilHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> ubcwmParameters = new ParameterInfo[]
        {
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE),
            new ParameterInfo("MAX_PERC_RATE", ClassType.CLASS_SOIL),
            new ParameterInfo("UBC_INFIL_SOIL_DEF", ClassType.CLASS_SOIL),
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("UBC_GW_SPLIT", ClassType.CLASS_GLOBAL),
            new ParameterInfo("UBC_FLASH_PONDING", ClassType.CLASS_GLOBAL)
        };

        /// <summary>
        /// Specified algorithm for glacial infiltration simulation
        /// </summary>
        GlacialInfilType type;

        public GlacierInfilHydroProcess(Model model, GlacialInfilType i_type) 
            : base(model, HydroProcessType.GLACIER_INFIL)
        {
            type = i_type;

            if (type == GlacialInfilType.GINFIL_UBCWM)
            {
                DynamicSpecifyConnections(3);

                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[0] = model.GetStateVarIndex(SVType.GLACIER);

                FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[1] = model.GetStateVarIndex(SVType.SOIL, 2);

                FromIndices[2] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[2] = model.GetStateVarIndex(SVType.SOIL, 3);

            }
        }

        

        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            if (type == GlacialInfilType.GINFIL_UBCWM)
            {
                return ubcwmParameters;
            }
            else
            {
                throw new InvalidOperationException("GlacierInfilHydroProcess.GetParticipatingParamList: undefined glacial infil algorithm");
            }
        }


        static readonly IReadOnlyList<StateVariableInfo> ubcwmStateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.PONDED_WATER),
            new StateVariableInfo(SVType.SOIL, 2),
            new StateVariableInfo(SVType.SOIL, 3)
        };

        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(GlacialInfilType r_type)
        {
            if (r_type == GlacialInfilType.GINFIL_UBCWM)
            {
                return ubcwmStateVariableInfos;
            }
            else
            {
                throw new InvalidOperationException("GlacierInfilHydroProcess.GetParticipatingStateVarList: undefined glacial infil algorithm");
            }
        }


        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            if (hydroUnit.GetHRUType() != HRUType.HRU_GLACIER) 
            { 
                return; 
            }

            //-----------------------------------------------------------------
            if (type == GlacialInfilType.GINFIL_UBCWM)
            {
                double to_GW, runoff;
                double b2;

                double ponded = stateVars[FromIndices[0]];
                double rain_and_melt = ponded / options.timestep;

                double max_perc_rate = hydroUnit.GetSoilProps(1).max_perc_rate;
                double P0DSH = Model.GetGlobalParams().UBC_GW_split;

                //.NET
                //to_GW=0;
                //runoff=rain_and_melt;

                //RFS:
                b2 = g_debug_vars[0];//RFS Cheat - uses b2 calculated for adjacent soil
                to_GW = Min(max_perc_rate, rain_and_melt) * (1.0 - b2); //overflows to GW
                runoff = rain_and_melt * b2 + Max(rain_and_melt * (1 - b2) - to_GW, 0.0);

                rates[0] = runoff;              //ponded_water->glacier
                rates[1] = (1.0 - P0DSH) * to_GW;   //ponded_water->upper grounwater
                rates[2] = (P0DSH) * to_GW;   //ponded_water->lower groundwater
            }
        }

        public override void ApplyConstraints(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            if (hydroUnit.GetHRUType() != HRUType.HRU_GLACIER) 
            { 
                return; 
            }

            if (rates[0] < 0.0) 
            {
                // positivity constraint on runoff
                rates[0] = 0.0; 
            }

            // Cannot remove more than is there
            rates[0] = ThreshMin(rates[0], stateVars[FromIndices[0]] / options.timestep, 0.0);
        }




    }
}
