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

using System.ComponentModel;
using System.Xml;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class BinaryPropertyDefinition : PropertyDefinition
    {
        byte[]? _defaultValue;
        const int DefaultSize = 256;
        int _size = DefaultSize;

        [XmlIgnore]
        public override PropertyKind Kind => PropertyKind.Binary;

        [XmlAttribute]
        public byte[]? Default { get => _defaultValue; set => _defaultValue = value; }

        [XmlAttribute("Size"), DefaultValue(null)]
        public string? SizeAsString
        {
            get
            {
                if (_size.Equals(DefaultSize))
                {
                    return null;
                }
                else if (_size <= 0 || _size >= 4000)
                {
                    return "Max";
                }
                return _size.ToString();
            }

            set
            {
                if (value != null)
                {
                    if (string.Equals(value, "Max", StringComparison.OrdinalIgnoreCase))
                    {
                        _size = -1;
                        return;
                    }
                    _size = int.Parse(value);
                    if (_size <= 0 || _size >= 4000)
                    {
                        _size = -1;
                    }
                }
                else
                {
                    _size = DefaultSize;
                }
            }
        }
        [XmlIgnore]
        public int Size { get => _size; set => _size = value; }
    }









}
