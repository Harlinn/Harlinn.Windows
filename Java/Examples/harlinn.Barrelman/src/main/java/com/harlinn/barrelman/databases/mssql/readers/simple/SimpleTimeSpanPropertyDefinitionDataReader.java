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

public class SimpleTimeSpanPropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tspd.[Id], \r\n" +
            "  tspd.[EntityType], \r\n" +
            "  tspd.[RowVersion], \r\n" +
            "  tspd.[ElementType], \r\n" +
            "  tspd.[Name], \r\n" +
            "  tspd.[Description], \r\n" +
            "  tspd.[DefaultValue], \r\n" +
            "  tspd.[MinValue], \r\n" +
            "  tspd.[MaxValue] \r\n" +
            "FROM [TimeSpanPropertyDefinitionView] tspd \r\n";

    public final static String BaseViewName = "TimeSpanPropertyDefinitionView";
    public final static String ViewAliasName = "tspd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleTimeSpanPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final TimeSpan getDefaultValue() throws SQLException {
        return getTimeSpan( DEFAULTVALUE_FIELD_ID );
    }

    public final TimeSpan getMinValue() throws SQLException {
        return getTimeSpan( MINVALUE_FIELD_ID );
    }

    public final TimeSpan getMaxValue() throws SQLException {
        return getTimeSpan( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeTimeSpan( getDefaultValue( ) );
        destination.writeTimeSpan( getMinValue( ) );
        destination.writeTimeSpan( getMaxValue( ) );
    }

    @Override
    public TimeSpanPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new TimeSpanPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getMinValue( ), getMaxValue( ) );
    }

}
