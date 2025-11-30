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
using static Harlinn.Mathematics.Net.Common;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// melt from glacier
    /// </summary>

    public class GlacierMeltHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> simpleMeltParameters = [];
        static readonly IReadOnlyList<ParameterInfo> hbvParameters = [new ParameterInfo("HBV_MELT_GLACIER_CORR", ClassType.CLASS_LANDUSE)];

        /// <summary>
        /// Specified algorithm for glacier melt simulation
        /// </summary>
        GlacialMeltType _type;


        public GlacierMeltHydroProcess(Model model, GlacialMeltType melt_type) 
            : base(model, HydroProcessType.GLACIER_MELT)
        {
            _type = melt_type;

            if ((_type == GlacialMeltType.GMELT_HBV) || (_type == GlacialMeltType.GMELT_SIMPLE_MELT))
            {
                DynamicSpecifyConnections(1);

                FromIndices[0] = model.GetStateVarIndex(SVType.GLACIER_ICE);
                ToIndices[0] = model.GetStateVarIndex(SVType.GLACIER);
            }
            else if (_type == GlacialMeltType.GMELT_UBC)
            {
                DynamicSpecifyConnections(2);
                FromIndices[0] = model.GetStateVarIndex(SVType.GLACIER_ICE);
                ToIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER);
                FromIndices[1] = model.GetStateVarIndex(SVType.GLACIER_CC);
                ToIndices[1] = model.GetStateVarIndex(SVType.GLACIER_CC);
            }
        }

        

        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            if (_type == GlacialMeltType.GMELT_SIMPLE_MELT || _type == GlacialMeltType.GMELT_UBC)
            {
                return simpleMeltParameters;
            }
            else if (_type == GlacialMeltType.GMELT_HBV)
            {
                return hbvParameters;
            }
            else
            {
                throw new InvalidOperationException("GlacierMeltHydroProcess.GetParticipatingParamList: undefined glacial melt algorithm");
            }
        }


        static readonly IReadOnlyList<StateVariableInfo> simpleStateVariableInfos = [new StateVariableInfo(SVType.GLACIER_ICE), new StateVariableInfo(SVType.GLACIER)];
        static readonly IReadOnlyList<StateVariableInfo> hbvStateVariableInfos = [new StateVariableInfo(SVType.GLACIER_ICE), new StateVariableInfo(SVType.GLACIER), new StateVariableInfo(SVType.GLACIER_CC)];

        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(GlacialMeltType melt_type)
        {
            if ((melt_type == GlacialMeltType.GMELT_SIMPLE_MELT) || (melt_type == GlacialMeltType.GMELT_HBV))
            {
                return simpleStateVariableInfos;
            }
            else if (melt_type == GlacialMeltType.GMELT_UBC)
            {
                return hbvStateVariableInfos;
            }
            else
            {
                throw new InvalidOperationException("GlacierMeltHydroProcess.GetParticipatingStateVarList: undefined glacial melt algorithm");
            }
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            if (hydroUnit.GetHRUType() != HRUType.HRU_GLACIER) 
            { 
                return; 
            }

            if (_type == GlacialMeltType.GMELT_SIMPLE_MELT)
            {
                rates[0] = hydroUnit.GetForcingFunctions().potential_melt;
            }
            else if (_type == GlacialMeltType.GMELT_HBV)
            {
                if (stateVars[Model.GetStateVarIndex(SVType.SNOW)] > REAL_SMALL) 
                {
                    // Melt doesnt proceed until snow is gone
                    return; 
                }

                rates[0] = hydroUnit.GetSurfaceProps().HBV_melt_glacier_corr * ThreshPositive(hydroUnit.GetForcingFunctions().potential_melt);
            }
            else if (_type == GlacialMeltType.GMELT_UBC)
            {
                // glacier cold content [mm]
                double CC = stateVars[FromIndices[1]];
                // snow cover
                double snow_coverage = hydroUnit.GetSnowCover();
                // potential melt [mm/d]
                double pot_melt = hydroUnit.GetForcingFunctions().potential_melt;

                if (pot_melt > 0.0) 
                {
                    // glacier doesnt melt if snow is on top
                    pot_melt *= (1.0 - snow_coverage); 
                }
                else 
                {
                    // issue?? cold content for glaciers will never increase...
                    pot_melt = 0.0; 
                } 

                // Reduce/increase cold content (always leads to pot_melt>=0, CC>=0)
                if (CC > pot_melt * options.timestep)
                {
                    CC -= pot_melt * options.timestep;
                    pot_melt = 0;
                }
                else
                {
                    pot_melt -= CC / options.timestep;
                    CC = 0.0;
                }

                // decay of cold content
                double P0CTKG = 0.0; //basically sets CC=0 for this problem
                CC *= (1 - (1 / (1 + P0CTKG)));

                // glacier ->ponded water
                rates[0] = pot_melt;
                // CC modification
                rates[1] = (CC - stateVars[FromIndices[1]]) / options.timestep; 
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
                //positivity constraint on melt
                rates[0] = 0.0; 
            }
        }

    }
}
