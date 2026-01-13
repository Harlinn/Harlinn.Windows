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

public class SimpleDateTimePropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dtpd.[Id], \r\n" +
            "  dtpd.[EntityType], \r\n" +
            "  dtpd.[RowVersion], \r\n" +
            "  dtpd.[ElementType], \r\n" +
            "  dtpd.[Name], \r\n" +
            "  dtpd.[Description], \r\n" +
            "  dtpd.[DefaultValue], \r\n" +
            "  dtpd.[MinValue], \r\n" +
            "  dtpd.[MaxValue] \r\n" +
            "FROM [DateTimePropertyDefinitionView] dtpd \r\n";

    public final static String BaseViewName = "DateTimePropertyDefinitionView";
    public final static String ViewAliasName = "dtpd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleDateTimePropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getDefaultValue() throws SQLException {
        return getString( DEFAULTVALUE_FIELD_ID );
    }

    public final String getMinValue() throws SQLException {
        return getString( MINVALUE_FIELD_ID );
    }

    public final String getMaxValue() throws SQLException {
        return getString( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getDefaultValue( ) );
        destination.writeStringUtf8( getMinValue( ) );
        destination.writeStringUtf8( getMaxValue( ) );
    }

    @Override
    public DateTimePropertyDefinitionObject getDataObject( ) throws SQLException {
        return new DateTimePropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getMinValue( ), getMaxValue( ) );
    }

}
