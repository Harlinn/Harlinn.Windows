using Harlinn.Common.Core.Net.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Common.Core.Net.Entities
{
    public class EntityContextEventArgs<TKind> : EventArgs where TKind : struct, Enum
    {
        private EntityContextBase<TKind> context;
        public EntityContextEventArgs(EntityContextBase<TKind> entityContext)
        {
            context = entityContext;
        }

        public EntityContextBase<TKind> Context
        {
            get
            {
                return context;
            }
        }
    }

    //----------------------------------------------------------------------------------------------------------
    public class EventContextUpdatedEventArgs<TKind> : EntityContextEventArgs<TKind> where TKind : struct, Enum
    {
        readonly UpdateData<TKind> _updateData;
        public EventContextUpdatedEventArgs(EntityContextBase<TKind> entityContext, UpdateData<TKind> updateData)
            : base(entityContext)
        {
            _updateData = updateData;
        }

        public UpdateData<TKind> UpdateData => _updateData;
    }

    //----------------------------------------------------------------------------------------------------------
    public class EventContextBeforeCommitEventArgs<TKind> : EntityContextEventArgs<TKind> where TKind : struct, Enum
    {
        readonly UpdateData<TKind> _updateData;
        public EventContextBeforeCommitEventArgs(EntityContextBase<TKind> entityContext, UpdateData<TKind> updateData)
            : base(entityContext)
        {
            _updateData = updateData;
        }

        public UpdateData<TKind> UpdateData => _updateData;
    }

    //----------------------------------------------------------------------------------------------------------
    public class EventContextAfterCommitEventArgs<TKind> : EntityContextEventArgs<TKind> where TKind : struct, Enum
    {
        readonly UpdateData<TKind> _updateData;
        public EventContextAfterCommitEventArgs(EntityContextBase<TKind> entityContext, UpdateData<TKind> updateData)
            : base(entityContext)
        {
            _updateData = updateData;
        }

        public UpdateData<TKind> UpdateData => _updateData;
    }



    //----------------------------------------------------------------------------------------------------------
    public class EventContextEntityPropertyChangedEventArgs<TKind> : EntityContextEventArgs<TKind> where TKind : struct, Enum
    {
        readonly BaseEntity<TKind> _entity;
        readonly string _propertyName;
        public EventContextEntityPropertyChangedEventArgs(EntityContextBase<TKind> entityContext, BaseEntity<TKind> entity, string propertyName)
            : base(entityContext)
        {
            _entity = entity;
            _propertyName = propertyName;
        }

        public BaseEntity<TKind> Entity => _entity;

        public string PropertyName => _propertyName;
    }


    //----------------------------------------------------------------------------------------------------------

    public delegate void EntityContextExceptionEventHandler<TKind>(object sender, EntityContextExceptionEventArgs<TKind> eventArgs) where TKind : struct, Enum;
    public class EntityContextExceptionEventArgs<TKind> : EntityContextEventArgs<TKind> where TKind : struct, Enum
    {
        Exception _exception;
        string _method;
        bool _handled;

        public EntityContextExceptionEventArgs(EntityContextBase<TKind> entityContext, Exception exception, string method)
            : base(entityContext)
        {
            _exception = exception;
            _method = method;
        }


        public Exception Exception
        {
            get
            {
                return _exception;
            }
        }
        public string Method
        {
            get
            {
                return _method;
            }
        }
        public bool Handled
        {
            get
            {
                return _handled;
            }
            set
            {
                _handled = value;
            }
        }

    }
}
