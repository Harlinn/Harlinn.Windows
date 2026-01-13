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

public class SimpleGuidPropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gpd.[Id], \r\n" +
            "  gpd.[EntityType], \r\n" +
            "  gpd.[RowVersion], \r\n" +
            "  gpd.[ElementType], \r\n" +
            "  gpd.[Name], \r\n" +
            "  gpd.[Description], \r\n" +
            "  gpd.[DefaultValue] \r\n" +
            "FROM [GuidPropertyDefinitionView] gpd \r\n";

    public final static String BaseViewName = "GuidPropertyDefinitionView";
    public final static String ViewAliasName = "gpd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;

    public SimpleGuidPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getDefaultValue() throws SQLException {
        return getGuid( DEFAULTVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeGuid( getDefaultValue( ) );
    }

    @Override
    public GuidPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new GuidPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ) );
    }

}
