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
using System.IO;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Parses data from file
    /// </summary>
    public class Parser
    {
        /// <summary>
        /// current input
        /// </summary>
        TextReader _INPUT;
        /// <summary>
        /// current line in input file
        /// </summary>
        int _lineno;
        /// <summary>
        /// current input filename
        /// </summary>
        string _filename;
        /// <summary>
        /// true if spaces & tabs ignored in tokenization
        /// </summary>
        bool _comma_only;
        /// <summary>
        /// true if currently parsing math exp (commas not ignored)
        /// </summary>
        bool _parsing_math_exp; 



    }






}
