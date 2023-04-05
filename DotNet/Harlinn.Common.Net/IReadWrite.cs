using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Common.Net
{
    public interface IReadWrite
    {
        void Read(Net.IO.BinaryReader reader);
        void Write(Net.IO.BinaryWriter writer);
    }
}
