/*
   Copyright 2024 Espen Harlinn

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

namespace Barrelman.Data.Tests
{
    [TestClass]
    public class TimeseriesCatalogUnitTest
    {
        [TestMethod]
        public void BasicCreateRetrieveUpdateDeleteTestMethod()
        {
            var loggerFactory = LoggerFactoryHelper.LoggerFactory;
            var connection = ConnectionHelper.Connection;
            var dataContext = new Databases.MsSql.SqlServerDataContext(loggerFactory, connection, Guid.NewGuid());

            Guid id = new Guid("{C76C4997-9B8C-4D22-A24F-44057A174A73}");
            string name1 = "Catalog1";
            string name2 = "Catalog2";

            // Cleanup if previous run was aborted

            var deleteCommand1 = connection.CreateCommand();
            deleteCommand1.CommandText = "DELETE FROM [TimeseriesCatalog] WHERE Id = @id";
            var deleteCommandParameters1 = deleteCommand1.Parameters;
            deleteCommandParameters1.AddGuid("@id", id);
            deleteCommand1.CommandType = System.Data.CommandType.Text;
            deleteCommand1.ExecuteNonQuery();

            var deleteCommand2 = connection.CreateCommand();
            deleteCommand2.CommandText = "DELETE FROM [TimeseriesCatalogElement] WHERE Id = @id";
            var deleteCommandParameters2 = deleteCommand2.Parameters;
            deleteCommandParameters2.AddGuid("@id", id);
            deleteCommand2.CommandType = System.Data.CommandType.Text;
            deleteCommand2.ExecuteNonQuery();

            // Start of test

            // 1: Create a TimeseriesCatalogObject object
            var timeseriesCatalog = new Types.TimeseriesCatalogObject();

            // 2: Assign initial values
            timeseriesCatalog.ObjectState = Harlinn.Common.Core.Net.Data.ObjectState.New;
            timeseriesCatalog.Id = id;
            timeseriesCatalog.Name = name1;

            // 3: Insert the object
            var inserted = dataContext.Insert(timeseriesCatalog);
            Assert.IsTrue(inserted);

            // 4: Retrieve a copy of the object from the database.
            //  a: GetTimeseriesCatalogElementById uses ComplexTimeseriesCatalogElementDataReader and returns any TimeseriesCatalogElementObject derived object
            var retrievedTimeseriesCatalogElement = dataContext.GetTimeseriesCatalogElementById(id);
            Assert.IsNotNull(retrievedTimeseriesCatalogElement);
            //  b: Check that the retrieved object is of the expected type
            Assert.IsTrue(retrievedTimeseriesCatalogElement is Types.TimeseriesCatalogObject);
            //  c: Check that the retrieved object is equal to the original object
            Assert.IsTrue(retrievedTimeseriesCatalogElement.Equals(timeseriesCatalog));

            // 5: Change the assigned name and update the database
            timeseriesCatalog.Name = name2;
            var updated = dataContext.Update(timeseriesCatalog); 
            Assert.IsTrue(updated);

            // 6: Retrieve a copy of the object from the database.
            //  a: GetTimeseriesCatalogById uses SimpleTimeseriesCatalogDataReader, which is more efficient than ComplexTimeseriesCatalogElementDataReader, and only returns TimeseriesCatalogObject objects
            var retrievedTimeseriesCatalog = dataContext.GetTimeseriesCatalogById(id);
            Assert.IsNotNull(retrievedTimeseriesCatalog);
            //  b: Check that the retrieved object is equal to the original object
            Assert.IsTrue(retrievedTimeseriesCatalog.Equals(timeseriesCatalog));

            // 7: Mark the object as deleted and delete it from the database.
            timeseriesCatalog.ObjectState = Harlinn.Common.Core.Net.Data.ObjectState.Deleted;
            var deleted = dataContext.Delete(timeseriesCatalog);
            Assert.IsTrue(deleted);

            // 8: Verify that the object cannot be retrieved from the database.
            retrievedTimeseriesCatalogElement = dataContext.GetTimeseriesCatalogElementById(id);
            Assert.IsNull(retrievedTimeseriesCatalogElement);
        }

        [TestMethod]
        public void SerializationDeserializationTestMethod()
        {
            var loggerFactory = LoggerFactoryHelper.LoggerFactory;
            var connection = ConnectionHelper.Connection;
            var dataContext = new Databases.MsSql.SqlServerDataContext(loggerFactory, connection, Guid.NewGuid());

            Guid id = new Guid("{C76C4997-9B8C-4D22-A24F-44057A174A73}");
            string name1 = "Catalog1";

            // Cleanup if previous run was aborted

            var deleteCommand1 = connection.CreateCommand();
            deleteCommand1.CommandText = "DELETE FROM [TimeseriesCatalog] WHERE Id = @id";
            var deleteCommandParameters1 = deleteCommand1.Parameters;
            deleteCommandParameters1.AddGuid("@id", id);
            deleteCommand1.CommandType = System.Data.CommandType.Text;
            deleteCommand1.ExecuteNonQuery();

            var deleteCommand2 = connection.CreateCommand();
            deleteCommand2.CommandText = "DELETE FROM [TimeseriesCatalogElement] WHERE Id = @id";
            var deleteCommandParameters2 = deleteCommand2.Parameters;
            deleteCommandParameters2.AddGuid("@id", id);
            deleteCommand2.CommandType = System.Data.CommandType.Text;
            deleteCommand2.ExecuteNonQuery();

            // Start of test

            // 1: Create a TimeseriesCatalogObject object
            var timeseriesCatalog = new Types.TimeseriesCatalogObject();

            // 2: Assign initial values
            timeseriesCatalog.ObjectState = Harlinn.Common.Core.Net.Data.ObjectState.New;
            timeseriesCatalog.Id = id;
            timeseriesCatalog.Name = name1;

            // 3: Insert the object
            var inserted = dataContext.Insert(timeseriesCatalog);
            Assert.IsTrue(inserted);

            var memoryStream = new MemoryStream();

            // 4: Retrieve a copy of the object from the database.
            //  a: GetTimeseriesCatalogElementById uses ComplexTimeseriesCatalogElementDataReader and serializes any TimeseriesCatalogElementObject derived object
            dataContext.GetTimeseriesCatalogElementById(id, memoryStream);
            memoryStream.Position = 0;
            var binaryReader = new BinaryReader(memoryStream,System.Text.Encoding.Unicode);
            //  b: Check that the object was found
            var foundRequestedObject = binaryReader.ReadBoolean();
            Assert.IsTrue(foundRequestedObject);
            //  c: deserialize the object
            var factory = new Types.DataObjectFactory();
            var kind = (Types.Kind)binaryReader.ReadInt32();
            var retrievedTimeseriesCatalog = (Types.TimeseriesCatalogObject)factory.Create(kind);
            retrievedTimeseriesCatalog.ReadFrom(binaryReader);

            //  d: Check that the retrieved object is equal to the original object
            Assert.IsTrue(retrievedTimeseriesCatalog.Equals(timeseriesCatalog));

            // 5: Mark the object as deleted and delete it from the database.
            timeseriesCatalog.ObjectState = Harlinn.Common.Core.Net.Data.ObjectState.Deleted;
            var deleted = dataContext.Delete(timeseriesCatalog);
            Assert.IsTrue(deleted);

            // 6: Verify that the object cannot be retrieved from the database.
            var retrievedTimeseriesCatalogElement = dataContext.GetTimeseriesCatalogElementById(id);
            Assert.IsNull(retrievedTimeseriesCatalogElement);
        }

        [TestMethod]
        public void EntityContextCreateRetrieveUpdateDeleteTestMethod1()
        {
            var loggerFactory = LoggerFactoryHelper.LoggerFactory;
            var connection = ConnectionHelper.Connection;
            var dataContext = new Databases.MsSql.SqlServerDataContext(loggerFactory, connection, Guid.NewGuid());

            Guid id = new Guid("{C76C4997-9B8C-4D22-A24F-44057A174A73}");
            string name1 = "Catalog3";
            string name2 = "Catalog4";

            // Cleanup if previous run was aborted

            var deleteCommand1 = connection.CreateCommand();
            deleteCommand1.CommandText = "DELETE FROM [TimeseriesCatalog] WHERE Id = @id";
            var deleteCommandParameters1 = deleteCommand1.Parameters;
            deleteCommandParameters1.AddGuid("@id", id);
            deleteCommand1.CommandType = System.Data.CommandType.Text;
            deleteCommand1.ExecuteNonQuery();

            var deleteCommand2 = connection.CreateCommand();
            deleteCommand2.CommandText = "DELETE FROM [TimeseriesCatalogElement] WHERE Id = @id";
            var deleteCommandParameters2 = deleteCommand2.Parameters;
            deleteCommandParameters2.AddGuid("@id", id);
            deleteCommand2.CommandType = System.Data.CommandType.Text;
            deleteCommand2.ExecuteNonQuery();

            // Start of test
            var dataFactory = new Types.DataObjectFactory();
            var entityFactory = new Entities.EntityFactory(dataFactory);
            var entityContext = new Entities.EntityContext(loggerFactory, dataContext, entityFactory, dataFactory, false);


            // 1: Create a TimeseriesCatalogObject object
            var timeseriesCatalog = (Entities.TimeseriesCatalogEntity)entityContext.AddNew(Types.Kind.TimeseriesCatalog, id);

            // 2: Assign initial values
            timeseriesCatalog.Name = name1;

            // 3: Insert the object
            entityContext.Commit();

            // 4: Retrieve a copy of the object from the database.
            //  a: GetTimeseriesCatalogElementById uses ComplexTimeseriesCatalogElementDataReader and returns any TimeseriesCatalogElementObject derived object
            var retrievedTimeseriesCatalogElement = dataContext.GetTimeseriesCatalogElementById(id);
            Assert.IsNotNull(retrievedTimeseriesCatalogElement);
            //  b: Check that the retrieved object is of the expected type
            Assert.IsTrue(retrievedTimeseriesCatalogElement is Types.TimeseriesCatalogObject);
            //  c: Check that the retrieved object is equal to the original object
            Assert.IsTrue(retrievedTimeseriesCatalogElement.Equals(Entities.EntityContext.GetDataOf( timeseriesCatalog )));

            // 5: Change the assigned name and update the database
            timeseriesCatalog.Name = name2;
            entityContext.Commit();

            // 6: Retrieve a copy of the object from the database.
            //  a: GetTimeseriesCatalogById uses SimpleTimeseriesCatalogDataReader, which is more efficient than ComplexTimeseriesCatalogElementDataReader, and only returns TimeseriesCatalogObject objects
            var retrievedTimeseriesCatalog = dataContext.GetTimeseriesCatalogById(id);
            Assert.IsNotNull(retrievedTimeseriesCatalog);
            //  b: Check that the retrieved object is equal to the original object
            Assert.IsTrue(retrievedTimeseriesCatalog.Equals(Entities.EntityContext.GetDataOf(timeseriesCatalog)));

            // 7: Mark the object as deleted and delete it from the database.
            timeseriesCatalog.Delete();
            entityContext.Commit();

            // 8: Verify that the object cannot be retrieved from the database.
            retrievedTimeseriesCatalogElement = dataContext.GetTimeseriesCatalogElementById(id);
            Assert.IsNull(retrievedTimeseriesCatalogElement);
        }

        [TestMethod]
        public void EntityContextCreateRetrieveUpdateDeleteTestMethod2()
        {
            var loggerFactory = LoggerFactoryHelper.LoggerFactory;
            var connection = ConnectionHelper.Connection;
            var dataContext = new Databases.MsSql.SqlServerDataContext(loggerFactory, connection, Guid.NewGuid());

            Guid id = new Guid("{C76C4997-9B8C-4D22-A24F-44057A174A73}");
            string name1 = "Catalog3";
            string name2 = "Catalog4";

            // Cleanup if previous run was aborted

            var deleteCommand1 = connection.CreateCommand();
            deleteCommand1.CommandText = "DELETE FROM [TimeseriesCatalog] WHERE Id = @id";
            var deleteCommandParameters1 = deleteCommand1.Parameters;
            deleteCommandParameters1.AddGuid("@id", id);
            deleteCommand1.CommandType = System.Data.CommandType.Text;
            deleteCommand1.ExecuteNonQuery();

            var deleteCommand2 = connection.CreateCommand();
            deleteCommand2.CommandText = "DELETE FROM [TimeseriesCatalogElement] WHERE Id = @id";
            var deleteCommandParameters2 = deleteCommand2.Parameters;
            deleteCommandParameters2.AddGuid("@id", id);
            deleteCommand2.CommandType = System.Data.CommandType.Text;
            deleteCommand2.ExecuteNonQuery();

            // Start of test
            var dataFactory = new Types.DataObjectFactory();
            var entityFactory = new Entities.EntityFactory(dataFactory);
            var entityContext = new Entities.EntityContext(loggerFactory, dataContext, entityFactory, dataFactory, false);


            // 1: Create a TimeseriesCatalogObject object
            var timeseriesCatalog = entityContext.AddNew<Entities.TimeseriesCatalogEntity>(id);

            // 2: Assign initial values
            timeseriesCatalog.Name = name1;

            // 3: Insert the object
            entityContext.Commit();

            // 4: Retrieve a copy of the object from the entity context.
            //  a: GetTimeseriesCatalogElementById returns the instance of the object tracked by the entity context 
            var retrievedTimeseriesCatalogElement = entityContext.GetTimeseriesCatalogElementById(id);
            Assert.IsNotNull(retrievedTimeseriesCatalogElement);
            //  b: Check that the retrieved object is of the expected type
            Assert.IsTrue(retrievedTimeseriesCatalogElement is Entities.TimeseriesCatalogEntity);
            //  c: Check that the retrieved object is equal to the original object
            Assert.IsTrue(retrievedTimeseriesCatalogElement.Equals(timeseriesCatalog));
            //  d: Check that the retrieved object is the same as the original object
            Assert.IsTrue(ReferenceEquals(retrievedTimeseriesCatalogElement, timeseriesCatalog));

            // 5: Change the assigned name and update the database
            timeseriesCatalog.Name = name2;
            entityContext.Commit();

            // 6: Retrieve a copy of the object from the entity context.
            //  a: GetTimeseriesCatalogById returns the instance of the object tracked by the entity context 
            var retrievedTimeseriesCatalog = entityContext.GetTimeseriesCatalogById(id);
            Assert.IsNotNull(retrievedTimeseriesCatalog);
            //  b: Check that the retrieved object is equal to the original object
            Assert.IsTrue(retrievedTimeseriesCatalog.Equals(timeseriesCatalog));
            //  c: Check that the retrieved object is the same as the original object
            Assert.IsTrue(ReferenceEquals(retrievedTimeseriesCatalog, timeseriesCatalog));

            // 7: Mark the object as deleted and delete it from the database.
            timeseriesCatalog.Delete();
            entityContext.Commit();

            // 8: Verify that the object cannot be retrieved from the database.
            retrievedTimeseriesCatalogElement = entityContext.GetTimeseriesCatalogElementById(id);
            Assert.IsNull(retrievedTimeseriesCatalogElement);
        }

    }
}