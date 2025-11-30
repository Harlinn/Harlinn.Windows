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

using System.ComponentModel;
using static Harlinn.Hydrology.Constants;

namespace Harlinn.Hydrology
{
    public struct StateVariableInfo
    {
        SVType _type = SVType.UNRECOGNIZED_SVTYPE;
        int _level = DOESNT_EXIST;

        public StateVariableInfo()
        {
        }

        public StateVariableInfo(SVType type, int level = DOESNT_EXIST)
        {
            _type = type;
            _level = level;
        }

        /// <summary>
        /// State variable type
        /// </summary>
        public SVType Type { get => _type; set => _type = value; }

        /// <summary>
        /// Level of multilevel state variables (or DOESNT_EXIST, if single level)
        /// </summary>
        [Description("Level of multilevel state variables (or DOESNT_EXIST, if single level)")]
        public int Level { get => _level; set => _level = value; }
    }

}
