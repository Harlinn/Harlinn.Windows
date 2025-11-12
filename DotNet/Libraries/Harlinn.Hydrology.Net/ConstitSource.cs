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
    public class ConstitSource
    {
        /// <summary>
        /// true for dirichlet, false for neumann
        /// </summary>
        bool dirichlet;
        /// <summary>
        /// constituent index (c)
        /// </summary>
        int constit_index;
        /// <summary>
        /// index of water storage compartment
        /// </summary>
        int i_stor;
        /// <summary>
        /// index of HRU group to which source is applied (default is all for DOESNT_EXIST)
        /// </summary>
        int kk;
        /// <summary>
        /// fixed concentration [mg/m2] or enthalpy [MJ/m2] (or DOESNT_EXIST=-1 if time series should be used)
        /// </summary>
        double concentration;
        /// <summary>
        /// fixed concentration [mg/m2] or enthalpy [MJ/m2] for blend-type condition
        /// </summary>
        double concentration2;
        /// <summary>
        /// fixed mass flux [mg/m2/d] or heat flux [MJ/m2/d] (or DOESNT_EXIST=-1 if time series should be used)
        /// </summary>
        double flux;
        /// <summary>
        /// time series of fixed concentration or mass/heat flux (or NULL if fixed should be used)
        /// </summary>
        TimeSeries pTS; 
    }
}
