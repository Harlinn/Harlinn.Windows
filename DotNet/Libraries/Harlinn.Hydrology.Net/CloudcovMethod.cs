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
    /// Methods used for estimating cloud cover
    /// </summary>
    public enum CloudcovMethod
    {
        /// <summary>
        /// Cloud cover corrections not used
        /// </summary>
        CLOUDCOV_NONE,
        /// <summary>
        /// Uses gauge data for cloud cover
        /// </summary>
        CLOUDCOV_DATA,
        /// <summary>
        /// Temperature range-based approach from UBCWM
        /// </summary>
        CLOUDCOV_UBCWM
    }
}
