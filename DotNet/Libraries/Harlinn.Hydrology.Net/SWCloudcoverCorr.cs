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
    /// Methods correting shortwave radiation for cloud cover
    /// </summary>
    public enum SWCloudcoverCorr
    {
        /// <summary>
        /// Cloud cover corrections not used (e.g, when shortwave is measured by radiometer)
        /// </summary>
        SW_CLOUD_CORR_NONE,
        /// <summary>
        /// Based on UBCWM apporach, which is identical to Dingman (2008) Eq. 5-31
        /// </summary>
        SW_CLOUD_CORR_UBCWM,
        /// <summary>
        /// Dingman (2008) Eq. 5-30     (does not require a parameter)
        /// </summary>
        SW_CLOUD_CORR_DINGMAN,
        /// <summary>
        /// Annandale et al., (2002) temperature based estimate of cloud cover influence
        /// </summary>
        SW_CLOUD_CORR_ANNANDALE
    }

}
