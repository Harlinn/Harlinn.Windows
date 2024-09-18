using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Collections;
using System.Reflection;
using System.Security.Permissions;
using System.Security;

namespace Harlinn.Common.Core.Net.Entities
{
    [Serializable]
    public class BindingListEx<T,TKind> : ICustomTypeDescriptor,
        IList<T>,
        IList,
        IBindingList,
        ICancelAddNew,
        System.Collections.Specialized.INotifyCollectionChanged,
        IRaiseItemChangedEvents where T : BaseEntity<TKind> where TKind : struct, Enum
    {
        IList<T> items;
        [NonSerialized]
        private Object synchRoot;


        private int addNewPos = -1;
        private bool raiseListChangedEvents = true;
        private bool raiseItemChangedEvents = false;

        [NonSerialized()]
        private PropertyDescriptorCollection itemTypeProperties = null;

        [NonSerialized()]
        private PropertyChangedEventHandler propertyChangedEventHandler = null;

        [NonSerialized()]
        private AddingNewEventHandler onAddingNew;

        [NonSerialized()]
        private ListChangedEventHandler onListChanged;

        [NonSerialized()]
        private int lastChangeIndex = -1;

        private bool allowNew = true;
        private bool allowEdit = true;
        private bool allowRemove = true;
        private bool userSetAllowNew = false;

        public event System.Collections.Specialized.NotifyCollectionChangedEventHandler CollectionChanged;

        public BindingListEx()
        {
            items = new List<T>();
            Initialize();
        }

        public BindingListEx(IList<T> list)
        {
            if (list == null)
            {
                throw new ArgumentNullException("list");
            }
            items = list;
            Initialize();
        }

        /*
        public int Compare(IList<T> list)
        {
            int result = Count - list.Count;
            if (result == 0)
            {
                for (int i = 0; i < Count; i++)
                {
                    T first = items[i];
                    T second = list[i];
                    int compareResult = first.CompareTo(second);
                    if (compareResult != 0)
                    {
                        result = compareResult;
                    }

                }
            }
            return result;
        }
        */


        [Browsable(false)]
        public int Count
        {
            get
            {
                return items.Count;
            }
        }


        protected IList<T> Items
        {
            get
            {
                return items;
            }
        }


        public T this[int index]
        {
            get
            {
                return items[index];
            }
            set
            {
                if (items.IsReadOnly)
                {
                    throw new NotSupportedException("This is a read only collection, operation not supported.");
                }

                if (index < 0 || index >= items.Count)
                {
                    throw new ArgumentOutOfRangeException(string.Format("Index ({1}) out of range, number of elements in the collection is {0}.", Count, index));
                }

                SetItem(index, value);
            }
        }

        public void Add(T item)
        {
            if (items.IsReadOnly)
            {
                throw new NotSupportedException("This is a read only collection, operation not supported.");
            }

            int index = items.Count;
            InsertItem(index, item);
        }

        public void Clear()
        {
            if (items.IsReadOnly)
            {
                throw new NotSupportedException("This is a read only collection, operation not supported.");
            }

            ClearItems();
        }


        public void CopyTo(T[] array, int index)
        {
            items.CopyTo(array, index);
        }


        public bool Contains(T item)
        {
            return items.Contains(item);
        }

        public IEnumerator<T> GetEnumerator()
        {
            return items.GetEnumerator();
        }

        public int IndexOf(T item)
        {
            return items.IndexOf(item);
        }


        public void Insert(int index, T item)
        {
            if (items.IsReadOnly)
            {
                throw new NotSupportedException("This is a read only collection, operation not supported.");
            }

            if (index < 0 || index > items.Count)
            {
                throw new ArgumentOutOfRangeException(string.Format("Index ({1}) out of range, number of elements in the collection is {0}.", Count, index));
            }

            InsertItem(index, item);
        }

        public bool Remove(T item)
        {
            if (items.IsReadOnly)
            {
                throw new NotSupportedException("This is a read only collection, operation not supported.");
            }

            int index = items.IndexOf(item);
            if (index < 0) return false;
            RemoveItem(index);
            return true;
        }

        public void RemoveAt(int index)
        {
            if (items.IsReadOnly)
            {
                throw new NotSupportedException("This is a read only collection, operation not supported.");
            }

            if (index < 0 || index >= items.Count)
            {
                throw new ArgumentOutOfRangeException(string.Format("Index ({1}) out of range, number of elements in the collection is {0}.", Count, index));
            }

            RemoveItem(index);
        }

        [Browsable(false)]
        bool ICollection<T>.IsReadOnly
        {
            get
            {
                return items.IsReadOnly;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)items).GetEnumerator();
        }

