package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAircraftDataReader extends SimpleTrackableItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  a.[Id], \r\n" +
            "  a.[EntityType], \r\n" +
            "  a.[RowVersion], \r\n" +
            "  a.[Name], \r\n" +
            "  a.[Type] \r\n" +
            "FROM [AircraftView] a \r\n";

    public final static String BaseViewName = "AircraftView";
    public final static String ViewAliasName = "a";

    public final static int NAME_FIELD_ID = 4;
    public final static int TYPE_FIELD_ID = 5;

    public SimpleAircraftDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final Guid getTypeField() throws SQLException {
        return getNullableGuid( TYPE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getName( ) );
        destination.writeNullableGuid( getTypeField( ) );
    }

}
