/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexTimeseriesPropertyDefinitionDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  tpd.[Id], \r\n" +
            "  tpd.[EntityType], \r\n" +
            "  tpd.[RowVersion], \r\n" +
            "  tpd.[ElementType], \r\n" +
            "  tpd.[Name], \r\n" +
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
            "  tpd.[Description] \r\n" +
            "FROM [TimeseriesPropertyDefinitionView] tpd \r\n" +
            "  LEFT JOIN [BinaryTimeseriesPropertyDefinition] btpd ON(tpd.[Id] = btpd.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseriesPropertyDefinition] botpd ON(tpd.[Id] = botpd.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseriesPropertyDefinition] bytpd ON(tpd.[Id] = bytpd.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseriesPropertyDefinition] dttpd ON(tpd.[Id] = dttpd.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseriesPropertyDefinition] dotpd ON(tpd.[Id] = dotpd.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseriesPropertyDefinition] gtpd ON(tpd.[Id] = gtpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int16TimeseriesPropertyDefinition] i16tpd ON(tpd.[Id] = i16tpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int32TimeseriesPropertyDefinition] i32tpd ON(tpd.[Id] = i32tpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int64TimeseriesPropertyDefinition] i64tpd ON(tpd.[Id] = i64tpd.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseriesPropertyDefinition] rtpd ON(tpd.[Id] = rtpd.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseriesPropertyDefinition] sbtpd ON(tpd.[Id] = sbtpd.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseriesPropertyDefinition] sitpd ON(tpd.[Id] = sitpd.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseriesPropertyDefinition] sttpd ON(tpd.[Id] = sttpd.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseriesPropertyDefinition] tstpd ON(tpd.[Id] = tstpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16TimeseriesPropertyDefinition] u16tpd ON(tpd.[Id] = u16tpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32TimeseriesPropertyDefinition] u32tpd ON(tpd.[Id] = u32tpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64TimeseriesPropertyDefinition] u64tpd ON(tpd.[Id] = u64tpd.[Id] ) \r\n";

    public final static String BaseViewName = "TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "tpd";

    public final static int TPD_ID_FIELD_ID = 1;
    public final static int TPD_KIND_FIELD_ID = 2;
    public final static int TPD_ROWVERSION_FIELD_ID = 3;
    public final static int TPD_ELEMENTTYPE_FIELD_ID = 4;
    public final static int TPD_NAME_FIELD_ID = 5;
    public final static int BYTPD_MINVALUE_FIELD_ID = 6;
    public final static int BYTPD_MAXVALUE_FIELD_ID = 7;
    public final static int DTTPD_MINVALUE_FIELD_ID = 8;
    public final static int DTTPD_MAXVALUE_FIELD_ID = 9;
    public final static int DOTPD_MINVALUE_FIELD_ID = 10;
    public final static int DOTPD_MAXVALUE_FIELD_ID = 11;
    public final static int I16TPD_MINVALUE_FIELD_ID = 12;
    public final static int I16TPD_MAXVALUE_FIELD_ID = 13;
    public final static int I32TPD_MINVALUE_FIELD_ID = 14;
    public final static int I32TPD_MAXVALUE_FIELD_ID = 15;
    public final static int I64TPD_MINVALUE_FIELD_ID = 16;
    public final static int I64TPD_MAXVALUE_FIELD_ID = 17;
    public final static int RTPD_REFERENCEDELEMENTTYPE_FIELD_ID = 18;
    public final static int SBTPD_MINVALUE_FIELD_ID = 19;
    public final static int SBTPD_MAXVALUE_FIELD_ID = 20;
    public final static int SITPD_MINVALUE_FIELD_ID = 21;
    public final static int SITPD_MAXVALUE_FIELD_ID = 22;
    public final static int STTPD_PATTERN_FIELD_ID = 23;
    public final static int TSTPD_MINVALUE_FIELD_ID = 24;
    public final static int TSTPD_MAXVALUE_FIELD_ID = 25;
    public final static int U16TPD_MINVALUE_FIELD_ID = 26;
    public final static int U16TPD_MAXVALUE_FIELD_ID = 27;
    public final static int U32TPD_MINVALUE_FIELD_ID = 28;
    public final static int U32TPD_MAXVALUE_FIELD_ID = 29;
    public final static int U64TPD_MINVALUE_FIELD_ID = 30;
    public final static int U64TPD_MAXVALUE_FIELD_ID = 31;
    public final static int TPD_DESCRIPTION_FIELD_ID = 32;

    public ComplexTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( TPD_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( TPD_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( TPD_ROWVERSION_FIELD_ID );
    }

    public Guid getElementType( ) throws SQLException {
        return getGuid( TPD_ELEMENTTYPE_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( TPD_NAME_FIELD_ID );
    }

    public String getDescription( ) throws SQLException {
        return getString( TPD_DESCRIPTION_FIELD_ID );
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

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BinaryTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
            }
            break;
            case Kind.BooleanTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
            }
            break;
            case Kind.ByteTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeUInt8( getByteTimeseriesPropertyDefinitionMinValue( ) );
                destination.writeUInt8( getByteTimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.DateTimeTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeStringUtf8( getDateTimeTimeseriesPropertyDefinitionMinValue( ) );
                destination.writeStringUtf8( getDateTimeTimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.DoubleTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeDouble( getDoubleTimeseriesPropertyDefinitionMinValue( ) );
                destination.writeDouble( getDoubleTimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.GuidTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
            }
            break;
            case Kind.Int16TimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeInt16( getInt16TimeseriesPropertyDefinitionMinValue( ) );
                destination.writeInt16( getInt16TimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.Int32TimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeInt32( getInt32TimeseriesPropertyDefinitionMinValue( ) );
                destination.writeInt32( getInt32TimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.Int64TimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeInt64( getInt64TimeseriesPropertyDefinitionMinValue( ) );
                destination.writeInt64( getInt64TimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.ReferenceTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeNullableGuid( getReferenceTimeseriesPropertyDefinitionReferencedElementType( ) );
            }
            break;
            case Kind.SByteTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeInt8( getSByteTimeseriesPropertyDefinitionMinValue( ) );
                destination.writeInt8( getSByteTimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.SingleTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeSingle( getSingleTimeseriesPropertyDefinitionMinValue( ) );
                destination.writeSingle( getSingleTimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.StringTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeStringUtf8( getStringTimeseriesPropertyDefinitionPattern( ) );
            }
            break;
            case Kind.TimeSpanTimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeTimeSpan( getTimeSpanTimeseriesPropertyDefinitionMinValue( ) );
                destination.writeTimeSpan( getTimeSpanTimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.UInt16TimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeUInt16( getUInt16TimeseriesPropertyDefinitionMinValue( ) );
                destination.writeUInt16( getUInt16TimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.UInt32TimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeUInt32( getUInt32TimeseriesPropertyDefinitionMinValue( ) );
                destination.writeUInt32( getUInt32TimeseriesPropertyDefinitionMaxValue( ) );
            }
            break;
            case Kind.UInt64TimeseriesPropertyDefinition: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getElementType( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeInt64( getUInt64TimeseriesPropertyDefinitionMinValue( ) );
                destination.writeInt64( getUInt64TimeseriesPropertyDefinitionMaxValue( ) );
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

    public TimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BinaryTimeseriesPropertyDefinition: {
                return new BinaryTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ) );
            }
            case Kind.BooleanTimeseriesPropertyDefinition: {
                return new BooleanTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ) );
            }
            case Kind.ByteTimeseriesPropertyDefinition: {
                return new ByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getByteTimeseriesPropertyDefinitionMinValue( ), getByteTimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.DateTimeTimeseriesPropertyDefinition: {
                return new DateTimeTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDateTimeTimeseriesPropertyDefinitionMinValue( ), getDateTimeTimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.DoubleTimeseriesPropertyDefinition: {
                return new DoubleTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDoubleTimeseriesPropertyDefinitionMinValue( ), getDoubleTimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.GuidTimeseriesPropertyDefinition: {
                return new GuidTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ) );
            }
            case Kind.Int16TimeseriesPropertyDefinition: {
                return new Int16TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getInt16TimeseriesPropertyDefinitionMinValue( ), getInt16TimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.Int32TimeseriesPropertyDefinition: {
                return new Int32TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getInt32TimeseriesPropertyDefinitionMinValue( ), getInt32TimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.Int64TimeseriesPropertyDefinition: {
                return new Int64TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getInt64TimeseriesPropertyDefinitionMinValue( ), getInt64TimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.ReferenceTimeseriesPropertyDefinition: {
                return new ReferenceTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getReferenceTimeseriesPropertyDefinitionReferencedElementType( ) );
            }
            case Kind.SByteTimeseriesPropertyDefinition: {
                return new SByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getSByteTimeseriesPropertyDefinitionMinValue( ), getSByteTimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.SingleTimeseriesPropertyDefinition: {
                return new SingleTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getSingleTimeseriesPropertyDefinitionMinValue( ), getSingleTimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.StringTimeseriesPropertyDefinition: {
                return new StringTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getStringTimeseriesPropertyDefinitionPattern( ) );
            }
            case Kind.TimeSpanTimeseriesPropertyDefinition: {
                return new TimeSpanTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getTimeSpanTimeseriesPropertyDefinitionMinValue( ), getTimeSpanTimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.UInt16TimeseriesPropertyDefinition: {
                return new UInt16TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getUInt16TimeseriesPropertyDefinitionMinValue( ), getUInt16TimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.UInt32TimeseriesPropertyDefinition: {
                return new UInt32TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getUInt32TimeseriesPropertyDefinitionMinValue( ), getUInt32TimeseriesPropertyDefinitionMaxValue( ) );
            }
            case Kind.UInt64TimeseriesPropertyDefinition: {
                return new UInt64TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getUInt64TimeseriesPropertyDefinitionMinValue( ), getUInt64TimeseriesPropertyDefinitionMaxValue( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

