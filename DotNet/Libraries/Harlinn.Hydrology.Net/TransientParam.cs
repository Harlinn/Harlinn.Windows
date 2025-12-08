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
using Harlinn.Hydrology;
using System.Linq;

namespace Harlinn.Hydrology
{
    public class TransientParam
    {
        Model _model;

        /// <summary>
        /// Name of parameter (e.g., "HYDRAULIC_COND")
        /// </summary>
        string _paramName;
        /// <summary>
        /// parameter class type (e.g., SOIL, TERRAIN,LANDUSE,GLOBAL)
        /// </summary>
        ClassType _paramType;
        /// <summary>
        /// class name (e.g., "GuelphLoam")(ignored for global params)
        /// </summary>
        string _className;

        /// <summary>
        /// Time series of parameter value
        /// </summary>
        TimeSeries _timeSeries;


        /// <summary>
        /// Initializes a new instance of the <see cref="TransientParam"/> class.
        /// </summary>
        /// <param name="model">
        /// The model to which the parameter belongs.
        /// </param>
        /// <param name="timeSeries">
        /// time series of parameter history
        /// </param>
        /// <param name="paramName">
        /// name of parameter (e.g., "HYDRAULIC_COND")
        /// </param>
        /// <param name="paramType">
        /// class of parameter(e.g., CLASS_SOIL or CLASS_GLOBAL)
        /// </param>
        /// <param name="className">
        /// class of parameter time series (e.g., "GuelphLoam") 
        /// not used for CLASS_GLOBAL parameters
        /// </param>
        public TransientParam(Model model, TimeSeries timeSeries,
                                 string paramName,
                                 ClassType paramType,
                                 string className)
        {
            _model = model;
            _timeSeries = timeSeries;
            _paramName = paramName;
            _paramType = paramType;
            _className = string.Empty;
            if (paramType != ClassType.CLASS_GLOBAL)
            {
                _className = className;
            }
        }

        /// <summary>
        /// Returns associated time series
        /// </summary>
        /// <returns>The associated time series</returns>
        public TimeSeries GetTimeSeries() 
        { 
            return _timeSeries; 
        }

        /// <summary>
        /// Returns associated parameter name
        /// </summary>
        /// <returns>The associated parameter name.</returns>
        public string GetParameterName() 
        { 
            return _paramName; 
        }

        /// <summary>
        /// Returns associated parameter class name.
        /// </summary>
        /// <returns>The associated parameter class name.</returns>
        public string GetParameterClass() 
        { 
            return _className; 
        }

        public Initialize(Model model, Options Options)
        {
            _timeSeries.Initialize(Options.start,
                          Options.julian_start_year,
                          Options.duration,
                          Options.timestep,
                          false,
                          Options.calendar);

  if (param_type==CLASS_SOIL)
  {
    if (_pModel->StringToSoilClass(class_name) == NULL){
      string msg = "CTransientParam::Initialize: invalid soil class name: " + class_name;
        ExitGracefully(msg.c_str(), BAD_DATA);
    }
}
  else if (param_type == CLASS_VEGETATION)
{
    if (_pModel->StringToVegClass(class_name) == NULL)
    {
        string msg = "CTransientParam::Initialize: invalid vegetation class name: " + class_name;
        ExitGracefully(msg.c_str(), BAD_DATA);
    }
}
else if (param_type == CLASS_TERRAIN)
{
    if (_pModel->StringToTerrainClass(class_name) == NULL)
    {
        string msg = "CTransientParam::Initialize: invalid terrain class name: " + class_name;
        ExitGracefully(msg.c_str(), BAD_DATA);
    }
}
else if (param_type == CLASS_LANDUSE)
{
    if (_pModel->StringToLUClass(class_name) == NULL)
    {
        string msg = "CTransientParam::Initialize: invalid land use/land type class name: " + class_name;
        ExitGracefully(msg.c_str(), BAD_DATA);
    }
}
else if (param_type == CLASS_GLOBAL)
{
    //
}

}

    }


}
