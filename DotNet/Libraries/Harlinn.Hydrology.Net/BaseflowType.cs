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

namespace Harlinn.Hydrology
{

    /// <summary>
    /// Methods for modelling baseflow
    /// </summary>
    public enum BaseflowType
    {
        /// <summary>
        /// Constant baseflow method
        /// </summary>
        BASE_CONSTANT,
        /// <summary>
        /// simple bucket model (HBV,PRMS,UBCWM,...)
        /// </summary>
        BASE_LINEAR,
        /// <summary>
        /// simple bucket model but limited down to FC
        /// </summary>
        BASE_LINEAR_CONSTRAIN,
        /// <summary>
        /// simple bucket model, analytical sol'n over timestep
        /// </summary>
        BASE_LINEAR_ANALYTIC,
        /// <summary>
        /// VIC baseflow method
        /// </summary>
        BASE_VIC,
        /// <summary>
        /// TOPMODEL Baseflow method
        /// </summary>
        BASE_TOPMODEL,
        /// <summary>
        /// Power Law saturation
        /// </summary>
        BASE_POWER_LAW,
        /// <summary>
        /// GR4J Baseflow method
        /// </summary>
        BASE_GR4J,
        /// <summary>
        /// power law saturation above threshold
        /// </summary>
        BASE_THRESH_POWER,
        /// <summary>
        /// linear storage above threshold (HBV-Lite)
        /// </summary>
        BASE_THRESH_STOR
    }
}
