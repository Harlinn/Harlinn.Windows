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
    /// Desired output format
    /// </summary>
    public enum OutFormat
    {
        /// <summary>
        /// Output in default format (.csv files)
        /// </summary>
        OUTPUT_STANDARD,
        /// <summary>
        /// Output in Ensim format (.tb0 files)
        /// </summary>
        OUTPUT_ENSIM,
        /// <summary>
        /// Output in NetCDF format (.nc files)
        /// </summary>
        OUTPUT_NETCDF,
        /// <summary>
        /// Output is suppressed
        /// </summary>
        OUTPUT_NONE
    }
}
