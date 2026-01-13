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
