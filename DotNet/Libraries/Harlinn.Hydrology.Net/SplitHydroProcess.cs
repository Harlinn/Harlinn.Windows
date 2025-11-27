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
    /// The complete dump of water from one storage compartment to two others
    /// </summary>
    public class SplitHydroProcess : HydroProcess
    {
        /// <summary>
        /// percentage of water going to target compartment #1
        /// </summary>
        double _splitPercentage;

        public SplitHydroProcess(Model model, int inIndex, int outIndex1, int outIndex2, double splitPercentage )
            : base(model, HydroProcessType.SPLIT)
        {
            Runtime.ExitGracefullyIf(inIndex == DOESNT_EXIST,
                             "SplitHydroProcess Constructor: invalid 'from' compartment specified", ExitCode.BAD_DATA);
            Runtime.ExitGracefullyIf(outIndex1 == DOESNT_EXIST,
                             "SplitHydroProcess Constructor: invalid 'to' compartment specified", ExitCode.BAD_DATA);
            Runtime.ExitGracefullyIf(outIndex2 == DOESNT_EXIST,
                             "SplitHydroProcess Constructor: invalid 'to' compartment specified", ExitCode.BAD_DATA);
            _splitPercentage = splitPercentage;

            DynamicSpecifyConnections(2);

            FromIndices[0] = inIndex; 
            ToIndices[0] = outIndex1;
            FromIndices[1] = inIndex;
            ToIndices[1] = outIndex2;
        }

        override public void GetRatesOfChange(double[] storage, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            rates[0] = _splitPercentage * storage[FromIndices[0]] / options.timestep;
            rates[1] = (1.0 - _splitPercentage) * storage[FromIndices[0]] / options.timestep;
        }
    }
}
