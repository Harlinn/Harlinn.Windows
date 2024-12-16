using System;
using System.IO;

namespace Harlinn.Common.Core.Net.IO
{
    public interface IReadWrite
    {
        void Read(BinaryReader reader);
        void Write(BinaryWriter writer);
    }
}
