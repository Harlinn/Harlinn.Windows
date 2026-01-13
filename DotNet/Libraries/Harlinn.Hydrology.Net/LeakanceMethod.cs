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
    public enum LeakanceMethod
    {
        /// <summary>
        /// Leakance coefficient given as a single value
        /// </summary>
        LEAK_CONSTANT,
        /// <summary>
        /// MODFLOW River leakance, hydraulic conductivity of clogging layer over its thickness
        /// </summary>
        LEAK_MODFLOW,
        /// <summary>
        /// Morel-Seytoux et al. (2018) analytically derived, physically based coefficient
        /// </summary>
        LEAK_MOREL_SEYTOUX,
    }
}
