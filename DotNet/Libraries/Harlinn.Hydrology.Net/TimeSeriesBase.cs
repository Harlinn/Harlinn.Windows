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

    public class TimeSeriesBase
    {
        /// <summary>
        /// type - regular or irregular
        /// </summary>
        TimeSeriesType _type;
        /// <summary>
        /// name of time series (used only for error messages)
        /// </summary>
        string _name;
        /// <summary>
        /// location ID (stores additional info, like HRU or SBID for observation data)
        /// </summary>
        long _loc_ID;
        /// <summary>
        /// constituent index, if a concentration/temperature observation
        /// </summary>
        int _constit_ind;
        /// <summary>
        /// original source file
        /// </summary>
        string _srcfile;
        /// <summary>
        /// integer ID tag for (e.g.,) demand ID
        /// </summary>
        long _demand_ID;
    }
}
