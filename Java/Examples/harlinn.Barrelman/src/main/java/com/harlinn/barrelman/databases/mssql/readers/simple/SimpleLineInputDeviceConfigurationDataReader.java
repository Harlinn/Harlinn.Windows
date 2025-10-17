package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLineInputDeviceConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  lidc.[Id], \r\n" +
            "  lidc.[RowVersion], \r\n" +
            "  lidc.[LineInputDevice], \r\n" +
            "  lidc.[Timestamp], \r\n" +
            "  lidc.[StoreReceivedSentences], \r\n" +
            "  lidc.[StoreSentMessages], \r\n" +
            "  lidc.[StoreUnsentMessages], \r\n" +
            "  lidc.[NMEA], \r\n" +
            "  lidc.[StrictNMEA], \r\n" +
            "  lidc.[ConnectionType], \r\n" +
            "  lidc.[UdpReceivePort], \r\n" +
            "  lidc.[UdpSendHostname], \r\n" +
            "  lidc.[UdpSendPort], \r\n" +
            "  lidc.[TcpHostname], \r\n" +
            "  lidc.[TcpPort], \r\n" +
            "  lidc.[UseHttpLogin], \r\n" +
            "  lidc.[LoginHostname], \r\n" +
            "  lidc.[LoginPort], \r\n" +
            "  lidc.[UserName], \r\n" +
            "  lidc.[Password], \r\n" +
            "  lidc.[ComPort], \r\n" +
            "  lidc.[BaudRate], \r\n" +
            "  lidc.[DataBits], \r\n" +
            "  lidc.[DiscardNull], \r\n" +
            "  lidc.[DtrEnable], \r\n" +
            "  lidc.[Handshake], \r\n" +
            "  lidc.[NewLine], \r\n" +
            "  lidc.[Parity], \r\n" +
            "  lidc.[ParityReplace], \r\n" +
            "  lidc.[ReadBufferSize], \r\n" +
            "  lidc.[ReadTimeout], \r\n" +
            "  lidc.[ReceivedBytesThreshold], \r\n" +
            "  lidc.[RtsEnable], \r\n" +
            "  lidc.[StopBits], \r\n" +
            "  lidc.[WriteBufferSize], \r\n" +
            "  lidc.[WriteTimeout], \r\n" +
            "  lidc.[PairedComPort] \r\n" +
            "FROM [LineInputDeviceConfigurationView] lidc \r\n";

    public final static String BaseViewName = "LineInputDeviceConfigurationView";
    public final static String ViewAliasName = "lidc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int LINEINPUTDEVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int STORERECEIVEDSENTENCES_FIELD_ID = 5;
    public final static int STORESENTMESSAGES_FIELD_ID = 6;
    public final static int STOREUNSENTMESSAGES_FIELD_ID = 7;
    public final static int NMEA_FIELD_ID = 8;
    public final static int STRICTNMEA_FIELD_ID = 9;
    public final static int CONNECTIONTYPE_FIELD_ID = 10;
    public final static int UDPRECEIVEPORT_FIELD_ID = 11;
    public final static int UDPSENDHOSTNAME_FIELD_ID = 12;
    public final static int UDPSENDPORT_FIELD_ID = 13;
    public final static int TCPHOSTNAME_FIELD_ID = 14;
    public final static int TCPPORT_FIELD_ID = 15;
    public final static int USEHTTPLOGIN_FIELD_ID = 16;
    public final static int LOGINHOSTNAME_FIELD_ID = 17;
    public final static int LOGINPORT_FIELD_ID = 18;
    public final static int USERNAME_FIELD_ID = 19;
    public final static int PASSWORD_FIELD_ID = 20;
    public final static int COMPORT_FIELD_ID = 21;
    public final static int BAUDRATE_FIELD_ID = 22;
    public final static int DATABITS_FIELD_ID = 23;
    public final static int DISCARDNULL_FIELD_ID = 24;
    public final static int DTRENABLE_FIELD_ID = 25;
    public final static int HANDSHAKE_FIELD_ID = 26;
    public final static int NEWLINE_FIELD_ID = 27;
    public final static int PARITY_FIELD_ID = 28;
    public final static int PARITYREPLACE_FIELD_ID = 29;
    public final static int READBUFFERSIZE_FIELD_ID = 30;
    public final static int READTIMEOUT_FIELD_ID = 31;
    public final static int RECEIVEDBYTESTHRESHOLD_FIELD_ID = 32;
    public final static int RTSENABLE_FIELD_ID = 33;
    public final static int STOPBITS_FIELD_ID = 34;
    public final static int WRITEBUFFERSIZE_FIELD_ID = 35;
    public final static int WRITETIMEOUT_FIELD_ID = 36;
    public final static int PAIREDCOMPORT_FIELD_ID = 37;

    public SimpleLineInputDeviceConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getLineInputDevice() throws SQLException {
        return getGuid( LINEINPUTDEVICE_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final boolean getStoreReceivedSentences() throws SQLException {
        return getBoolean( STORERECEIVEDSENTENCES_FIELD_ID );
    }

    public final boolean getStoreSentMessages() throws SQLException {
        return getBoolean( STORESENTMESSAGES_FIELD_ID );
    }

    public final boolean getStoreUnsentMessages() throws SQLException {
        return getBoolean( STOREUNSENTMESSAGES_FIELD_ID );
    }

    public final boolean getNMEA() throws SQLException {
        return getBoolean( NMEA_FIELD_ID );
    }

    public final boolean getStrictNMEA() throws SQLException {
        return getBoolean( STRICTNMEA_FIELD_ID );
    }

    public final int getConnectionType() throws SQLException {
        return getInt32( CONNECTIONTYPE_FIELD_ID );
    }

    public final int getUdpReceivePort() throws SQLException {
        return getInt32( UDPRECEIVEPORT_FIELD_ID );
    }

    public final String getUdpSendHostname() throws SQLException {
        return getString( UDPSENDHOSTNAME_FIELD_ID );
    }

    public final int getUdpSendPort() throws SQLException {
        return getInt32( UDPSENDPORT_FIELD_ID );
    }

    public final String getTcpHostname() throws SQLException {
        return getString( TCPHOSTNAME_FIELD_ID );
    }

    public final int getTcpPort() throws SQLException {
        return getInt32( TCPPORT_FIELD_ID );
    }

    public final boolean getUseHttpLogin() throws SQLException {
        return getBoolean( USEHTTPLOGIN_FIELD_ID );
    }

    public final String getLoginHostname() throws SQLException {
        return getString( LOGINHOSTNAME_FIELD_ID );
    }

    public final int getLoginPort() throws SQLException {
        return getInt32( LOGINPORT_FIELD_ID );
    }

    public final String getUserName() throws SQLException {
        return getString( USERNAME_FIELD_ID );
    }

    public final String getPassword() throws SQLException {
        return getString( PASSWORD_FIELD_ID );
    }

    public final String getComPort() throws SQLException {
        return getString( COMPORT_FIELD_ID );
    }

    public final int getBaudRate() throws SQLException {
        return getInt32( BAUDRATE_FIELD_ID );
    }

    public final int getDataBits() throws SQLException {
        return getInt32( DATABITS_FIELD_ID );
    }

    public final boolean getDiscardNull() throws SQLException {
        return getBoolean( DISCARDNULL_FIELD_ID );
    }

    public final boolean getDtrEnable() throws SQLException {
        return getBoolean( DTRENABLE_FIELD_ID );
    }

    public final int getHandshake() throws SQLException {
        return getInt32( HANDSHAKE_FIELD_ID );
    }

    public final String getNewLine() throws SQLException {
        return getString( NEWLINE_FIELD_ID );
    }

    public final int getParity() throws SQLException {
        return getInt32( PARITY_FIELD_ID );
    }

    public final byte getParityReplace() throws SQLException {
        return getUInt8( PARITYREPLACE_FIELD_ID );
    }

    public final int getReadBufferSize() throws SQLException {
        return getInt32( READBUFFERSIZE_FIELD_ID );
    }

    public final TimeSpan getReadTimeout() throws SQLException {
        return getTimeSpan( READTIMEOUT_FIELD_ID );
    }

    public final int getReceivedBytesThreshold() throws SQLException {
        return getInt32( RECEIVEDBYTESTHRESHOLD_FIELD_ID );
    }

    public final boolean getRtsEnable() throws SQLException {
        return getBoolean( RTSENABLE_FIELD_ID );
    }

    public final int getStopBits() throws SQLException {
        return getInt32( STOPBITS_FIELD_ID );
    }

    public final int getWriteBufferSize() throws SQLException {
        return getInt32( WRITEBUFFERSIZE_FIELD_ID );
    }

    public final TimeSpan getWriteTimeout() throws SQLException {
        return getTimeSpan( WRITETIMEOUT_FIELD_ID );
    }

    public final String getPairedComPort() throws SQLException {
        return getString( PAIREDCOMPORT_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LineInputDeviceConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getLineInputDevice( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeBoolean( getStoreReceivedSentences( ) );
        destination.writeBoolean( getStoreSentMessages( ) );
        destination.writeBoolean( getStoreUnsentMessages( ) );
        destination.writeBoolean( getNMEA( ) );
        destination.writeBoolean( getStrictNMEA( ) );
        destination.writeInt32( getConnectionType( ) );
        destination.writeInt32( getUdpReceivePort( ) );
        destination.writeStringUtf8( getUdpSendHostname( ) );
        destination.writeInt32( getUdpSendPort( ) );
        destination.writeStringUtf8( getTcpHostname( ) );
        destination.writeInt32( getTcpPort( ) );
        destination.writeBoolean( getUseHttpLogin( ) );
        destination.writeStringUtf8( getLoginHostname( ) );
        destination.writeInt32( getLoginPort( ) );
        destination.writeStringUtf8( getUserName( ) );
        destination.writeStringUtf8( getPassword( ) );
        destination.writeStringUtf8( getComPort( ) );
        destination.writeInt32( getBaudRate( ) );
        destination.writeInt32( getDataBits( ) );
        destination.writeBoolean( getDiscardNull( ) );
        destination.writeBoolean( getDtrEnable( ) );
        destination.writeInt32( getHandshake( ) );
        destination.writeStringUtf8( getNewLine( ) );
        destination.writeInt32( getParity( ) );
        destination.writeUInt8( getParityReplace( ) );
        destination.writeInt32( getReadBufferSize( ) );
        destination.writeTimeSpan( getReadTimeout( ) );
        destination.writeInt32( getReceivedBytesThreshold( ) );
        destination.writeBoolean( getRtsEnable( ) );
        destination.writeInt32( getStopBits( ) );
        destination.writeInt32( getWriteBufferSize( ) );
        destination.writeTimeSpan( getWriteTimeout( ) );
        destination.writeStringUtf8( getPairedComPort( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