        bool ICollection.IsSynchronized
        {
            get
            {
                return false;
            }
        }

        [Browsable(false)]
        object ICollection.SyncRoot
        {
            get
            {
                if (synchRoot == null)
                {
                    ICollection c = items as ICollection;
                    if (c != null)
                    {
                        synchRoot = c.SyncRoot;
                    }
                    else
                    {
                        System.Threading.Interlocked.CompareExchange<Object>(ref synchRoot, new Object(), null);
                    }
                }
                return synchRoot;
            }
        }

        void ICollection.CopyTo(Array array, int index)
        {
            if (array == null)
            {
                throw new ArgumentNullException("array");
            }

            if (array.Rank != 1)
            {
                throw new ArgumentException("Multi dimensional arrays not supported.");
            }

            if (array.GetLowerBound(0) != 0)
            {
                throw new ArgumentException("Arrays with non-zero lower bound not supported.");
            }

            if (index < 0)
            {
                throw new ArgumentOutOfRangeException(string.Format("Index ({1}) out of range, number of elements in the collection is {0}.", Count, index));
            }

            if (array.Length - index < Count)
            {
                throw new ArgumentException("Length of array too small.");
            }

            T[] tArray = array as T[];
            if (tArray != null)
            {
                items.CopyTo(tArray, index);
            }
            else
            {
                Type targetType = array.GetType().GetElementType();
                Type sourceType = typeof(T);
                if (!(targetType.IsAssignableFrom(sourceType) || sourceType.IsAssignableFrom(targetType)))
                {
                    throw new ArgumentException("Invalid array type.");
                }

                object[] objects = array as object[];
                if (objects == null)
                {
                    // T is not an object
                    throw new ArgumentException("Invalid array type.");
                }

                int count = items.Count;
                try
                {
                    for (int i = 0; i < count; i++)
                    {
                        objects[index++] = items[i];
                    }
                }
                catch (ArrayTypeMismatchException)
                {
                    throw new ArgumentException("Invalid array type.");
                }
            }
        }

        [Browsable(false)]
        object IList.this[int index]
        {
            get
            {
                return items[index];
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }

