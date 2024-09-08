using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Harlinn.Common.Core.Net
{
    public partial class NativeFunctions
    {
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(CallConvCdecl), typeof(CallConvSuppressGCTransition) })]
        [LibraryImport("msvcrt.dll", EntryPoint = "memcmp")]
        internal static partial int memcmp([MarshalAs(UnmanagedType.LPArray)] byte[] b1, [MarshalAs(UnmanagedType.LPArray)] byte[] b2, long count);
    }
}
