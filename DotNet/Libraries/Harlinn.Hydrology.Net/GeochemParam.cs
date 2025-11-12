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
    public class GeochemParam
    {
        /// <summary>
        /// parameter type
        /// </summary>
        GParamType type;
        /// <summary>
        /// parameter value (units determined by type)
        /// </summary>
        double value;
        /// <summary>
        /// constituent index
        /// </summary>
        int constit_ind;
        /// <summary>
        /// 2nd constituent index (for reactions/transformations)
        /// </summary>
        int constit_ind2;
        /// <summary>
        /// process index
        /// </summary>
        int process_ind;
        /// <summary>
        /// soil/veg/LU class name
        /// </summary>
        string class_name;
        /// <summary>
        /// water storage compartment index ii
        /// </summary>
        int ii_water_stor;

        public GeochemParam(GParamType ty)
        { 
            type = ty;
            value = 0.0;
            constit_ind = 0;
            constit_ind2 = DOESNT_EXIST;
            process_ind = DOESNT_EXIST;
            ii_water_stor = DOESNT_EXIST;
            class_name = string.Empty;
        }
    }
}
