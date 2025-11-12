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
    /// Methods of modeling glacier melt
    /// </summary>
    public enum GlacialMeltType
    {
        /// <summary>
        /// simple potential melt approach
        /// </summary>
        GMELT_SIMPLE_MELT,
        /// <summary>
        /// HBV-EC Degree-day method for modellign glacier melt
        /// </summary>
        GMELT_HBV,
        /// <summary>
        /// UBC method for modellign glacier melt
        /// </summary>
        GMELT_UBC
    }
}
