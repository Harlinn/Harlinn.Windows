package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexTimeseriesPropertyDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  tp.[Id], \r\n" +
            "  tp.[EntityType], \r\n" +
            "  tp.[RowVersion], \r\n" +
            "  tp.[Element], \r\n" +
            "  tp.[Definition], \r\n" +
            "  btp.[Timeseries], \r\n" +
            "  botp.[Timeseries], \r\n" +
            "  bytp.[Timeseries], \r\n" +
            "  dttp.[Timeseries], \r\n" +
            "  dotp.[Timeseries], \r\n" +
            "  gtp.[Timeseries], \r\n" +
            "  i16tp.[Timeseries], \r\n" +
            "  i32tp.[Timeseries], \r\n" +
            "  i64tp.[Timeseries], \r\n" +
            "  rtp.[Timeseries], \r\n" +
            "  sbtp.[Timeseries], \r\n" +
            "  sitp.[Timeseries], \r\n" +
            "  sttp.[Timeseries], \r\n" +
            "  tstp.[Timeseries], \r\n" +
            "  u16tp.[Timeseries], \r\n" +
            "  u32tp.[Timeseries], \r\n" +
            "  u64tp.[Timeseries] \r\n" +
            "FROM [TimeseriesPropertyView] tp \r\n" +
            "  LEFT JOIN [BinaryTimeseriesProperty] btp ON(tp.[Id] = btp.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseriesProperty] botp ON(tp.[Id] = botp.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseriesProperty] bytp ON(tp.[Id] = bytp.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseriesProperty] dttp ON(tp.[Id] = dttp.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseriesProperty] dotp ON(tp.[Id] = dotp.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseriesProperty] gtp ON(tp.[Id] = gtp.[Id] ) \r\n" +
            "  LEFT JOIN [Int16TimeseriesProperty] i16tp ON(tp.[Id] = i16tp.[Id] ) \r\n" +
            "  LEFT JOIN [Int32TimeseriesProperty] i32tp ON(tp.[Id] = i32tp.[Id] ) \r\n" +
            "  LEFT JOIN [Int64TimeseriesProperty] i64tp ON(tp.[Id] = i64tp.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseriesProperty] rtp ON(tp.[Id] = rtp.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseriesProperty] sbtp ON(tp.[Id] = sbtp.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseriesProperty] sitp ON(tp.[Id] = sitp.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseriesProperty] sttp ON(tp.[Id] = sttp.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseriesProperty] tstp ON(tp.[Id] = tstp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16TimeseriesProperty] u16tp ON(tp.[Id] = u16tp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32TimeseriesProperty] u32tp ON(tp.[Id] = u32tp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64TimeseriesProperty] u64tp ON(tp.[Id] = u64tp.[Id] ) \r\n";

    public final static String BaseViewName = "TimeseriesPropertyView";
    public final static String ViewAliasName = "tp";

    public final static int TP_ID_FIELD_ID = 1;
    public final static int TP_KIND_FIELD_ID = 2;
    public final static int TP_ROWVERSION_FIELD_ID = 3;
    public final static int TP_ELEMENT_FIELD_ID = 4;
    public final static int TP_DEFINITION_FIELD_ID = 5;
    public final static int BTP_TIMESERIES_FIELD_ID = 6;
    public final static int BOTP_TIMESERIES_FIELD_ID = 7;
    public final static int BYTP_TIMESERIES_FIELD_ID = 8;
    public final static int DTTP_TIMESERIES_FIELD_ID = 9;
    public final static int DOTP_TIMESERIES_FIELD_ID = 10;
    public final static int GTP_TIMESERIES_FIELD_ID = 11;
    public final static int I16TP_TIMESERIES_FIELD_ID = 12;
    public final static int I32TP_TIMESERIES_FIELD_ID = 13;
    public final static int I64TP_TIMESERIES_FIELD_ID = 14;
    public final static int RTP_TIMESERIES_FIELD_ID = 15;
    public final static int SBTP_TIMESERIES_FIELD_ID = 16;
    public final static int SITP_TIMESERIES_FIELD_ID = 17;
    public final static int STTP_TIMESERIES_FIELD_ID = 18;
    public final static int TSTP_TIMESERIES_FIELD_ID = 19;
    public final static int U16TP_TIMESERIES_FIELD_ID = 20;
    public final static int U32TP_TIMESERIES_FIELD_ID = 21;
    public final static int U64TP_TIMESERIES_FIELD_ID = 22;

    public ComplexTimeseriesPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( TP_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( TP_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( TP_ROWVERSION_FIELD_ID );
    }

    public Guid getElement( ) throws SQLException {
        return getGuid( TP_ELEMENT_FIELD_ID );
    }

    public Guid getDefinition( ) throws SQLException {
        return getGuid( TP_DEFINITION_FIELD_ID );
    }

    public Guid getBinaryTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( BTP_TIMESERIES_FIELD_ID );
    }

    public Guid getBooleanTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( BOTP_TIMESERIES_FIELD_ID );
    }

    public Guid getByteTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( BYTP_TIMESERIES_FIELD_ID );
    }

    public Guid getDateTimeTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( DTTP_TIMESERIES_FIELD_ID );
    }

    public Guid getDoubleTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( DOTP_TIMESERIES_FIELD_ID );
    }

    public Guid getGuidTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( GTP_TIMESERIES_FIELD_ID );
    }

    public Guid getInt16TimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( I16TP_TIMESERIES_FIELD_ID );
    }

    public Guid getInt32TimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( I32TP_TIMESERIES_FIELD_ID );
    }

    public Guid getInt64TimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( I64TP_TIMESERIES_FIELD_ID );
    }

    public Guid getReferenceTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( RTP_TIMESERIES_FIELD_ID );
    }

    public Guid getSByteTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( SBTP_TIMESERIES_FIELD_ID );
    }

    public Guid getSingleTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( SITP_TIMESERIES_FIELD_ID );
    }

    public Guid getStringTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( STTP_TIMESERIES_FIELD_ID );
    }

    public Guid getTimeSpanTimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( TSTP_TIMESERIES_FIELD_ID );
    }

    public Guid getUInt16TimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( U16TP_TIMESERIES_FIELD_ID );
    }

    public Guid getUInt32TimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( U32TP_TIMESERIES_FIELD_ID );
    }

    public Guid getUInt64TimeseriesPropertyTimeseries( ) throws SQLException {
        return getNullableGuid( U64TP_TIMESERIES_FIELD_ID );
    }

}

