package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrack3DDataReader extends SimpleTrackBaseDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  t3d.[Id], \r\n" +
            "  t3d.[EntityType], \r\n" +
            "  t3d.[RowVersion], \r\n" +
            "  t3d.[Tracker], \r\n" +
            "  t3d.[TrackNumber], \r\n" +
            "  t3d.[Timestamp] \r\n" +
            "FROM [Track3DView] t3d \r\n";

    public final static String BaseViewName = "Track3DView";
    public final static String ViewAliasName = "t3d";

    public SimpleTrack3DDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public Track3DObject GetDataObject( ) throws SQLException {
        return new Track3DObject( ObjectState.Stored, getId( ), getRowVersion( ), getTracker( ), getTrackNumber( ), getTimestamp( ) );
    }

}
