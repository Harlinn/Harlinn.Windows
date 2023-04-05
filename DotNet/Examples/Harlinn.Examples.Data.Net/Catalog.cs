using System;

namespace Harlinn.Examples.Data.Net
{
    public class Catalog : CatalogItem
    {
        public Catalog()
        {
        }

        public Catalog(Guid id, string name) 
            : base(id, name)
        {
        }

        public Catalog(Guid id, string name, Guid owner) 
            : base(id, name, owner)
        {
        }

        public override CatalogItemType Kind
        {
            get
            {
                return CatalogItemType.Catalog;
            }
        }
    }






}
