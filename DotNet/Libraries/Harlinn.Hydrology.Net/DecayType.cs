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
    /// Decay type
    /// </summary>
    enum DecayType
    {
        /// <summary>
        /// basic decay, calculated as -k*C
        /// </summary>
        DECAY_BASIC,
        /// <summary>
        /// analytic treatment of first-order decay/loss over finite time step
        /// </summary>
        DECAY_LINEAR,
        /// <summary>
        /// analytic treatment of zeroth-order decay/loss over finite time step
        /// </summary>
        DECAY_ZEROORDER,
        /// <summary>
        /// adds temperature/saturation correction factor to decay rate
        /// </summary>
        DECAY_DENITRIF,
        /// <summary>
        /// exchange with atmosphere
        /// </summary>
        DECAY_HOOKESLAW
    }
}
