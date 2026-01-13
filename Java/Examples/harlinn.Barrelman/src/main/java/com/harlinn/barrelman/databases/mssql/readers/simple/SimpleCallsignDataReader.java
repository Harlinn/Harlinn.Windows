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

public class SimpleCallsignDataReader extends SimpleIdentityDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  c.[Id], \r\n" +
            "  c.[EntityType], \r\n" +
            "  c.[RowVersion], \r\n" +
            "  c.[Identifier] \r\n" +
            "FROM [CallsignView] c \r\n";

    public final static String BaseViewName = "CallsignView";
    public final static String ViewAliasName = "c";

    public final static int IDENTIFIER_FIELD_ID = 4;

    public SimpleCallsignDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getIdentifier() throws SQLException {
        return getString( IDENTIFIER_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getIdentifier( ) );
    }

    @Override
    public CallsignObject getDataObject( ) throws SQLException {
        return new CallsignObject( ObjectState.Stored, getId( ), getRowVersion( ), getIdentifier( ) );
    }

}
