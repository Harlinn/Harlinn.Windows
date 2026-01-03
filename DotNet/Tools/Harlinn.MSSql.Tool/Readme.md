# Harlinn.MSSql.Tool

This project contains command line tools that generates C# code for 
working with Microsoft SQL Server databases using the [Microsoft.Data.SqlClient](https://learn.microsoft.com/en-us/sql/connect/ado-net/microsoft-ado-net-sql-server)
library. 

*It's under development but usable for production use.*

Using the [Microsoft.Data.SqlClient](https://learn.microsoft.com/en-us/sql/connect/ado-net/microsoft-ado-net-sql-server)
library can be beneficial for performance and features, especially when working with large datasets or complex queries.

This tool automates the process of generating most of the C# code required for working with SQL Server databases,
supporting a reasonable subset of the available features.

# Features

- Import table, view and stored procedure definitions from an existing database into an xml file.
- Generate SQL scripts for creating the imported tables.
  - This feature is useful for verification of the imported table definitions, and the generated
    SQL script must be carefully reviewed before it's applied to a database.
- Generate SQL scripts to create stored procedures for create, update and delete operations.
- Generate thin C# wrapper classes for reading data from tables and views.
- Generate thin C# code for inserting, updating and deleting data from tables using the generated stored procedures.

# Planned Features

- Generate C# wrapper classes for the imported stored procedures.
- Generate C# wrapper classes for SQL queries.
- Entity Framework support.
 

The generated code should be copied into your own projects and modified as needed.

See [AdventureWorks](https://github.com/Harlinn/Harlinn.Windows/tree/master/DotNet/Examples/SqlClient/AdventureWorks) for
an example of code generated using this tool. 

It's also quite interesting to observe how well copilot works with the generated code, as it seems to understand 
the patterns used in the generated code quite well.


# Requirements

- The [Microsoft.Data.SqlClient](https://learn.microsoft.com/en-us/sql/connect/ado-net/microsoft-ado-net-sql-server) library.
- The [Microsoft.SqlServer.Types](https://learn.microsoft.com/en-us/dotnet/api/microsoft.sqlserver.types) library.

The generated code targets .NET 9.0 and C# 13.0, and does not require any additional libraries.


## Usage

Run the following command to see the available options for the `import` command:
```
Harlinn.MSSql.Tool.exe import --help
```
This will display the following help information:

```
  -c, --connection_string    SQL Server connection string.

  -i, --initial_catalog      SQL Server initial catalog. Use this to connect to the default local SQL Server using
                             integrated security.

  -s, --schema               Schema name.

  -o, --object               Name of, or regex to match if used with -r for, the objects to import.

  -r, --regex                (Default: false) Use regular expressions.

  -e, --exclude              Name of, or regex to match if used with -r for, the objects to exclude from the import.

  -u, --procedures           (Default: false) Import all stored procedures from the specified schemas.

  -t, --tables               (Default: false) Import all tables from the specified schemas.

  -v, --views                (Default: false) Import all views from the specified schemas.

  -p, --project              Required. Project file path.

  --help                     Display this help screen.

  --version                  Display version information.
```
Run the following command to see the available options for the `build` command:

```
Harlinn.MSSql.Tool.exe build --help
```
This will display the following help information:

```
  -o, --output                  Output directory.

  -w, --use_wrappers            Use wrappers.

  -e, --use_entity_framework    Use Entity Framework.

  -p, --project                 Required. Project file path.

  --help                        Display this help screen.

  --version                     Display version information.
```


To import the table definitions from a database, run the following command:

```
Harlinn.MSSql.Tool import -s dbo -t -i MyDB -p TestProject.xml
```

This will import the tables within the `dbo` schema from the `MyDB` database
and generate the TestProject.xml file in the current directory.

The generated XML file can then be used to generate SQL and C# code using the following command:

```
Harlinn.MSSql.Tool -p TestProject.xml -o OutputDirectory
```
This will generate SQL and C# code in the specified output directory.

The tool will generate SQL files that creates the tables in the database 
along with stored procedures for inserting, updating, deleting data from the tables. 

It will also generate C# code that contains classes for each table along with 
a C# wrapper for the stored procedures.


To import the [AdventureWorks2019](https://learn.microsoft.com/en-us/sql/samples/adventureworks-install-configure?view=sql-server-ver17&tabs=ssms) database tables from multiple schemas, run the following command:

```
Harlinn.MSSql.Tool import -s dbo;HumanResources;Person;Production;Purchasing;Sales -u -t -v -i AdventureWorks2019 -p AdventureWorks.xml
```

Then edit the generated `AdventureWorks.xml` file, ensuring that `Name` and `Namespace` 
attributes of the root `Project` element are set to appropriate values:

```
<Project xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" 
        Name="AdventureWorks" Namespace="AdventureWorks">

```
Save the changes to the `AdventureWorks.xml` file, and then run the following command to generate SQL and C# code:

```
Harlinn.MSSql.Tool -p AdventureWorks.xml

```

This will generate SQL and C# code in the `Generated` directory under the current directory.

The `Generated` directory will contain two subdirectories `MSSql` and `CSharp`.

Apply the following generated SQL scripts to your `AdventureWorks2019` database:

- `MSSql/InsertProcedures.sql`
- `MSSql/UpdateProcedures.sql`
- `MSSql/DeleteProcedures.sql`

Reimporting the database with filtering to only include the original stored procedures can be done using the following command: 

```
Harlinn.MSSql.Tool import -s dbo;HumanResources;Person;Production;Purchasing;Sales -u -t -v -r -e "Insert.*" "Update.*" "Delete.*" -i AdventureWorks2019 -p AdventureWorks.xml
```

The generated code can also be found in the `Harlinn.Windows\DotNet\Examples\SqlClient\AdventureWorks\AdventureWorks.csproj` project, 
which I use for testing.


Example of using the generated `PersonReader` class to read data from the `AdventureWorks2019` `Person` table:

```
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

```

Where `PersonReader` is a generated class that provides methods for reading data from the `Person` 
table in the `AdventureWorks2019` database. It is designed to work with the `Microsoft.Data.SqlClient` 
library and provides a strongly typed interface for accessing the data in the table.


```
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

```


