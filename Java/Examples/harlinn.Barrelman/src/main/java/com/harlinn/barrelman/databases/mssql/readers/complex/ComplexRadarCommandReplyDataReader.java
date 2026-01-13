/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexRadarCommandReplyDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  rcr.[Id], \r\n" +
            "  rcr.[EntityType], \r\n" +
            "  rcr.[RowVersion], \r\n" +
            "  rcr.[Radar], \r\n" +
            "  rcr.[Timestamp], \r\n" +
            "  rcr.[Command], \r\n" +
            "  rcr.[Status], \r\n" +
            "  rcrgs.[AzimuthCount], \r\n" +
            "  rcrgs.[TriggerCount], \r\n" +
            "  rcrgs.[RotationCount], \r\n" +
            "  rcrgs.[Pulse], \r\n" +
            "  rcrgs.[Tx], \r\n" +
            "  rcr.[Message] \r\n" +
            "FROM [RadarCommandReplyView] rcr \r\n" +
            "  LEFT JOIN [RadarCommandReplyGetStatus] rcrgs ON(rcr.[Id] = rcrgs.[Id] ) \r\n";

    public final static String BaseViewName = "RadarCommandReplyView";
    public final static String ViewAliasName = "rcr";

    public final static int RCR_ID_FIELD_ID = 1;
    public final static int RCR_KIND_FIELD_ID = 2;
    public final static int RCR_ROWVERSION_FIELD_ID = 3;
    public final static int RCR_RADAR_FIELD_ID = 4;
    public final static int RCR_TIMESTAMP_FIELD_ID = 5;
    public final static int RCR_COMMAND_FIELD_ID = 6;
    public final static int RCR_STATUS_FIELD_ID = 7;
    public final static int RCRGS_AZIMUTHCOUNT_FIELD_ID = 8;
    public final static int RCRGS_TRIGGERCOUNT_FIELD_ID = 9;
    public final static int RCRGS_ROTATIONCOUNT_FIELD_ID = 10;
    public final static int RCRGS_PULSE_FIELD_ID = 11;
    public final static int RCRGS_TX_FIELD_ID = 12;
    public final static int RCR_MESSAGE_FIELD_ID = 13;

    public ComplexRadarCommandReplyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( RCR_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( RCR_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( RCR_ROWVERSION_FIELD_ID );
    }

    public Guid getRadar( ) throws SQLException {
        return getGuid( RCR_RADAR_FIELD_ID );
    }

    public DateTime getTimestamp( ) throws SQLException {
        return getDateTimeFromLong( RCR_TIMESTAMP_FIELD_ID );
    }

    public Guid getCommand( ) throws SQLException {
        return getNullableGuid( RCR_COMMAND_FIELD_ID );
    }

    public int getStatus( ) throws SQLException {
        return getInt32( RCR_STATUS_FIELD_ID );
    }

    public String getMessage( ) throws SQLException {
        return getString( RCR_MESSAGE_FIELD_ID );
    }

    public int getRadarCommandReplyGetStatusAzimuthCount( ) throws SQLException {
        return getInt32( RCRGS_AZIMUTHCOUNT_FIELD_ID );
    }

    public int getRadarCommandReplyGetStatusTriggerCount( ) throws SQLException {
        return getInt32( RCRGS_TRIGGERCOUNT_FIELD_ID );
    }

    public TimeSpan getRadarCommandReplyGetStatusRotationCount( ) throws SQLException {
        return getTimeSpan( RCRGS_ROTATIONCOUNT_FIELD_ID );
    }

    public int getRadarCommandReplyGetStatusPulse( ) throws SQLException {
        return getInt32( RCRGS_PULSE_FIELD_ID );
    }

    public boolean getRadarCommandReplyGetStatusTx( ) throws SQLException {
        return getBoolean( RCRGS_TX_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.RadarCommandReply: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getRadar( ) );
                destination.writeDateTime( getTimestamp( ) );
                destination.writeNullableGuid( getCommand( ) );
                destination.writeInt32( getStatus( ) );
                destination.writeStringUtf8( getMessage( ) );
            }
            break;
            case Kind.RadarCommandReplyGetStatus: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getRadar( ) );
                destination.writeDateTime( getTimestamp( ) );
                destination.writeNullableGuid( getCommand( ) );
                destination.writeInt32( getStatus( ) );
                destination.writeStringUtf8( getMessage( ) );
                destination.writeInt32( getRadarCommandReplyGetStatusAzimuthCount( ) );
                destination.writeInt32( getRadarCommandReplyGetStatusTriggerCount( ) );
                destination.writeTimeSpan( getRadarCommandReplyGetStatusRotationCount( ) );
                destination.writeInt32( getRadarCommandReplyGetStatusPulse( ) );
                destination.writeBoolean( getRadarCommandReplyGetStatusTx( ) );
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

    public RadarCommandReplyObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.RadarCommandReply: {
                return new RadarCommandReplyObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getCommand( ), getStatus( ), getMessage( ) );
            }
            case Kind.RadarCommandReplyGetStatus: {
                return new RadarCommandReplyGetStatusObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getCommand( ), getStatus( ), getMessage( ), getRadarCommandReplyGetStatusAzimuthCount( ), getRadarCommandReplyGetStatusTriggerCount( ), getRadarCommandReplyGetStatusRotationCount( ), getRadarCommandReplyGetStatusPulse( ), getRadarCommandReplyGetStatusTx( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

