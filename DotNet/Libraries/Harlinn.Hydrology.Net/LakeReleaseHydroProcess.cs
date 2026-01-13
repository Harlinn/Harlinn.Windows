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
    /// calculates release of lake storage into surface water
    /// </summary>
    public class LakeReleaseHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> linearParameters = new ParameterInfo[]
        {
            new ParameterInfo("LAKE_REL_COEFF", ClassType.CLASS_LANDUSE)
        };

        /// <summary>
        /// Model of abstraction selected
        /// </summary>
        LakeRelType _type;

        public LakeReleaseHydroProcess(Model model, LakeRelType lktype)
            : base(model, HydroProcessType.LAKE_RELEASE)
        {
            _type = lktype;

            DynamicSpecifyConnections(1);
            FromIndices[0] = model.GetLakeStorageIndex();
            ToIndices[0] = model.GetStateVarIndex(SVType.SURFACE_WATER);

            if (FromIndices[0] == DOESNT_EXIST)
            {
                throw new ArgumentException("LakeReleaseHydroProcess Constructor: invalid lake storage compartment specified");
            }

            if (FromIndices[0] == (int)SVType.SURFACE_WATER)
            {
                string warn = "LakeReleaseHydroProcess Constructor: shouldn't use lake release if surface water is lake reservoir - it does nothing";
                Runtime.WriteWarning(warn, true);
            }
        }


        

        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            if (_type == LakeRelType.LAKEREL_LINEAR)
            {
                return linearParameters;
            }
            else
            {
                throw new InvalidOperationException("LakeReleaseHydroProcess.GetParticipatingParamList: invalid lake release type");
            }
        }

        static readonly IReadOnlyList<StateVariableInfo> stateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.SURFACE_WATER)
        };

        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(LakeRelType lakeRelType)
        {
            return stateVariableInfos;
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            if (!hydroUnit.IsLake) 
            { 
                return; 
            }

            if (hydroUnit.IsLinkedToReservoir) 
            {
                //reservoir-linked HRUs release directly to surface water
                rates[0] = stateVars[FromIndices[0]] / options.timestep; 
            }

            if (_type == LakeRelType.LAKEREL_LINEAR)
            {
                double K = hydroUnit.GetSurfaceProps().lake_rel_coeff;
                rates[0] = stateVars[FromIndices[0]] * (1 - Exp(-K * options.timestep)) / options.timestep;
            }
        }

        public override void ApplyConstraints(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            // cannot create negative surface water storage
            rates[0] = ThreshMax(rates[0], -stateVars[ToIndices[0]] / options.timestep, 0.0);
        }

    }
}
