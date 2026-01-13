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
    /// Transformation algorithm type
    /// </summary>
    public enum TransformationType
    {
        /// <summary>
        /// analytic treatment of decay over finite time step, dC/dt=-k*C dA/dt=+s*k*C
        /// </summary>
        TRANS_LINEAR,
        /// <summary>
        /// basic power law transformation, analytic treatment  calculated as dC/dt=-k*C^n; dA/dt=+s*k*C^n
        /// </summary>
        TRANS_NONLINEAR
    }

}
