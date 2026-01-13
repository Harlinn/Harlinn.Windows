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
    public class Ensemble
    {
        /// <summary>
        /// ensemble type (e.g., ENSEMBLE_MONTECARLO)
        /// </summary>
        EnsembleType _type;

        /// <summary>
        /// number of ensemble members
        /// </summary>
        int _nMembers;

        /// <summary>
        /// array of output directory names [size: _nMembers]
        /// </summary>
        string[] _aOutputDirs;
        /// <summary>
        /// array of output runnames [size: _nMembers]
        /// </summary>
        string[] _aRunNames;
        /// <summary>
        /// array of input solution filenames [size: _nMembers]
        /// </summary>
        public string[] _aSolutionFiles;

        /// <summary>
        /// random seed
        /// </summary>
        int _rand_seed;

        /// <summary>
        /// true if output from ensemble should be turned off (default: false)
        /// </summary>
        bool _disable_output; 

    }
}
