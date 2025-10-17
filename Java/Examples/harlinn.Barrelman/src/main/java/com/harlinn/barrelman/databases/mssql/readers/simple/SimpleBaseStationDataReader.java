package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBaseStationDataReader extends SimpleItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bs.[Id], \r\n" +
            "  bs.[EntityType], \r\n" +
            "  bs.[RowVersion], \r\n" +
            "  bs.[Name], \r\n" +
            "  bs.[Type] \r\n" +
            "FROM [BaseStationView] bs \r\n";

    public final static String BaseViewName = "BaseStationView";
    public final static String ViewAliasName = "bs";

    public final static int NAME_FIELD_ID = 4;
    public final static int TYPE_FIELD_ID = 5;

    public SimpleBaseStationDataReader( ResultSet resultSet ) {
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
