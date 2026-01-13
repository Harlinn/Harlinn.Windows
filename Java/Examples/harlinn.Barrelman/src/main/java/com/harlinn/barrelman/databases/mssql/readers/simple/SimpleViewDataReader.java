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

public class SimpleViewDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  v.[Id], \r\n" +
            "  v.[RowVersion], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[LatitudeTimeseries], \r\n" +
            "  v.[LongitudeTimeseries], \r\n" +
            "  v.[ZoomLevelTimeseries] \r\n" +
            "FROM [ViewView] v \r\n";

    public final static String BaseViewName = "ViewView";
    public final static String ViewAliasName = "v";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int NAME_FIELD_ID = 3;
    public final static int LATITUDETIMESERIES_FIELD_ID = 4;
    public final static int LONGITUDETIMESERIES_FIELD_ID = 5;
    public final static int ZOOMLEVELTIMESERIES_FIELD_ID = 6;

    public SimpleViewDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final Guid getLatitudeTimeseries() throws SQLException {
        return getNullableGuid( LATITUDETIMESERIES_FIELD_ID );
    }

    public final Guid getLongitudeTimeseries() throws SQLException {
        return getNullableGuid( LONGITUDETIMESERIES_FIELD_ID );
    }

    public final Guid getZoomLevelTimeseries() throws SQLException {
        return getNullableGuid( ZOOMLEVELTIMESERIES_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.View );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeNullableGuid( getLatitudeTimeseries( ) );
        destination.writeNullableGuid( getLongitudeTimeseries( ) );
        destination.writeNullableGuid( getZoomLevelTimeseries( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public ViewObject getDataObject( ) throws SQLException {
            return new ViewObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getLatitudeTimeseries( ), getLongitudeTimeseries( ), getZoomLevelTimeseries( ) );
    }

}
