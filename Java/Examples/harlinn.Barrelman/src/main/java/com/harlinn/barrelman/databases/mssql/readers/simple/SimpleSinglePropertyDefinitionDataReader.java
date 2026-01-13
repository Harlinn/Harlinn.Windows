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

public class SimpleSinglePropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sipd.[Id], \r\n" +
            "  sipd.[EntityType], \r\n" +
            "  sipd.[RowVersion], \r\n" +
            "  sipd.[ElementType], \r\n" +
            "  sipd.[Name], \r\n" +
            "  sipd.[Description], \r\n" +
            "  sipd.[DefaultValue], \r\n" +
            "  sipd.[MinValue], \r\n" +
            "  sipd.[MaxValue] \r\n" +
            "FROM [SinglePropertyDefinitionView] sipd \r\n";

    public final static String BaseViewName = "SinglePropertyDefinitionView";
    public final static String ViewAliasName = "sipd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleSinglePropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final float getDefaultValue() throws SQLException {
        return getSingle( DEFAULTVALUE_FIELD_ID );
    }

    public final float getMinValue() throws SQLException {
        return getSingle( MINVALUE_FIELD_ID );
    }

    public final float getMaxValue() throws SQLException {
        return getSingle( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeSingle( getDefaultValue( ) );
        destination.writeSingle( getMinValue( ) );
        destination.writeSingle( getMaxValue( ) );
    }

    @Override
    public SinglePropertyDefinitionObject getDataObject( ) throws SQLException {
        return new SinglePropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getMinValue( ), getMaxValue( ) );
    }

}
