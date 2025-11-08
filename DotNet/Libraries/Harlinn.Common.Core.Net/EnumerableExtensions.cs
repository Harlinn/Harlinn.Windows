using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Common.Core.Net
{
    public static class EnumerableExtensions
    {
        public static string Join(this IEnumerable<object> source, string separator = ", ") => string.Join(separator, source);


    }
}
