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
using System.Collections.Generic;
using System.IO;
using Harlinn.Common.Core.Net.IO;

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
