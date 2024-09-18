using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;

using Harlinn.Common.Core.Net.Data;

namespace Harlinn.Common.Core.Net.Entities
{
    
    public class BaseEntity<TKind> : INotifyPropertyChanged,
        INotifyPropertyChanging,
        IEditableObject,
        IChangeTracking,
        IRevertibleChangeTracking,
        IEquatable<BaseEntity<TKind>>,
        IComparable<BaseEntity<TKind>>,
        IComparable where TKind : struct, Enum
    {

        public event PropertyChangedEventHandler? PropertyChanged;
        public event PropertyChangingEventHandler? PropertyChanging;

        WeakReference _entityContext;

        BaseDataGuid<TKind> _data;
        BaseDataGuid<TKind>? _clone;

        public BaseEntity(EntityContextBase<TKind> entityContext, BaseDataGuid<TKind> data)
        {
            _entityContext = new WeakReference(entityContext ?? throw new ArgumentNullException(nameof(entityContext)));
            _data = data;
        }

        ~BaseEntity()
        {
            var context = _Context;
            if ((context != null) && (_data != null))
            {
                context.RemoveEntityFromCache(_data.Id);
            }
        }


        internal void Update(BaseDataGuid<TKind> serverData)
        {
            if (_data.ObjectState == ObjectState.Stored || _data.ObjectState == ObjectState.New)
            {
                FirePropertyChanging(serverData, false);
                var tmp = _data;
                _data = serverData;
                FirePropertyChanged(tmp);
            }
            else
            {
                _clone = serverData;
            }
        }


        public void Delete()
        {
            var context = _Context;
            if (context != null)
            {
                context.OnDelete(this);
            }
        }


        protected internal virtual string GetDisplayLabel()
        {
            return String.Empty;
        }
        protected internal virtual string GetDisplayText()
        {
            return String.Empty;
        }
        protected internal virtual string GetDescription()
        {
            return String.Empty;
        }

        public bool IsNew()
        {
            return _data.ObjectState == ObjectState.New;
        }
        public bool IsDeleted()
        {
            return _data.ObjectState == ObjectState.Deleted;
        }

        protected virtual void FirePropertyChanging(BaseDataGuid<TKind> newDataObject, bool beginEdit)
        {

        }

        protected virtual void FirePropertyChanged(BaseDataGuid<TKind> oldDataObject)
        {

        }



        /// <summary>
        /// Triggers the PropertyChanged event.
        /// </summary>
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = "")
        {
            if (PropertyChanged != null)
            {
                var ea = new PropertyChangedEventArgs(propertyName);
                PropertyChanged(this, ea);
            }
            var context = _Context;
            if (context != null)
            {
                context.FireEntityPropertyChangedEvent(this, propertyName);
            }
        }

        /// <summary>
        /// Triggers the PropertyChanging event.
        /// </summary>
        protected virtual void OnPropertyChanging([CallerMemberName] string propertyName = "", bool beginEdit = true)
        {
            if (PropertyChanging != null)
            {
                var ea = new PropertyChangingEventArgs(propertyName);
                PropertyChanging(this, ea);
            }
            if (beginEdit)
            {
                BeginEdit();
            }
        }


        public void BeginEdit()
        {
            if (_clone == null)
            {
                _clone = (BaseDataGuid<TKind>)_data.Clone();
            }
            if (_data.ObjectState == ObjectState.Stored)
            {
                var context = _Context;
                if (context != null)
                {
                    context.OnChanged(this);
                }
            }
        }

        public void CancelEdit()
        {
            if (_clone != null)
            {
                if (_clone.CompareTo(_data) != 0)
                {
                    FirePropertyChanging(_clone, false);
                    var tmp = _data;
                    _data = _clone;
                    FirePropertyChanged(tmp);
                }
                else
                {
                    _data = _clone;
                }
                _clone = null;


                var context = _Context;
                if (context != null)
                {
                    context.OnChanged(this);
                }
            }
        }




        public void EndEdit()
        {
            _clone = null;
        }



        [Browsable(false)]
        public bool IsChanged
        {
            get
            {
                return IsNew() || _data.ObjectState == ObjectState.Changed;
            }
        }

        public BaseEntity<TKind> This
        {
            get
            {
                return this;
            }
        }

        public void AcceptChanges()
        {
            EndEdit();
        }

        public void RejectChanges()
        {
            CancelEdit();
        }


        public bool Equals(BaseEntity<TKind> other)
        {
            return _data.Equals(other._data);
        }

        public int CompareTo(BaseEntity<TKind> other)
        {
            return _data.CompareTo(other._data);
        }

        int IComparable.CompareTo(object obj)
        {
            return CompareTo((BaseEntity<TKind>)obj);
        }


        [Browsable(false)]
        protected internal EntityContextBase<TKind> _Context
        {
            get
            {
                return (EntityContextBase<TKind>)_entityContext.Target;
            }
        }

        protected internal BaseDataGuid<TKind> _GetData()
        {
            return _data;
        }


#if !DEBUG
        [Browsable(false)]
#endif
        [Category("Debug")]
        public TKind ObjectType
        {
            get
            {
                return _data.GetObjectType();
            }
        }
        public bool IsOfType(TKind typeCode)
        {
            return _data.IsOfType(typeCode);
        }

        internal virtual bool KeepInCache()
        {
            return false;
        }




        /// <summary>
        /// The primary key of the object
        /// </summary>
#if !DEBUG
        [Browsable(false)]
#endif
        [Category("Debug")]
        public Guid Id
        {
            get
            {
                return _data.Id;
            }
        }
    }
}
