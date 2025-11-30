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
    /// The complete dump of water from one storage compartment to another
    /// </summary>
    public class FlushHydroProcess : HydroProcess
    {
        double _percentage;
        static readonly IReadOnlyList<StateVariableInfo> stateVariableInfos = Array.Empty<StateVariableInfo>();

        public FlushHydroProcess(Model model, int inIndex, int outIndex, double pct)
            : base(model, HydroProcessType.FLUSH, inIndex, outIndex)
        {
            Runtime.ExitGracefullyIf(inIndex == DOESNT_EXIST, "FlushHydroProcess Constructor: invalid 'from' compartment specified", ExitCode.BAD_DATA);
            Runtime.ExitGracefullyIf(outIndex == DOESNT_EXIST, "FlushHydroProcess Constructor: invalid 'to' compartment specified", ExitCode.BAD_DATA);

            _percentage = pct;
        }

        

        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList()
        {
            return stateVariableInfos;
        }

        public override void GetRatesOfChange(double[] storage, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            rates[0] = _percentage * storage[FromIndices[0]] / options.timestep;
        }
    }
}
