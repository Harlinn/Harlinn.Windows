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
    /// reservoir constraint conditions
    /// </summary>
    public enum ResConstraint
    {
        RC_MAX_STAGE,
        RC_MIN_STAGE,
        RC_NATURAL,
        RC_TARGET,
        RC_DOWNSTREAM_FLOW,
        RC_MAX_FLOW_INCREASE,
        RC_MAX_FLOW_DECREASE,
        RC_MIN_FLOW,
        RC_MAX_FLOW,
        RC_OVERRIDE_FLOW,
        RC_DRY_RESERVOIR,
        RC_MANAGEMENT,
        RC_DZTR
    }

}
