package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexUInt32TimeseriesDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  u32t.[Id], \r\n" +
            "  u32t.[EntityType], \r\n" +
            "  u32t.[RowVersion], \r\n" +
            "  u32t.[Catalog], \r\n" +
            "  u32t.[Name], \r\n" +
            "  u32t.[MaxRetention], \r\n" +
            "  rst.[Radome] \r\n" +
            "FROM [UInt32TimeseriesView] u32t \r\n" +
            "  LEFT JOIN [RadomeStatusTimeseries] rst ON(u32t.[Id] = rst.[Id] ) \r\n";

    public final static String BaseViewName = "UInt32TimeseriesView";
    public final static String ViewAliasName = "u32t";

    public final static int U32T_ID_FIELD_ID = 1;
    public final static int U32T_KIND_FIELD_ID = 2;
    public final static int U32T_ROWVERSION_FIELD_ID = 3;
    public final static int U32T_CATALOG_FIELD_ID = 4;
    public final static int U32T_NAME_FIELD_ID = 5;
    public final static int U32T_MAXRETENTION_FIELD_ID = 6;
    public final static int RST_RADOME_FIELD_ID = 7;

    public ComplexUInt32TimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( U32T_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( U32T_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( U32T_ROWVERSION_FIELD_ID );
    }

    public Guid getCatalog( ) throws SQLException {
        return getNullableGuid( U32T_CATALOG_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( U32T_NAME_FIELD_ID );
    }

    public TimeSpan getMaxRetention( ) throws SQLException {
        return getTimeSpan( U32T_MAXRETENTION_FIELD_ID );
    }

    public Guid getRadomeStatusTimeseriesRadome( ) throws SQLException {
        return getNullableGuid( RST_RADOME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.UInt32Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.RadomeStatusTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadomeStatusTimeseriesRadome( ) );
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

    public UInt32TimeseriesObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.UInt32Timeseries: {
                return new UInt32TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.RadomeStatusTimeseries: {
                return new RadomeStatusTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadomeStatusTimeseriesRadome( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

