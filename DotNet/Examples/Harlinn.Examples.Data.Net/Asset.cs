using System;

namespace Harlinn.Examples.Data.Net
{
    public class Asset : CatalogItem
    {
        public Asset()
        {
        }

        public Asset(Guid id, string name) 
            : base(id, name)
        {
        }

        public Asset(Guid id, string name, Guid owner) 
            : base(id, name, owner)
        {
        }

        public override CatalogItemType Kind
        {
            get
            {
                return CatalogItemType.Asset;
            }
        }
    }






}
