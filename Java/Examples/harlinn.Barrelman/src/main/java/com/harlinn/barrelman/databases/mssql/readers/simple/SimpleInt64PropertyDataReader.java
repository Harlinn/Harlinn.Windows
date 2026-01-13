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

public class SimpleInt64PropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i64p.[Id], \r\n" +
            "  i64p.[EntityType], \r\n" +
            "  i64p.[RowVersion], \r\n" +
            "  i64p.[Element], \r\n" +
            "  i64p.[Definition], \r\n" +
            "  i64p.[Value] \r\n" +
            "FROM [Int64PropertyView] i64p \r\n";

    public final static String BaseViewName = "Int64PropertyView";
    public final static String ViewAliasName = "i64p";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleInt64PropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final long getValue() throws SQLException {
        return getInt64( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt64( getValue( ) );
    }

    @Override
    public Int64PropertyObject getDataObject( ) throws SQLException {
        return new Int64PropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
