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

public class SimpleBinaryPropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bp.[Id], \r\n" +
            "  bp.[EntityType], \r\n" +
            "  bp.[RowVersion], \r\n" +
            "  bp.[Element], \r\n" +
            "  bp.[Definition], \r\n" +
            "  bp.[Value] \r\n" +
            "FROM [BinaryPropertyView] bp \r\n";

    public final static String BaseViewName = "BinaryPropertyView";
    public final static String ViewAliasName = "bp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleBinaryPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte[] getValue() throws SQLException {
        return getBinary( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt8Array( getValue( ) );
    }

    @Override
    public BinaryPropertyObject getDataObject( ) throws SQLException {
        return new BinaryPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
