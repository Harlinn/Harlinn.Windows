using System;
using System.IO;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Examples.Data.Net
{
    public abstract class CatalogItem : Owned
    {
        protected CatalogItem()
        {
        }

        protected CatalogItem(Guid id, string name) 
            : base(id, name)
        {
        }

        protected CatalogItem(Guid id, string name, Guid owner) 
            : base(id, name, owner)
        {
        }

        public abstract CatalogItemType Kind
        {
            get;
        }

        public override void Write(BinaryWriter writer)
        {
            short kind = (short)Kind;
            writer.Write(kind);
            base.Write(writer);
        }

        public static CatalogItemType ReadKind(BinaryReader reader)
        {
            var kind = reader.ReadInt16();
            return (CatalogItemType)kind;
        }
    }

}
