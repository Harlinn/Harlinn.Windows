/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmTranGlobalRecoveryTransactionsDataType
{
    readonly int _databaseId = 0;
    readonly Guid _transactionUow;
    readonly int _transactionManagerDbid = 0;
    readonly Guid _transactionManagerRmid;
    readonly string? _transactionManagerServerName;
    readonly string? _transactionManagerDatabaseName;

    public DmTranGlobalRecoveryTransactionsDataType( )
    {
    }

    public DmTranGlobalRecoveryTransactionsDataType(int databaseId,
        Guid transactionUow,
        int transactionManagerDbid,
        Guid transactionManagerRmid,
        string? transactionManagerServerName,
        string? transactionManagerDatabaseName)
    {
        _databaseId = databaseId;
        _transactionUow = transactionUow;
        _transactionManagerDbid = transactionManagerDbid;
        _transactionManagerRmid = transactionManagerRmid;
        _transactionManagerServerName = transactionManagerServerName;
        _transactionManagerDatabaseName = transactionManagerDatabaseName;
    }

    public int DatabaseId => _databaseId;
    public Guid TransactionUow => _transactionUow;
    public int TransactionManagerDbid => _transactionManagerDbid;
    public Guid TransactionManagerRmid => _transactionManagerRmid;
    public string? TransactionManagerServerName => _transactionManagerServerName;
    public string? TransactionManagerDatabaseName => _transactionManagerDatabaseName;
}
