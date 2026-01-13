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
