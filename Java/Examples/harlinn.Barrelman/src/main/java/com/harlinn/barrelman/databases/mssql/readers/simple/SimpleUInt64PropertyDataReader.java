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

public class SimpleUInt64PropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u64p.[Id], \r\n" +
            "  u64p.[EntityType], \r\n" +
            "  u64p.[RowVersion], \r\n" +
            "  u64p.[Element], \r\n" +
            "  u64p.[Definition], \r\n" +
            "  u64p.[Value] \r\n" +
            "FROM [UInt64PropertyView] u64p \r\n";

    public final static String BaseViewName = "UInt64PropertyView";
    public final static String ViewAliasName = "u64p";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleUInt64PropertyDataReader( ResultSet resultSet ) {
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
    public UInt64PropertyObject getDataObject( ) throws SQLException {
        return new UInt64PropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
