# Harlinn.MSSql.Tool

This project contains command line tools that generates C# code for 
working with Microsoft SQL Server databases using the [Microsoft.Data.SqlClient](https://learn.microsoft.com/en-us/sql/connect/ado-net/microsoft-ado-net-sql-server)
library. 

*It's under development but usable for production use.*

Using the [Microsoft.Data.SqlClient](https://learn.microsoft.com/en-us/sql/connect/ado-net/microsoft-ado-net-sql-server)
library can be beneficial for performance and features, especially when working with large datasets or complex queries.

It can also be time consuming, and error prone, to write and maintain the necessary 
C# code for interacting with SQL Server databases.

This tool automates the process of generating C# code for working with SQL Server databases,
supporting a subset of the features provided by Microsoft SQL Server.

# Features

- Import table definitions from an existing database
- Generate SQL scripts for creating tables and stored procedures
- Generate C# code for interacting with SQL Server databases
- Support for basic CRUD operations



## Usage

To import the table definitions from a database, run the following command:

```
Harlinn.MSSql.Tool import -s dbo  -i MyDB -p TestProject.xml
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


```

```
