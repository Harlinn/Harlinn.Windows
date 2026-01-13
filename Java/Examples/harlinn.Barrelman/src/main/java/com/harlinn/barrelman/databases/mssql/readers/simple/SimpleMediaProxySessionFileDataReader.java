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

public class SimpleMediaProxySessionFileDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mpsf.[Id], \r\n" +
            "  mpsf.[RowVersion], \r\n" +
            "  mpsf.[ProxySession], \r\n" +
            "  mpsf.[Timestamp], \r\n" +
            "  mpsf.[StreamName] \r\n" +
            "FROM [MediaProxySessionFileView] mpsf \r\n";

    public final static String BaseViewName = "MediaProxySessionFileView";
    public final static String ViewAliasName = "mpsf";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int PROXYSESSION_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int STREAMNAME_FIELD_ID = 5;

    public SimpleMediaProxySessionFileDataReader( ResultSet resultSet ) {
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

    public final String getStreamName() throws SQLException {
        return getString( STREAMNAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MediaProxySessionFile );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getProxySession( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeStringUtf8( getStreamName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public MediaProxySessionFileObject getDataObject( ) throws SQLException {
            return new MediaProxySessionFileObject( ObjectState.Stored, getId( ), getRowVersion( ), getProxySession( ), getTimestamp( ), getStreamName( ) );
    }

}
