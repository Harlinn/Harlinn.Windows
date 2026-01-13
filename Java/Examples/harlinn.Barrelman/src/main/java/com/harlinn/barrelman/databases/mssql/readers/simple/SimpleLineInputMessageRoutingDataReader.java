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

public class SimpleLineInputMessageRoutingDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  limr.[Id], \r\n" +
            "  limr.[RowVersion], \r\n" +
            "  limr.[LineInputDevice], \r\n" +
            "  limr.[Type] \r\n" +
            "FROM [LineInputMessageRoutingView] limr \r\n";

    public final static String BaseViewName = "LineInputMessageRoutingView";
    public final static String ViewAliasName = "limr";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int LINEINPUTDEVICE_FIELD_ID = 3;
    public final static int TYPE_FIELD_ID = 4;

    public SimpleLineInputMessageRoutingDataReader( ResultSet resultSet ) {
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

    public final String getTypeField() throws SQLException {
        return getString( TYPE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LineInputMessageRouting );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getLineInputDevice( ) );
        destination.writeStringUtf8( getTypeField( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public LineInputMessageRoutingObject getDataObject( ) throws SQLException {
            return new LineInputMessageRoutingObject( ObjectState.Stored, getId( ), getRowVersion( ), getLineInputDevice( ), getTypeField( ) );
    }

}
