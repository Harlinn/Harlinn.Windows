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
using static System.Math;
using static Harlinn.Hydrology.Common;
using static Harlinn.Mathematics.Net.Common;
namespace Harlinn.Hydrology
{
    /// <summary>
    /// Calculates the loss depression storage into surface water
    /// </summary>
    public class DepressionOverflowHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> threshpowParameters = [new ParameterInfo("DEP_THRESHOLD", ClassType.CLASS_LANDUSE), new ParameterInfo("DEP_N", ClassType.CLASS_LANDUSE), new ParameterInfo("DEP_MAX_FLOW", ClassType.CLASS_LANDUSE), new ParameterInfo("DEP_MAX", ClassType.CLASS_LANDUSE)];
        static readonly IReadOnlyList<ParameterInfo> linearParameters = [new ParameterInfo("DEP_THRESHOLD", ClassType.CLASS_LANDUSE), new ParameterInfo("DEP_K", ClassType.CLASS_LANDUSE)];
        static readonly IReadOnlyList<ParameterInfo> weirParameters = [new ParameterInfo("DEP_THRESHOLD", ClassType.CLASS_LANDUSE), new ParameterInfo("DEP_CRESTRATIO", ClassType.CLASS_LANDUSE)];

        static readonly IReadOnlyList<StateVariableInfo> stateVariableInfos = [new StateVariableInfo(SVType.DEPRESSION), new StateVariableInfo(SVType.SURFACE_WATER)];

        /// <summary>
        /// Model of abstaction selected
        /// </summary>
        DepflowType _type; 

        public DepressionOverflowHydroProcess(Model model, DepflowType dtype)
            : base(model, HydroProcessType.DEPRESSION_OVERFLOW)
        {
            _type = dtype;

            DynamicSpecifyConnections(1);
            
            FromIndices[0] = model.GetStateVarIndex(SVType.DEPRESSION);
            ToIndices[0] = model.GetStateVarIndex(SVType.SURFACE_WATER);
        }

        

        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            if (_type == DepflowType.DFLOW_THRESHPOW)
            {
                return threshpowParameters;
            }
            else if (_type == DepflowType.DFLOW_LINEAR)
            {
                return linearParameters;
            }
            else if (_type == DepflowType.DFLOW_WEIR)
            {
                return weirParameters;
            }
            else
            {
                throw new InvalidOperationException("DepressionOverflowHydroProcess.GetParticipatingParamList: undefined depression overflow algorithm");
            }
        }

        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(DepflowType dtype)
        {
            return stateVariableInfos;
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            double stor = stateVars[FromIndices[0]];
            
            if (_type == DepflowType.DFLOW_THRESHPOW)
            {
                double max_flow = hydroUnit.GetSurfaceProps().dep_max_flow;
                double n = hydroUnit.GetSurfaceProps().dep_n;
                double thresh_stor = hydroUnit.GetSurfaceProps().dep_threshold;
                double max_stor = hydroUnit.GetSurfaceProps().dep_max;

                if (max_stor < thresh_stor)
                {
                    rates[0] = max_flow;
                }
                else
                {
                    rates[0] = max_flow * Pow(Max((stor - thresh_stor) / (max_stor - thresh_stor), 0.0), n);
                }
            }
            else if (_type == DepflowType.DFLOW_LINEAR)
            {
                double thresh_stor = hydroUnit.GetSurfaceProps().dep_threshold;
                double dep_k = hydroUnit.GetSurfaceProps().dep_k;

                // analytical formulation
                rates[0] = Max(stor - thresh_stor, 0.0) * (1 - Exp(-dep_k * options.timestep)) / options.timestep; 
            }
            else if (_type == DepflowType.DFLOW_WEIR)
            {
                double thresh_stor = hydroUnit.GetSurfaceProps().dep_threshold;
                double dep_rat = hydroUnit.GetSurfaceProps().dep_crestratio;
                double area = hydroUnit.GetArea();
                double c = dep_rat * Sqrt(area); 

                rates[0] = 0.666 * c / area * Sqrt(2 * GRAVITY) * Pow(Max(stor - thresh_stor, 0.0), 1.5);
            }
        }

        public override void ApplyConstraints(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            // Cannot remove more than is there
            rates[0] = ThreshMin(rates[0], Max(stateVars[FromIndices[0]] / options.timestep, 0.0), 0.0);
        }

    }
}
