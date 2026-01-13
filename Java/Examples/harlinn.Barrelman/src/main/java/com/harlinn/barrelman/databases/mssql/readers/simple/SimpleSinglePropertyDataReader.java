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

public class SimpleSinglePropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sip.[Id], \r\n" +
            "  sip.[EntityType], \r\n" +
            "  sip.[RowVersion], \r\n" +
            "  sip.[Element], \r\n" +
            "  sip.[Definition], \r\n" +
            "  sip.[Value] \r\n" +
            "FROM [SinglePropertyView] sip \r\n";

    public final static String BaseViewName = "SinglePropertyView";
    public final static String ViewAliasName = "sip";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleSinglePropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final float getValue() throws SQLException {
        return getSingle( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeSingle( getValue( ) );
    }

    @Override
    public SinglePropertyObject getDataObject( ) throws SQLException {
        return new SinglePropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
