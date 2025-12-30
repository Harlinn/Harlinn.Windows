# Harlinn.Common.Core.Net

This project contains C# classes for working with the [Microsoft.Data.SqlClient](https://learn.microsoft.com/en-us/sql/connect/ado-net/microsoft-ado-net-sql-server), 
and some common functionality used by other projects in this repository.

Key classes include:

- [DataReaderWrapper](https://github.com/Harlinn/Harlinn.Windows/blob/master/DotNet/Libraries/Harlinn.Common.Core.Net/Data/SqlClient/DataReaderWrapper.md): A robust wrapper around `SqlDataReader` that provides safe access, typed getters, and logging.
- [SqlParameterCollectionExtensions](https://github.com/Harlinn/Harlinn.Windows/blob/master/DotNet/Libraries/Harlinn.Common.Core.Net/Data/SqlClient/SqlParameterCollectionExtensions.md): Extension methods for `SqlParameterCollection` to simplify adding parameters with correct types and sizes.
- [SqlConnectionExtensions](https://github.com/Harlinn/Harlinn.Windows/blob/master/DotNet/Libraries/Harlinn.Common.Core.Net/Data/SqlClient/SqlCommandExtensions.md): Extension methods for `SqlConnection` to streamline access to some of the SQL Server system views.

