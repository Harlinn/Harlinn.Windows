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
    public enum LakeFreezeType
    {
        /// <summary>
        /// basic - based upon potential melt energy, moderated by SWE
        /// </summary>
        LFREEZE_BASIC,
        /// <summary>
        /// based upon enthaly balance model
        /// </summary>
        LFREEZE_THERMAL
    }
}
