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

public class SimpleLogTraceEntryDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  lte.[Id], \r\n" +
            "  lte.[RowVersion], \r\n" +
            "  lte.[Thread], \r\n" +
            "  lte.[SequenceNumber], \r\n" +
            "  lte.[Location], \r\n" +
            "  lte.[Depth], \r\n" +
            "  lte.[Entered], \r\n" +
            "  lte.[Ended] \r\n" +
            "FROM [LogTraceEntryView] lte \r\n";

    public final static String BaseViewName = "LogTraceEntryView";
    public final static String ViewAliasName = "lte";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int THREAD_FIELD_ID = 3;
    public final static int SEQUENCENUMBER_FIELD_ID = 4;
    public final static int LOCATION_FIELD_ID = 5;
    public final static int DEPTH_FIELD_ID = 6;
    public final static int ENTERED_FIELD_ID = 7;
    public final static int ENDED_FIELD_ID = 8;

    public SimpleLogTraceEntryDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getThread() throws SQLException {
        return getGuid( THREAD_FIELD_ID );
    }

    public final long getSequenceNumber() throws SQLException {
        return getInt64( SEQUENCENUMBER_FIELD_ID );
    }

    public final Guid getLocation() throws SQLException {
        return getGuid( LOCATION_FIELD_ID );
    }

    public final int getDepth() throws SQLException {
        return getInt32( DEPTH_FIELD_ID );
    }

    public final DateTime getEntered() throws SQLException {
        return getDateTimeFromLong( ENTERED_FIELD_ID );
    }

    public final DateTime getEnded() throws SQLException {
        return getNullableDateTimeFromLong( ENDED_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LogTraceEntry );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getThread( ) );
        destination.writeInt64( getSequenceNumber( ) );
        destination.writeGuid( getLocation( ) );
        destination.writeInt32( getDepth( ) );
        destination.writeDateTime( getEntered( ) );
        destination.writeNullableDateTime( getEnded( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public LogTraceEntryObject getDataObject( ) throws SQLException {
            return new LogTraceEntryObject( ObjectState.Stored, getId( ), getRowVersion( ), getThread( ), getSequenceNumber( ), getLocation( ), getDepth( ), getEntered( ), getEnded( ) );
    }

}
