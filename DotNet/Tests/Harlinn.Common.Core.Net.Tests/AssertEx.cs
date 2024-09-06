using System;

namespace Harlinn.Common.Core.Net.Tests
{
    public class AssertEx
    {
        public static void AreEqual<T>(T[] first, T[] second)
        {
            Assert.AreEqual(first.Length, second.Length);
            for (int i = 0; i < first.Length; i++)
            {
                Assert.AreEqual(first[i], second[i]);
            }
        }
    }
}