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

public class SimpleNameDataReader extends SimpleIdentityDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  n.[Id], \r\n" +
            "  n.[EntityType], \r\n" +
            "  n.[RowVersion], \r\n" +
            "  n.[Text] \r\n" +
            "FROM [NameView] n \r\n";

    public final static String BaseViewName = "NameView";
    public final static String ViewAliasName = "n";

    public final static int TEXT_FIELD_ID = 4;

    public SimpleNameDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getText() throws SQLException {
        return getString( TEXT_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getText( ) );
    }

    @Override
    public NameObject getDataObject( ) throws SQLException {
        return new NameObject( ObjectState.Stored, getId( ), getRowVersion( ), getText( ) );
    }

}
