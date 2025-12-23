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


namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public enum SystemType : byte
    {
        Unknown = 0,
        Image = 34,
        Text = 35,
        Uniqueidentifier = 36,
        Date = 40,
        Time = 41,
        DateTime2 = 42,
        DateTimeOffset = 43,
        TinyInt = 48,
        SmallInt = 52,
        Int = 56,
        SmallDateTime = 58,
        Real = 59,
        Money = 60,
        DateTime = 61,
        Float = 62,
        SqlVariant = 98,
        NText = 99,
        Bit = 104,
        Decimal = 106,
        Numeric = 108,
        SmallMoney = 122,
        BigInt = 127,
        HierarchyId = 240,
        Geometry = 240,
        Geography = 240,
        VarBinary = 165,
        VarChar = 167,
        Binary = 173,
        Char = 175,
        Timestamp = 189,
        NVarChar = 231,
        NChar = 239,
        Xml = 241,
        SysName = 231
    }





}
