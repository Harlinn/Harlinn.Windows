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

    public ViewObject GetDataObject( ) throws SQLException {
            return new ViewObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getLatitudeTimeseries( ), getLongitudeTimeseries( ), getZoomLevelTimeseries( ) );
    }

}
