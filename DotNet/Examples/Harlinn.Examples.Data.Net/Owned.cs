using System;
using System.IO;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Examples.Data.Net
{
    public class Owned : Named
    {
        Guid _owner;

        public Owned()
        {
        }

        public Owned(Guid id, string name) 
            : base(id, name)
        {
        }

        public Owned(Guid id, string name, Guid owner)
            : base(id, name)
        {
            _owner = owner;
        }

        public Guid Owner { get => _owner; set => _owner = value; }

        public override void Read(BinaryReader reader)
        {
            base.Read(reader);
            _owner = reader.ReadGuid();
        }

        public override void Write(BinaryWriter writer)
        {
            base.Write(writer);
            writer.Write(_owner);
        }

    }






}
