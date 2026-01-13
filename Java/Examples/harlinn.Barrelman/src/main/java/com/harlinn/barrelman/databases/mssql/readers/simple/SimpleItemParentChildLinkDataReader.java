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

public class SimpleItemParentChildLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ipcl.[Id], \r\n" +
            "  ipcl.[RowVersion], \r\n" +
            "  ipcl.[Parent], \r\n" +
            "  ipcl.[Child], \r\n" +
            "  ipcl.[Timestamp] \r\n" +
            "FROM [ItemParentChildLinkView] ipcl \r\n";

    public final static String BaseViewName = "ItemParentChildLinkView";
    public final static String ViewAliasName = "ipcl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int PARENT_FIELD_ID = 3;
    public final static int CHILD_FIELD_ID = 4;
    public final static int TIMESTAMP_FIELD_ID = 5;

    public SimpleItemParentChildLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getParent() throws SQLException {
        return getGuid( PARENT_FIELD_ID );
    }

    public final Guid getChild() throws SQLException {
        return getGuid( CHILD_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ItemParentChildLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getParent( ) );
        destination.writeGuid( getChild( ) );
        destination.writeDateTime( getTimestamp( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public ItemParentChildLinkObject getDataObject( ) throws SQLException {
            return new ItemParentChildLinkObject( ObjectState.Stored, getId( ), getRowVersion( ), getParent( ), getChild( ), getTimestamp( ) );
    }

}
