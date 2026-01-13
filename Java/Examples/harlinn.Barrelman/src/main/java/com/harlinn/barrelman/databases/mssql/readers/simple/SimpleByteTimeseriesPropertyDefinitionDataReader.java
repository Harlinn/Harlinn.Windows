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

public class SimpleByteTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bytpd.[Id], \r\n" +
            "  bytpd.[EntityType], \r\n" +
            "  bytpd.[RowVersion], \r\n" +
            "  bytpd.[ElementType], \r\n" +
            "  bytpd.[Name], \r\n" +
            "  bytpd.[Description], \r\n" +
            "  bytpd.[MinValue], \r\n" +
            "  bytpd.[MaxValue] \r\n" +
            "FROM [ByteTimeseriesPropertyDefinitionView] bytpd \r\n";

    public final static String BaseViewName = "ByteTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "bytpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleByteTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte getMinValue() throws SQLException {
        return getUInt8( MINVALUE_FIELD_ID );
    }

    public final byte getMaxValue() throws SQLException {
        return getUInt8( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt8( getMinValue( ) );
        destination.writeUInt8( getMaxValue( ) );
    }

    @Override
    public ByteTimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new ByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
