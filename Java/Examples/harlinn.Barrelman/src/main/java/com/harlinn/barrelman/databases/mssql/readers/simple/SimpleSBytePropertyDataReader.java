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

public class SimpleSBytePropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sp.[Id], \r\n" +
            "  sp.[EntityType], \r\n" +
            "  sp.[RowVersion], \r\n" +
            "  sp.[Element], \r\n" +
            "  sp.[Definition], \r\n" +
            "  sp.[Value] \r\n" +
            "FROM [SBytePropertyView] sp \r\n";

    public final static String BaseViewName = "SBytePropertyView";
    public final static String ViewAliasName = "sp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleSBytePropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte getValue() throws SQLException {
        return getInt8( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt8( getValue( ) );
    }

    @Override
    public SBytePropertyObject getDataObject( ) throws SQLException {
        return new SBytePropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
