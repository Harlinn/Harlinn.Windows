
using System;
using System.Runtime.CompilerServices;
using System.Diagnostics.CodeAnalysis;

using Microsoft.Extensions.Logging;

using Harlinn.Common.Core.Net.Data;
using System.ComponentModel;


namespace Harlinn.Common.Core.Net.Entities
{

    public partial class EntityContextBase<TKind> : IDisposable where TKind : struct, Enum 
    {
        public event EntityContextExceptionEventHandler<TKind> OnExceptionEvent;
        public event EventHandler<EventContextUpdatedEventArgs<TKind>> OnContextUpdated;
        public event EventHandler<EventContextEntityPropertyChangedEventArgs<TKind>> OnEntityPropertyChangedEvent;
        public event EventHandler<EventContextBeforeCommitEventArgs<TKind>> OnBeforeCommitEvent;
        public event EventHandler<EventContextAfterCommitEventArgs<TKind>> OnAfterCommitEvent;

        protected object _lock = new object();
        private ILogger _logger;
        IDataContextBase<TKind> _dataContext;
        IBaseEntityFactory<TKind> _entityFactory;
        IBaseDataFactory<TKind> _dataFactory;
        Dictionary<Guid, WeakReference> _entities;
        Dictionary<Guid, BaseEntity<TKind>> _changedEntities;
        Dictionary<Guid, BaseEntity<TKind>> _newEntities;
        Dictionary<Guid, BaseEntity<TKind>> _deletedEntities;
        Dictionary<Guid, BaseEntity<TKind>> _cachedEntities;
        
        long _sequenceNumber;
        bool _ownsDataContext;
        bool disposedValue;

        public EntityContextBase([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] IDataContextBase<TKind> dataContext, [DisallowNull] IBaseEntityFactory<TKind> entityFactory, [DisallowNull] IBaseDataFactory<TKind> dataFactory, bool ownsDataContext = true)
        {
            _logger = loggerFactory.CreateLogger<EntityContextBase<TKind>>();
            _entities = new Dictionary<Guid, WeakReference>();
            _changedEntities = new Dictionary<Guid, BaseEntity<TKind>>();
            _newEntities = new Dictionary<Guid, BaseEntity<TKind>>();
            _deletedEntities = new Dictionary<Guid, BaseEntity<TKind>>();
            _cachedEntities = new Dictionary<Guid, BaseEntity<TKind>>();
            _dataContext = dataContext;
            _entityFactory = entityFactory;
            _dataFactory = dataFactory;
            _sequenceNumber = 0;
            _ownsDataContext = ownsDataContext;
        }


        private void DirectLogException(Exception exc, [CallerMemberName] string callerName = "")
        {
            string exceptionMessageText = exc.Message;
            string messageText = string.Format("Exception in {0} - {1}", callerName, exceptionMessageText);
            _logger.LogError(exc, messageText);
#if DEBUG
            if (System.Diagnostics.Debugger.IsAttached)
            {
                System.Diagnostics.Debugger.Log(1, "Exception", messageText);
                System.Diagnostics.Debugger.Break();
            }
#endif
        }

        private void LogException(Exception exc, [CallerMemberName] string callerName = "")
        {
            DirectLogException(exc, callerName);
            OnException(exc, callerName);
        }

