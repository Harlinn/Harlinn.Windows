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

public class SimpleCircularZoneDataReader extends SimpleZoneDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cz.[Id], \r\n" +
            "  cz.[EntityType], \r\n" +
            "  cz.[RowVersion], \r\n" +
            "  cz.[Name], \r\n" +
            "  cz.[Longitude], \r\n" +
            "  cz.[Latitude], \r\n" +
            "  cz.[AlarmType], \r\n" +
            "  cz.[AlarmTime], \r\n" +
            "  cz.[RadarTrackMinimumLifetime], \r\n" +
            "  cz.[Speed], \r\n" +
            "  cz.[StrokeColor], \r\n" +
            "  cz.[FillColor], \r\n" +
            "  cz.[Radius] \r\n" +
            "FROM [CircularZoneView] cz \r\n";

    public final static String BaseViewName = "CircularZoneView";
    public final static String ViewAliasName = "cz";

    public final static int RADIUS_FIELD_ID = 13;

    public SimpleCircularZoneDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final double getRadius() throws SQLException {
        return getDouble( RADIUS_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeDouble( getRadius( ) );
    }

    @Override
    public CircularZoneObject getDataObject( ) throws SQLException {
        return new CircularZoneObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getLongitude( ), getLatitude( ), getAlarmType( ), getAlarmTime( ), getRadarTrackMinimumLifetime( ), getSpeed( ), getStrokeColor( ), getFillColor( ), getRadius( ) );
    }

}
