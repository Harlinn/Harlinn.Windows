package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexTrackBaseDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  tb.[Id], \r\n" +
            "  tb.[EntityType], \r\n" +
            "  tb.[RowVersion], \r\n" +
            "  tb.[Tracker], \r\n" +
            "  tb.[TrackNumber], \r\n" +
            "  tb.[Timestamp] \r\n" +
            "FROM [TrackBaseView] tb \r\n" +
            "  LEFT JOIN [Track] t ON(tb.[Id] = t.[Id] ) \r\n" +
            "  LEFT JOIN [Track3D] t3d ON(tb.[Id] = t3d.[Id] ) \r\n";

    public final static String BaseViewName = "TrackBaseView";
    public final static String ViewAliasName = "tb";

    public final static int TB_ID_FIELD_ID = 1;
    public final static int TB_KIND_FIELD_ID = 2;
    public final static int TB_ROWVERSION_FIELD_ID = 3;
    public final static int TB_TRACKER_FIELD_ID = 4;
    public final static int TB_TRACKNUMBER_FIELD_ID = 5;
    public final static int TB_TIMESTAMP_FIELD_ID = 6;

    public ComplexTrackBaseDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( TB_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( TB_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( TB_ROWVERSION_FIELD_ID );
    }

    public Guid getTracker( ) throws SQLException {
        return getGuid( TB_TRACKER_FIELD_ID );
    }

    public long getTrackNumber( ) throws SQLException {
        return getInt64( TB_TRACKNUMBER_FIELD_ID );
    }

    public DateTime getTimestamp( ) throws SQLException {
        return getDateTimeFromLong( TB_TIMESTAMP_FIELD_ID );
    }

}

