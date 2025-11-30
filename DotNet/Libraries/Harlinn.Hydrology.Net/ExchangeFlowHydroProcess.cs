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
    /// <summary>
    /// Exchange flow with a mixing zone
    /// </summary>
    public class ExchangeFlowHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> parameters = [new ParameterInfo("EXCHANGE_FLOW", ClassType.CLASS_SOIL)];

        public ExchangeFlowHydroProcess(Model model, int inIndex, int outIndex)
            : base(model, HydroProcessType.EXCHANGE_FLOW, inIndex, outIndex)
        {
            Runtime.ExitGracefullyIf(inIndex == DOESNT_EXIST, "ExchangeFlowHydroProcess Constructor: invalid 'from' compartment specified", ExitCode.BAD_DATA);
            Runtime.ExitGracefullyIf(outIndex == DOESNT_EXIST, "ExchangeFlowHydroProcess Constructor: invalid 'to' compartment specified", ExitCode.BAD_DATA);
            DynamicSpecifyConnections(2);
            FromIndices[0] = inIndex;
            ToIndices[0] = outIndex;
            FromIndices[1] = outIndex;
            ToIndices[1] = inIndex;
        }

        public override void Initialize()
        {
            base.Initialize();
            SVType fromType = Model.GetStateVarType(FromIndices[0]);
            Runtime.ExitGracefullyIf(fromType != SVType.SOIL, "ExchangeFlowHydroProcess.Initialize: exchange flow must be from a soil unit", ExitCode.BAD_DATA);
            SVType toType = Model.GetStateVarType(ToIndices[0]);
            Runtime.ExitGracefullyIf((toType != SVType.SOIL), "ExchangeFlowHydroProcess.Initialize: exchange flow  must be between two soil units", ExitCode.BAD_DATA);
        }

        
        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            return parameters;
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            // Uses mixing layer property
            int m = Model.GetStateVarLayer(FromIndices[0]); 
            rates[0] = hydroUnit.GetSoilProps(m).exchange_flow;
            rates[1] = hydroUnit.GetSoilProps(m).exchange_flow;
        }
    }
}
