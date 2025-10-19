package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroDeviceConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gdc.[Id], \r\n" +
            "  gdc.[RowVersion], \r\n" +
            "  gdc.[GyroDevice], \r\n" +
            "  gdc.[Timestamp], \r\n" +
            "  gdc.[DefaultHeadingTrueNorth], \r\n" +
            "  gdc.[DefaultMagneticTrueNorth], \r\n" +
            "  gdc.[HeadingTrueNorthOffset], \r\n" +
            "  gdc.[HeadingMagneticNorthOffset], \r\n" +
            "  gdc.[PitchTransducerName], \r\n" +
            "  gdc.[RollTransducerName] \r\n" +
            "FROM [GyroDeviceConfigurationView] gdc \r\n";

    public final static String BaseViewName = "GyroDeviceConfigurationView";
    public final static String ViewAliasName = "gdc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int GYRODEVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int DEFAULTHEADINGTRUENORTH_FIELD_ID = 5;
    public final static int DEFAULTMAGNETICTRUENORTH_FIELD_ID = 6;
    public final static int HEADINGTRUENORTHOFFSET_FIELD_ID = 7;
    public final static int HEADINGMAGNETICNORTHOFFSET_FIELD_ID = 8;
    public final static int PITCHTRANSDUCERNAME_FIELD_ID = 9;
    public final static int ROLLTRANSDUCERNAME_FIELD_ID = 10;

    public SimpleGyroDeviceConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getGyroDevice() throws SQLException {
        return getGuid( GYRODEVICE_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final double getDefaultHeadingTrueNorth() throws SQLException {
        return getDouble( DEFAULTHEADINGTRUENORTH_FIELD_ID );
    }

    public final double getDefaultMagneticTrueNorth() throws SQLException {
        return getDouble( DEFAULTMAGNETICTRUENORTH_FIELD_ID );
    }

    public final double getHeadingTrueNorthOffset() throws SQLException {
        return getDouble( HEADINGTRUENORTHOFFSET_FIELD_ID );
    }

    public final double getHeadingMagneticNorthOffset() throws SQLException {
        return getDouble( HEADINGMAGNETICNORTHOFFSET_FIELD_ID );
    }

    public final String getPitchTransducerName() throws SQLException {
        return getString( PITCHTRANSDUCERNAME_FIELD_ID );
    }

    public final String getRollTransducerName() throws SQLException {
        return getString( ROLLTRANSDUCERNAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.GyroDeviceConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getGyroDevice( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeDouble( getDefaultHeadingTrueNorth( ) );
        destination.writeDouble( getDefaultMagneticTrueNorth( ) );
        destination.writeDouble( getHeadingTrueNorthOffset( ) );
        destination.writeDouble( getHeadingMagneticNorthOffset( ) );
        destination.writeStringUtf8( getPitchTransducerName( ) );
        destination.writeStringUtf8( getRollTransducerName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public GyroDeviceConfigurationObject getDataObject( ) throws SQLException {
            return new GyroDeviceConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getGyroDevice( ), getTimestamp( ), getDefaultHeadingTrueNorth( ), getDefaultMagneticTrueNorth( ), getHeadingTrueNorthOffset( ), getHeadingMagneticNorthOffset( ), getPitchTransducerName( ), getRollTransducerName( ) );
    }

}
