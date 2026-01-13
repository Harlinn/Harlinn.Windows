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

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Overflow of water from one storage compartment to another
    /// </summary>
    public class OverflowHydroProcess : HydroProcess
    {
        public OverflowHydroProcess(Model model, int inIndex, int outIndex)
            : base(model, HydroProcessType.OVERFLOW_PROC, inIndex, outIndex)
        {
            Runtime.ExitGracefullyIf(inIndex == DOESNT_EXIST, "OverflowHydroProcess Constructor: invalid 'from' compartment specified", ExitCode.BAD_DATA);
            Runtime.ExitGracefullyIf(outIndex == DOESNT_EXIST, "OverflowHydroProcess Constructor: invalid 'to' compartment specified", ExitCode.BAD_DATA);
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            double max_storage = Math.Max(hydroUnit.GetStateVarMax(FromIndices[0], stateVars, options), 0.0);
            rates[0] = Math.Max(stateVars[FromIndices[0]] - max_storage, 0.0) / options.timestep;
        }
    }

}
