package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleVehicleDataReader extends SimpleTrackableItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  v.[Id], \r\n" +
            "  v.[EntityType], \r\n" +
            "  v.[RowVersion], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[Type] \r\n" +
            "FROM [VehicleView] v \r\n";

    public final static String BaseViewName = "VehicleView";
    public final static String ViewAliasName = "v";

    public final static int NAME_FIELD_ID = 4;
    public final static int TYPE_FIELD_ID = 5;

    public SimpleVehicleDataReader( ResultSet resultSet ) {
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
