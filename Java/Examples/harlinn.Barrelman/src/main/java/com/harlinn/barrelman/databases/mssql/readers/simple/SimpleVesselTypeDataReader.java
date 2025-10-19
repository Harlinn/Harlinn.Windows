package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleVesselTypeDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vt.[Id], \r\n" +
            "  vt.[RowVersion], \r\n" +
            "  vt.[Name], \r\n" +
            "  vt.[Code] \r\n" +
            "FROM [VesselTypeView] vt \r\n";

    public final static String BaseViewName = "VesselTypeView";
    public final static String ViewAliasName = "vt";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int NAME_FIELD_ID = 3;
    public final static int CODE_FIELD_ID = 4;

    public SimpleVesselTypeDataReader( ResultSet resultSet ) {
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

    public final int getCode() throws SQLException {
        return getInt32( CODE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.VesselType );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeInt32( getCode( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public VesselTypeObject getDataObject( ) throws SQLException {
            return new VesselTypeObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getCode( ) );
    }

}
