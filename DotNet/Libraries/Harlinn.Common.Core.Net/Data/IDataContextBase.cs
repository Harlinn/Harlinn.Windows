using System;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data
{
    public interface IDataContextBase<TKind> : IDisposable where TKind : struct, Enum
    {
        Guid SessionId { get; }
        bool Update([DisallowNull] UpdateData<TKind> updateData);

        bool Merge([DisallowNull] BaseDataGuid<TKind> dataObject);
        bool Insert([DisallowNull] BaseDataGuid<TKind> dataObject);
        bool Update([DisallowNull] BaseDataGuid<TKind> dataObject);
        bool Delete([DisallowNull] BaseDataGuid<TKind> dataObject);



    }
}
