using System;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Console;

namespace Barrelman.Data.Tests
{
    internal class LoggerFactoryHelper
    {
        static ILoggerFactory? _loggerFactory;

        public static ILoggerFactory LoggerFactory
        {
            get
            {
                if(_loggerFactory == null)
                {
                    _loggerFactory = Microsoft.Extensions.Logging.LoggerFactory.Create(builder => builder.AddConsole()); 
                }
                return _loggerFactory;
            }
        }
    }
}
