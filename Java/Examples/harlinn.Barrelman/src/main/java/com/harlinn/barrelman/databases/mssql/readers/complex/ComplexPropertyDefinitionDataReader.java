package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexPropertyDefinitionDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  pd.[Id], \r\n" +
            "  pd.[EntityType], \r\n" +
            "  pd.[RowVersion], \r\n" +
            "  pd.[ElementType], \r\n" +
            "  pd.[Name], \r\n" +
            "  bopd.[DefaultValue], \r\n" +
            "  bypd.[DefaultValue], \r\n" +
            "  bypd.[MinValue], \r\n" +
            "  bypd.[MaxValue], \r\n" +
            "  dtpd.[DefaultValue], \r\n" +
            "  dtpd.[MinValue], \r\n" +
            "  dtpd.[MaxValue], \r\n" +
            "  dpd.[DefaultValue], \r\n" +
            "  dpd.[MinValue], \r\n" +
            "  dpd.[MaxValue], \r\n" +
            "  gpd.[DefaultValue], \r\n" +
            "  i16pd.[DefaultValue], \r\n" +
            "  i16pd.[MinValue], \r\n" +
            "  i16pd.[MaxValue], \r\n" +
            "  i32pd.[DefaultValue], \r\n" +
            "  i32pd.[MinValue], \r\n" +
            "  i32pd.[MaxValue], \r\n" +
            "  i64pd.[DefaultValue], \r\n" +
            "  i64pd.[MinValue], \r\n" +
            "  i64pd.[MaxValue], \r\n" +
            "  rpd.[DefaultValue], \r\n" +
            "  rpd.[ReferencedElementType], \r\n" +
            "  sbpd.[DefaultValue], \r\n" +
            "  sbpd.[MinValue], \r\n" +
            "  sbpd.[MaxValue], \r\n" +
            "  sipd.[DefaultValue], \r\n" +
            "  sipd.[MinValue], \r\n" +
            "  sipd.[MaxValue], \r\n" +
            "  stpd.[DefaultValue], \r\n" +
            "  stpd.[Pattern], \r\n" +
            "  bytpd.[MinValue], \r\n" +
            "  bytpd.[MaxValue], \r\n" +
            "  dttpd.[MinValue], \r\n" +
            "  dttpd.[MaxValue], \r\n" +
            "  dotpd.[MinValue], \r\n" +
            "  dotpd.[MaxValue], \r\n" +
            "  i16tpd.[MinValue], \r\n" +
            "  i16tpd.[MaxValue], \r\n" +
            "  i32tpd.[MinValue], \r\n" +
            "  i32tpd.[MaxValue], \r\n" +
            "  i64tpd.[MinValue], \r\n" +
            "  i64tpd.[MaxValue], \r\n" +
            "  rtpd.[ReferencedElementType], \r\n" +
            "  sbtpd.[MinValue], \r\n" +
            "  sbtpd.[MaxValue], \r\n" +
            "  sitpd.[MinValue], \r\n" +
            "  sitpd.[MaxValue], \r\n" +
            "  sttpd.[Pattern], \r\n" +
            "  tstpd.[MinValue], \r\n" +
            "  tstpd.[MaxValue], \r\n" +
            "  u16tpd.[MinValue], \r\n" +
            "  u16tpd.[MaxValue], \r\n" +
            "  u32tpd.[MinValue], \r\n" +
            "  u32tpd.[MaxValue], \r\n" +
            "  u64tpd.[MinValue], \r\n" +
            "  u64tpd.[MaxValue], \r\n" +
            "  tspd.[DefaultValue], \r\n" +
            "  tspd.[MinValue], \r\n" +
            "  tspd.[MaxValue], \r\n" +
            "  u16pd.[DefaultValue], \r\n" +
            "  u16pd.[MinValue], \r\n" +
            "  u16pd.[MaxValue], \r\n" +
            "  u32pd.[DefaultValue], \r\n" +
            "  u32pd.[MinValue], \r\n" +
            "  u32pd.[MaxValue], \r\n" +
            "  u64pd.[DefaultValue], \r\n" +
            "  u64pd.[MinValue], \r\n" +
            "  u64pd.[MaxValue], \r\n" +
            "  pd.[Description], \r\n" +
            "  bpd.[DefaultValue] \r\n" +
            "FROM [PropertyDefinitionView] pd \r\n" +
            "  LEFT JOIN [BinaryPropertyDefinition] bpd ON(pd.[Id] = bpd.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanPropertyDefinition] bopd ON(pd.[Id] = bopd.[Id] ) \r\n" +
            "  LEFT JOIN [BytePropertyDefinition] bypd ON(pd.[Id] = bypd.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimePropertyDefinition] dtpd ON(pd.[Id] = dtpd.[Id] ) \r\n" +
            "  LEFT JOIN [DoublePropertyDefinition] dpd ON(pd.[Id] = dpd.[Id] ) \r\n" +
            "  LEFT JOIN [GuidPropertyDefinition] gpd ON(pd.[Id] = gpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int16PropertyDefinition] i16pd ON(pd.[Id] = i16pd.[Id] ) \r\n" +
            "  LEFT JOIN [Int32PropertyDefinition] i32pd ON(pd.[Id] = i32pd.[Id] ) \r\n" +
            "  LEFT JOIN [Int64PropertyDefinition] i64pd ON(pd.[Id] = i64pd.[Id] ) \r\n" +
            "  LEFT JOIN [ReferencePropertyDefinition] rpd ON(pd.[Id] = rpd.[Id] ) \r\n" +
            "  LEFT JOIN [SBytePropertyDefinition] sbpd ON(pd.[Id] = sbpd.[Id] ) \r\n" +
            "  LEFT JOIN [SinglePropertyDefinition] sipd ON(pd.[Id] = sipd.[Id] ) \r\n" +
            "  LEFT JOIN [StringPropertyDefinition] stpd ON(pd.[Id] = stpd.[Id] ) \r\n" +
            "  LEFT JOIN [TimeseriesPropertyDefinition] tpd ON(pd.[Id] = tpd.[Id] ) \r\n" +
            "  LEFT JOIN [BinaryTimeseriesPropertyDefinition] btpd ON(pd.[Id] = btpd.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseriesPropertyDefinition] botpd ON(pd.[Id] = botpd.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseriesPropertyDefinition] bytpd ON(pd.[Id] = bytpd.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseriesPropertyDefinition] dttpd ON(pd.[Id] = dttpd.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseriesPropertyDefinition] dotpd ON(pd.[Id] = dotpd.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseriesPropertyDefinition] gtpd ON(pd.[Id] = gtpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int16TimeseriesPropertyDefinition] i16tpd ON(pd.[Id] = i16tpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int32TimeseriesPropertyDefinition] i32tpd ON(pd.[Id] = i32tpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int64TimeseriesPropertyDefinition] i64tpd ON(pd.[Id] = i64tpd.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseriesPropertyDefinition] rtpd ON(pd.[Id] = rtpd.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseriesPropertyDefinition] sbtpd ON(pd.[Id] = sbtpd.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseriesPropertyDefinition] sitpd ON(pd.[Id] = sitpd.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseriesPropertyDefinition] sttpd ON(pd.[Id] = sttpd.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseriesPropertyDefinition] tstpd ON(pd.[Id] = tstpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16TimeseriesPropertyDefinition] u16tpd ON(pd.[Id] = u16tpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32TimeseriesPropertyDefinition] u32tpd ON(pd.[Id] = u32tpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64TimeseriesPropertyDefinition] u64tpd ON(pd.[Id] = u64tpd.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanPropertyDefinition] tspd ON(pd.[Id] = tspd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16PropertyDefinition] u16pd ON(pd.[Id] = u16pd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32PropertyDefinition] u32pd ON(pd.[Id] = u32pd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64PropertyDefinition] u64pd ON(pd.[Id] = u64pd.[Id] ) \r\n";

    public final static String BaseViewName = "PropertyDefinitionView";
    public final static String ViewAliasName = "pd";

    public final static int PD_ID_FIELD_ID = 1;
    public final static int PD_KIND_FIELD_ID = 2;
    public final static int PD_ROWVERSION_FIELD_ID = 3;
    public final static int PD_ELEMENTTYPE_FIELD_ID = 4;
    public final static int PD_NAME_FIELD_ID = 5;
    public final static int BOPD_DEFAULTVALUE_FIELD_ID = 6;
    public final static int BYPD_DEFAULTVALUE_FIELD_ID = 7;
    public final static int BYPD_MINVALUE_FIELD_ID = 8;
    public final static int BYPD_MAXVALUE_FIELD_ID = 9;
    public final static int DTPD_DEFAULTVALUE_FIELD_ID = 10;
    public final static int DTPD_MINVALUE_FIELD_ID = 11;
    public final static int DTPD_MAXVALUE_FIELD_ID = 12;
    public final static int DPD_DEFAULTVALUE_FIELD_ID = 13;
    public final static int DPD_MINVALUE_FIELD_ID = 14;
    public final static int DPD_MAXVALUE_FIELD_ID = 15;
    public final static int GPD_DEFAULTVALUE_FIELD_ID = 16;
    public final static int I16PD_DEFAULTVALUE_FIELD_ID = 17;
    public final static int I16PD_MINVALUE_FIELD_ID = 18;
    public final static int I16PD_MAXVALUE_FIELD_ID = 19;
    public final static int I32PD_DEFAULTVALUE_FIELD_ID = 20;
    public final static int I32PD_MINVALUE_FIELD_ID = 21;
    public final static int I32PD_MAXVALUE_FIELD_ID = 22;
    public final static int I64PD_DEFAULTVALUE_FIELD_ID = 23;
    public final static int I64PD_MINVALUE_FIELD_ID = 24;
    public final static int I64PD_MAXVALUE_FIELD_ID = 25;
    public final static int RPD_DEFAULTVALUE_FIELD_ID = 26;
    public final static int RPD_REFERENCEDELEMENTTYPE_FIELD_ID = 27;
    public final static int SBPD_DEFAULTVALUE_FIELD_ID = 28;
    public final static int SBPD_MINVALUE_FIELD_ID = 29;
    public final static int SBPD_MAXVALUE_FIELD_ID = 30;
    public final static int SIPD_DEFAULTVALUE_FIELD_ID = 31;
    public final static int SIPD_MINVALUE_FIELD_ID = 32;
    public final static int SIPD_MAXVALUE_FIELD_ID = 33;
    public final static int STPD_DEFAULTVALUE_FIELD_ID = 34;
    public final static int STPD_PATTERN_FIELD_ID = 35;
    public final static int BYTPD_MINVALUE_FIELD_ID = 36;
    public final static int BYTPD_MAXVALUE_FIELD_ID = 37;
    public final static int DTTPD_MINVALUE_FIELD_ID = 38;
    public final static int DTTPD_MAXVALUE_FIELD_ID = 39;
    public final static int DOTPD_MINVALUE_FIELD_ID = 40;
    public final static int DOTPD_MAXVALUE_FIELD_ID = 41;
    public final static int I16TPD_MINVALUE_FIELD_ID = 42;
    public final static int I16TPD_MAXVALUE_FIELD_ID = 43;
    public final static int I32TPD_MINVALUE_FIELD_ID = 44;
    public final static int I32TPD_MAXVALUE_FIELD_ID = 45;
    public final static int I64TPD_MINVALUE_FIELD_ID = 46;
    public final static int I64TPD_MAXVALUE_FIELD_ID = 47;
    public final static int RTPD_REFERENCEDELEMENTTYPE_FIELD_ID = 48;
    public final static int SBTPD_MINVALUE_FIELD_ID = 49;
    public final static int SBTPD_MAXVALUE_FIELD_ID = 50;
    public final static int SITPD_MINVALUE_FIELD_ID = 51;
    public final static int SITPD_MAXVALUE_FIELD_ID = 52;
    public final static int STTPD_PATTERN_FIELD_ID = 53;
    public final static int TSTPD_MINVALUE_FIELD_ID = 54;
    public final static int TSTPD_MAXVALUE_FIELD_ID = 55;
    public final static int U16TPD_MINVALUE_FIELD_ID = 56;
    public final static int U16TPD_MAXVALUE_FIELD_ID = 57;
    public final static int U32TPD_MINVALUE_FIELD_ID = 58;
    public final static int U32TPD_MAXVALUE_FIELD_ID = 59;
    public final static int U64TPD_MINVALUE_FIELD_ID = 60;
    public final static int U64TPD_MAXVALUE_FIELD_ID = 61;
    public final static int TSPD_DEFAULTVALUE_FIELD_ID = 62;
    public final static int TSPD_MINVALUE_FIELD_ID = 63;
    public final static int TSPD_MAXVALUE_FIELD_ID = 64;
    public final static int U16PD_DEFAULTVALUE_FIELD_ID = 65;
    public final static int U16PD_MINVALUE_FIELD_ID = 66;
    public final static int U16PD_MAXVALUE_FIELD_ID = 67;
    public final static int U32PD_DEFAULTVALUE_FIELD_ID = 68;
    public final static int U32PD_MINVALUE_FIELD_ID = 69;
    public final static int U32PD_MAXVALUE_FIELD_ID = 70;
    public final static int U64PD_DEFAULTVALUE_FIELD_ID = 71;
    public final static int U64PD_MINVALUE_FIELD_ID = 72;
    public final static int U64PD_MAXVALUE_FIELD_ID = 73;
    public final static int PD_DESCRIPTION_FIELD_ID = 74;
    public final static int BPD_DEFAULTVALUE_FIELD_ID = 75;

    public ComplexPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( PD_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( PD_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( PD_ROWVERSION_FIELD_ID );
    }

    public Guid getElementType( ) throws SQLException {
        return getGuid( PD_ELEMENTTYPE_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( PD_NAME_FIELD_ID );
    }

    public String getDescription( ) throws SQLException {
        return getString( PD_DESCRIPTION_FIELD_ID );
    }

    public byte[] getBinaryPropertyDefinitionDefaultValue( ) throws SQLException {
        return getBinary( BPD_DEFAULTVALUE_FIELD_ID );
    }

    public boolean getBooleanPropertyDefinitionDefaultValue( ) throws SQLException {
        return getBoolean( BOPD_DEFAULTVALUE_FIELD_ID );
    }

    public byte getBytePropertyDefinitionDefaultValue( ) throws SQLException {
        return getUInt8( BYPD_DEFAULTVALUE_FIELD_ID );
    }

    public byte getBytePropertyDefinitionMinValue( ) throws SQLException {
        return getUInt8( BYPD_MINVALUE_FIELD_ID );
    }

    public byte getBytePropertyDefinitionMaxValue( ) throws SQLException {
        return getUInt8( BYPD_MAXVALUE_FIELD_ID );
    }

    public String getDateTimePropertyDefinitionDefaultValue( ) throws SQLException {
        return getString( DTPD_DEFAULTVALUE_FIELD_ID );
    }

    public String getDateTimePropertyDefinitionMinValue( ) throws SQLException {
        return getString( DTPD_MINVALUE_FIELD_ID );
    }

    public String getDateTimePropertyDefinitionMaxValue( ) throws SQLException {
        return getString( DTPD_MAXVALUE_FIELD_ID );
    }

    public double getDoublePropertyDefinitionDefaultValue( ) throws SQLException {
        return getDouble( DPD_DEFAULTVALUE_FIELD_ID );
    }

    public double getDoublePropertyDefinitionMinValue( ) throws SQLException {
        return getDouble( DPD_MINVALUE_FIELD_ID );
    }

    public double getDoublePropertyDefinitionMaxValue( ) throws SQLException {
        return getDouble( DPD_MAXVALUE_FIELD_ID );
    }

    public Guid getGuidPropertyDefinitionDefaultValue( ) throws SQLException {
        return getGuid( GPD_DEFAULTVALUE_FIELD_ID );
    }

    public short getInt16PropertyDefinitionDefaultValue( ) throws SQLException {
        return getInt16( I16PD_DEFAULTVALUE_FIELD_ID );
    }

    public short getInt16PropertyDefinitionMinValue( ) throws SQLException {
        return getInt16( I16PD_MINVALUE_FIELD_ID );
    }

    public short getInt16PropertyDefinitionMaxValue( ) throws SQLException {
        return getInt16( I16PD_MAXVALUE_FIELD_ID );
    }

    public int getInt32PropertyDefinitionDefaultValue( ) throws SQLException {
        return getInt32( I32PD_DEFAULTVALUE_FIELD_ID );
    }

    public int getInt32PropertyDefinitionMinValue( ) throws SQLException {
        return getInt32( I32PD_MINVALUE_FIELD_ID );
    }

    public int getInt32PropertyDefinitionMaxValue( ) throws SQLException {
        return getInt32( I32PD_MAXVALUE_FIELD_ID );
    }

    public long getInt64PropertyDefinitionDefaultValue( ) throws SQLException {
        return getInt64( I64PD_DEFAULTVALUE_FIELD_ID );
    }

    public long getInt64PropertyDefinitionMinValue( ) throws SQLException {
        return getInt64( I64PD_MINVALUE_FIELD_ID );
    }

    public long getInt64PropertyDefinitionMaxValue( ) throws SQLException {
        return getInt64( I64PD_MAXVALUE_FIELD_ID );
    }

    public Guid getReferencePropertyDefinitionDefaultValue( ) throws SQLException {
        return getNullableGuid( RPD_DEFAULTVALUE_FIELD_ID );
    }

    public Guid getReferencePropertyDefinitionReferencedElementType( ) throws SQLException {
        return getNullableGuid( RPD_REFERENCEDELEMENTTYPE_FIELD_ID );
    }

    public byte getSBytePropertyDefinitionDefaultValue( ) throws SQLException {
        return getInt8( SBPD_DEFAULTVALUE_FIELD_ID );
    }

    public byte getSBytePropertyDefinitionMinValue( ) throws SQLException {
        return getInt8( SBPD_MINVALUE_FIELD_ID );
    }

    public byte getSBytePropertyDefinitionMaxValue( ) throws SQLException {
        return getInt8( SBPD_MAXVALUE_FIELD_ID );
    }

    public float getSinglePropertyDefinitionDefaultValue( ) throws SQLException {
        return getSingle( SIPD_DEFAULTVALUE_FIELD_ID );
    }

    public float getSinglePropertyDefinitionMinValue( ) throws SQLException {
        return getSingle( SIPD_MINVALUE_FIELD_ID );
    }

    public float getSinglePropertyDefinitionMaxValue( ) throws SQLException {
        return getSingle( SIPD_MAXVALUE_FIELD_ID );
    }

    public String getStringPropertyDefinitionDefaultValue( ) throws SQLException {
        return getString( STPD_DEFAULTVALUE_FIELD_ID );
    }

    public String getStringPropertyDefinitionPattern( ) throws SQLException {
        return getString( STPD_PATTERN_FIELD_ID );
    }

    public byte getByteTimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getUInt8( BYTPD_MINVALUE_FIELD_ID );
    }

    public byte getByteTimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getUInt8( BYTPD_MAXVALUE_FIELD_ID );
    }

    public String getDateTimeTimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getString( DTTPD_MINVALUE_FIELD_ID );
    }

    public String getDateTimeTimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getString( DTTPD_MAXVALUE_FIELD_ID );
    }

    public double getDoubleTimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getDouble( DOTPD_MINVALUE_FIELD_ID );
    }

    public double getDoubleTimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getDouble( DOTPD_MAXVALUE_FIELD_ID );
    }

    public short getInt16TimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getInt16( I16TPD_MINVALUE_FIELD_ID );
    }

    public short getInt16TimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getInt16( I16TPD_MAXVALUE_FIELD_ID );
    }

    public int getInt32TimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getInt32( I32TPD_MINVALUE_FIELD_ID );
    }

    public int getInt32TimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getInt32( I32TPD_MAXVALUE_FIELD_ID );
    }

    public long getInt64TimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getInt64( I64TPD_MINVALUE_FIELD_ID );
    }

    public long getInt64TimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getInt64( I64TPD_MAXVALUE_FIELD_ID );
    }

    public Guid getReferenceTimeseriesPropertyDefinitionReferencedElementType( ) throws SQLException {
        return getNullableGuid( RTPD_REFERENCEDELEMENTTYPE_FIELD_ID );
    }

    public byte getSByteTimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getInt8( SBTPD_MINVALUE_FIELD_ID );
    }

    public byte getSByteTimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getInt8( SBTPD_MAXVALUE_FIELD_ID );
    }

    public float getSingleTimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getSingle( SITPD_MINVALUE_FIELD_ID );
    }

    public float getSingleTimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getSingle( SITPD_MAXVALUE_FIELD_ID );
    }

    public String getStringTimeseriesPropertyDefinitionPattern( ) throws SQLException {
        return getString( STTPD_PATTERN_FIELD_ID );
    }

    public TimeSpan getTimeSpanTimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getTimeSpan( TSTPD_MINVALUE_FIELD_ID );
    }

    public TimeSpan getTimeSpanTimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getTimeSpan( TSTPD_MAXVALUE_FIELD_ID );
    }

    public short getUInt16TimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getUInt16( U16TPD_MINVALUE_FIELD_ID );
    }

    public short getUInt16TimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getUInt16( U16TPD_MAXVALUE_FIELD_ID );
    }

    public int getUInt32TimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getUInt32( U32TPD_MINVALUE_FIELD_ID );
    }

    public int getUInt32TimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getUInt32( U32TPD_MAXVALUE_FIELD_ID );
    }

    public long getUInt64TimeseriesPropertyDefinitionMinValue( ) throws SQLException {
        return getInt64( U64TPD_MINVALUE_FIELD_ID );
    }

    public long getUInt64TimeseriesPropertyDefinitionMaxValue( ) throws SQLException {
        return getInt64( U64TPD_MAXVALUE_FIELD_ID );
    }

    public TimeSpan getTimeSpanPropertyDefinitionDefaultValue( ) throws SQLException {
        return getTimeSpan( TSPD_DEFAULTVALUE_FIELD_ID );
    }

    public TimeSpan getTimeSpanPropertyDefinitionMinValue( ) throws SQLException {
        return getTimeSpan( TSPD_MINVALUE_FIELD_ID );
    }

    public TimeSpan getTimeSpanPropertyDefinitionMaxValue( ) throws SQLException {
        return getTimeSpan( TSPD_MAXVALUE_FIELD_ID );
    }

    public short getUInt16PropertyDefinitionDefaultValue( ) throws SQLException {
        return getUInt16( U16PD_DEFAULTVALUE_FIELD_ID );
    }

    public short getUInt16PropertyDefinitionMinValue( ) throws SQLException {
        return getUInt16( U16PD_MINVALUE_FIELD_ID );
    }

    public short getUInt16PropertyDefinitionMaxValue( ) throws SQLException {
        return getUInt16( U16PD_MAXVALUE_FIELD_ID );
    }

    public int getUInt32PropertyDefinitionDefaultValue( ) throws SQLException {
        return getUInt32( U32PD_DEFAULTVALUE_FIELD_ID );
    }

    public int getUInt32PropertyDefinitionMinValue( ) throws SQLException {
        return getUInt32( U32PD_MINVALUE_FIELD_ID );
    }

    public int getUInt32PropertyDefinitionMaxValue( ) throws SQLException {
        return getUInt32( U32PD_MAXVALUE_FIELD_ID );
    }

    public long getUInt64PropertyDefinitionDefaultValue( ) throws SQLException {
        return getInt64( U64PD_DEFAULTVALUE_FIELD_ID );
    }

    public long getUInt64PropertyDefinitionMinValue( ) throws SQLException {
        return getInt64( U64PD_MINVALUE_FIELD_ID );
    }

    public long getUInt64PropertyDefinitionMaxValue( ) throws SQLException {
        return getInt64( U64PD_MAXVALUE_FIELD_ID );
    }

}

