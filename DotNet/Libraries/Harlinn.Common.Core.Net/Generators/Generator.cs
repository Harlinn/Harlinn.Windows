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

namespace Harlinn.Common.Core.Net.Generators
{
    public abstract class Generator
    {
        double _baseValue;
        TimeSpan _interval;
        TimeSpan _offset;

        protected Generator(double baseValue, TimeSpan interval, TimeSpan offset = default)
        {
            _baseValue = baseValue;
            _interval = interval;
            _offset = offset;
        }

        public double BaseValue { get => _baseValue; set => _baseValue = value; }
        public TimeSpan Interval { get => _interval; set => _interval = value; }
        public TimeSpan Offset { get => _offset; set => _offset = value; }

        public abstract double Generate(DateTime timestamp);
    }

    public class SineGenerator : Generator
    {
        double _amplitude;

        public SineGenerator(double baseValue, TimeSpan interval, TimeSpan offset = default, double amplitude = 1.0)
            : base(baseValue, interval, offset)
        {
            _amplitude = amplitude;
        }

        public override double Generate(DateTime timestamp)
        {
            var ts = timestamp + Offset;
            var ticks = ts.Ticks % Interval.Ticks;
            double interval = Interval.Ticks;
            double time = ticks;
            double factor = Math.Sin((time / interval) * Math.PI * 2);
            double value = BaseValue + _amplitude * factor;
            return value;
        }
    }
}
