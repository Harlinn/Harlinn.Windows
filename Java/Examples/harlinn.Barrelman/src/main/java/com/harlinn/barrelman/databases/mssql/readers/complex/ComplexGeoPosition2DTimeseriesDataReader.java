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
package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexGeoPosition2DTimeseriesDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  gp2d.[Id], \r\n" +
            "  gp2d.[EntityType], \r\n" +
            "  gp2d.[RowVersion], \r\n" +
            "  gp2d.[Catalog], \r\n" +
            "  gp2d.[Name], \r\n" +
            "  gp2d.[MaxRetention], \r\n" +
            "  aatnpt.[AidToNavigation] \r\n" +
            "FROM [GeoPosition2DTimeseriesView] gp2d \r\n" +
            "  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(gp2d.[Id] = aatnpt.[Id] ) \r\n";

    public final static String BaseViewName = "GeoPosition2DTimeseriesView";
    public final static String ViewAliasName = "gp2d";

    public final static int GP2D_ID_FIELD_ID = 1;
    public final static int GP2D_KIND_FIELD_ID = 2;
    public final static int GP2D_ROWVERSION_FIELD_ID = 3;
    public final static int GP2D_CATALOG_FIELD_ID = 4;
    public final static int GP2D_NAME_FIELD_ID = 5;
    public final static int GP2D_MAXRETENTION_FIELD_ID = 6;
    public final static int AATNPT_AIDTONAVIGATION_FIELD_ID = 7;

    public ComplexGeoPosition2DTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( GP2D_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( GP2D_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( GP2D_ROWVERSION_FIELD_ID );
    }

    public Guid getCatalog( ) throws SQLException {
        return getNullableGuid( GP2D_CATALOG_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( GP2D_NAME_FIELD_ID );
    }

    public TimeSpan getMaxRetention( ) throws SQLException {
        return getTimeSpan( GP2D_MAXRETENTION_FIELD_ID );
    }

    public Guid getAisAidToNavigationPositionTimeseriesAidToNavigation( ) throws SQLException {
        return getNullableGuid( AATNPT_AIDTONAVIGATION_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.GeoPosition2DTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.AisAidToNavigationPositionTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getAisAidToNavigationPositionTimeseriesAidToNavigation( ) );
            }
            break;
            default: {
                var exc = new SQLException( "Cannot perform serialization for kind=" + kind + "." );
                throw exc;
            }
        }
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public GeoPosition2DTimeseriesObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.GeoPosition2DTimeseries: {
                return new GeoPosition2DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.AisAidToNavigationPositionTimeseries: {
                return new AisAidToNavigationPositionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getAisAidToNavigationPositionTimeseriesAidToNavigation( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

