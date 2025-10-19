package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexTrackableItemDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  ti.[Id], \r\n" +
            "  ti.[EntityType], \r\n" +
            "  ti.[RowVersion], \r\n" +
            "  a.[Name], \r\n" +
            "  a.[Type], \r\n" +
            "  aatn.[Name], \r\n" +
            "  aatn.[MMSI], \r\n" +
            "  aatn.[NavigationalAidType], \r\n" +
            "  aatn.[Position], \r\n" +
            "  aatn.[IsVirtual], \r\n" +
            "  aatn.[ToBow], \r\n" +
            "  aatn.[ToStern], \r\n" +
            "  aatn.[ToPort], \r\n" +
            "  aatn.[ToStarboard], \r\n" +
            "  aatn.[OffPositionTimeseries], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[Type], \r\n" +
            "  vsl.[Name], \r\n" +
            "  vsl.[Type], \r\n" +
            "  vsl.[ToBow], \r\n" +
            "  vsl.[ToStern], \r\n" +
            "  vsl.[ToPort], \r\n" +
            "  vsl.[ToStarboard], \r\n" +
            "  vsl.[DraughtTimeseries], \r\n" +
            "  vsl.[PersonsOnBoardTimeseries] \r\n" +
            "FROM [TrackableItemView] ti \r\n" +
            "  LEFT JOIN [Aircraft] a ON(ti.[Id] = a.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigation] aatn ON(ti.[Id] = aatn.[Id] ) \r\n" +
            "  LEFT JOIN [Vehicle] v ON(ti.[Id] = v.[Id] ) \r\n" +
            "  LEFT JOIN [Vessel] vsl ON(ti.[Id] = vsl.[Id] ) \r\n";

    public final static String BaseViewName = "TrackableItemView";
    public final static String ViewAliasName = "ti";

    public final static int TI_ID_FIELD_ID = 1;
    public final static int TI_KIND_FIELD_ID = 2;
    public final static int TI_ROWVERSION_FIELD_ID = 3;
    public final static int A_NAME_FIELD_ID = 4;
    public final static int A_TYPE_FIELD_ID = 5;
    public final static int AATN_NAME_FIELD_ID = 6;
    public final static int AATN_MMSI_FIELD_ID = 7;
    public final static int AATN_NAVIGATIONALAIDTYPE_FIELD_ID = 8;
    public final static int AATN_POSITION_FIELD_ID = 9;
    public final static int AATN_ISVIRTUAL_FIELD_ID = 10;
    public final static int AATN_TOBOW_FIELD_ID = 11;
    public final static int AATN_TOSTERN_FIELD_ID = 12;
    public final static int AATN_TOPORT_FIELD_ID = 13;
    public final static int AATN_TOSTARBOARD_FIELD_ID = 14;
    public final static int AATN_OFFPOSITIONTIMESERIES_FIELD_ID = 15;
    public final static int V_NAME_FIELD_ID = 16;
    public final static int V_TYPE_FIELD_ID = 17;
    public final static int VSL_NAME_FIELD_ID = 18;
    public final static int VSL_TYPE_FIELD_ID = 19;
    public final static int VSL_TOBOW_FIELD_ID = 20;
    public final static int VSL_TOSTERN_FIELD_ID = 21;
    public final static int VSL_TOPORT_FIELD_ID = 22;
    public final static int VSL_TOSTARBOARD_FIELD_ID = 23;
    public final static int VSL_DRAUGHTTIMESERIES_FIELD_ID = 24;
    public final static int VSL_PERSONSONBOARDTIMESERIES_FIELD_ID = 25;

    public ComplexTrackableItemDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( TI_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( TI_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( TI_ROWVERSION_FIELD_ID );
    }

    public String getAircraftName( ) throws SQLException {
        return getString( A_NAME_FIELD_ID );
    }

    public Guid getAircraftType( ) throws SQLException {
        return getNullableGuid( A_TYPE_FIELD_ID );
    }

    public String getAisAidToNavigationName( ) throws SQLException {
        return getString( AATN_NAME_FIELD_ID );
    }

    public Guid getAisAidToNavigationMMSI( ) throws SQLException {
        return getNullableGuid( AATN_MMSI_FIELD_ID );
    }

    public int getAisAidToNavigationNavigationalAidType( ) throws SQLException {
        return getInt32( AATN_NAVIGATIONALAIDTYPE_FIELD_ID );
    }

    public Guid getAisAidToNavigationPosition( ) throws SQLException {
        return getNullableGuid( AATN_POSITION_FIELD_ID );
    }

    public boolean getAisAidToNavigationIsVirtual( ) throws SQLException {
        return getBoolean( AATN_ISVIRTUAL_FIELD_ID );
    }

    public int getAisAidToNavigationToBow( ) throws SQLException {
        return getInt32( AATN_TOBOW_FIELD_ID );
    }

    public int getAisAidToNavigationToStern( ) throws SQLException {
        return getInt32( AATN_TOSTERN_FIELD_ID );
    }

    public int getAisAidToNavigationToPort( ) throws SQLException {
        return getInt32( AATN_TOPORT_FIELD_ID );
    }

    public int getAisAidToNavigationToStarboard( ) throws SQLException {
        return getInt32( AATN_TOSTARBOARD_FIELD_ID );
    }

    public Guid getAisAidToNavigationOffPositionTimeseries( ) throws SQLException {
        return getNullableGuid( AATN_OFFPOSITIONTIMESERIES_FIELD_ID );
    }

    public String getVehicleName( ) throws SQLException {
        return getString( V_NAME_FIELD_ID );
    }

    public Guid getVehicleType( ) throws SQLException {
        return getNullableGuid( V_TYPE_FIELD_ID );
    }

    public String getVesselName( ) throws SQLException {
        return getString( VSL_NAME_FIELD_ID );
    }

    public Guid getVesselType( ) throws SQLException {
        return getNullableGuid( VSL_TYPE_FIELD_ID );
    }

    public int getVesselToBow( ) throws SQLException {
        return getInt32( VSL_TOBOW_FIELD_ID );
    }

    public int getVesselToStern( ) throws SQLException {
        return getInt32( VSL_TOSTERN_FIELD_ID );
    }

    public int getVesselToPort( ) throws SQLException {
        return getInt32( VSL_TOPORT_FIELD_ID );
    }

    public int getVesselToStarboard( ) throws SQLException {
        return getInt32( VSL_TOSTARBOARD_FIELD_ID );
    }

    public Guid getVesselDraughtTimeseries( ) throws SQLException {
        return getNullableGuid( VSL_DRAUGHTTIMESERIES_FIELD_ID );
    }

    public Guid getVesselPersonsOnBoardTimeseries( ) throws SQLException {
        return getNullableGuid( VSL_PERSONSONBOARDTIMESERIES_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.Aircraft: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getAircraftName( ) );
                destination.writeNullableGuid( getAircraftType( ) );
            }
            break;
            case Kind.AisAidToNavigation: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getAisAidToNavigationName( ) );
                destination.writeNullableGuid( getAisAidToNavigationMMSI( ) );
                destination.writeInt32( getAisAidToNavigationNavigationalAidType( ) );
                destination.writeNullableGuid( getAisAidToNavigationPosition( ) );
                destination.writeBoolean( getAisAidToNavigationIsVirtual( ) );
                destination.writeInt32( getAisAidToNavigationToBow( ) );
                destination.writeInt32( getAisAidToNavigationToStern( ) );
                destination.writeInt32( getAisAidToNavigationToPort( ) );
                destination.writeInt32( getAisAidToNavigationToStarboard( ) );
                destination.writeNullableGuid( getAisAidToNavigationOffPositionTimeseries( ) );
            }
            break;
            case Kind.Vehicle: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getVehicleName( ) );
                destination.writeNullableGuid( getVehicleType( ) );
            }
            break;
            case Kind.Vessel: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getVesselName( ) );
                destination.writeNullableGuid( getVesselType( ) );
                destination.writeInt32( getVesselToBow( ) );
                destination.writeInt32( getVesselToStern( ) );
                destination.writeInt32( getVesselToPort( ) );
                destination.writeInt32( getVesselToStarboard( ) );
                destination.writeNullableGuid( getVesselDraughtTimeseries( ) );
                destination.writeNullableGuid( getVesselPersonsOnBoardTimeseries( ) );
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

    public TrackableItemObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.Aircraft: {
                return new AircraftObject( ObjectState.Stored, getId( ), getRowVersion( ), getAircraftName( ), getAircraftType( ) );
            }
            case Kind.AisAidToNavigation: {
                return new AisAidToNavigationObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisAidToNavigationName( ), getAisAidToNavigationMMSI( ), getAisAidToNavigationNavigationalAidType( ), getAisAidToNavigationPosition( ), getAisAidToNavigationIsVirtual( ), getAisAidToNavigationToBow( ), getAisAidToNavigationToStern( ), getAisAidToNavigationToPort( ), getAisAidToNavigationToStarboard( ), getAisAidToNavigationOffPositionTimeseries( ) );
            }
            case Kind.Vehicle: {
                return new VehicleObject( ObjectState.Stored, getId( ), getRowVersion( ), getVehicleName( ), getVehicleType( ) );
            }
            case Kind.Vessel: {
                return new VesselObject( ObjectState.Stored, getId( ), getRowVersion( ), getVesselName( ), getVesselType( ), getVesselToBow( ), getVesselToStern( ), getVesselToPort( ), getVesselToStarboard( ), getVesselDraughtTimeseries( ), getVesselPersonsOnBoardTimeseries( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

