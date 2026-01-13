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

public class SimpleDateTimePropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dtp.[Id], \r\n" +
            "  dtp.[EntityType], \r\n" +
            "  dtp.[RowVersion], \r\n" +
            "  dtp.[Element], \r\n" +
            "  dtp.[Definition], \r\n" +
            "  dtp.[Value] \r\n" +
            "FROM [DateTimePropertyView] dtp \r\n";

    public final static String BaseViewName = "DateTimePropertyView";
    public final static String ViewAliasName = "dtp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleDateTimePropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final DateTime getValue() throws SQLException {
        return getDateTimeFromLong( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeDateTime( getValue( ) );
    }

    @Override
    public DateTimePropertyObject getDataObject( ) throws SQLException {
        return new DateTimePropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
