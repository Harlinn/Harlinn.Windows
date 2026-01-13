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

public class SimpleTimeSpanTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tstpd.[Id], \r\n" +
            "  tstpd.[EntityType], \r\n" +
            "  tstpd.[RowVersion], \r\n" +
            "  tstpd.[ElementType], \r\n" +
            "  tstpd.[Name], \r\n" +
            "  tstpd.[Description], \r\n" +
            "  tstpd.[MinValue], \r\n" +
            "  tstpd.[MaxValue] \r\n" +
            "FROM [TimeSpanTimeseriesPropertyDefinitionView] tstpd \r\n";

    public final static String BaseViewName = "TimeSpanTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "tstpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleTimeSpanTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
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
        destination.writeTimeSpan( getMinValue( ) );
        destination.writeTimeSpan( getMaxValue( ) );
    }

    @Override
    public TimeSpanTimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new TimeSpanTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
