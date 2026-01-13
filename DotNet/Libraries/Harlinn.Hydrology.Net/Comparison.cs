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
    /// Possible comparison results
    /// </summary>
    public enum Comparison
    {
        /// <summary>
        /// Compared entities are equal
        /// </summary>
        COMPARE_IS_EQUAL,
        /// <summary>
        /// Compared entities are not equal
        /// </summary>
        COMPARE_NOT_EQUAL,
        /// <summary>
        /// Entity 1 greater than entity 2
        /// </summary>
        COMPARE_GREATERTHAN,
        /// <summary>
        /// Entity 1 less than entity 2
        /// </summary>
        COMPARE_LESSTHAN,
        /// <summary>
        /// Entity 1 within range
        /// </summary>
        COMPARE_BETWEEN
    }
}
