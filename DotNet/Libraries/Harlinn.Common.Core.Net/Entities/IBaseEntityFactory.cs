
using System;

using Harlinn.Common.Core.Net.Data;


namespace Harlinn.Common.Core.Net.Entities
{
    public interface IBaseEntityFactory<TKind> where TKind : struct, Enum
    {
        BaseEntity<TKind> Create(EntityContextBase<TKind> entityContextBase, TKind objectType);
        BaseEntity<TKind> Create(EntityContextBase<TKind> entityContextBase, BaseDataGuid<TKind> dataObject);
    }
}
