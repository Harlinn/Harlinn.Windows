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
    public class AircraftTypeUnitTest
    {
        [TestMethod]
        public void TestMethod1()
        {
            var loggerFactory = LoggerFactoryHelper.LoggerFactory;
            var connection = ConnectionHelper.Connection;
            var storedProcedures = new Database.StoredProcedures(loggerFactory, connection);

            Guid id = new Guid("{E9D19608-ADEE-41B5-ADDF-E519AE336B0C}");
            string name1 = "Lockheed Martin F-35 Lightning II";
            string name2 = "NASA M2-F1";
            Int64 rowVersion = 0;

            var deleteCommand = connection.CreateCommand();
            deleteCommand.CommandText = "DELETE FROM AircraftType WHERE Id = @id";
            var deleteCommandParameters = deleteCommand.Parameters;
            deleteCommandParameters.AddGuid("@id", id);
            deleteCommand.CommandType = System.Data.CommandType.Text;
            deleteCommand.ExecuteNonQuery();
            

            var inserted = storedProcedures.InsertAircraftType(ref id, name1);
            Assert.IsTrue(inserted);

            var sql = Database.SimpleAircraftTypeDataReader.BaseQuery + "WHERE Id = @id";
            var afterInsertedCommand = connection.CreateCommand();
            afterInsertedCommand.CommandText = sql;
            var afterInsertedCommandParameters = afterInsertedCommand.Parameters;
            afterInsertedCommandParameters.AddGuid("@id", id);
            var afterInsertedCommandReader = afterInsertedCommand.ExecuteReader();

            var afterInsertedReader = new Database.SimpleAircraftTypeDataReader(loggerFactory, afterInsertedCommandReader);
            var afterInsertedReaderFound = afterInsertedReader.Read();
            Assert.IsTrue(afterInsertedReaderFound);
            if(afterInsertedReaderFound)
            {
                var retriedName = afterInsertedReader.Name;
                Assert.AreEqual(name1, retriedName);
            }
            afterInsertedCommandReader.Close();

            var updated = storedProcedures.UpdateAircraftType(id, ref rowVersion, name2);
            Assert.IsTrue(updated);

            var afterUpdatedCommand = connection.CreateCommand();
            afterUpdatedCommand.CommandText = sql;
            var afterUpdatedCommandParameters = afterUpdatedCommand.Parameters;
            afterUpdatedCommandParameters.AddGuid("@id", id);
            var afterUpdatedCommandReader = afterUpdatedCommand.ExecuteReader();

            var afterUpdatedReader = new Database.SimpleAircraftTypeDataReader(loggerFactory, afterUpdatedCommandReader);
            var afterUpdatedReaderFound = afterUpdatedReader.Read();
            Assert.IsTrue(afterUpdatedReaderFound);
            if (afterUpdatedReaderFound)
            {
                var retriedName = afterUpdatedReader.Name;
                Assert.AreEqual(name2, retriedName);
            }
            afterUpdatedCommandReader.Close();

            var deleted = storedProcedures.DeleteAircraftType(id, rowVersion);
            Assert.IsTrue(deleted);

        }

        [TestMethod]
        public void TestMethod2()
        {
            var loggerFactory = LoggerFactoryHelper.LoggerFactory;
            var connection = ConnectionHelper.Connection;
            var dataContext = new Database.SqlServerDataContext(loggerFactory, connection, Guid.NewGuid());

            Guid id = new Guid("{E9D19608-ADEE-41B5-ADDF-E519AE336B0C}");
            string name1 = "Lockheed Martin F-35 Lightning II";
            string name2 = "NASA M2-F1";
            

            var deleteCommand = connection.CreateCommand();
            deleteCommand.CommandText = "DELETE FROM AircraftType WHERE Id = @id";
            var deleteCommandParameters = deleteCommand.Parameters;
            deleteCommandParameters.AddGuid("@id", id);
            deleteCommand.CommandType = System.Data.CommandType.Text;
            deleteCommand.ExecuteNonQuery();

            var aircraftType1 = new Types.AircraftTypeObject();
            aircraftType1.Id = id;
            aircraftType1.Name = name1;
            aircraftType1.ObjectState = Harlinn.Common.Core.Net.Data.ObjectState.New;

            var inserted = dataContext.Insert(aircraftType1);
            Assert.IsTrue(inserted);

            var retrievedAircraftType1 = dataContext.GetAircraftTypeById(id);
            Assert.IsNotNull(retrievedAircraftType1);

            Assert.IsTrue(retrievedAircraftType1.Equals(aircraftType1));

            aircraftType1.Name = name2;
            var updated = dataContext.Update(aircraftType1);
            Assert.IsTrue(updated);

            var retrievedAircraftType2 = dataContext.GetAircraftTypeById(id);
            Assert.IsNotNull(retrievedAircraftType2);

            Assert.IsTrue(retrievedAircraftType2.Equals(aircraftType1));

            aircraftType1.ObjectState = Harlinn.Common.Core.Net.Data.ObjectState.Deleted;
            var deleted = dataContext.Delete(aircraftType1);
            Assert.IsTrue(deleted);

            var retrievedAircraftType3 = dataContext.GetAircraftTypeById(id);
            Assert.IsNull(retrievedAircraftType3);
        }
    }
}