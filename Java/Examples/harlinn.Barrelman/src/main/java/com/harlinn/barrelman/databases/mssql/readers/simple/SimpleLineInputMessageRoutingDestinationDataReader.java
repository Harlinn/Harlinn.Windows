package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLineInputMessageRoutingDestinationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  limrd.[Id], \r\n" +
            "  limrd.[RowVersion], \r\n" +
            "  limrd.[Routing], \r\n" +
            "  limrd.[Listener] \r\n" +
            "FROM [LineInputMessageRoutingDestinationView] limrd \r\n";

    public final static String BaseViewName = "LineInputMessageRoutingDestinationView";
    public final static String ViewAliasName = "limrd";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ROUTING_FIELD_ID = 3;
    public final static int LISTENER_FIELD_ID = 4;

    public SimpleLineInputMessageRoutingDestinationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getRouting() throws SQLException {
        return getGuid( ROUTING_FIELD_ID );
    }

    public final Guid getListener() throws SQLException {
        return getNullableGuid( LISTENER_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LineInputMessageRoutingDestination );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getRouting( ) );
        destination.writeNullableGuid( getListener( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public LineInputMessageRoutingDestinationObject getDataObject( ) throws SQLException {
            return new LineInputMessageRoutingDestinationObject( ObjectState.Stored, getId( ), getRowVersion( ), getRouting( ), getListener( ) );
    }

}
