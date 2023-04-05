using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Common.Net.Generators
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
