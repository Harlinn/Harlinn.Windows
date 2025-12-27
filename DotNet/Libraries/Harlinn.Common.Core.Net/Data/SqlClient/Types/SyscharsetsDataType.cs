/*
   Copyright 2024-2025 Espen Harlinn

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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class SyscharsetsDataType
{
    readonly short _type = 0;
    readonly byte _id = 0;
    readonly byte _csid = 0;
    readonly short? _status;
    readonly string _name = string.Empty;
    readonly string _description = string.Empty;
    readonly byte[]? _binarydefinition;
    readonly byte[]? _definition;

    public SyscharsetsDataType( )
    {
    }

    public SyscharsetsDataType(short type,
        byte id,
        byte csid,
        short? status,
        string name,
        string description,
        byte[]? binarydefinition,
        byte[]? definition)
    {
        _type = type;
        _id = id;
        _csid = csid;
        _status = status;
        _name = name;
        _description = description;
        _binarydefinition = binarydefinition;
        _definition = definition;
    }

    public short Type => _type;
    public byte Id => _id;
    public byte Csid => _csid;
    public short? Status => _status;
    public string Name => _name;
    public string Description => _description;
    public byte[]? Binarydefinition => _binarydefinition;
    public byte[]? Definition => _definition;
}
