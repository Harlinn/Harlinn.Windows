package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisAidToNavigationPositionTimeseriesDataReader extends SimpleGeoPosition2DTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aatnpt.[Id], \r\n" +
            "  aatnpt.[EntityType], \r\n" +
            "  aatnpt.[RowVersion], \r\n" +
            "  aatnpt.[Catalog], \r\n" +
            "  aatnpt.[Name], \r\n" +
            "  aatnpt.[MaxRetention], \r\n" +
            "  aatnpt.[AidToNavigation] \r\n" +
            "FROM [AisAidToNavigationPositionTimeseriesView] aatnpt \r\n";

    public final static String BaseViewName = "AisAidToNavigationPositionTimeseriesView";
    public final static String ViewAliasName = "aatnpt";

    public final static int AIDTONAVIGATION_FIELD_ID = 7;

    public SimpleAisAidToNavigationPositionTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getAidToNavigation() throws SQLException {
        return getNullableGuid( AIDTONAVIGATION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getAidToNavigation( ) );
    }

    @Override
    public AisAidToNavigationPositionTimeseriesObject GetDataObject( ) throws SQLException {
        return new AisAidToNavigationPositionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getAidToNavigation( ) );
    }

}
