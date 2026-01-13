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

    public class Expression
    {
        /// <summary>
        /// 2D irregular array of pointers to expression terms size:[nGroups][nTermsPerGrp[j]]
        /// </summary>
        ExpressionTerm[][] pTerms;
        /// <summary>
        /// total number of terms groups in expression
        /// </summary>
        int nGroups;
        /// <summary>
        /// number of terms per group [size: nGroups]
        /// </summary>
        int[] nTermsPerGrp;
        /// <summary>
        /// comparison operator (==, <, >)
        /// </summary>
        Comparison compare;

        /// <summary>
        /// original string expression
        /// </summary>
        string origexp;
    }

}
