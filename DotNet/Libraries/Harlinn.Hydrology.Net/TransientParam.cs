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
    public class TransientParam
    {
        /// <summary>
        /// Name of parameter (e.g., "HYDRAULIC_COND")
        /// </summary>
        string param_name;
        /// <summary>
        /// parameter class type (e.g., SOIL, TERRAIN,LANDUSE,GLOBAL)
        /// </summary>
        ClassType param_type;
        /// <summary>
        /// class name (e.g., "GuelphLoam")(ignored for global params)
        /// </summary>
        string className;

        /// <summary>
        /// Time series of parameter value
        /// </summary>
        TimeSeries pTimeSeries; 
        Model _pModel;
    }


}
