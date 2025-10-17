package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrackerFilterParametersConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tfpc.[Id], \r\n" +
            "  tfpc.[RowVersion], \r\n" +
            "  tfpc.[Parameters], \r\n" +
            "  tfpc.[Timestamp], \r\n" +
            "  tfpc.[UseNaivePredictor], \r\n" +
            "  tfpc.[NumberOfPoints], \r\n" +
            "  tfpc.[WindowSize], \r\n" +
            "  tfpc.[StabilizeCount], \r\n" +
            "  tfpc.[MaxBadPoints], \r\n" +
            "  tfpc.[ModelType], \r\n" +
            "  tfpc.[SigmaR], \r\n" +
            "  tfpc.[SigmaAcc], \r\n" +
            "  tfpc.[TauVel], \r\n" +
            "  tfpc.[TauAcc], \r\n" +
            "  tfpc.[DeltaRMin], \r\n" +
            "  tfpc.[DeltaVMax], \r\n" +
            "  tfpc.[DeltaAMax] \r\n" +
            "FROM [TrackerFilterParametersConfigurationView] tfpc \r\n";

    public final static String BaseViewName = "TrackerFilterParametersConfigurationView";
    public final static String ViewAliasName = "tfpc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int PARAMETERS_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int USENAIVEPREDICTOR_FIELD_ID = 5;
    public final static int NUMBEROFPOINTS_FIELD_ID = 6;
    public final static int WINDOWSIZE_FIELD_ID = 7;
    public final static int STABILIZECOUNT_FIELD_ID = 8;
    public final static int MAXBADPOINTS_FIELD_ID = 9;
    public final static int MODELTYPE_FIELD_ID = 10;
    public final static int SIGMAR_FIELD_ID = 11;
    public final static int SIGMAACC_FIELD_ID = 12;
    public final static int TAUVEL_FIELD_ID = 13;
    public final static int TAUACC_FIELD_ID = 14;
    public final static int DELTARMIN_FIELD_ID = 15;
    public final static int DELTAVMAX_FIELD_ID = 16;
    public final static int DELTAAMAX_FIELD_ID = 17;

    public SimpleTrackerFilterParametersConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getParameters() throws SQLException {
        return getGuid( PARAMETERS_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final boolean getUseNaivePredictor() throws SQLException {
        return getBoolean( USENAIVEPREDICTOR_FIELD_ID );
    }

    public final int getNumberOfPoints() throws SQLException {
        return getInt32( NUMBEROFPOINTS_FIELD_ID );
    }

    public final int getWindowSize() throws SQLException {
        return getInt32( WINDOWSIZE_FIELD_ID );
    }

    public final int getStabilizeCount() throws SQLException {
        return getInt32( STABILIZECOUNT_FIELD_ID );
    }

    public final int getMaxBadPoints() throws SQLException {
        return getInt32( MAXBADPOINTS_FIELD_ID );
    }

    public final int getModelType() throws SQLException {
        return getInt32( MODELTYPE_FIELD_ID );
    }

    public final double getSigmaR() throws SQLException {
        return getDouble( SIGMAR_FIELD_ID );
    }

    public final double getSigmaAcc() throws SQLException {
        return getDouble( SIGMAACC_FIELD_ID );
    }

    public final double getTauVel() throws SQLException {
        return getDouble( TAUVEL_FIELD_ID );
    }

    public final double getTauAcc() throws SQLException {
        return getDouble( TAUACC_FIELD_ID );
    }

    public final double getDeltaRMin() throws SQLException {
        return getDouble( DELTARMIN_FIELD_ID );
    }

    public final double getDeltaVMax() throws SQLException {
        return getDouble( DELTAVMAX_FIELD_ID );
    }

    public final double getDeltaAMax() throws SQLException {
        return getDouble( DELTAAMAX_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackerFilterParametersConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getParameters( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeBoolean( getUseNaivePredictor( ) );
        destination.writeInt32( getNumberOfPoints( ) );
        destination.writeInt32( getWindowSize( ) );
        destination.writeInt32( getStabilizeCount( ) );
        destination.writeInt32( getMaxBadPoints( ) );
        destination.writeInt32( getModelType( ) );
        destination.writeDouble( getSigmaR( ) );
        destination.writeDouble( getSigmaAcc( ) );
        destination.writeDouble( getTauVel( ) );
        destination.writeDouble( getTauAcc( ) );
        destination.writeDouble( getDeltaRMin( ) );
        destination.writeDouble( getDeltaVMax( ) );
        destination.writeDouble( getDeltaAMax( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
