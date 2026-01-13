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

public class SimpleSecurityRoleDataReader extends SimpleSecurityIdentifierDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sr.[Id], \r\n" +
            "  sr.[EntityType], \r\n" +
            "  sr.[RowVersion], \r\n" +
            "  sr.[Domain], \r\n" +
            "  sr.[Identity], \r\n" +
            "  sr.[Description], \r\n" +
            "  sr.[Name] \r\n" +
            "FROM [SecurityRoleView] sr \r\n";

    public final static String BaseViewName = "SecurityRoleView";
    public final static String ViewAliasName = "sr";

    public final static int NAME_FIELD_ID = 7;

    public SimpleSecurityRoleDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getName( ) );
    }

    @Override
    public SecurityRoleObject getDataObject( ) throws SQLException {
        return new SecurityRoleObject( ObjectState.Stored, getId( ), getRowVersion( ), getDomain( ), getIdentity( ), getDescription( ), getName( ) );
    }

}
