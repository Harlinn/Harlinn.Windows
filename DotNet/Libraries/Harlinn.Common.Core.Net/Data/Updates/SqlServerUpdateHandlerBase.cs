using Microsoft.Extensions.Logging;
using Microsoft.Identity.Client;
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Common.Core.Net.Data.Updates
{
    public abstract class SqlServerUpdateNodeBase<TKind> where TKind : struct, Enum
    {
        SqlServerUpdateHandlerBase<TKind> _updateHandler;
        BaseDataGuid<TKind> _data;
        ObjectState _objectState;
        Dictionary<Guid, SqlServerUpdateNodeBase<TKind>> _dependsOn;
        bool _executed = false;
        bool _requiresUpdate2 = false;

        public SqlServerUpdateNodeBase([DisallowNull] SqlServerUpdateHandlerBase<TKind> updateHandler, [DisallowNull] BaseDataGuid<TKind> data)
        {
            _updateHandler = updateHandler;
            _data = data;
            _objectState = _data.ObjectState;
            _dependsOn = new Dictionary<Guid, SqlServerUpdateNodeBase<TKind>>();
        }

        public SqlServerUpdateHandlerBase<TKind> Handler => _updateHandler;

        public Dictionary<Guid, SqlServerUpdateNodeBase<TKind>> UpdateNodes => Handler.UpdateNodes;

        protected BaseDataGuid<TKind> _GetData() { return _data; }
        public Guid Id => _data.Id;

        public ObjectState State => _objectState;

        public Dictionary<Guid, SqlServerUpdateNodeBase<TKind>> DependsOn => _dependsOn;
        public bool IsNew => _objectState == ObjectState.New;
        public bool IsChanged => _objectState == ObjectState.Changed;
        public bool IsDeleted => _objectState == ObjectState.Deleted;

        public bool Executed => _executed;
        public bool RequiresUpdate2 { get => _requiresUpdate2; set => _requiresUpdate2 = value; }

        public void AddDependency(SqlServerUpdateNodeBase<TKind> dependency)
        {
            _dependsOn.Add(dependency.Id, dependency);
        }

        public void Execute()
        {
            if (_executed == false)
            {
                foreach (var entry in _dependsOn)
                {
                    var node = entry.Value;
                    node.Execute();
                }
                var state = State;
                switch (state)
                {
                    case ObjectState.New:
                    {
                        if (RequiresUpdate2)
                        {
                            Insert1();
                        }
                        else
                        {
                            Insert();
                        }
                    }
                    break;
                    case ObjectState.Changed:
                    {
                        if (RequiresUpdate2)
                        {
                            Update1();
                        }
                        else
                        {
                            Update();
                        }
                    }
                    break;
                    case ObjectState.Deleted:
                    {
                        Delete();
                    }
                    break;
                }
                _executed = true;
            }
        }

        public virtual void CollectDependencies()
        {

        }

        public abstract void Insert();
        public virtual void Insert1()
        {
            throw new NotImplementedException();
        }

        public abstract void Update();
        public virtual void Update1()
        {
            throw new NotImplementedException();
        }
        public virtual void Update2()
        {
            throw new NotImplementedException();
        }

        public abstract void Delete();


    }


    public interface IUpdateNodeFactory<TKind> where TKind : struct, Enum
    {
        SqlServerUpdateNodeBase<TKind> Create([DisallowNull] SqlServerUpdateHandlerBase<TKind> updateHandler, [DisallowNull] BaseDataGuid<TKind> data);
    }

    public interface IStoredProcedures
    {

    }

    public class SqlServerUpdateHandlerBase<TKind> where TKind : struct, Enum
    {
        ILogger _logger;
        IStoredProcedures _storedProcedures;
        UpdateData<TKind> _updateData;
        IUpdateNodeFactory<TKind> _updateNodeFactory;
        Dictionary<Guid, SqlServerUpdateNodeBase<TKind>> _updateNodes;
        public SqlServerUpdateHandlerBase([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] IStoredProcedures storedProcedures, [DisallowNull] UpdateData<TKind> updateData, [DisallowNull] IUpdateNodeFactory<TKind> updateNodeFactory)
        {
            _logger = loggerFactory.CreateLogger<SqlServerUpdateHandlerBase<TKind>>();
            _storedProcedures = storedProcedures;
            _updateData = updateData;
            _updateNodeFactory = updateNodeFactory;
            _updateNodes = new Dictionary<Guid, SqlServerUpdateNodeBase<TKind>>();
            CreateUpdateNodes();
        }

        public IStoredProcedures StoredProcedures => _storedProcedures;
        public Dictionary<Guid, SqlServerUpdateNodeBase<TKind>> UpdateNodes => _updateNodes;

        public void CreateUpdateNodes()
        {
            var inserted = _updateData.Inserted;
            var count = inserted.Count;
            for (int i = 0; i < count; i++)
            {
                var dataObject = inserted[i];
                var updateNode = _updateNodeFactory.Create(this, dataObject);
                _updateNodes.Add(updateNode.Id, updateNode);
            }
            var updated = _updateData.Updated;
            count = updated.Count;
            for (int i = 0; i < count; i++)
            {
                var dataObject = updated[i];
                var updateNode = _updateNodeFactory.Create(this, dataObject);
                _updateNodes.Add(updateNode.Id, updateNode);
            }
            var deleted = _updateData.Deleted;
            count = deleted.Count;
            for (int i = 0; i < count; i++)
            {
                var dataObject = deleted[i];
                var updateNode = _updateNodeFactory.Create(this, dataObject);
                _updateNodes.Add(updateNode.Id, updateNode);
            }
            foreach (var entry in _updateNodes)
            {
                var node = entry.Value;
                node.CollectDependencies();
            }
        }

        public void Execute()
        {
            foreach (var entry in _updateNodes)
            {
                var node = entry.Value;
                node.Execute();
            }
            foreach (var entry in _updateNodes)
            {
                var node = entry.Value;
                if (node.RequiresUpdate2)
                {
                    node.Update2();
                }
            }
        }

    }
}
