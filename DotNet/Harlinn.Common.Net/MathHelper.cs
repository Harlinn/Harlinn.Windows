using System;
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
