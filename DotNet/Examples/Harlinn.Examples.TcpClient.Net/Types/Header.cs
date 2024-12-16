using System;
using System.IO;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Examples.TcpClient.Net.Types
{
    public class Header : IReadWrite
    {
        RequestReplyType _type;

        public Header()
        {
            _type = RequestReplyType.Unknown;
        }

        public Header(RequestReplyType requestType)
        {
            _type = requestType;
        }

        public RequestReplyType Type
        {
            get
            {
                return _type;
            }
            set
            {
                _type = value;
            }
        }

        public virtual void Write(BinaryWriter writer)
        {
            byte value = (byte)_type;
            writer.Write(value);
        }

        public static RequestReplyType ReadRequestReplyType(BinaryReader reader)
        {
            return (RequestReplyType)reader.ReadByte();
        }

        public virtual void Read(BinaryReader reader)
        {
        }
    };

}
