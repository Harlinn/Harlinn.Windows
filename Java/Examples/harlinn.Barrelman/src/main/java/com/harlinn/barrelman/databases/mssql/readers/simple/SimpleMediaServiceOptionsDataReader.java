package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMediaServiceOptionsDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mso.[Id], \r\n" +
            "  mso.[RowVersion], \r\n" +
            "  mso.[MediaService], \r\n" +
            "  mso.[Timestamp], \r\n" +
            "  mso.[RtspPortNumber], \r\n" +
            "  mso.[HttpPortNumber] \r\n" +
            "FROM [MediaServiceOptionsView] mso \r\n";

    public final static String BaseViewName = "MediaServiceOptionsView";
    public final static String ViewAliasName = "mso";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int MEDIASERVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int RTSPPORTNUMBER_FIELD_ID = 5;
    public final static int HTTPPORTNUMBER_FIELD_ID = 6;

    public SimpleMediaServiceOptionsDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getMediaService() throws SQLException {
        return getGuid( MEDIASERVICE_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getRtspPortNumber() throws SQLException {
        return getInt32( RTSPPORTNUMBER_FIELD_ID );
    }

    public final int getHttpPortNumber() throws SQLException {
        return getInt32( HTTPPORTNUMBER_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MediaServiceOptions );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getMediaService( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getRtspPortNumber( ) );
        destination.writeInt32( getHttpPortNumber( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public MediaServiceOptionsObject GetDataObject( ) throws SQLException {
            return new MediaServiceOptionsObject( ObjectState.Stored, getId( ), getRowVersion( ), getMediaService( ), getTimestamp( ), getRtspPortNumber( ), getHttpPortNumber( ) );
    }

}
