package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleVesselDataReader extends SimpleTrackableItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vsl.[Id], \r\n" +
            "  vsl.[EntityType], \r\n" +
            "  vsl.[RowVersion], \r\n" +
            "  vsl.[Name], \r\n" +
            "  vsl.[Type], \r\n" +
            "  vsl.[ToBow], \r\n" +
            "  vsl.[ToStern], \r\n" +
            "  vsl.[ToPort], \r\n" +
            "  vsl.[ToStarboard], \r\n" +
            "  vsl.[DraughtTimeseries], \r\n" +
            "  vsl.[PersonsOnBoardTimeseries] \r\n" +
            "FROM [VesselView] vsl \r\n";

    public final static String BaseViewName = "VesselView";
    public final static String ViewAliasName = "vsl";

    public final static int NAME_FIELD_ID = 4;
    public final static int TYPE_FIELD_ID = 5;
    public final static int TOBOW_FIELD_ID = 6;
    public final static int TOSTERN_FIELD_ID = 7;
    public final static int TOPORT_FIELD_ID = 8;
    public final static int TOSTARBOARD_FIELD_ID = 9;
    public final static int DRAUGHTTIMESERIES_FIELD_ID = 10;
    public final static int PERSONSONBOARDTIMESERIES_FIELD_ID = 11;

    public SimpleVesselDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final Guid getTypeField() throws SQLException {
        return getNullableGuid( TYPE_FIELD_ID );
    }

    public final int getToBow() throws SQLException {
        return getInt32( TOBOW_FIELD_ID );
    }

    public final int getToStern() throws SQLException {
        return getInt32( TOSTERN_FIELD_ID );
    }

    public final int getToPort() throws SQLException {
        return getInt32( TOPORT_FIELD_ID );
    }

    public final int getToStarboard() throws SQLException {
        return getInt32( TOSTARBOARD_FIELD_ID );
    }

    public final Guid getDraughtTimeseries() throws SQLException {
        return getNullableGuid( DRAUGHTTIMESERIES_FIELD_ID );
    }

    public final Guid getPersonsOnBoardTimeseries() throws SQLException {
        return getNullableGuid( PERSONSONBOARDTIMESERIES_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getName( ) );
        destination.writeNullableGuid( getTypeField( ) );
        destination.writeInt32( getToBow( ) );
        destination.writeInt32( getToStern( ) );
        destination.writeInt32( getToPort( ) );
        destination.writeInt32( getToStarboard( ) );
        destination.writeNullableGuid( getDraughtTimeseries( ) );
        destination.writeNullableGuid( getPersonsOnBoardTimeseries( ) );
    }

    @Override
    public VesselObject getDataObject( ) throws SQLException {
        return new VesselObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getTypeField( ), getToBow( ), getToStern( ), getToPort( ), getToStarboard( ), getDraughtTimeseries( ), getPersonsOnBoardTimeseries( ) );
    }

}
