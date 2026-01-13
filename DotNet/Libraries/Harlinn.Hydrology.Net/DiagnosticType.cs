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
    /// 
    /// </summary>
    public enum DiagnosticType
    {
        /// <summary>
        /// track state variable
        /// </summary>
        VAR_STATE_VAR,
        /// <summary>
        /// track forcing function
        /// </summary>
        VAR_FORCING_FUNCTION,
        /// <summary>
        /// track hydraulic conductivity
        /// </summary>
        VAR_HYD_COND,
        /// <summary>
        /// track gross flux from specific state variable
        /// </summary>
        VAR_FROM_FLUX,
        /// <summary>
        /// track gross flux to specific state variable
        /// </summary>
        VAR_TO_FLUX,
        /// <summary>
        /// track net flux between specific state variables
        /// </summary>
        VAR_BETWEEN_FLUX
    }
}
