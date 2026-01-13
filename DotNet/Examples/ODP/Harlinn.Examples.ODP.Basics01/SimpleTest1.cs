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
﻿using System;
using System.Collections.Generic;
using System.Linq;
using Oracle.ManagedDataAccess.Client;
using Oracle.ManagedDataAccess.Types;

namespace Harlinn.Examples.ODP.Basics01
{
    class SimpleTest1
    {
        OracleConnection _connection;

        

        public SimpleTest1(OracleConnection connection)
        {
            _connection = connection;
        }

        public void Clear()
        {
            using (var command = _connection.CreateCommand())
            {
                command.CommandText = "DELETE FROM SimpleTest1";
                command.ExecuteNonQuery();
            }
        }

        public SimpleTest1Data Insert(string name, string description = null)
        {
            using (var command = _connection.CreateCommand())
            {
                command.CommandText = "INSERT INTO SimpleTest1(Id, OptimisticLock, Name, Description ) "+
                                    "VALUES(SimpleTest1Seq.NextVal,0,:1,:2) RETURNING Id INTO :3";

                OracleParameter nameParameter = new OracleParameter();
                nameParameter.OracleDbType = OracleDbType.NVarchar2;
                nameParameter.Value = name;

                OracleParameter descriptionParameter = new OracleParameter();
                descriptionParameter.OracleDbType = OracleDbType.NVarchar2;
                descriptionParameter.Value = string.IsNullOrWhiteSpace(description) ? DBNull.Value : description;

                OracleParameter idParameter = new OracleParameter();
                idParameter.OracleDbType = OracleDbType.Int64;

                command.Parameters.Add(nameParameter);
                command.Parameters.Add(descriptionParameter);
                command.Parameters.Add(idParameter);

                command.ExecuteNonQuery();

                var idValue  = (OracleDecimal)idParameter.Value;

                var result = new SimpleTest1Data(idValue.ToInt64(), name, description );
                return result;
            }
        }

        public SimpleTest1Data Select(long id)
        {
            using (var command = _connection.CreateCommand())
            {
                command.CommandText = "SELECT OptimisticLock, Name, Description FROM SimpleTest1 "+
                                        "WHERE Id = :1";

                OracleParameter idParameter = new OracleParameter();
                idParameter.OracleDbType = OracleDbType.Int64;
                idParameter.Value = id;

                command.Parameters.Add(idParameter);

                using (var reader = command.ExecuteReader(System.Data.CommandBehavior.SingleRow))
                {
                    if (reader.Read())
                    {
                        var optimisticLock = reader.GetInt64(0);
                        var name = reader.GetString(1);
                        string description = null;
                        if (reader.IsDBNull(2) == false)
                        {
                            description = reader.GetString(2);
                        }
                        var result = new SimpleTest1Data(id, optimisticLock, name, description);
                        return result;
                    }
                    else
                    {
                        return null;
                    }
                }
            }
        }

        public Dictionary<long, SimpleTest1Data> Select()
        {
            var result = new Dictionary<long, SimpleTest1Data>();
            using (var command = _connection.CreateCommand())
            {
                command.CommandText = "SELECT Id, OptimisticLock, Name, Description FROM SimpleTest1";

                using (var reader = command.ExecuteReader(System.Data.CommandBehavior.SingleResult))
                {
                    while (reader.Read())
                    {
                        var id = reader.GetInt64(0);
                        var optimisticLock = reader.GetInt64(1);
                        var name = reader.GetString(2);
                        string description = null;
                        if (reader.IsDBNull(3) == false)
                        {
                            description = reader.GetString(3);
                        }
                        var rowData = new SimpleTest1Data(id, optimisticLock, name, description);
                        result.Add(id, rowData);
                    }
                }
            }
            return result;
        }


