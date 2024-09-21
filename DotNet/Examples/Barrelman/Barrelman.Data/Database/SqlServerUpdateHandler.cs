using System;
using System.Diagnostics.CodeAnalysis;
using System.Collections.Generic;


using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;

using Harlinn.Common.Core.Net.Data;

using Barrelman.Data.Types;

namespace Barrelman.Data.Database
{
    internal class SqlServerUpdateNode
    {
        BaseDataGuid<Kind> _data;
        Dictionary<Guid,SqlServerUpdateNode> _dependsOn;

        internal SqlServerUpdateNode(BaseDataGuid<Kind> data )
        {
            _data = data;
            _dependsOn = new Dictionary<Guid, SqlServerUpdateNode>();
        }
    }

    internal partial class SqlServerUpdateHandler
    {
        ILogger _logger;
        StoredProcedures _storedProcedures;
        SqlServerDataContext _dataContext;
        UpdateData<Kind> _updateData;
        Dictionary<Guid, SqlServerUpdateNode> _updateNodes;
        internal SqlServerUpdateHandler([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] StoredProcedures storedProcedures, [DisallowNull] SqlServerDataContext dataContext, [DisallowNull] UpdateData<Kind> updateData )
        {
            _logger = loggerFactory.CreateLogger<SqlServerUpdateHandler>();
            _storedProcedures = storedProcedures;
            _dataContext = dataContext;
            _updateData = updateData;
            _updateNodes = new Dictionary<Guid, SqlServerUpdateNode>();
        }
        internal void Update()
        {
            
        }
    }
}
