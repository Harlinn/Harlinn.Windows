#pragma once
#ifndef __HOCICONSTANTS_H__
#define __HOCICONSTANTS_H__
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

#include <HODef.h>
#include <HOCIEnums.h>

namespace Harlinn::OCI
{

    constexpr Int16 Int8MaxPrecision = 2;
    constexpr Int16 Int16MaxPrecision = 4;
    constexpr Int16 Int32MaxPrecision = 8;
    constexpr Int16 Int64MaxPrecision = 18;

    namespace Result
    {
        /// <summary>
        /// maps to SQL_SUCCESS of SAG CLI
        /// </summary>
        constexpr Int32 OCI_SUCCESS = 0;
        /// <summary>
        /// maps to SQL_SUCCESS of SAG CLI (OCI_SUCCESS)
        /// </summary>
        constexpr Int32 Success = 0;
        /// <summary>
        /// maps to SQL_SUCCESS_WITH_INFO
        /// </summary>
        constexpr Int32 OCI_SUCCESS_WITH_INFO = 1;
        /// <summary>
        /// maps to SQL_SUCCESS_WITH_INFO (OCI_SUCCESS_WITH_INFO)
        /// </summary>
        constexpr Int32 SuccessWithInfo = 1;
        /// <summary>
        /// maps to SQL_NO_DATA
        /// </summary>
        constexpr Int32 OCI_NO_DATA = 100;
        /// <summary>
        /// maps to SQL_NO_DATA (OCI_NO_DATA)
        /// </summary>
        constexpr Int32 NoData = 100;
        /// <summary>
        /// maps to SQL_ERROR
        /// </summary>
        constexpr Int32 OCI_ERROR = -1;
        /// <summary>
        /// maps to SQL_ERROR (OCI_ERROR)
        /// </summary>
        constexpr Int32 Error = -1;
        /// <summary>
        /// maps to SQL_INVALID_HANDLE
        /// </summary>
        constexpr Int32 OCI_INVALID_HANDLE = -2;
        /// <summary>
        /// maps to SQL_INVALID_HANDLE (OCI_INVALID_HANDLE)
        /// </summary>
        constexpr Int32 InvalidHandle = -2;
        /// <summary>
        /// maps to SQL_NEED_DATA
        /// </summary>
        constexpr Int32 OCI_NEED_DATA = 99;
        /// <summary>
        /// maps to SQL_NEED_DATA (OCI_NEED_DATA)
        /// </summary>
        constexpr Int32 NeedData = 99;
        /// <summary>
        /// OCI would block error
        /// </summary>
        constexpr Int32 OCI_STILL_EXECUTING = -3123;
        /// <summary>
        /// OCI would block error (OCI_STILL_EXECUTING)
        /// </summary>
        constexpr Int32 StillExecuting = -3123;
    }

    /// <summary>
    /// OCI Collation IDs
    /// </summary>
    /// <remarks>
    /// collation IDs of a number of frequently used collations, mainly
    /// pseudo-collations; they are returned as values of the attribute
    /// Attribute::COLLATION_ID; the SQL names of the collations corresponding
    /// to the IDs are given in comments below
    /// </remarks>
    namespace Collation
    {
        /// <summary>
        /// undefined collation; no collation has been specified 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NONE = 0x00000000;
        constexpr UInt32 None = 0x00000000;
        /// <summary>
        /// pseudo-collation USING_NLS_COMP 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_COMP = 0x00003FFE;
        constexpr UInt32 NlsComp = 0x00003FFE;
        /// <summary>
        /// pseudo-collation USING_NLS_SORT 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_SORT = 0x00003FFD;
        constexpr UInt32 NlsSort = 0x00003FFD;
        /// <summary>
        /// pseudo-collation USING_NLS_SORT_CI 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_SORT_CI = 0x00003FFC;
        constexpr UInt32 NlsSortCI = 0x00003FFC;
        /// <summary>
        /// pseudo-collation USING_NLS_SORT_AI 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_SORT_AI = 0x00003FFB;
        constexpr UInt32 NlsSortAI = 0x00003FFB;
        /// <summary>
        /// pseudo-collation USING_NLS_SORT_CS 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_SORT_CS = 0x00003FFA;
        constexpr UInt32 NlsSortCS = 0x00003FFA;
        /// <summary>
        /// pseudo-collation USING_NLS_SORT_VAR1 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_SORT_VAR1 = 0x00003FF9;
        constexpr UInt32 NlsSortVar1 = 0x00003FF9;
        /// <summary>
        /// pseudo-collation USING_NLS_SORT_VAR1_CI 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_SORT_VAR1_CI = 0x00003FF8;
        constexpr UInt32 NlsSortVar1CI = 0x00003FF8;
        /// <summary>
        /// pseudo-collation USING_NLS_SORT_VAR1_AI 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_SORT_VAR1_AI = 0x00003FF7;
        constexpr UInt32 NlsSortVar1AI = 0x00003FF7;
        /// <summary>
        /// pseudo-collation USING_NLS_SORT_VAR1_CS 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_NLS_SORT_VAR1_CS = 0x00003FF6;
        constexpr UInt32 NlsSortVar1CS = 0x00003FF6;
        /// <summary>
        /// BINARY 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_BINARY = 0x00003FFF;
        constexpr UInt32 Binary = 0x00003FFF;
        /// <summary>
        /// BINARY_CI 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_BINARY_CI = 0x00023FFF;
        constexpr UInt32 BinaryCI = 0x00023FFF;
        /// <summary>
        /// BINARY_AI 
        /// </summary>
        constexpr UInt32 OCI_COLLATION_BINARY_AI = 0x00013FFF;
        constexpr UInt32 BinaryAI = 0x00013FFF;

    }

}

#endif
