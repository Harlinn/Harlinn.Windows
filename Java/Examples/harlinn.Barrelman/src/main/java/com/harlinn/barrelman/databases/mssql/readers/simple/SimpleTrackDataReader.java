package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrackDataReader extends SimpleTrackBaseDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  t.[Id], \r\n" +
            "  t.[EntityType], \r\n" +
            "  t.[RowVersion], \r\n" +
            "  t.[Tracker], \r\n" +
            "  t.[TrackNumber], \r\n" +
            "  t.[Timestamp] \r\n" +
            "FROM [TrackView] t \r\n";

    public final static String BaseViewName = "TrackView";
    public final static String ViewAliasName = "t";

    public SimpleTrackDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public TrackObject getDataObject( ) throws SQLException {
        return new TrackObject( ObjectState.Stored, getId( ), getRowVersion( ), getTracker( ), getTrackNumber( ), getTimestamp( ) );
    }

}
