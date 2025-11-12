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
namespace Harlinn.Hydrology
{

    /// <summary>
    /// Flow diversion data strucure, relates diversion quantity to flow rate in subbasin
    /// </summary>
    public class Diversion
    {
        /// <summary>
        /// Julian start date of flow diversion (e.g., 90 for Apr 1)
        /// </summary>
        int julian_start;
        /// <summary>
        /// Julian end date of flow diversion (e.g., 242 for Aug 31)
        /// </summary>
        int julian_end;
        /// <summary>
        /// INDEX (not subbasin ID) of target basin (or -1 if diverted from system)
        /// </summary>
        int target_p;

        /// <summary>
        /// minimum flow above which flow is diverted [m3/s] (Q>0)
        /// </summary>
        double min_flow;
        /// <summary>
        /// percentage of flow above minimum which is diverted
        /// </summary>
        double percentage;

        /// <summary>
        /// number of points in flow-diversion lookup table
        /// </summary>
        int nPoints;
        /// <summary>
        /// array of discharges [m3/s] in flow diversion lookup table
        /// </summary>
        double[] aQsource;
        /// <summary>
        /// array of diversion flow rates [m3/s] correspionding to discharges in flow diversion lookup table
        /// </summary>
        double[] aQdivert;
    }
}
