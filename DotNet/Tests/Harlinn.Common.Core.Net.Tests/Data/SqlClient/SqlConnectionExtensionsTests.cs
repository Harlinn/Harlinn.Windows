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

using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using System;

namespace Harlinn.Common.Core.Net.Tests;

[TestClass]
public class SqlConnectionExtensionsTests
{
    private const string InitialCatalog = "barrelman";
    private const string defaultConnectionString = $"Data Source=(local);Initial Catalog={InitialCatalog};Integrated Security=True;Encrypt=True;Trust Server Certificate=True";

    

    [TestMethod]
    public void GetTablesTest1()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var tables = connection.GetTables();
        Assert.IsNotNull(tables);
    }

    [TestMethod]
    public void GetTablesTest2()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var schemas = connection.GetSchemas();
        Assert.IsNotNull(schemas);
        foreach (var schema in schemas)
        {
            var tables = connection.GetTables(schema);
            Assert.IsNotNull(tables);
        }
    }


    [TestMethod]
    public void GetViewsTest1()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var views = connection.GetViews();
        Assert.IsNotNull(views);
    }

    [TestMethod]
    public void GetViewsTest2()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var schemas = connection.GetSchemas();
        Assert.IsNotNull(schemas);
        foreach (var schema in schemas)
        {
            var views = connection.GetViews(schema);
            Assert.IsNotNull(views);
        }

    }

    [TestMethod]
    public void GetSchemasTest1()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var schemas = connection.GetSchemas();
        Assert.IsNotNull(schemas);

    }

    [TestMethod]
    public void GetSchemaObjectsTest1()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var schemaObjects = connection.GetSchemaObjects();
        Assert.IsNotNull(schemaObjects);

    }

    [TestMethod]
    public void GetSchemaObjectsTest2()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var schemas = connection.GetSchemas();
        Assert.IsNotNull(schemas);
        foreach (var schema in schemas)
        {
            var schemaObjects = connection.GetSchemaObjects(schema);
            Assert.IsNotNull(schemaObjects);
        }
    }

    [TestMethod]
    public void GetTablesTest3()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var tables = connection.GetTables();
        Assert.IsNotNull(tables);
        foreach (var table in tables)
        {
            var columns = connection.GetColumns(table);
            Assert.IsNotNull(columns);
            var primaryKey = connection.GetPrimaryKey(table);
            Assert.IsNotNull(primaryKey);
            var primaryKeyColumns = connection.GetIndexColumns(primaryKey);
            Assert.IsNotNull(primaryKeyColumns);


            var indexes = connection.GetIndexes(table);
            Assert.IsNotNull(indexes);
            foreach (var index in indexes)
            {
                var indexColumns = connection.GetIndexColumns(index);
                Assert.IsNotNull(indexColumns);
            }

            var foreignKeys = connection.GetForeignKeys(table);
            Assert.IsNotNull(foreignKeys);
            foreach (var foreignKey in foreignKeys)
            {
                var foreignKeyColumns = connection.GetForeignKeyColumns(foreignKey);
                Assert.IsNotNull(foreignKeyColumns);
            }



        }

    }

    [TestMethod]
    public void DescribeFirstResultSetTest1()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var resultSet = connection.DescribeFirstResultSet("SELECT * FROM sys.types", null, true);
        Assert.IsNotNull(resultSet);
    }

    [TestMethod]
    public void DescribeFirstResultSetTest2()
    {
        using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
        connection.Open();
        var resultSet = connection.DescribeFirstResultSet("EXEC sys.sp_server_info", null, true);
        Assert.IsNotNull(resultSet);
    }



}