        protected void OnException(Exception exc, [CallerMemberName] string callerName = "")
        {
            if (OnExceptionEvent != null)
            {
                EntityContextExceptionEventArgs<TKind> eventArgs = new EntityContextExceptionEventArgs<TKind>(this, exc, callerName);
                OnExceptionEvent(this, eventArgs);
            }
        }


        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing && _ownsDataContext && _dataContext is IDisposable)
                {
                    ((IDisposable)_dataContext).Dispose();
                }
                disposedValue = true;
            }
        }

        public void Dispose()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }

        protected IDataContextBase<TKind> DataContextBase
        {
            get
            {
                return _dataContext;
            }
        }


        public Guid SessionId
        {
            get
            {
                var dataContext = DataContextBase;
                var result = dataContext.SessionId;
                return result;
            }
        }


        /// <summary>
        /// <para>
        /// This is here to make it possible for external code
        /// to access the data object of the entity.
        /// </para>
        /// <para>
        /// Do <em>not</em> modify the returned data object in any way.
        /// </para>
        /// </summary>
        /// <param name="entity">The entity</param>
        /// <returns>The data object of the entity</returns>
        public static BaseDataGuid<TKind> GetDataOf([DisallowNull] BaseEntity<TKind> entity)
        {
            return entity._GetData();
        }

        internal void AddToContext([DisallowNull] BaseEntity<TKind> entity)
        {
            _entities.Add(entity.Id, new WeakReference(entity));
            if (entity.KeepInCache())
            {
                _cachedEntities.Add(entity.Id, entity);
            }
            if (entity.IsNew())
            {
                _newEntities.Add(entity.Id, entity);
            }
        }
        public BaseEntity<TKind> AddToContext([DisallowNull] BaseDataGuid<TKind> data)
        {
            WeakReference entityReference;
            if (_entities.TryGetValue(data.Id, out entityReference))
            {
                var existingEntity = (BaseEntity<TKind>)entityReference.Target;
                if (existingEntity != null)
                {
                    existingEntity.Update(data);
                    return existingEntity;
                }
                else
                {
                    _entities.Remove(data.Id);
                }
            }
            var entity = _entityFactory.Create(this, data);
            AddToContext(entity);
            return entity;
        }

        protected BindingList<TEntity> ToEntityList<TEntity,TData>( [DisallowNull] IList<TData> dataItems ) where TEntity : BaseEntity<TKind> where TData : BaseDataGuid<TKind>
        {
            var count = dataItems.Count;
            var result = new BindingList<TEntity>();

            for (int i = 0; i < count; i++)
            {
                var dataItem = dataItems[i];
                var entity = (TEntity?)GetEntityFromCache(dataItem.Id);
                if(entity == null)
                {
                    entity = (TEntity)AddToContext(dataItem);
                }
                else
                {
                    entity.Update(dataItem);
                }
                result.Add(entity);
            }
            return result;
        }


        void ClearGarbageCollectedEntries()
        {
            List<Guid> keysToRemove = new List<Guid>();
            try
            {
                foreach (var entry in _entities)
                {
                    var weakRef = entry.Value;
                    if (weakRef == null || weakRef.Target == null)
                    {
                        keysToRemove.Add(entry.Key);
                    }
                }
            }
            catch
            {
                // Garbage collection may happen in another thread,
                // and garbage collected entities will try to remove
                // themselves from the entity context. This is not an
                // error, so here we just ignore the exception.

                // Garbage collection from a background thread is supposed to 
                // block all other executing .Net threads, so there should be
                // no need to synchronize access to avoid corruption of the
                // containers.
            }
            var count = keysToRemove.Count;
            for (int i = 0; i < count; i++)
            {
                _entities.Remove(keysToRemove[i]);
            }
        }

        protected internal BaseEntity<TKind>? GetEntityFromCache(Guid id)
        {
            WeakReference weakReference;
            if (_entities.TryGetValue(id, out weakReference))
            {
                var result = weakReference.Target as BaseEntity<TKind>;
                if (result == null)
                {
                    ClearGarbageCollectedEntries();
                }
                return result;
            }
            return null;
        }

        internal void RemoveEntityFromCache(Guid id)
        {
            _entities.Remove(id);
            _cachedEntities.Remove(id);
            _changedEntities.Remove(id);
            _newEntities.Remove(id);
            _deletedEntities.Remove(id);
        }

        internal void FireEntityPropertyChangedEvent(BaseEntity<TKind> entity, string propertyName)
        {
            if (OnEntityPropertyChangedEvent != null)
            {
                var eventArgs = new EventContextEntityPropertyChangedEventArgs<TKind>(this, entity, propertyName);
                OnEntityPropertyChangedEvent(this, eventArgs);
            }
        }


        internal void OnChanged(BaseEntity<TKind> entity)
        {
            if (entity.IsNew() == false && _changedEntities.ContainsKey(entity.Id) == false)
            {
                _changedEntities.Add(entity.Id, entity);
            }
        }

        internal void OnCancelEdit(BaseEntity<TKind> entity)
        {
            if (entity.IsNew() == false && _changedEntities.ContainsKey(entity.Id) == false)
            {
                _changedEntities.Remove(entity.Id);
            }
        }


        internal void OnDelete(BaseEntity<TKind> entity)
        {
            if (entity.IsNew() == false)
            {
                _deletedEntities[entity.Id] = entity;
            }
            else
            {
                _newEntities.Remove(entity.Id);
            }
            _entities.Remove(entity.Id);
            _cachedEntities.Remove(entity.Id);
            _changedEntities.Remove(entity.Id);
        }

        internal bool IsDeleted(Guid id)
        {
            return _deletedEntities.ContainsKey(id);
        }


        public bool HasChanges()
        {
            return _newEntities.Count > 0 || _changedEntities.Count > 0 || _deletedEntities.Count > 0;
        }

        public void Commit()
        {
            if (HasChanges())
            {
                var inserted = new List<BaseDataGuid<TKind>>(_newEntities.Count);
                var updated = new List<BaseDataGuid<TKind>>(_changedEntities.Count);
                var deleted = new List<BaseDataGuid<TKind>>(_deletedEntities.Count);

                foreach (var entry in _newEntities)
                {
                    var newEntity = entry.Value;
                    var data = newEntity._GetData();
                    inserted.Add(data);
                }
                foreach (var entry in _changedEntities)
                {
                    var changedEntity = entry.Value;
                    var data = changedEntity._GetData();
                    updated.Add(data);
                }
                foreach (var entry in _deletedEntities)
                {
                    var deletedEntity = entry.Value;
                    var data = deletedEntity._GetData();
                    deleted.Add(data);
                }

                _sequenceNumber++;

                var updateData = new UpdateData<TKind>(_dataFactory, SessionId, DateTime.UtcNow, _sequenceNumber, inserted, updated, deleted);

                if (OnBeforeCommitEvent != null)
                {
                    var eventArgs = new EventContextBeforeCommitEventArgs<TKind>(this, updateData);
                    OnBeforeCommitEvent(this, eventArgs);
                }

                var dataContext = DataContextBase;


                dataContext.Update(updateData);
                _newEntities.Clear();
                _changedEntities.Clear();
                _deletedEntities.Clear();
                ClearGarbageCollectedEntries();
                foreach (var entry in _entities)
                {
                    var weakRef = entry.Value;
                    if (weakRef != null)
                    {
                        var entity = (BaseEntity<TKind>)weakRef.Target;
                        if (entity != null)
                        {
                            entity.EndEdit();
                            var data = entity._GetData();
                            if (data.ObjectState != ObjectState.Stored)
                            {
                                data.ObjectState = ObjectState.Stored;
                            }

                        }
                    }
                }
                if (OnAfterCommitEvent != null)
                {
                    var eventArgs = new EventContextAfterCommitEventArgs<TKind>(this, updateData);
                    OnAfterCommitEvent(this, eventArgs);
                }

            }

        }

        public void ProcessUpdate(UpdateData<TKind> updateData)
        {
            var updated = updateData.Updated;
            foreach (var item in updated)
            {
                WeakReference entityReference;
                if (_entities.TryGetValue(item.Id, out entityReference))
                {
                    var entity = (BaseEntity<TKind>)entityReference.Target;
                    if (entity != null)
                    {
                        entity.Update(item);
                    }
                }
            }
            var deleted = updateData.Deleted;
            foreach (var item in deleted)
            {
                if (_entities.ContainsKey(item.Id))
                {
                    RemoveEntityFromCache(item.Id);
                }
            }

            if (OnContextUpdated != null)
            {
                var eventArgs = new EventContextUpdatedEventArgs<TKind>(this, updateData);
                OnContextUpdated(this, eventArgs);
            }

        }

    }
}
