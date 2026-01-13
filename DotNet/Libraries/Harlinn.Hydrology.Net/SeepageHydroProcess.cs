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
using static Harlinn.Mathematics.Net.Common;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Calculates the seepage of depression storage into lower soils
    /// </summary>
    public class SeepageHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> linearParameters = new ParameterInfo[]
        {
            new ParameterInfo("DEP_SEEP_K", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<StateVariableInfo> stateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.DEPRESSION)
        };

        /// <summary>
        /// Model of abstaction selected
        /// </summary>
        SeepageType _type; 

        public SeepageHydroProcess(Model model, SeepageType stype, int iToSoil)
            : base(model, HydroProcessType.SEEPAGE)
        {
            if(iToSoil == DOESNT_EXIST)
            {
                throw new ArgumentException("SeepageHydroProcess Constructor: invalid to compartment specified");
            }
            _type = stype;

            DynamicSpecifyConnections(1);
            
            FromIndices[0] = model.GetStateVarIndex(SVType.DEPRESSION);
            ToIndices[0] = iToSoil;
        }

        public override void Initialize()
        {
            if((Model.GetStateVarType(ToIndices[0]) != SVType.SOIL) &&
                  (Model.GetStateVarType(ToIndices[0]) != SVType.GROUNDWATER))
            { 
                throw new Exception("SeepageHydroProcess.Initialize: seepage must move water to soil or groundwater unit");
            }
        }

        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            if (_type == SeepageType.SEEP_LINEAR)
            {
                return linearParameters;
            }
            else
            {
                throw new InvalidOperationException("SeepageHydroProcess.GetParticipatingParamList: undefined seepage algorithm");
            }
        }

        

        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(SeepageType seepageType)
        {
            return stateVariableInfos;
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            double stor = stateVars[FromIndices[0]];

            if (_type == SeepageType.SEEP_LINEAR)
            {
                double dep_k = hydroUnit.GetSurfaceProps().dep_seep_k;

                //analytical formulation
                rates[0] = Max(stor, 0.0) * (1 - Exp(-dep_k * options.timestep)) / options.timestep; 
            }
        }

        public override void ApplyConstraints(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            // cannot remove more than is there
            rates[0] = ThreshMin(rates[0], Max(stateVars[FromIndices[0]] / options.timestep, 0.0), 0.0);

            // can't overfill target storage
            // water flow simply slows (or stops) so that receptor will not overfill during tstep
            double room = ThreshMax(hydroUnit.GetStateVarMax(ToIndices[0], stateVars, options) - stateVars[ToIndices[0]], 0.0, 0.0);
            rates[0] = ThreshMin(rates[0], room / options.timestep, 0.0);
        }


    }

}
