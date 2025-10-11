# harlinn.common

This is an experimental library. 

It relies on a dynamic link library, *harlinn.common.jni-x64r.dll*, 
which is created by a release build of the *harlinn.common.jni* project
located under *Harlinn.Windows\Java\Examples\harlinn.common.jni*. 

To build:

1. Ensure that Harlinn.Windows\x64\Release is in your PATH environment variable.
1. Ensure that *mssql-jdbc_auth-13.2.0.x64.dll* can be located using the PATH environment variable. It's distributed with version 13.2.0 of the [Microsoft SQL Server JDBC driver](https://github.com/microsoft/mssql-jdbc).
1. Import *Harlinn.Windows\Java\Examples\harlinn.common* as a gradle project into [Eclipse](https://eclipseide.org/).
1. Perform a release build of the *harlinn.common.jni* project.
1. Verify that the JUnit tests executes as expected.


## packages

### com.harlinn.common.data

Implements wrapper classes, for selected jdbc interfaces, that ensures that any
exception thrown by their implementation will be logged.

#### CallableStatementWrapper

Wraps the java.sql.CallableStatement interface.

#### ConnectionWrapper

Wraps the java.sql.Connection interface.

#### PreparedStatementWrapper

Wraps the java.sql.PreparedStatement interface.

#### ResultSetWrapper

Wraps the java.sql.ResultSet interface.

#### StatementWrapper

Wraps the java.sql.Statement interface.

### com.harlinn.common.io

I/O helper classes.

#### AbstractBinaryReader

#### AbstractBinaryWriter

#### MemoryInputStream

#### MemoyOutputStream


### com.harlinn.common.platform

Provides a set of classes for accessing functionality provided by the Windows operating system. 

#### Kernel32

#### Ole32


### com.harlinn.common.serialization

#### AbstractDataReader

Use this class to deserialise data serialised using the Harlinn::Common::Core::IO::Serialization::DataWriter 
template class of the Harlinn.Common.Core C++ library.

#### DataType

Holds field type identifiers used for serialisation and deserialisation.

#### SerializationException

#### UnexpectedDataTypeException

The exception thrown when not encountering expected type identifiers during deserialization.

### com.harlinn.common.util

#### BitConverter

Converts base data types to an array of bytes, and an array of bytes to base data types.

#### ByteSwap

Reverses the bytes of a long, int, or short, value. 

#### Currency

A Currency number stored as a long, scaled by 10,000 to give a fixed-point 
number with 15 digits to the left of the decimal point and 4 digits to the right.

#### DateTime

This class represents a date and time using a long that stores the
date and time as the number of 100 nanosecond intervals since
12:00 AM January 1, year 1 A.D. in the proleptic Gregorian Calendar.

It is intended to be fairly compatible with the DateTime struct
as implemented by the .Net platform, as ticks have the same duration.


#### DayOfWeek

Specifies the day of the week.

#### Guid

Represents a globally unique identifier (GUID).

A GUID is a 128-bit integer (16 bytes) that can be used across all computers and networks wherever a unique identifier is required. Such an identifier has a very low probability of being duplicated.

Unlike the java.util.UUID class, Guid implements ordering that is compatible with the .Net struct Guid type.

#### TimeBase

Holds constants that are useful for working with dates and time.

#### TimeSpan

Represents a time interval.

#### UnsignedByte

Signifies that the wrapped value should be treated as an unsigned value.

#### UnsignedInteger

Signifies that the wrapped value should be treated as an unsigned value.

#### UnsignedLong

Signifies that the wrapped value should be treated as an unsigned value.

#### UnsignedShort

Signifies that the wrapped value should be treated as an unsigned value.
