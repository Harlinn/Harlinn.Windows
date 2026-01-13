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
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Common.Net
{
    public static class MathHelper
    {
        public static bool SignBit(this double self)
        {
            return (((ulong)BitConverter.DoubleToInt64Bits(self)) & 0x8000_0000_0000_0000) != 0;
        }
        public static bool SignBit(this float self)
        {
            return (((ulong)BitConverter.DoubleToInt64Bits(self)) & 0x8000_0000) != 0;
        }


        public static double CopySign(this double self, double signSource)
        {
            var x = (((ulong)BitConverter.DoubleToInt64Bits(self)) & 0x7FFF_FFFF_FFFF_FFFF);
            var y = ((ulong)BitConverter.DoubleToInt64Bits(self)) & 0x8000_0000_0000_0000;
            var bits = x | y;
            return BitConverter.Int64BitsToDouble((long)bits);
        }
        public static float CopySign(this float self, float signSource)
        {
            var x = (((uint)BitConverter.SingleToInt32Bits(self)) & 0x7FFF_FFFF);
            var y = ((uint)BitConverter.SingleToInt32Bits(self)) & 0x8000_0000;
            var bits = x | y;
            return BitConverter.Int32BitsToSingle((int)bits);
        }


    }
}
