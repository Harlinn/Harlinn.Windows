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
    /// Tabular stage discharge relation
    /// </summary>
    public class StageDischargeTable : StageDischargeRelation
    {
        /// <summary>
        /// number of points on rating curve
        /// </summary>
        int _Np;
        /// <summary>
        /// Base rating curve for stage elevation [m]
        /// </summary>
        double[] _aStage;
        /// <summary>
        /// Rating curve for overflow (e.g., weir) flow rates [m3/s]
        /// </summary>
        double[] _aQ;
    }
}
