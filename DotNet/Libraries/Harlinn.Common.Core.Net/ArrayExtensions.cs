/*
   Copyright 2024 Espen Harlinn

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
