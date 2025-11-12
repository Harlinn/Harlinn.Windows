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
    /// <summary>
    /// Methods class for related state variable parsing and querying routines
    /// </summary>
    public class StateVariable
    {
        /// <summary>
        /// total number of aliases
        /// </summary>
        int _nAliases;
        /// <summary>
        /// Array of alias values [size: nAliases]
        /// </summary>
        string[] _aAliases;
        /// <summary>
        /// Array of strings referenced by aliases [size: nAliases]
        /// </summary>
        string[] _aAliasReferences;
        
        TransportModel _pTransportModel;   
    }
}
