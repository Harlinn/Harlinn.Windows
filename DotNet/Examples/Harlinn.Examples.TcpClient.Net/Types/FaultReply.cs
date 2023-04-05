using System;
using Harlinn.Common.Net.IO;

namespace Harlinn.Examples.TcpClient.Net.Types
{
    public class FaultReply : Header
    {
        UInt64 _sessionId;
        Int64 _errorCode;
        string _message;

        public FaultReply()
            : base(RequestReplyType.Fault)
        {
        }

        public FaultReply(ulong sessionId, long errorCode, string message)
            : base(RequestReplyType.Fault)
        {
            _sessionId = sessionId;
            _errorCode = errorCode;
            _message = message;
        }

        public ulong SessionId { get => _sessionId; set => _sessionId = value; }
        public long ErrorCode { get => _errorCode; set => _errorCode = value; }
        public string Message { get => _message; set => _message = value; }

        public override void Write(BinaryWriter writer)
        {
            base.Write(writer);
            writer.Write(_sessionId);
            writer.Write(_errorCode);
            writer.Write(_message);
        }

        public override void Read(BinaryReader reader)
        {
            base.Read(reader);
            _sessionId = reader.ReadUInt64();
            _errorCode = reader.ReadInt64();
            _message = reader.ReadString();
        }

    }

}
