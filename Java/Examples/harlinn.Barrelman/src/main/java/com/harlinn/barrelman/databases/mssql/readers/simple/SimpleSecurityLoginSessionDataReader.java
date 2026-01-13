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

public class SimpleSecurityLoginSessionDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sls.[Id], \r\n" +
            "  sls.[RowVersion], \r\n" +
            "  sls.[Login], \r\n" +
            "  sls.[FromTime], \r\n" +
            "  sls.[ThroughTime], \r\n" +
            "  sls.[ClientSession], \r\n" +
            "  sls.[NotificationQueueName], \r\n" +
            "  sls.[MessageQueueName] \r\n" +
            "FROM [SecurityLoginSessionView] sls \r\n";

    public final static String BaseViewName = "SecurityLoginSessionView";
    public final static String ViewAliasName = "sls";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int LOGIN_FIELD_ID = 3;
    public final static int FROMTIME_FIELD_ID = 4;
    public final static int THROUGHTIME_FIELD_ID = 5;
    public final static int CLIENTSESSION_FIELD_ID = 6;
    public final static int NOTIFICATIONQUEUENAME_FIELD_ID = 7;
    public final static int MESSAGEQUEUENAME_FIELD_ID = 8;

    public SimpleSecurityLoginSessionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getLogin() throws SQLException {
        return getGuid( LOGIN_FIELD_ID );
    }

    public final DateTime getFromTime() throws SQLException {
        return getDateTimeFromLong( FROMTIME_FIELD_ID );
    }

    public final DateTime getThroughTime() throws SQLException {
        return getNullableDateTimeFromLong( THROUGHTIME_FIELD_ID );
    }

    public final Guid getClientSession() throws SQLException {
        return getGuid( CLIENTSESSION_FIELD_ID );
    }

    public final String getNotificationQueueName() throws SQLException {
        return getString( NOTIFICATIONQUEUENAME_FIELD_ID );
    }

    public final String getMessageQueueName() throws SQLException {
        return getString( MESSAGEQUEUENAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.SecurityLoginSession );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getLogin( ) );
        destination.writeDateTime( getFromTime( ) );
        destination.writeNullableDateTime( getThroughTime( ) );
        destination.writeGuid( getClientSession( ) );
        destination.writeStringUtf8( getNotificationQueueName( ) );
        destination.writeStringUtf8( getMessageQueueName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public SecurityLoginSessionObject getDataObject( ) throws SQLException {
            return new SecurityLoginSessionObject( ObjectState.Stored, getId( ), getRowVersion( ), getLogin( ), getFromTime( ), getThroughTime( ), getClientSession( ), getNotificationQueueName( ), getMessageQueueName( ) );
    }

}
