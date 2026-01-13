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

public class SimpleInternationalMaritimeOrganizationNumberDataReader extends SimpleIdentityDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  imon.[Id], \r\n" +
            "  imon.[EntityType], \r\n" +
            "  imon.[RowVersion], \r\n" +
            "  imon.[Identifier] \r\n" +
            "FROM [InternationalMaritimeOrganizationNumberView] imon \r\n";

    public final static String BaseViewName = "InternationalMaritimeOrganizationNumberView";
    public final static String ViewAliasName = "imon";

    public final static int IDENTIFIER_FIELD_ID = 4;

    public SimpleInternationalMaritimeOrganizationNumberDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final long getIdentifier() throws SQLException {
        return getInt64( IDENTIFIER_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt64( getIdentifier( ) );
    }

    @Override
    public InternationalMaritimeOrganizationNumberObject getDataObject( ) throws SQLException {
        return new InternationalMaritimeOrganizationNumberObject( ObjectState.Stored, getId( ), getRowVersion( ), getIdentifier( ) );
    }

}
