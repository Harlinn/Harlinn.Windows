package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMediaProxySessionOptionsDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mpso.[Id], \r\n" +
            "  mpso.[RowVersion], \r\n" +
            "  mpso.[ProxySession], \r\n" +
            "  mpso.[Timestamp], \r\n" +
            "  mpso.[SourceStreamUrl], \r\n" +
            "  mpso.[StreamName], \r\n" +
            "  mpso.[Mode], \r\n" +
            "  mpso.[TunnelOverHTTPPortNumber], \r\n" +
            "  mpso.[Username], \r\n" +
            "  mpso.[Password], \r\n" +
            "  mpso.[RecorderPortNumber], \r\n" +
            "  mpso.[SessionType], \r\n" +
            "  mpso.[MaxFileTime], \r\n" +
            "  mpso.[MaxFileRetention], \r\n" +
            "  mpso.[VideoDirectory] \r\n" +
            "FROM [MediaProxySessionOptionsView] mpso \r\n";

    public final static String BaseViewName = "MediaProxySessionOptionsView";
    public final static String ViewAliasName = "mpso";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int PROXYSESSION_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int SOURCESTREAMURL_FIELD_ID = 5;
    public final static int STREAMNAME_FIELD_ID = 6;
    public final static int MODE_FIELD_ID = 7;
    public final static int TUNNELOVERHTTPPORTNUMBER_FIELD_ID = 8;
    public final static int USERNAME_FIELD_ID = 9;
    public final static int PASSWORD_FIELD_ID = 10;
    public final static int RECORDERPORTNUMBER_FIELD_ID = 11;
    public final static int SESSIONTYPE_FIELD_ID = 12;
    public final static int MAXFILETIME_FIELD_ID = 13;
    public final static int MAXFILERETENTION_FIELD_ID = 14;
    public final static int VIDEODIRECTORY_FIELD_ID = 15;

    public SimpleMediaProxySessionOptionsDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getProxySession() throws SQLException {
        return getGuid( PROXYSESSION_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final String getSourceStreamUrl() throws SQLException {
        return getString( SOURCESTREAMURL_FIELD_ID );
    }

    public final String getStreamName() throws SQLException {
        return getString( STREAMNAME_FIELD_ID );
    }

    public final int getMode() throws SQLException {
        return getInt32( MODE_FIELD_ID );
    }

    public final int getTunnelOverHTTPPortNumber() throws SQLException {
        return getInt32( TUNNELOVERHTTPPORTNUMBER_FIELD_ID );
    }

    public final String getUsername() throws SQLException {
        return getString( USERNAME_FIELD_ID );
    }

    public final String getPassword() throws SQLException {
        return getString( PASSWORD_FIELD_ID );
    }

    public final int getRecorderPortNumber() throws SQLException {
        return getInt32( RECORDERPORTNUMBER_FIELD_ID );
    }

    public final int getSessionType() throws SQLException {
        return getInt32( SESSIONTYPE_FIELD_ID );
    }

    public final TimeSpan getMaxFileTime() throws SQLException {
        return getTimeSpan( MAXFILETIME_FIELD_ID );
    }

    public final TimeSpan getMaxFileRetention() throws SQLException {
        return getTimeSpan( MAXFILERETENTION_FIELD_ID );
    }

    public final String getVideoDirectory() throws SQLException {
        return getString( VIDEODIRECTORY_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MediaProxySessionOptions );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getProxySession( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeStringUtf8( getSourceStreamUrl( ) );
        destination.writeStringUtf8( getStreamName( ) );
        destination.writeInt32( getMode( ) );
        destination.writeInt32( getTunnelOverHTTPPortNumber( ) );
        destination.writeStringUtf8( getUsername( ) );
        destination.writeStringUtf8( getPassword( ) );
        destination.writeInt32( getRecorderPortNumber( ) );
        destination.writeInt32( getSessionType( ) );
        destination.writeTimeSpan( getMaxFileTime( ) );
        destination.writeTimeSpan( getMaxFileRetention( ) );
        destination.writeStringUtf8( getVideoDirectory( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public MediaProxySessionOptionsObject getDataObject( ) throws SQLException {
            return new MediaProxySessionOptionsObject( ObjectState.Stored, getId( ), getRowVersion( ), getProxySession( ), getTimestamp( ), getSourceStreamUrl( ), getStreamName( ), getMode( ), getTunnelOverHTTPPortNumber( ), getUsername( ), getPassword( ), getRecorderPortNumber( ), getSessionType( ), getMaxFileTime( ), getMaxFileRetention( ), getVideoDirectory( ) );
    }

}
