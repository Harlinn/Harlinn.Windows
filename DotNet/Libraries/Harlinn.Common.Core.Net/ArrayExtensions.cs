using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Harlinn.Common.Core.Net
{
    public static class ArrayExtensions
    {
        
        public static bool Equals(this byte[]? self, byte[]? other)
        {
            if (ReferenceEquals(self, other))
            {
                return true;
            }
            else if (ReferenceEquals(self, null))
            {
                return false;
            }
            else if (ReferenceEquals(other, null))
            {
                return false;
            }
            else if (self.Length == other.Length)
            {
                return NativeFunctions.memcmp(self, other, self.LongLength) == 0;

            }
            return false;
        }
    }
}
