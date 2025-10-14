package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisPositionReportForLongRangeApplicationsMessageObject extends AisMessageObject {

    private int _positionAccuracy = PositionAccuracy.Low;
    private int _raim = Raim.NotInUse;
    private int _navigationStatus = NavigationStatus.UnderWayUsingEngine;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private double _speedOverGround = 0.0;
    private double _courseOverGround = 0.0;
    private int _gnssPositionStatus = GnssPositionStatus.CurrentGnssPosition;
    private int _spare = 0;

    @Override
    public int getObjectType( ) {
        return Kind.AisPositionReportForLongRangeApplicationsMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisPositionReportForLongRangeApplicationsMessageObject( );
    }

    public int getPositionAccuracy( ) {
        return _positionAccuracy;
    }
    public void setPositionAccuracy( int value ) {
        if( !Comparer.equalsInt32( _positionAccuracy, value ) ) {
            _positionAccuracy = value;
            onPropertyChanged( );
        }
    }

    public int getRaim( ) {
        return _raim;
    }
    public void setRaim( int value ) {
        if( !Comparer.equalsInt32( _raim, value ) ) {
            _raim = value;
            onPropertyChanged( );
        }
    }

    public int getNavigationStatus( ) {
        return _navigationStatus;
    }
    public void setNavigationStatus( int value ) {
        if( !Comparer.equalsInt32( _navigationStatus, value ) ) {
            _navigationStatus = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getSpeedOverGround( ) {
        return _speedOverGround;
    }
    public void setSpeedOverGround( double value ) {
        if( !Comparer.equalsDouble( _speedOverGround, value ) ) {
            _speedOverGround = value;
            onPropertyChanged( );
        }
    }

    public double getCourseOverGround( ) {
        return _courseOverGround;
    }
    public void setCourseOverGround( double value ) {
        if( !Comparer.equalsDouble( _courseOverGround, value ) ) {
            _courseOverGround = value;
            onPropertyChanged( );
        }
    }

    public int getGnssPositionStatus( ) {
        return _gnssPositionStatus;
    }
    public void setGnssPositionStatus( int value ) {
        if( !Comparer.equalsInt32( _gnssPositionStatus, value ) ) {
            _gnssPositionStatus = value;
            onPropertyChanged( );
        }
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( !Comparer.equalsInt32( _spare, value ) ) {
            _spare = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _positionAccuracy );
        destination.writeInt32( _raim );
        destination.writeInt32( _navigationStatus );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeDouble( _speedOverGround );
        destination.writeDouble( _courseOverGround );
        destination.writeInt32( _gnssPositionStatus );
        destination.writeInt32( _spare );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _positionAccuracy = source.readInt32( );
        _raim = source.readInt32( );
        _navigationStatus = source.readInt32( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _speedOverGround = source.readDouble( );
        _courseOverGround = source.readDouble( );
        _gnssPositionStatus = source.readInt32( );
        _spare = source.readInt32( );
    }

}
