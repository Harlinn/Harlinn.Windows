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
    public class ParameterDistribution
    {
        /// <summary>
        /// parameter name
        /// </summary>
        public string param_name;
        /// <summary>
        /// parametre type e.g., CLASS_SOIL
        /// </summary>
        public ClassType param_class;
        /// <summary>
        /// specific class (e.g., SILTY_SAND) this refers to
        /// </summary>
        public string class_group;
        /// <summary>
        /// base parameter value
        /// </summary>
        public double default_val;
        /// <summary>
        /// statistical distribution
        /// </summary>
        public DistType distribution;
        /// <summary>
        /// distribution parameters
        /// </summary>
        public readonly double[] distpar = new double[3];  

    }
}
