package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisAidToNavigationOffPositionTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aatnopt.[Id], \r\n" +
            "  aatnopt.[EntityType], \r\n" +
            "  aatnopt.[RowVersion], \r\n" +
            "  aatnopt.[Catalog], \r\n" +
            "  aatnopt.[Name], \r\n" +
            "  aatnopt.[MaxRetention], \r\n" +
            "  aatnopt.[AidToNavigation] \r\n" +
            "FROM [AisAidToNavigationOffPositionTimeseriesView] aatnopt \r\n";

    public final static String BaseViewName = "AisAidToNavigationOffPositionTimeseriesView";
    public final static String ViewAliasName = "aatnopt";

    public final static int AIDTONAVIGATION_FIELD_ID = 7;

    public SimpleAisAidToNavigationOffPositionTimeseriesDataReader( ResultSet resultSet ) {
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
    public AisAidToNavigationOffPositionTimeseriesObject GetDataObject( ) throws SQLException {
        return new AisAidToNavigationOffPositionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getAidToNavigation( ) );
    }

}
