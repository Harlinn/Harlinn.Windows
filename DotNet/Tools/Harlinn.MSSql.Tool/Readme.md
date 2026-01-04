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
- Generate C# `System.Data.DataTable` wrappers for the imported tables. 

# Planned Features

- Generate C# wrapper classes for the imported stored procedures.
  - Partially implemented, currently wraps stored procedures that can be called using `SqlCommand.ExecuteNonQuery()`.
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

If the `AdventureWorks2019` database does not already contain a memory optimized filegroup,
apply the following SQL script to add one:
 
```
ALTER DATABASE AdventureWorks2019
ADD FILEGROUP AdventureWorks2019_mod CONTAINS MEMORY_OPTIMIZED_DATA;

ALTER DATABASE AdventureWorks2019
ADD FILE (name = N'AdventureWorks2019_mod_Data', filename = N'C:\MSSQL\MSSQL15.MSSQL\MSSQL\DATA\AdventureWorks2019_mod_Data.hdt')
TO FILEGROUP AdventureWorks2019_mod;

```
Then the generated merge stored procedures can be applied to the database by applying:

- `MSSql/CreateTableTypes.sql`
- `MSSql/MergeProcedures.sql`



 
Reimporting the database with filtering to only include the original stored procedures can be done using the following command: 

```
Harlinn.MSSql.Tool import -s dbo;HumanResources;Person;Production;Purchasing;Sales -u -t -v -r -e "Insert.*" "Merge.*" "Update.*" "Delete.*" -i AdventureWorks2019 -p AdventureWorks.xml
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

## XML Project File Format

The XML project file used by the tool has the following structure:
```xml
<?xml version="1.0" encoding="utf-8"?>
<Project xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
             xmlns:xsd="http://www.w3.org/2001/XMLSchema" 
             Name="AdventureWorks" 
             Namespace="AdventureWorks">
  <Databases>
    ...
  </Databases>
</Project>
```
Where the `<Project>` element has the following attributes:
- `Name`: The name of the project.
- `Namespace`: The root namespace to use for the generated C# code.

and contains a `<Databases>` element that contains `<Database>` elements:

```xml
  <Database Name="AdventureWorks2019">
    <Schemas>
      ...
    </Schemas>
    <Description>AdventureWorks 2016 Sample OLTP Database</Description>
  </Database>
```
Where the `<Database>` element has the following attributes:
- `Name`: The name of the database.

The `<Database>` element contains a an optional `<Description>` element that 
contains the description of the database, and a `<Schemas>` element 
that contains one or more `<Schema>` elements:

```xml
  <Schema Name="dbo" 
            Namespace="Dbo" 
            DataTypesNamespace="Types"
            DatabaseNamespace="Database"
            ReadersNamespace="Readers"
            DataTypeSuffix="DataType"
            DataTypePrefix=""
            ReaderSuffix="Reader"
            ReaderPrefix="">
    <Types/>
    <Objects/>
    <Queries/>
  </Schema>
```
The `<Schema>` element has the following attributes:
- `Name`: The name of the schema.
- `Namespace`: The namespace to use for the generated C# code for this schema. 
  The namespace will be nested under the root namespace specified in the 
  `<Project>` element. If not specified, the namespace will be the same as 
  the schema name converted to pascal case.
- `DataTypesNamespace`: The namespace to use for the generated C# data types 
  for this schema. The namespace will be nested under the schema namespace.
  The default is `Types`.
- `DatabaseNamespace`: The namespace to use for the generated C# database objects for this schema. 
  The namespace will be nested under the schema namespace. The default is `Database`.
- `ReadersNamespace`: The namespace to use for the generated C# data readers for this schema.
  The namespace will be nested under the database namespace. The default is `Readers`.
- `DataTypeSuffix`: The suffix to use for the generated C# data types for this schema.
  The default is `DataType`.
- `DataTypePrefix`: The prefix to use for the generated C# data types for this schema.
  The default is an empty string. 
- `ReaderSuffix`: The suffix to use for the generated C# data readers for this schema.
  The default is `Reader`.
- `ReaderPrefix`: The prefix to use for the generated C# data readers for this schema.
  The default is an empty string.

### The `<Types>` Element

The elements under the `<Types>` element define custom data types for the schema.

Three kinds of custom data types are supported:

- `<Enum>`: Defines an enumeration type.
- `<Struct>`: Defines a struct type.
- `<Class>`: Defines a class type.

**This feature is under development.**

Code generation is implemented, neither import from the database nor integration
with the generated code for tables, views and stored procedures are done.

### The `<Objects>` Element

The elements under the `<Objects>` element define the database objects (tables, views, stored procedures, etc.) for the schema.

**This feature is under development.**

Three kinds of database objects are supported:

- `<Entity>`: Defines a table object.
- `<View>`: Defines a view object.
- `<StoredProcedure>`: Defines a stored procedure object.

Both `<Entity>` and `<View>` contains a `<Fields>` element that defines the fields/columns for the object.

```xml
<Fields>
  <Boolean />
  <Byte/>
  <SByte/>
  <Char/>
  <Int16/>
  <UInt16/>
  <Int32/>
  <UInt32/>
  <Int64/>
  <UInt64/>
  <Single/>
  <Double/>
  <Decimal/>
  <DateTime/>
  <TimeSpan/>
  <Guid/>
  <String/>
  <Binary/>
  <SqlVariant/>
  <HierarchyId/>
  <Geometry/>
  <Geography/>
  <Xml/>
  <Object/>
  <Enum/>
