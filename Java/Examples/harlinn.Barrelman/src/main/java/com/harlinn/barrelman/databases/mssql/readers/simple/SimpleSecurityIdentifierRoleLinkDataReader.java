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

public class SimpleSecurityIdentifierRoleLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sirl.[Id], \r\n" +
            "  sirl.[RowVersion], \r\n" +
            "  sirl.[Member], \r\n" +
            "  sirl.[Role], \r\n" +
            "  sirl.[Start], \r\n" +
            "  sirl.[End] \r\n" +
            "FROM [SecurityIdentifierRoleLinkView] sirl \r\n";

    public final static String BaseViewName = "SecurityIdentifierRoleLinkView";
    public final static String ViewAliasName = "sirl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int MEMBER_FIELD_ID = 3;
    public final static int ROLE_FIELD_ID = 4;
    public final static int START_FIELD_ID = 5;
    public final static int END_FIELD_ID = 6;

    public SimpleSecurityIdentifierRoleLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getMember() throws SQLException {
        return getGuid( MEMBER_FIELD_ID );
    }

    public final Guid getRole() throws SQLException {
        return getGuid( ROLE_FIELD_ID );
    }

    public final DateTime getStart() throws SQLException {
        return getDateTimeFromLong( START_FIELD_ID );
    }

    public final DateTime getEnd() throws SQLException {
        return getNullableDateTimeFromLong( END_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.SecurityIdentifierRoleLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getMember( ) );
        destination.writeGuid( getRole( ) );
        destination.writeDateTime( getStart( ) );
        destination.writeNullableDateTime( getEnd( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public SecurityIdentifierRoleLinkObject getDataObject( ) throws SQLException {
            return new SecurityIdentifierRoleLinkObject( ObjectState.Stored, getId( ), getRowVersion( ), getMember( ), getRole( ), getStart( ), getEnd( ) );
    }

}
