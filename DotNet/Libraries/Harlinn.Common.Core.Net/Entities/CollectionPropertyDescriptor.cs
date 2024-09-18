using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace Harlinn.Common.Core.Net.Entities
{
    public class CollectionPropertyDescriptor<T,TKind> : PropertyDescriptor where T : BaseEntity<TKind> where TKind : struct, Enum
    {
        private BindingListEx<T, TKind> collection;
        private int index = -1;

        public CollectionPropertyDescriptor(BindingListEx<T, TKind> collection, int index)
            : base("#" + index, null)
        {
            this.collection = collection;
            this.index = index;
        }

        public override string DisplayName
        {
            get
            {
                T element = collection[index];
                return element.GetDisplayLabel();
            }
        }


        public override string Description
        {
            get
            {
                T element = collection[index];
                return element.GetDescription();
            }
        }


        public override AttributeCollection Attributes
        {
            get
            {
                return new AttributeCollection(null);
            }
        }

        public override bool CanResetValue(object component)
        {
            return true;
        }


        public override Type ComponentType
        {
            get
            {
                return collection.GetType();
            }
        }

        public override bool ShouldSerializeValue(object component)
        {
            return true;
        }

        public override void ResetValue(object component)
        {

        }

        public override void SetValue(object component, object value)
        {
            collection[index] = (T)value;
        }



        public override object GetValue(object component)
        {
            return collection[index];
        }

        public override bool IsReadOnly
        {
            get
            {
                return true;
            }
        }

        public override Type PropertyType
        {
            get
            {
                return typeof(T);
            }
        }
    }
}
