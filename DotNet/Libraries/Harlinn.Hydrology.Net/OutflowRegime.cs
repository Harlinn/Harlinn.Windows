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
    /// The flow regime that defines conditions for operating in this regime
    /// </summary>
    public class OutflowRegime
    {

        string _name;

        /// <summary>
        /// pointer to access model for querying flows
        /// </summary>
        Model _pModel;

        /// <summary>
        /// stage discharge curve (or other Q=f(h) relation)
        /// </summary>
        StageDischargeRelation _pCurve;

        /// <summary>
        /// conditions for operation *e.g., date range, etc., ALL conditions must be met
        /// </summary>
        RegimeCondition[] _pConditions;
        /// <summary>
        /// number of conditions for operation under this regime
        /// </summary>
        int _nConditions;
        /// <summary>
        /// constraints on operation, sorted by priority
        /// </summary>
        RegimeConstraint[] _pConstraints;
        /// <summary>
        /// number of constraints
        /// </summary>
        int _nConstraints;
    }

}
