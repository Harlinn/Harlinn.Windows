# Harlinn.MSSql.Tool

This project contains command line tools that generates C# code for 
working with Microsoft SQL Server databases. 

It's under development but usable for production use.

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


