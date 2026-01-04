using AdventureWorks;
using AdventureWorks.Person;
using AdventureWorks.Person.Database;
using AdventureWorks.Person.Database.Readers;
using AdventureWorks.Person.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Tests
{
    [TestClass]
    public sealed class Test1
    {
        private const string InitialCatalog = "AdventureWorks2019";
        private const string defaultConnectionString = $"Data Source=(local);Initial Catalog={InitialCatalog};Integrated Security=True;Encrypt=True;Trust Server Certificate=True";

        [TestMethod]
        public void PersonReaderTest1()
        {
            using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
            connection.Open();
            var command = connection.CreateCommand();

            var sql = PersonReader.Sql;
            command.CommandText = sql;

            using var reader = command.ExecuteReader();
            var personReader = new PersonReader(reader, ownsReader: false);

            var persons = personReader.ToList();

            Assert.IsNotEmpty(persons);
        }

        [TestMethod]
        public void PersonReaderTest2()
        {
            using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
            connection.Open();
            var command = connection.CreateCommand();

            var sql = $"{PersonReader.Sql} WHERE {PersonReader.ShortName}.[Businessentityid] = @BusinessEntityId";
            command.CommandText = sql;

            // Set the desired BusinessEntityId value:
            command.Parameters.AddWithValue("@BusinessEntityId", 1);

            using var reader = command.ExecuteReader();
            var personReader = new PersonReader(reader, ownsReader: false);

            var hasRow = personReader.Read();
            Assert.IsTrue(hasRow, "Expected at least one row for BusinessEntityId = 1");
            var person = personReader.ToDataObject();
            Assert.AreEqual(1, person.Businessentityid, "Businessentityid does not match the requested value.");

        }

        static PersonDataType CreatePerson()
        {
            var rowGuid = new Guid("{EC22ADCC-FBDC-43EC-ACB9-38CB0231292D}");
            return new PersonDataType
            {
                Persontype = "EM",
                Namestyle = false,
                Title = "Mr.",
                Firstname = "John",
                Middlename = "A",
                Lastname = "Doe",
                Suffix = null,
                Emailpromotion = 0,
                Rowguid = rowGuid,
                Additionalcontactinfo = SqlXml.Null,
                Demographics = SqlXml.Null,
                Modifieddate = DateTime.UtcNow,
            };
        }

        static BusinessentityDataType CreateBusinessentity()
        {
            var rowGuid = new Guid("{156A80DC-E340-4BCB-B734-AA1E0053ACE1}");
            return new BusinessentityDataType
            {
                Rowguid = rowGuid,
                Modifieddate = DateTime.UtcNow,
            };
        }

        static void DeleteTestPersonIfExists(Microsoft.Data.SqlClient.SqlConnection connection)
        {
            var rowGuid = new Guid("{EC22ADCC-FBDC-43EC-ACB9-38CB0231292D}");
            var command = connection.CreateCommand();
            command.CommandText = $"DELETE FROM Person.Person WHERE Rowguid = @Rowguid";
            command.Parameters.AddWithValue("@Rowguid", rowGuid);
            command.ExecuteNonQuery();
        }

        static void DeleteTestBusinessentityIfExists(Microsoft.Data.SqlClient.SqlConnection connection)
        {
            var rowGuid = new Guid("{156A80DC-E340-4BCB-B734-AA1E0053ACE1}");
            var command = connection.CreateCommand();
            command.CommandText = $"DELETE FROM Person.Businessentity WHERE Rowguid = @Rowguid";
            command.Parameters.AddWithValue("@Rowguid", rowGuid);
            command.ExecuteNonQuery();
        }



        [TestMethod]
        public void PersonReaderTest3()
        {
            var testBusinessEntity = CreateBusinessentity();
            var testPerson = CreatePerson();

            using var connection = new Microsoft.Data.SqlClient.SqlConnection(defaultConnectionString);
            connection.Open();

            DeleteTestPersonIfExists(connection);
            DeleteTestBusinessentityIfExists(connection);

            var insertedBusinessEntity = StoredProcedures.InsertBusinessentity(connection, testBusinessEntity);
            testPerson.Businessentityid = testBusinessEntity.Businessentityid;
            var insertedPerson = StoredProcedures.InsertPerson(connection, testPerson);
            Assert.IsTrue(insertedPerson);

            testPerson.Middlename = "B";
            var updatedPerson = StoredProcedures.UpdatePerson(connection, testPerson);
            Assert.IsTrue(updatedPerson);

            var command = connection.CreateCommand();

            var sql = $"{PersonReader.Sql} WHERE {PersonReader.ShortName}.[Businessentityid] = @BusinessEntityId";
            command.CommandText = sql;

            // Set the desired BusinessEntityId value:
            command.Parameters.AddWithValue("@BusinessEntityId", testBusinessEntity.Businessentityid);

            using var reader = command.ExecuteReader();
            var personReader = new PersonReader(reader, ownsReader: false);

            var hasRow = personReader.Read();
            Assert.IsTrue(hasRow, $"Expected at least one row for BusinessEntityId = {testBusinessEntity.Businessentityid}");
            var person = personReader.ToDataObject();
            Assert.AreEqual(testBusinessEntity.Businessentityid, person.Businessentityid, "Businessentityid does not match the requested value.");

            Assert.AreEqual(testPerson.Firstname, person.Firstname, "Firstname does not match the requested value.");
            Assert.AreEqual(testPerson.Lastname, person.Lastname, "Lastname does not match the requested value.");
            Assert.AreEqual(testPerson.Middlename, person.Middlename, "Middlename does not match the requested value.");
            Assert.AreEqual(testPerson.Rowguid, person.Rowguid, "Rowguid does not match the requested value.");

        }


    }
}
