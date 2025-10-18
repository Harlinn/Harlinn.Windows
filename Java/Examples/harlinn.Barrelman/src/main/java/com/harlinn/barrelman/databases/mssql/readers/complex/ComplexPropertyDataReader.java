package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexPropertyDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  p.[Id], \r\n" +
            "  p.[EntityType], \r\n" +
            "  p.[RowVersion], \r\n" +
            "  p.[Element], \r\n" +
            "  p.[Definition], \r\n" +
            "  bop.[Value], \r\n" +
            "  byp.[Value], \r\n" +
            "  dtp.[Value], \r\n" +
            "  dp.[Value], \r\n" +
            "  gp.[Value], \r\n" +
            "  i16p.[Value], \r\n" +
            "  i32p.[Value], \r\n" +
            "  i64p.[Value], \r\n" +
            "  rp.[Value], \r\n" +
            "  sp.[Value], \r\n" +
            "  sip.[Value], \r\n" +
            "  stp.[Value], \r\n" +
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
            "  u64tp.[Timeseries], \r\n" +
            "  tsp.[Value], \r\n" +
            "  u16p.[Value], \r\n" +
            "  u32p.[Value], \r\n" +
            "  u64p.[Value], \r\n" +
            "  bp.[Value] \r\n" +
            "FROM [PropertyView] p \r\n" +
            "  LEFT JOIN [BinaryProperty] bp ON(p.[Id] = bp.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanProperty] bop ON(p.[Id] = bop.[Id] ) \r\n" +
            "  LEFT JOIN [ByteProperty] byp ON(p.[Id] = byp.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeProperty] dtp ON(p.[Id] = dtp.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleProperty] dp ON(p.[Id] = dp.[Id] ) \r\n" +
            "  LEFT JOIN [GuidProperty] gp ON(p.[Id] = gp.[Id] ) \r\n" +
            "  LEFT JOIN [Int16Property] i16p ON(p.[Id] = i16p.[Id] ) \r\n" +
            "  LEFT JOIN [Int32Property] i32p ON(p.[Id] = i32p.[Id] ) \r\n" +
            "  LEFT JOIN [Int64Property] i64p ON(p.[Id] = i64p.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceProperty] rp ON(p.[Id] = rp.[Id] ) \r\n" +
            "  LEFT JOIN [SByteProperty] sp ON(p.[Id] = sp.[Id] ) \r\n" +
            "  LEFT JOIN [SingleProperty] sip ON(p.[Id] = sip.[Id] ) \r\n" +
            "  LEFT JOIN [StringProperty] stp ON(p.[Id] = stp.[Id] ) \r\n" +
            "  LEFT JOIN [TimeseriesProperty] tp ON(p.[Id] = tp.[Id] ) \r\n" +
            "  LEFT JOIN [BinaryTimeseriesProperty] btp ON(p.[Id] = btp.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseriesProperty] botp ON(p.[Id] = botp.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseriesProperty] bytp ON(p.[Id] = bytp.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseriesProperty] dttp ON(p.[Id] = dttp.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseriesProperty] dotp ON(p.[Id] = dotp.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseriesProperty] gtp ON(p.[Id] = gtp.[Id] ) \r\n" +
            "  LEFT JOIN [Int16TimeseriesProperty] i16tp ON(p.[Id] = i16tp.[Id] ) \r\n" +
            "  LEFT JOIN [Int32TimeseriesProperty] i32tp ON(p.[Id] = i32tp.[Id] ) \r\n" +
            "  LEFT JOIN [Int64TimeseriesProperty] i64tp ON(p.[Id] = i64tp.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseriesProperty] rtp ON(p.[Id] = rtp.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseriesProperty] sbtp ON(p.[Id] = sbtp.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseriesProperty] sitp ON(p.[Id] = sitp.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseriesProperty] sttp ON(p.[Id] = sttp.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseriesProperty] tstp ON(p.[Id] = tstp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16TimeseriesProperty] u16tp ON(p.[Id] = u16tp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32TimeseriesProperty] u32tp ON(p.[Id] = u32tp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64TimeseriesProperty] u64tp ON(p.[Id] = u64tp.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanProperty] tsp ON(p.[Id] = tsp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16Property] u16p ON(p.[Id] = u16p.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32Property] u32p ON(p.[Id] = u32p.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64Property] u64p ON(p.[Id] = u64p.[Id] ) \r\n";

    public final static String BaseViewName = "PropertyView";
    public final static String ViewAliasName = "p";

    public final static int P_ID_FIELD_ID = 1;
    public final static int P_KIND_FIELD_ID = 2;
    public final static int P_ROWVERSION_FIELD_ID = 3;
    public final static int P_ELEMENT_FIELD_ID = 4;
    public final static int P_DEFINITION_FIELD_ID = 5;
    public final static int BOP_VALUE_FIELD_ID = 6;
    public final static int BYP_VALUE_FIELD_ID = 7;
    public final static int DTP_VALUE_FIELD_ID = 8;
    public final static int DP_VALUE_FIELD_ID = 9;
    public final static int GP_VALUE_FIELD_ID = 10;
    public final static int I16P_VALUE_FIELD_ID = 11;
    public final static int I32P_VALUE_FIELD_ID = 12;
    public final static int I64P_VALUE_FIELD_ID = 13;
    public final static int RP_VALUE_FIELD_ID = 14;
    public final static int SP_VALUE_FIELD_ID = 15;
    public final static int SIP_VALUE_FIELD_ID = 16;
    public final static int STP_VALUE_FIELD_ID = 17;
    public final static int BTP_TIMESERIES_FIELD_ID = 18;
    public final static int BOTP_TIMESERIES_FIELD_ID = 19;
    public final static int BYTP_TIMESERIES_FIELD_ID = 20;
    public final static int DTTP_TIMESERIES_FIELD_ID = 21;
    public final static int DOTP_TIMESERIES_FIELD_ID = 22;
    public final static int GTP_TIMESERIES_FIELD_ID = 23;
    public final static int I16TP_TIMESERIES_FIELD_ID = 24;
    public final static int I32TP_TIMESERIES_FIELD_ID = 25;
    public final static int I64TP_TIMESERIES_FIELD_ID = 26;
    public final static int RTP_TIMESERIES_FIELD_ID = 27;
    public final static int SBTP_TIMESERIES_FIELD_ID = 28;
    public final static int SITP_TIMESERIES_FIELD_ID = 29;
    public final static int STTP_TIMESERIES_FIELD_ID = 30;
    public final static int TSTP_TIMESERIES_FIELD_ID = 31;
    public final static int U16TP_TIMESERIES_FIELD_ID = 32;
    public final static int U32TP_TIMESERIES_FIELD_ID = 33;
    public final static int U64TP_TIMESERIES_FIELD_ID = 34;
    public final static int TSP_VALUE_FIELD_ID = 35;
    public final static int U16P_VALUE_FIELD_ID = 36;
    public final static int U32P_VALUE_FIELD_ID = 37;
    public final static int U64P_VALUE_FIELD_ID = 38;
    public final static int BP_VALUE_FIELD_ID = 39;

    public ComplexPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( P_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( P_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( P_ROWVERSION_FIELD_ID );
    }

    public Guid getElement( ) throws SQLException {
        return getGuid( P_ELEMENT_FIELD_ID );
    }

    public Guid getDefinition( ) throws SQLException {
        return getGuid( P_DEFINITION_FIELD_ID );
    }

    public byte[] getBinaryPropertyValue( ) throws SQLException {
        return getBinary( BP_VALUE_FIELD_ID );
    }

    public boolean getBooleanPropertyValue( ) throws SQLException {
        return getBoolean( BOP_VALUE_FIELD_ID );
    }

    public byte getBytePropertyValue( ) throws SQLException {
        return getUInt8( BYP_VALUE_FIELD_ID );
    }

    public DateTime getDateTimePropertyValue( ) throws SQLException {
        return getDateTimeFromLong( DTP_VALUE_FIELD_ID );
    }

    public double getDoublePropertyValue( ) throws SQLException {
        return getDouble( DP_VALUE_FIELD_ID );
    }

    public Guid getGuidPropertyValue( ) throws SQLException {
        return getGuid( GP_VALUE_FIELD_ID );
    }

    public short getInt16PropertyValue( ) throws SQLException {
        return getInt16( I16P_VALUE_FIELD_ID );
    }

    public int getInt32PropertyValue( ) throws SQLException {
        return getInt32( I32P_VALUE_FIELD_ID );
    }

    public long getInt64PropertyValue( ) throws SQLException {
        return getInt64( I64P_VALUE_FIELD_ID );
    }

    public Guid getReferencePropertyValue( ) throws SQLException {
        return getNullableGuid( RP_VALUE_FIELD_ID );
    }

    public byte getSBytePropertyValue( ) throws SQLException {
        return getInt8( SP_VALUE_FIELD_ID );
    }

    public float getSinglePropertyValue( ) throws SQLException {
        return getSingle( SIP_VALUE_FIELD_ID );
    }

    public String getStringPropertyValue( ) throws SQLException {
        return getString( STP_VALUE_FIELD_ID );
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

    public TimeSpan getTimeSpanPropertyValue( ) throws SQLException {
        return getTimeSpan( TSP_VALUE_FIELD_ID );
    }

    public short getUInt16PropertyValue( ) throws SQLException {
        return getUInt16( U16P_VALUE_FIELD_ID );
    }

    public int getUInt32PropertyValue( ) throws SQLException {
        return getUInt32( U32P_VALUE_FIELD_ID );
    }

    public long getUInt64PropertyValue( ) throws SQLException {
        return getInt64( U64P_VALUE_FIELD_ID );
    }

}

