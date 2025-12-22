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

using System.Numerics;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class Identity<T> where T : struct, INumber<T>, IMinMaxValue<T>
    {
        T _seed = T.One;
        T _increment = T.One;

        public Identity()
        { }

        public Identity(T seed, T increment)
        {
            _seed = seed;
            _increment = increment;
        }

        [XmlAttribute]
        public T Seed { get => _seed; set => _seed = value; }
        [XmlAttribute]
        public T Increment { get => _increment; set => _increment = value; }
    }


}