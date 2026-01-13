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
package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleOilSpillDetectorCommandReplyDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  osdcr.[Id], \r\n" +
            "  osdcr.[RowVersion], \r\n" +
            "  osdcr.[OilSpillDetector], \r\n" +
            "  osdcr.[Timestamp], \r\n" +
            "  osdcr.[Command], \r\n" +
            "  osdcr.[Status], \r\n" +
            "  osdcr.[Message] \r\n" +
            "FROM [OilSpillDetectorCommandReplyView] osdcr \r\n";

    public final static String BaseViewName = "OilSpillDetectorCommandReplyView";
    public final static String ViewAliasName = "osdcr";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int OILSPILLDETECTOR_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int COMMAND_FIELD_ID = 5;
    public final static int STATUS_FIELD_ID = 6;
    public final static int MESSAGE_FIELD_ID = 7;

    public SimpleOilSpillDetectorCommandReplyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getOilSpillDetector() throws SQLException {
        return getGuid( OILSPILLDETECTOR_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final Guid getCommand() throws SQLException {
        return getNullableGuid( COMMAND_FIELD_ID );
    }

    public final int getStatus() throws SQLException {
        return getInt32( STATUS_FIELD_ID );
    }

    public final String getMessage() throws SQLException {
        return getString( MESSAGE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.OilSpillDetectorCommandReply );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getOilSpillDetector( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeNullableGuid( getCommand( ) );
        destination.writeInt32( getStatus( ) );
        destination.writeStringUtf8( getMessage( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public OilSpillDetectorCommandReplyObject getDataObject( ) throws SQLException {
            return new OilSpillDetectorCommandReplyObject( ObjectState.Stored, getId( ), getRowVersion( ), getOilSpillDetector( ), getTimestamp( ), getCommand( ), getStatus( ), getMessage( ) );
    }

}
