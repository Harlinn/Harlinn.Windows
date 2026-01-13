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
    /// release of glacier meltwater storage
    /// </summary>
    public class GlacierReleaseHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> hbvParameters = new ParameterInfo[]
        {
            new ParameterInfo("HBV_GLACIER_KMIN", ClassType.CLASS_LANDUSE),
            new ParameterInfo("GLAC_STORAGE_COEFF", ClassType.CLASS_LANDUSE),
            new ParameterInfo("HBV_GLACIER_AG", ClassType.CLASS_LANDUSE)
        };
        static readonly IReadOnlyList<ParameterInfo> linearParameters = new ParameterInfo[]
        {
            new ParameterInfo("GLAC_STORAGE_COEFF", ClassType.CLASS_LANDUSE)
        };


        static readonly IReadOnlyList<StateVariableInfo> hbvecStateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.GLACIER),
            new StateVariableInfo(SVType.SNOW),
            new StateVariableInfo(SVType.SNOW_LIQ),
            new StateVariableInfo(SVType.PONDED_WATER)
        };


        static readonly IReadOnlyList<StateVariableInfo> linearStateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.GLACIER)
        };


        /// <summary>
        /// Specified algorithm for glacial meltwater release simulation
        /// </summary>
        GlacialReleaseType _type;

        public GlacierReleaseHydroProcess(Model model, GlacialReleaseType r_type ) 
            : base(model, HydroProcessType.GLACIER_RELEASE)
        {
            _type = r_type;

            if ((_type == GlacialReleaseType.GRELEASE_HBV_EC) || (_type == GlacialReleaseType.GRELEASE_LINEAR) || (_type == GlacialReleaseType.GRELEASE_LINEAR_ANALYTIC))
            {
                DynamicSpecifyConnections(1);

                FromIndices[0] = model.GetStateVarIndex(SVType.GLACIER);
                ToIndices[0] = model.GetStateVarIndex(SVType.SURFACE_WATER);
            }
        }


        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            if (_type == GlacialReleaseType.GRELEASE_HBV_EC)
            {
                return hbvParameters;
            }
            else if (_type == GlacialReleaseType.GRELEASE_LINEAR || _type == GlacialReleaseType.GRELEASE_LINEAR_ANALYTIC)
            {
                return linearParameters;
            }
            else
            {
                throw new InvalidOperationException("Unknown glacial release algorithm");
            }
        }

        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(GlacialReleaseType r_type)
        {
            if (r_type == GlacialReleaseType.GRELEASE_HBV_EC)
            {
                return hbvecStateVariableInfos;
            }
            else
            {
                return linearStateVariableInfos;
            }
        }

        public override void GetRatesOfChange(double[] storage, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            if (hydroUnit.GetHRUType() != HRUType.HRU_GLACIER) 
            { 
                return; 
            }

            double glacier_stor = storage[Model.GetStateVarIndex(SVType.GLACIER)];

            if (_type == GlacialReleaseType.GRELEASE_HBV_EC)
            {
                double snow = storage[Model.GetStateVarIndex(SVType.SNOW)];
                double liq_snow = storage[Model.GetStateVarIndex(SVType.SNOW_LIQ)];

                double Kmin = hydroUnit.GetSurfaceProps().HBV_glacier_Kmin;
                double Kmax = hydroUnit.GetSurfaceProps().glac_storage_coeff;
                double Ag = hydroUnit.GetSurfaceProps().HBV_glacier_Ag;

                double K = Kmin + (Kmax - Kmin) * Exp(-Ag * (snow + liq_snow));

                rates[0] = K * glacier_stor;
            }
            else if (_type == GlacialReleaseType.GRELEASE_LINEAR)
            {
                double K = hydroUnit.GetSurfaceProps().glac_storage_coeff;

                rates[0] = K * glacier_stor;
            }
            else if (_type == GlacialReleaseType.GRELEASE_LINEAR_ANALYTIC)
            {
                double K = hydroUnit.GetSurfaceProps().glac_storage_coeff;
                // Alternate analytical formulation
                rates[0] = glacier_stor * (1 - Exp(-K * options.timestep)) / options.timestep; 
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
                //positivity constraint
                rates[0] = 0.0; 
            }
        }

    }
}
