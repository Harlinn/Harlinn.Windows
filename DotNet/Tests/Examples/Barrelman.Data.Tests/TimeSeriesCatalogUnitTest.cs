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
        public void TestMethod1()
        {
            var loggerFactory = LoggerFactoryHelper.LoggerFactory;
            var connection = ConnectionHelper.Connection;
            var dataContext = new Database.SqlServerDataContext(loggerFactory, connection);

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
            //  a: GetTimeseriesCatalogElementById returns any TimeseriesCatalogElementObject derived object
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
            //  a: GetTimeseriesCatalogById only returns TimeseriesCatalogObject objects
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
    }
}