package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class AisPositionReportClassAMessageBaseObject extends AisMessageObject {

    public final int KIND = Kind.AisPositionReportClassAMessageBase;

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

    public AisPositionReportClassAMessageBaseObject( ) {
    }
    public AisPositionReportClassAMessageBaseObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int navigationStatus, Integer rateOfTurn, double speedOverGround, int positionAccuracy, double longitude, double latitude, double courseOverGround, Integer trueHeading, int timestamp, int maneuverIndicator, int spare, int raim, int radioStatus ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._navigationStatus = navigationStatus;
        this._rateOfTurn = rateOfTurn;
        this._speedOverGround = speedOverGround;
        this._positionAccuracy = positionAccuracy;
        this._longitude = longitude;
        this._latitude = latitude;
        this._courseOverGround = courseOverGround;
        this._trueHeading = trueHeading;
        this._timestamp = timestamp;
        this._maneuverIndicator = maneuverIndicator;
        this._spare = spare;
        this._raim = raim;
        this._radioStatus = radioStatus;
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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisPositionReportClassAMessageBaseObject )target;
        targetObject._navigationStatus = this._navigationStatus;
        targetObject._rateOfTurn = this._rateOfTurn;
        targetObject._speedOverGround = this._speedOverGround;
        targetObject._positionAccuracy = this._positionAccuracy;
        targetObject._longitude = this._longitude;
        targetObject._latitude = this._latitude;
        targetObject._courseOverGround = this._courseOverGround;
        targetObject._trueHeading = this._trueHeading;
        targetObject._timestamp = this._timestamp;
        targetObject._maneuverIndicator = this._maneuverIndicator;
        targetObject._spare = this._spare;
        targetObject._raim = this._raim;
        targetObject._radioStatus = this._radioStatus;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisPositionReportClassAMessageBaseObject)obj;
        if( !Comparer.equalsInt32( this._navigationStatus, other._navigationStatus ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._rateOfTurn, other._rateOfTurn ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._speedOverGround, other._speedOverGround ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._positionAccuracy, other._positionAccuracy ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._courseOverGround, other._courseOverGround ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._trueHeading, other._trueHeading ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._maneuverIndicator, other._maneuverIndicator ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._raim, other._raim ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._radioStatus, other._radioStatus ) ) {
            return false;
        }
        return true;
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
