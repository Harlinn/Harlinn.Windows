# Harlinn.Common.Core.Net

This project contains C# classes for working with the [Microsoft.Data.SqlClient](https://learn.microsoft.com/en-us/sql/connect/ado-net/microsoft-ado-net-sql-server), 
and some common functionality used by other projects in this repository.

Key classes include:

- [DataReaderWrapper](Data/SqlClient/DataReaderWrapper.md): A robust wrapper around `SqlDataReader` that provides safe access, typed getters, and logging.
- [SqlParameterCollectionExtensions](Data/SqlClient/SqlParameterCollectionExtensions.md): Extension methods for `SqlParameterCollection` to simplify adding parameters with correct types and sizes.
- [SqlConnectionExtensions](Data/SqlClient/SqlConnectionExtensions.md): Extension methods for `SqlConnection` to streamline access to some of the SQL Server system views.
- [Readers](Data/SqlClient/Readers/Readme.md): Classes for reading SQL Server system catalog views and dynamic management views (DMVs).

