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
    /// Decision variable
    /// </summary>
    public class DecisionVar
    {
        /// <summary>
        /// decision variable names: Qxxxx or Dxxxx where xxxx is SBID
        /// </summary>
        string name;
        /// <summary>
        /// decision variable type: e.g., DV_QOUT or DV_DELIVERY
        /// </summary>
        DVType dvar_type;
        /// <summary>
        /// raw subbasin index p (not SBID) of decision variable (or DOESNT_EXIST if not linked to SB) (target basin for DV_RETURN, source basin for DV_DELIVERY)
        /// </summary>
        int p_index;
        /// <summary>
        /// demand index ii in subbasin p (or DOESNT_EXIST if type not DV_DELIVERY/DV_RETURN) (ii..nDemands in SB p_index, usually <=1)
        /// </summary>
        int dem_index;
        /// <summary>
        /// local index (rescount or subbasincount or demand count)
        /// </summary>
        int loc_index;
        /// <summary>
        /// solution value for decision variable
        /// </summary>
        double value;
        /// <summary>
        /// minimum bound (default=0)
        /// </summary>
        double min;
        /// <summary>
        /// maximum bound (default unbounded)
        /// </summary>
        double max;

        public DecisionVar(string nam, int p, DVType typ, int loc_ind)
        {
            name = nam;
            p_index = p;
            loc_index = loc_ind;
            value = 0.0; 
            min = -ALMOST_INF; 
            max = ALMOST_INF; 
            dvar_type = typ; 
            dem_index = DOESNT_EXIST;
        }
    }
}
