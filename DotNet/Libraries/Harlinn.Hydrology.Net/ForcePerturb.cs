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
    /// Contains information on forcing function random perturbations
    /// </summary>
    public class ForcePerturb
    {
        public ForcingType forcing;
        public DistType distribution;
        /// <summary>
        /// distribution parameters - conditional on distribution
        /// </summary>
        public readonly double[] distpar = new double[3];
        /// <summary>
        /// HRU group index (or DOESNT_EXIST if perturbation should apply everywhere)
        /// </summary>
        public int kk;
        /// <summary>
        /// additive or multiplicative adjustment
        /// </summary>
        public Adjustment adj_type;
        /// <summary>
        /// stored adjustment factors for day - allows perturbations to be pre-calculated for day so that daily mean/min/max can be generated
        /// </summary>
        public double[] eps;
    }
}
