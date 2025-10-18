package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleVehicleTypeDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vt.[Id], \r\n" +
            "  vt.[RowVersion], \r\n" +
            "  vt.[Name] \r\n" +
            "FROM [VehicleTypeView] vt \r\n";

    public final static String BaseViewName = "VehicleTypeView";
    public final static String ViewAliasName = "vt";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int NAME_FIELD_ID = 3;

    public SimpleVehicleTypeDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.VehicleType );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeStringUtf8( getName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public VehicleTypeObject GetDataObject( ) throws SQLException {
            return new VehicleTypeObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ) );
    }

}
