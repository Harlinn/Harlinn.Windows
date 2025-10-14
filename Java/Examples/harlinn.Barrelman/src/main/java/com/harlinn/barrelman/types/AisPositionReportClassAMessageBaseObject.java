package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class AisPositionReportClassAMessageBaseObject extends AisMessageObject {

    private int _navigationStatus = NavigationStatus.UnderWayUsingEngine;
    private Integer _rateOfTurn;
    private double _speedOverGround = 0.0;
    private int _positionAccuracy = PositionAccuracy.Low;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private double _courseOverGround = 0.0;
    private Integer _trueHeading;
    private int _timestamp = 0;
    private int _maneuverIndicator = ManeuverIndicator.NotAvailable;
    private int _spare = 0;
    private int _raim = Raim.NotInUse;
    private int _radioStatus = 0;


    public int getNavigationStatus( ) {
        return _navigationStatus;
    }
    public void setNavigationStatus( int value ) {
        if( !Comparer.equalsInt32( _navigationStatus, value ) ) {
            _navigationStatus = value;
            onPropertyChanged( );
        }
    }

    public Integer getRateOfTurn( ) {
        return _rateOfTurn;
    }
    public void setRateOfTurn( Integer value ) {
        if( !Comparer.equalsNullableInt32( _rateOfTurn, value ) ) {
            _rateOfTurn = value;
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

    public int getPositionAccuracy( ) {
        return _positionAccuracy;
    }
    public void setPositionAccuracy( int value ) {
        if( !Comparer.equalsInt32( _positionAccuracy, value ) ) {
            _positionAccuracy = value;
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

    public double getCourseOverGround( ) {
        return _courseOverGround;
    }
    public void setCourseOverGround( double value ) {
        if( !Comparer.equalsDouble( _courseOverGround, value ) ) {
            _courseOverGround = value;
            onPropertyChanged( );
        }
    }

    public Integer getTrueHeading( ) {
        return _trueHeading;
    }
    public void setTrueHeading( Integer value ) {
        if( !Comparer.equalsNullableInt32( _trueHeading, value ) ) {
            _trueHeading = value;
            onPropertyChanged( );
        }
    }

    public int getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( int value ) {
        if( !Comparer.equalsInt32( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getManeuverIndicator( ) {
        return _maneuverIndicator;
    }
    public void setManeuverIndicator( int value ) {
        if( !Comparer.equalsInt32( _maneuverIndicator, value ) ) {
            _maneuverIndicator = value;
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

    public int getRaim( ) {
        return _raim;
    }
    public void setRaim( int value ) {
        if( !Comparer.equalsInt32( _raim, value ) ) {
            _raim = value;
            onPropertyChanged( );
        }
    }

    public int getRadioStatus( ) {
        return _radioStatus;
    }
    public void setRadioStatus( int value ) {
        if( !Comparer.equalsInt32( _radioStatus, value ) ) {
            _radioStatus = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _navigationStatus );
        destination.writeNullableInt32( _rateOfTurn );
        destination.writeDouble( _speedOverGround );
        destination.writeInt32( _positionAccuracy );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeDouble( _courseOverGround );
        destination.writeNullableInt32( _trueHeading );
        destination.writeInt32( _timestamp );
        destination.writeInt32( _maneuverIndicator );
        destination.writeInt32( _spare );
        destination.writeInt32( _raim );
        destination.writeInt32( _radioStatus );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _navigationStatus = source.readInt32( );
        _rateOfTurn = source.readNullableInt32( );
        _speedOverGround = source.readDouble( );
        _positionAccuracy = source.readInt32( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _courseOverGround = source.readDouble( );
        _trueHeading = source.readNullableInt32( );
        _timestamp = source.readInt32( );
        _maneuverIndicator = source.readInt32( );
        _spare = source.readInt32( );
        _raim = source.readInt32( );
        _radioStatus = source.readInt32( );
    }

}
