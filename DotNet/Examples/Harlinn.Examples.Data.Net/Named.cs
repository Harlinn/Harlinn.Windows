using System;
using System.Collections.Generic;
using Harlinn.Common.Net;
using Harlinn.Common.Net.IO;

namespace Harlinn.Examples.Data.Net
{
    public class Named : IReadWrite
    {
        Guid _id;
        string _name;

        public Named()
        {
            _name = string.Empty;
        }

        public Named(Guid id, string name)
        {
            _id = id;
            _name = name;
        }

        public Guid Id { get => _id; set => _id = value; }
        public string Name { get => _name; set => _name = value; }

        public override string ToString()
        {
            if(!string.IsNullOrWhiteSpace( _name ))
            {
                return _name;
            }
            else
            {
                return _id.ToString();
            }
        }

        public virtual void Read(BinaryReader reader)
        {
            _id = reader.ReadGuid();
            _name = reader.ReadString();
        }

        public virtual void Write(BinaryWriter writer)
        {
            writer.Write(_id);
            writer.Write(_name);
        }
    }

}