                try
                {
                    this[index] = (T)value;
                }
                catch (InvalidCastException)
                {
                    throw new ArgumentException("Invalid type");
                }
            }
        }

        [Browsable(false)]
        bool IList.IsReadOnly
        {
            get
            {
                return items.IsReadOnly;
            }
        }

        [Browsable(false)]
        bool IList.IsFixedSize
        {
            get
            {
                IList list = items as IList;
                if (list != null)
                {
                    return list.IsFixedSize;
                }
                return items.IsReadOnly;
            }
        }

        int IList.Add(object value)
        {
            if (items.IsReadOnly)
            {
                throw new NotSupportedException("This is a read only collection, operation not supported.");
            }
            if (value == null)
            {
                throw new ArgumentNullException("value");
            }

            try
            {
                Add((T)value);
            }
            catch (InvalidCastException)
            {
                throw new ArgumentException("Invalid type");
            }

            return this.Count - 1;
        }

        bool IList.Contains(object value)
        {
            if (IsCompatibleObject(value))
            {
                return Contains((T)value);
            }
            return false;
        }

        int IList.IndexOf(object value)
        {
            if (IsCompatibleObject(value))
            {
                return IndexOf((T)value);
            }
            return -1;
        }

        void IList.Insert(int index, object value)
        {
            if (items.IsReadOnly)
            {
                throw new NotSupportedException("This is a read only collection, operation not supported.");
            }
            if (value == null)
            {
                throw new ArgumentNullException("value");
            }

            try
            {
                Insert(index, (T)value);
            }
            catch (InvalidCastException)
            {
                throw new ArgumentException("Invalid type");
            }

        }

        void IList.Remove(object value)
        {
            if (items.IsReadOnly)
            {
                throw new NotSupportedException("This is a read only collection, operation not supported.");
            }

            if (IsCompatibleObject(value))
            {
                Remove((T)value);
            }
        }

        private static bool IsCompatibleObject(object value)
        {
            return ((value is T) || (value == null && default(T) == null));
        }

        public AttributeCollection GetAttributes()
        {
            return TypeDescriptor.GetAttributes(this, true);
        }

        public string GetClassName()
        {
            return TypeDescriptor.GetClassName(this, true);
        }

        public string GetComponentName()
        {
            return TypeDescriptor.GetComponentName(this, true);
        }

        public TypeConverter GetConverter()
        {
            return TypeDescriptor.GetConverter(this, true);
        }

        public EventDescriptor GetDefaultEvent()
        {
            return TypeDescriptor.GetDefaultEvent(this, true);
        }

        public PropertyDescriptor GetDefaultProperty()
        {
            return TypeDescriptor.GetDefaultProperty(this, true);
        }

        public object GetEditor(Type editorBaseType)
        {
            return TypeDescriptor.GetEditor(this, editorBaseType, true);
        }

        public EventDescriptorCollection GetEvents(Attribute[] attributes)
        {
            return TypeDescriptor.GetEvents(this, attributes, true);
        }

        public EventDescriptorCollection GetEvents()
        {
            return TypeDescriptor.GetEvents(this, true);
        }

        public PropertyDescriptorCollection GetProperties(Attribute[] attributes)
        {
            return GetProperties();
        }


        protected virtual PropertyDescriptor GetPropertyDescriptor(int index)
        {
            CollectionPropertyDescriptor<T, TKind> result = new CollectionPropertyDescriptor<T, TKind>(this, index);
            return result;
        }


        public PropertyDescriptorCollection GetProperties()
        {
            PropertyDescriptorCollection result = new PropertyDescriptorCollection(null);

            for (int i = 0; i < items.Count; i++)
            {
                PropertyDescriptor propertyDescriptor = GetPropertyDescriptor(i);
                result.Add(propertyDescriptor);
            }

            return result;
        }

        public object GetPropertyOwner(PropertyDescriptor pd)
        {
            return this;
        }


        private void Initialize()
        {
            this.allowNew = ItemTypeHasDefaultConstructor;

            if (typeof(INotifyPropertyChanged).IsAssignableFrom(typeof(T)))
            {
                this.raiseItemChangedEvents = true;

                foreach (T item in this.Items)
                {
                    HookPropertyChanged(item);
                }
            }
        }

        [Browsable(false)]
        private bool ItemTypeHasDefaultConstructor
        {
            get
            {
                Type itemType = typeof(T);

                if (itemType.IsPrimitive)
                {
                    return true;
                }

                if (itemType.GetConstructor(BindingFlags.Public | BindingFlags.Instance | BindingFlags.CreateInstance, null, new Type[0], null) != null)
                {
                    return true;
                }

                return false;
            }
        }

        public event AddingNewEventHandler AddingNew
        {
            add
            {
                bool allowNewWasTrue = AllowNew;
                onAddingNew += value;
                if (allowNewWasTrue != AllowNew)
                {
                    FireListChanged(ListChangedType.Reset, -1);
                }
            }
            remove
            {
                bool allowNewWasTrue = AllowNew;
                onAddingNew -= value;
                if (allowNewWasTrue != AllowNew)
                {
                    FireListChanged(ListChangedType.Reset, -1);
                }
            }
        }

        protected virtual void OnAddingNew(AddingNewEventArgs e)
        {
            if (onAddingNew != null)
            {
                onAddingNew(this, e);
            }
        }


        protected object FireAddingNew()
        {
            AddingNewEventArgs e = new AddingNewEventArgs(null);
            OnAddingNew(e);
            return e.NewObject;
        }



        public event ListChangedEventHandler ListChanged
        {
            add
            {
                onListChanged += value;
            }
            remove
            {
                onListChanged -= value;
            }
        }

        protected virtual void OnListChanged(ListChangedEventArgs e)
        {
            if (onListChanged != null)
            {
                onListChanged(this, e);
            }
        }

        [Browsable(false)]
        public bool RaiseListChangedEvents
        {
            get
            {
                return this.raiseListChangedEvents;
            }

            set
            {
                if (this.raiseListChangedEvents != value)
                {
                    this.raiseListChangedEvents = value;
                }
            }
        }

        public void ResetBindings()
        {
            FireListChanged(ListChangedType.Reset, -1);
        }

        public void ResetItem(int position)
        {
            FireListChanged(ListChangedType.ItemChanged, position);
        }


        private void FireListChanged(ListChangedType type, int index)
        {
            if (this.raiseListChangedEvents)
            {
                OnListChanged(new ListChangedEventArgs(type, index));
            }
        }



        protected virtual void ClearItems()
        {
            EndNew(addNewPos);

            if (this.raiseItemChangedEvents)
            {
                foreach (T item in this.Items)
                {
                    UnhookPropertyChanged(item);
                }
            }

            items.Clear();
            FireListChanged(ListChangedType.Reset, -1);
        }

        protected virtual void InsertItem(int index, T item)
        {
            EndNew(addNewPos);
            items.Insert(index, item);

            if (this.raiseItemChangedEvents)
            {
                HookPropertyChanged(item);
            }

            FireListChanged(ListChangedType.ItemAdded, index);
        }

        protected virtual void RemoveItem(int index)
        {
            if (!this.allowRemove && !(this.addNewPos >= 0 && this.addNewPos == index))
            {
                throw new NotSupportedException();
            }

            EndNew(addNewPos);

            if (this.raiseItemChangedEvents)
            {
                UnhookPropertyChanged(this[index]);
            }

            items.RemoveAt(index);
            FireListChanged(ListChangedType.ItemDeleted, index);
        }

        protected virtual void SetItem(int index, T item)
        {
            if (this.raiseItemChangedEvents)
            {
                UnhookPropertyChanged(this[index]);
            }

            items[index] = item;

            if (this.raiseItemChangedEvents)
            {
                HookPropertyChanged(item);
            }

            FireListChanged(ListChangedType.ItemChanged, index);
        }

        public virtual void CancelNew(int itemIndex)
        {
            if (addNewPos >= 0 && addNewPos == itemIndex)
            {
                RemoveItem(addNewPos);
                addNewPos = -1;
            }
        }

        public virtual void EndNew(int itemIndex)
        {
            if (addNewPos >= 0 && addNewPos == itemIndex)
            {
                addNewPos = -1;
            }
        }

        public T AddNew()
        {
            return (T)((this as IBindingList).AddNew());
        }

        object IBindingList.AddNew()
        {
            object newItem = AddNewCore();

            addNewPos = (newItem != null) ? IndexOf((T)newItem) : -1;

            return newItem;
        }

        private bool AddingNewHandled
        {
            get
            {
                return onAddingNew != null && onAddingNew.GetInvocationList().Length > 0;
            }
        }

        protected virtual object AddNewCore()
        {
            object newItem = FireAddingNew();

            if (newItem == null)
            {
                Type type = typeof(T);
                newItem = SecureCreateInstance(type);
            }

            Add((T)newItem);

            return newItem;
        }

        public bool AllowNew
        {
            get
            {
                if (userSetAllowNew || allowNew)
                {
                    return this.allowNew;
                }
                return AddingNewHandled;
            }
            set
            {
                bool oldAllowNewValue = AllowNew;
                userSetAllowNew = true;
                this.allowNew = value;
                if (oldAllowNewValue != value)
                {
                    FireListChanged(ListChangedType.Reset, -1);
                }
            }
        }

        bool IBindingList.AllowNew
        {
            get
            {
                return AllowNew;
            }
        }

        public bool AllowEdit
        {
            get
            {
                return this.allowEdit;
            }
            set
            {
                if (this.allowEdit != value)
                {
                    this.allowEdit = value;
                    FireListChanged(ListChangedType.Reset, -1);
                }
            }
        }

        bool IBindingList.AllowEdit
        {
            get
            {
                return AllowEdit;
            }
        }

        public bool AllowRemove
        {
            get
            {
                return this.allowRemove;
            }
            set
            {
                if (this.allowRemove != value)
                {
                    this.allowRemove = value;
                    FireListChanged(ListChangedType.Reset, -1);
                }
            }
        }

        bool IBindingList.AllowRemove
        {
            get
            {
                return AllowRemove;
            }
        }

        bool IBindingList.SupportsChangeNotification
        {
            get
            {
                return SupportsChangeNotificationCore;
            }
        }

        protected virtual bool SupportsChangeNotificationCore
        {
            get
            {
                return true;
            }
        }

        bool IBindingList.SupportsSearching
        {
            get
            {
                return SupportsSearchingCore;
            }
        }

        protected virtual bool SupportsSearchingCore
        {
            get
            {
                return false;
            }
        }

        bool IBindingList.SupportsSorting
        {
            get
            {
                return SupportsSortingCore;
            }
        }

        protected virtual bool SupportsSortingCore
        {
            get
            {
                return false;
            }
        }

        bool IBindingList.IsSorted
        {
            get
            {
                return IsSortedCore;
            }
        }

        protected virtual bool IsSortedCore
        {
            get
            {
                return false;
            }
        }

        PropertyDescriptor IBindingList.SortProperty
        {
            get
            {
                return SortPropertyCore;
            }
        }

        protected virtual PropertyDescriptor SortPropertyCore
        {
            get
            {
                return null;
            }
        }

        ListSortDirection IBindingList.SortDirection
        {
            get
            {
                return SortDirectionCore;
            }
        }

        protected virtual ListSortDirection SortDirectionCore
        {
            get
            {
                return ListSortDirection.Ascending;
            }
        }

        void IBindingList.ApplySort(PropertyDescriptor prop, ListSortDirection direction)
        {
            ApplySortCore(prop, direction);
        }

        protected virtual void ApplySortCore(PropertyDescriptor prop, ListSortDirection direction)
        {
            throw new NotSupportedException();
        }

        void IBindingList.RemoveSort()
        {
            RemoveSortCore();
        }

        protected virtual void RemoveSortCore()
        {
            throw new NotSupportedException();
        }

        int IBindingList.Find(PropertyDescriptor prop, object key)
        {
            return FindCore(prop, key);
        }

        protected virtual int FindCore(PropertyDescriptor prop, object key)
        {
            throw new NotSupportedException();
        }

        void IBindingList.AddIndex(PropertyDescriptor prop)
        {

        }

        void IBindingList.RemoveIndex(PropertyDescriptor prop)
        {

        }


        private void HookPropertyChanged(T item)
        {
            INotifyPropertyChanged inpc = (item as INotifyPropertyChanged);

            if (null != inpc)
            {
                if (propertyChangedEventHandler == null)
                {
                    propertyChangedEventHandler = new PropertyChangedEventHandler(ElementPropertyChangedHandler);
                }
                inpc.PropertyChanged += propertyChangedEventHandler;
            }
        }

        private void UnhookPropertyChanged(T item)
        {
            INotifyPropertyChanged inpc = (item as INotifyPropertyChanged);

            if (null != inpc && null != propertyChangedEventHandler)
            {
                inpc.PropertyChanged -= propertyChangedEventHandler;
            }
        }

        void ElementPropertyChangedHandler(object sender, PropertyChangedEventArgs e)
        {
            if (this.RaiseListChangedEvents)
            {
                if (sender == null || e == null || string.IsNullOrEmpty(e.PropertyName))
                {
                    ResetBindings();
                }
                else
                {
                    T item;

                    try
                    {
                        item = (T)sender;
                    }
                    catch (InvalidCastException)
                    {
                        ResetBindings();
                        return;
                    }

                    int pos = lastChangeIndex;

                    if (pos < 0 || pos >= Count || !this[pos].Equals(item))
                    {
                        pos = this.IndexOf(item);
                        lastChangeIndex = pos;
                    }

                    if (pos == -1)
                    {
                        UnhookPropertyChanged(item);
                        ResetBindings();
                    }
                    else
                    {
                        if (this.itemTypeProperties == null)
                        {
                            itemTypeProperties = TypeDescriptor.GetProperties(typeof(T));
                        }

                        PropertyDescriptor pd = itemTypeProperties.Find(e.PropertyName, true);
                        ListChangedEventArgs args = new ListChangedEventArgs(ListChangedType.ItemChanged, pos, pd);
                        OnListChanged(args);
                    }
                }
            }
        }

        bool IRaiseItemChangedEvents.RaisesItemChangedEvents
        {
            get
            {
                return this.raiseItemChangedEvents;
            }
        }






        private static void DemandReflectionAccess(Type type)
        {
        }




        internal static object SecureCreateInstance(Type type)
        {
            return SecureCreateInstance(type, null, false);
        }

        private static bool HasReflectionPermission(Type type)
        {
            return true;
        }

        private static object SecureCreateInstance(Type type, object[] args, bool allowNonPublic)
        {
            if (type == null)
            {
                throw new ArgumentNullException("type");
            }

            BindingFlags flags = BindingFlags.Instance | BindingFlags.Public | BindingFlags.CreateInstance;

            if (allowNonPublic)
            {
                flags |= BindingFlags.NonPublic;
            }

            return Activator.CreateInstance(type, flags, null, args, null);
        }
    }
}
