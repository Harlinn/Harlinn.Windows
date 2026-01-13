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
    public class Application
    {
        /// <summary>
        /// 
        /// </summary>
        string _outputDirectory;
        /// <summary>
        /// can store any variables used during debugging; 
        /// </summary>
        double[] _debugVars = new double[10];   
        bool suppressWarnings;
        /// <summary>
        /// converts all output numbers less than REAL_SMALL to zero
        /// </summary>
        bool suppressZeros;
        /// <summary>
        /// disables freezing impacts in thermal wrapper code
        /// </summary>
        bool disableFreezing;
        /// <summary>
        /// minimum soil storage
        /// </summary>
        double minStorage;
        /// <summary>
        /// current ensemble member index
        /// </summary>
        int current_e;


        void FinalizeGracefully(string statement, ExitCode code)
        {

        }
        void ExitGracefully(string statement, ExitCode code)
        {

        }

        void ExitGracefullyIf(bool condition, string statement, ExitCode code)
        {
            if (condition)
            {
                ExitGracefully(statement, code);
            }
        }



    }
}
