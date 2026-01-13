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

public class SimpleTrackingServiceOptionsDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tso.[Id], \r\n" +
            "  tso.[RowVersion], \r\n" +
            "  tso.[Timestamp], \r\n" +
            "  tso.[TimerInterval], \r\n" +
            "  tso.[MaxAgeOfCurrentTrackValue], \r\n" +
            "  tso.[FalseThreshold], \r\n" +
            "  tso.[DistanceThreshold], \r\n" +
            "  tso.[DistanceUnmergeThreshold], \r\n" +
            "  tso.[UnmergeLatency], \r\n" +
            "  tso.[KalmanFiltering], \r\n" +
            "  tso.[MaxCourseDeviation], \r\n" +
            "  tso.[MaxSpeedDeviation], \r\n" +
            "  tso.[MinimumSpeedThreshold] \r\n" +
            "FROM [TrackingServiceOptionsView] tso \r\n";

    public final static String BaseViewName = "TrackingServiceOptionsView";
    public final static String ViewAliasName = "tso";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TIMESTAMP_FIELD_ID = 3;
    public final static int TIMERINTERVAL_FIELD_ID = 4;
    public final static int MAXAGEOFCURRENTTRACKVALUE_FIELD_ID = 5;
    public final static int FALSETHRESHOLD_FIELD_ID = 6;
    public final static int DISTANCETHRESHOLD_FIELD_ID = 7;
    public final static int DISTANCEUNMERGETHRESHOLD_FIELD_ID = 8;
    public final static int UNMERGELATENCY_FIELD_ID = 9;
    public final static int KALMANFILTERING_FIELD_ID = 10;
    public final static int MAXCOURSEDEVIATION_FIELD_ID = 11;
    public final static int MAXSPEEDDEVIATION_FIELD_ID = 12;
    public final static int MINIMUMSPEEDTHRESHOLD_FIELD_ID = 13;

    public SimpleTrackingServiceOptionsDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final TimeSpan getTimerInterval() throws SQLException {
        return getTimeSpan( TIMERINTERVAL_FIELD_ID );
    }

    public final TimeSpan getMaxAgeOfCurrentTrackValue() throws SQLException {
        return getTimeSpan( MAXAGEOFCURRENTTRACKVALUE_FIELD_ID );
    }

    public final double getFalseThreshold() throws SQLException {
        return getDouble( FALSETHRESHOLD_FIELD_ID );
    }

    public final double getDistanceThreshold() throws SQLException {
        return getDouble( DISTANCETHRESHOLD_FIELD_ID );
    }

    public final double getDistanceUnmergeThreshold() throws SQLException {
        return getDouble( DISTANCEUNMERGETHRESHOLD_FIELD_ID );
    }

    public final long getUnmergeLatency() throws SQLException {
        return getInt64( UNMERGELATENCY_FIELD_ID );
    }

    public final boolean getKalmanFiltering() throws SQLException {
        return getBoolean( KALMANFILTERING_FIELD_ID );
    }

    public final double getMaxCourseDeviation() throws SQLException {
        return getDouble( MAXCOURSEDEVIATION_FIELD_ID );
    }

    public final double getMaxSpeedDeviation() throws SQLException {
        return getDouble( MAXSPEEDDEVIATION_FIELD_ID );
    }

    public final double getMinimumSpeedThreshold() throws SQLException {
        return getDouble( MINIMUMSPEEDTHRESHOLD_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackingServiceOptions );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeTimeSpan( getTimerInterval( ) );
        destination.writeTimeSpan( getMaxAgeOfCurrentTrackValue( ) );
        destination.writeDouble( getFalseThreshold( ) );
        destination.writeDouble( getDistanceThreshold( ) );
        destination.writeDouble( getDistanceUnmergeThreshold( ) );
        destination.writeInt64( getUnmergeLatency( ) );
        destination.writeBoolean( getKalmanFiltering( ) );
        destination.writeDouble( getMaxCourseDeviation( ) );
        destination.writeDouble( getMaxSpeedDeviation( ) );
        destination.writeDouble( getMinimumSpeedThreshold( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public TrackingServiceOptionsObject getDataObject( ) throws SQLException {
            return new TrackingServiceOptionsObject( ObjectState.Stored, getId( ), getRowVersion( ), getTimestamp( ), getTimerInterval( ), getMaxAgeOfCurrentTrackValue( ), getFalseThreshold( ), getDistanceThreshold( ), getDistanceUnmergeThreshold( ), getUnmergeLatency( ), getKalmanFiltering( ), getMaxCourseDeviation( ), getMaxSpeedDeviation( ), getMinimumSpeedThreshold( ) );
    }

}
