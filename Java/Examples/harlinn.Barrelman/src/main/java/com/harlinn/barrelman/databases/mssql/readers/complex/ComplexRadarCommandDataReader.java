package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexRadarCommandDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[EntityType], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radar], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[DeviceCommandSourceType], \r\n" +
            "  rc.[DeviceCommandSourceId], \r\n" +
            "  rc.[Reply] \r\n" +
            "FROM [RadarCommandView] rc \r\n" +
            "  LEFT JOIN [RadarCommandGetStatus] rcgs ON(rc.[Id] = rcgs.[Id] ) \r\n";

    public final static String BaseViewName = "RadarCommandView";
    public final static String ViewAliasName = "rc";

    public final static int RC_ID_FIELD_ID = 1;
    public final static int RC_KIND_FIELD_ID = 2;
    public final static int RC_ROWVERSION_FIELD_ID = 3;
    public final static int RC_RADAR_FIELD_ID = 4;
    public final static int RC_TIMESTAMP_FIELD_ID = 5;
    public final static int RC_DEVICECOMMANDSOURCETYPE_FIELD_ID = 6;
    public final static int RC_DEVICECOMMANDSOURCEID_FIELD_ID = 7;
    public final static int RC_REPLY_FIELD_ID = 8;

    public ComplexRadarCommandDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( RC_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( RC_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( RC_ROWVERSION_FIELD_ID );
    }

    public Guid getRadar( ) throws SQLException {
        return getGuid( RC_RADAR_FIELD_ID );
    }

    public DateTime getTimestamp( ) throws SQLException {
        return getDateTimeFromLong( RC_TIMESTAMP_FIELD_ID );
    }

    public int getDeviceCommandSourceType( ) throws SQLException {
        return getInt32( RC_DEVICECOMMANDSOURCETYPE_FIELD_ID );
    }

    public Guid getDeviceCommandSourceId( ) throws SQLException {
        return getGuid( RC_DEVICECOMMANDSOURCEID_FIELD_ID );
    }

    public Guid getReply( ) throws SQLException {
        return getNullableGuid( RC_REPLY_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.RadarCommand: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getRadar( ) );
                destination.writeDateTime( getTimestamp( ) );
                destination.writeInt32( getDeviceCommandSourceType( ) );
                destination.writeGuid( getDeviceCommandSourceId( ) );
                destination.writeNullableGuid( getReply( ) );
            }
            break;
            case Kind.RadarCommandGetStatus: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getRadar( ) );
                destination.writeDateTime( getTimestamp( ) );
                destination.writeInt32( getDeviceCommandSourceType( ) );
                destination.writeGuid( getDeviceCommandSourceId( ) );
                destination.writeNullableGuid( getReply( ) );
            }
            break;
            default: {
                var exc = new SQLException( "Cannot perform serialization for kind=" + kind + "." );
                throw exc;
            }
        }
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public RadarCommandObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.RadarCommand: {
                return new RadarCommandObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ) );
            }
            case Kind.RadarCommandGetStatus: {
                return new RadarCommandGetStatusObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

