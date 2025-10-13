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
        if( _positionAccuracy != value ) {
            this._positionAccuracy = value;
            onPropertyChanged( );
        }
    }

    public int getRaim( ) {
        return _raim;
    }
    public void setRaim( int value ) {
        if( _raim != value ) {
            this._raim = value;
            onPropertyChanged( );
        }
    }

    public int getNavigationStatus( ) {
        return _navigationStatus;
    }
    public void setNavigationStatus( int value ) {
        if( _navigationStatus != value ) {
            this._navigationStatus = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( _longitude != value ) {
            this._longitude = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( _latitude != value ) {
            this._latitude = value;
            onPropertyChanged( );
        }
    }

    public double getSpeedOverGround( ) {
        return _speedOverGround;
    }
    public void setSpeedOverGround( double value ) {
        if( _speedOverGround != value ) {
            this._speedOverGround = value;
            onPropertyChanged( );
        }
    }

    public double getCourseOverGround( ) {
        return _courseOverGround;
    }
    public void setCourseOverGround( double value ) {
        if( _courseOverGround != value ) {
            this._courseOverGround = value;
            onPropertyChanged( );
        }
    }

    public int getGnssPositionStatus( ) {
        return _gnssPositionStatus;
    }
    public void setGnssPositionStatus( int value ) {
        if( _gnssPositionStatus != value ) {
            this._gnssPositionStatus = value;
            onPropertyChanged( );
        }
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( _spare != value ) {
            this._spare = value;
            onPropertyChanged( );
        }
    }


}
