/*
    Copyright 2024-2026 Espen Harlinn
 
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
﻿using System;
using System.IO;
using Harlinn.Common.Core.Net.IO;

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
