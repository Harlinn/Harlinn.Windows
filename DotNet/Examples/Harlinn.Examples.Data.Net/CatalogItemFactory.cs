using System;
using System.Collections.Generic;
using Harlinn.Common.Net.IO;

namespace Harlinn.Examples.Data.Net
{
    public class CatalogItemFactory
    {
        public static CatalogItem Create(CatalogItemType kind)
        {
            switch (kind)
            {
                case CatalogItemType.Catalog:
                    return new Catalog();
                case CatalogItemType.Asset:
                    return new Asset();
                default:
                    throw new Exception("Unsupported catalog item type");
            }
        }

        public static CatalogItem Read(BinaryReader reader)
        {
            var kind = CatalogItem.ReadKind(reader);
            var result = Create(kind);
            result.Read(reader);
            return result;
        }

        public static List<CatalogItem> ReadList(BinaryReader reader)
        {
            var count = reader.ReadInt32();
            var result = new List<CatalogItem>(count);
            for (int i = 0; i < count; ++i)
            {
                var item = Read(reader);
                result.Add(item);
            }
            return result;
        }
        public static Dictionary<Guid,CatalogItem> ReadDictionary(BinaryReader reader)
        {
            var count = reader.ReadInt32();
            var result = new Dictionary<Guid, CatalogItem>(count);
            for (int i = 0; i < count; ++i)
            {
                var item = Read(reader);
                result.Add(item.Id, item);
            }
            return result;
        }


    }



}