        public bool Update(SimpleTest1Data data)
        {
            using (var command = _connection.CreateCommand())
            {
                command.CommandText = "UPDATE SimpleTest1 "+
                                "SET OptimisticLock=OptimisticLock+1, Name=:1, Description=:2 "+
                                "WHERE Id=:3 AND OptimisticLock=:4";

                var id = data.Id;
                var optimisticLock = data.OptimisticLock;
                var name = data.Name;
                var description = data.Description;

                OracleParameter nameParameter = new OracleParameter();
                nameParameter.OracleDbType = OracleDbType.NVarchar2;
                nameParameter.Value = name;

                OracleParameter descriptionParameter = new OracleParameter();
                descriptionParameter.OracleDbType = OracleDbType.NVarchar2;
                descriptionParameter.Value = string.IsNullOrWhiteSpace(description) ? DBNull.Value : description;

                OracleParameter idParameter = new OracleParameter();
                idParameter.OracleDbType = OracleDbType.Int64;
                idParameter.Value = id;

                OracleParameter optimisticLockParameter = new OracleParameter();
                optimisticLockParameter.OracleDbType = OracleDbType.Int64;
                optimisticLockParameter.Value = optimisticLock;

                command.Parameters.Add(nameParameter);
                command.Parameters.Add(descriptionParameter);
                command.Parameters.Add(idParameter);
                command.Parameters.Add(optimisticLockParameter);

                if (command.ExecuteNonQuery() > 0)
                {
                    data.OptimisticLock = optimisticLock + 1;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        public bool Delete(SimpleTest1Data data)
        {
            using (var command = _connection.CreateCommand())
            {
                command.CommandText = "DELETE FROM SimpleTest1 " +
                                        "WHERE Id=:1 AND OptimisticLock=:2";

                var id = data.Id;
                var optimisticLock = data.OptimisticLock;

                OracleParameter idParameter = new OracleParameter();
                idParameter.OracleDbType = OracleDbType.Int64;
                idParameter.Value = id;

                OracleParameter optimisticLockParameter = new OracleParameter();
                optimisticLockParameter.OracleDbType = OracleDbType.Int64;
                optimisticLockParameter.Value = optimisticLock;

                command.Parameters.Add(idParameter);
                command.Parameters.Add(optimisticLockParameter);

                if (command.ExecuteNonQuery() > 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        public void Execute()
        {
            Clear();
            var originalItems = new Dictionary<long, SimpleTest1Data>( );
            int RowCount = 100;
            using (var transaction = _connection.BeginTransaction())
            {
                for (int i = 0; i < RowCount; ++i)
                {
                    var name = $"Name{i + 1}";
                    var description = i % 2 == 0 ? null : $"Description{i + 1}";
                    var data = Insert(name, description);
                    originalItems.Add(data.Id, data);
                }
                transaction.Commit();
            }

            var databaseItems = Select();

            foreach (var entry in originalItems)
            {
                var originalItem = entry.Value;
                if (databaseItems.ContainsKey(originalItem.Id))
                {
                    var databaseItem = databaseItems[originalItem.Id];
                    if (originalItem.Equals(databaseItem) == false)
                    {
                        throw new Exception($"The original item {originalItem} "+
                            $"is not equal to the item {databaseItem} "+
                            "retrieved from the database.");
                    }
                }
                else
                {
                    throw new Exception($"Did not retrieve {originalItem} from "+
                        "the database.");
                }
            }

            using (var transaction = _connection.BeginTransaction())
            {
                foreach (var entry in originalItems)
                {
                    var data = entry.Value;
                    if (string.IsNullOrWhiteSpace(data.Description))
                    {
                        data.Description = "Updated Description";
                        if (Update(data) == false)
                        {
                            var changedData = Select(data.Id);
                            if (changedData != null)
                            {
                                throw new Exception($"Unable to update {data}, the "+
                                    $"row has been updated by another user {changedData}");
                            }
                            else
                            {
                                throw new Exception($"Unable to update {data}, the "+
                                    $"row has been deleted by another user");
                            }
                        }
                    }
                }
                transaction.Commit();
            }

            int rowsToDeleteCount = RowCount/3;
            // Linq, because it is easy to use, 
            // but keep in mind that it performs rather poorly 
            var itemsToDelete = originalItems.Values.Take(rowsToDeleteCount).ToList();
            using (var transaction = _connection.BeginTransaction())
            {
                foreach (var item in itemsToDelete)
                {
                    if (Delete(item) == false)
                    {
                        throw new Exception($"Unable to delete {item}, the row has "
                            +"been deleted by another user");
                    }
                }
                transaction.Commit();
            }

            foreach (var item in itemsToDelete)
            {

                if ( Delete(item) )
                {
                    throw new Exception($"It appears {item}, was not deleted");
                }
            }
        }


    }
}