</Fields>
```
providing support for mapping common SQL Server data types to C# types.

Every field element supports the following common attributes:
- `Name`: The name of the field, which is required.
- `IsNullable`: Whether the field is nullable. Default is `false`.
- `DatabaseType`: The SQL Server data type of the field. The default is inferred from the field element name.
- `Column`: The name of the column in the database. If not specified, the column name is the same as the field name.

and have an optional `<Description>` element that contains the description of the field. 

```xml
<String Name="Title" IsNullable="true" DatabaseType="nvarchar" Size="8">
  <Description>A courtesy title. For example, Mr. or Ms.</Description>
</String>
```

`<Byte>`, `<SByte>`, `<Int16>`, `<UInt16>`, `<Int32>`, `<UInt32>`, `<Int64>`, `<UInt64>` 
and `<Decimal>` have a common child element `<Identity>` that defines identity column 
attributes:

```xml
<Identity Seed="1" Increment="1" />
```
where:
- `Seed`: The seed value for the identity column. Default is `1`.
- `Increment`: The increment value for the identity column. Default is `1`.

`<Single>`, `<Double>` and `<Decimal>` have a `Precision` attribute that defines the 
precision for the numeric types, and `<Decimal>` also has a `Scale` attribute that 
defines the scale for the decimal type:

```xml
<Decimal Name="Perassemblyqty" DatabaseType="decimal" Precision="8" Scale="2"/>
```

#### Boolean Field

`<Boolean>` fields map to `bit` columns in SQL Server.


#### Byte and SByte Fields

Both `<Byte>` and `<SByte>` fields map to `tinyint` columns in SQL Server.

#### Int16 and UInt16 Fields

Both `<Int16>` and `<UInt16>` fields map to `smallint` columns in SQL Server.

#### Int32 and UInt32 Fields

Both `<Int32>` and `<UInt32>` fields map to `int` columns in SQL Server.

#### Int64 and UInt64 Fields

Both `<Int64>` and `<UInt64>` fields map to `bigint` columns in SQL Server.

#### Single, Double and Decimal Fields
`<Single>` fields map to `real` columns in SQL Server.
`<Double>` fields map to `float` columns in SQL Server.
`<Decimal>` fields map to `decimal` columns in SQL Server.

#### DateTime Fields
`<DateTime>` fields map to `datetime2` columns in SQL Server.

#### TimeSpan Fields
`<TimeSpan>` fields map to `bigint` columns in SQL Server.

####  Guid Fields
`<Guid>` fields map to `uniqueidentifier` columns in SQL Server.

#### String Fields
`<String>` fields map to `nvarchar` columns in SQL Server.

#### Binary Fields
`<Binary>` fields map to `varbinary` columns in SQL Server.

#### SqlVariant Fields
`<SqlVariant>` fields map to `sql_variant` columns in SQL Server.

#### HierarchyId Fields
`<HierarchyId>` fields map to `hierarchyid` columns in SQL Server.

#### Geometry Fields
`<Geometry>` fields map to `geometry` columns in SQL Server.

#### Geography Fields
`<Geography>` fields map to `geography` columns in SQL Server.

#### Xml Fields
`<Xml>` fields map to `xml` columns in SQL Server.

#### Object Fields
`<Object>` is currently unsupported.

#### Enum Fields
`<Enum>` is currently unsupported.


### The `<Queries>` Element

The elements under the `<Queries>` element define the database queries for the schema.

**This feature is under development.**
