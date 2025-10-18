package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStandardClassBCsPositionReportMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisStandardClassBCsPositionReportMessage;

    private int _reserved = 0;
    private double _speedOverGround = 0.0;
    private int _positionAccuracy = PositionAccuracy.Low;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private double _courseOverGround = 0.0;
    private Integer _trueHeading;
    private int _timestamp = 0;
    private int _regionalReserved = 0;
    private boolean _isCsUnit = false;
    private boolean _hasDisplay = false;
    private boolean _hasDscCapability = false;
    private boolean _band = false;
    private boolean _canAcceptMessage22 = false;
    private boolean _assigned = false;
    private int _raim = Raim.NotInUse;
    private int _radioStatus = 0;

    public AisStandardClassBCsPositionReportMessageObject( ) {
    }
    public AisStandardClassBCsPositionReportMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int reserved, double speedOverGround, int positionAccuracy, double longitude, double latitude, double courseOverGround, Integer trueHeading, int timestamp, int regionalReserved, boolean isCsUnit, boolean hasDisplay, boolean hasDscCapability, boolean band, boolean canAcceptMessage22, boolean assigned, int raim, int radioStatus ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._reserved = reserved;
        this._speedOverGround = speedOverGround;
        this._positionAccuracy = positionAccuracy;
        this._longitude = longitude;
        this._latitude = latitude;
        this._courseOverGround = courseOverGround;
        this._trueHeading = trueHeading;
        this._timestamp = timestamp;
        this._regionalReserved = regionalReserved;
        this._isCsUnit = isCsUnit;
        this._hasDisplay = hasDisplay;
        this._hasDscCapability = hasDscCapability;
        this._band = band;
        this._canAcceptMessage22 = canAcceptMessage22;
        this._assigned = assigned;
        this._raim = raim;
        this._radioStatus = radioStatus;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisStandardClassBCsPositionReportMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisStandardClassBCsPositionReportMessageObject( );
    }

    public int getReserved( ) {
        return _reserved;
    }
    public void setReserved( int value ) {
        if( !Comparer.equalsInt32( _reserved, value ) ) {
            _reserved = value;
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

    public int getRegionalReserved( ) {
        return _regionalReserved;
    }
    public void setRegionalReserved( int value ) {
        if( !Comparer.equalsInt32( _regionalReserved, value ) ) {
            _regionalReserved = value;
            onPropertyChanged( );
        }
    }

    public boolean getIsCsUnit( ) {
        return _isCsUnit;
    }
    public void setIsCsUnit( boolean value ) {
        if( !Comparer.equalsBoolean( _isCsUnit, value ) ) {
            _isCsUnit = value;
            onPropertyChanged( );
        }
    }

    public boolean getHasDisplay( ) {
        return _hasDisplay;
    }
    public void setHasDisplay( boolean value ) {
        if( !Comparer.equalsBoolean( _hasDisplay, value ) ) {
            _hasDisplay = value;
            onPropertyChanged( );
        }
    }

    public boolean getHasDscCapability( ) {
        return _hasDscCapability;
    }
    public void setHasDscCapability( boolean value ) {
        if( !Comparer.equalsBoolean( _hasDscCapability, value ) ) {
            _hasDscCapability = value;
            onPropertyChanged( );
        }
    }

    public boolean getBand( ) {
        return _band;
    }
    public void setBand( boolean value ) {
        if( !Comparer.equalsBoolean( _band, value ) ) {
            _band = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanAcceptMessage22( ) {
        return _canAcceptMessage22;
    }
    public void setCanAcceptMessage22( boolean value ) {
        if( !Comparer.equalsBoolean( _canAcceptMessage22, value ) ) {
            _canAcceptMessage22 = value;
            onPropertyChanged( );
        }
    }

    public boolean getAssigned( ) {
        return _assigned;
    }
    public void setAssigned( boolean value ) {
        if( !Comparer.equalsBoolean( _assigned, value ) ) {
            _assigned = value;
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
        var targetObject = ( AisStandardClassBCsPositionReportMessageObject )target;
        targetObject._reserved = this._reserved;
        targetObject._speedOverGround = this._speedOverGround;
        targetObject._positionAccuracy = this._positionAccuracy;
        targetObject._longitude = this._longitude;
        targetObject._latitude = this._latitude;
        targetObject._courseOverGround = this._courseOverGround;
        targetObject._trueHeading = this._trueHeading;
        targetObject._timestamp = this._timestamp;
        targetObject._regionalReserved = this._regionalReserved;
        targetObject._isCsUnit = this._isCsUnit;
        targetObject._hasDisplay = this._hasDisplay;
        targetObject._hasDscCapability = this._hasDscCapability;
        targetObject._band = this._band;
        targetObject._canAcceptMessage22 = this._canAcceptMessage22;
        targetObject._assigned = this._assigned;
        targetObject._raim = this._raim;
        targetObject._radioStatus = this._radioStatus;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisStandardClassBCsPositionReportMessageObject)obj;
        if( !Comparer.equalsInt32( this._reserved, other._reserved ) ) {
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
        if( !Comparer.equalsInt32( this._regionalReserved, other._regionalReserved ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._isCsUnit, other._isCsUnit ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._hasDisplay, other._hasDisplay ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._hasDscCapability, other._hasDscCapability ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._band, other._band ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._canAcceptMessage22, other._canAcceptMessage22 ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._assigned, other._assigned ) ) {
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
        destination.writeInt32( _reserved );
        destination.writeDouble( _speedOverGround );
        destination.writeInt32( _positionAccuracy );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeDouble( _courseOverGround );
        destination.writeNullableInt32( _trueHeading );
        destination.writeInt32( _timestamp );
        destination.writeInt32( _regionalReserved );
        destination.writeBoolean( _isCsUnit );
        destination.writeBoolean( _hasDisplay );
        destination.writeBoolean( _hasDscCapability );
        destination.writeBoolean( _band );
        destination.writeBoolean( _canAcceptMessage22 );
        destination.writeBoolean( _assigned );
        destination.writeInt32( _raim );
        destination.writeInt32( _radioStatus );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _reserved = source.readInt32( );
        _speedOverGround = source.readDouble( );
        _positionAccuracy = source.readInt32( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _courseOverGround = source.readDouble( );
        _trueHeading = source.readNullableInt32( );
        _timestamp = source.readInt32( );
        _regionalReserved = source.readInt32( );
        _isCsUnit = source.readBoolean( );
        _hasDisplay = source.readBoolean( );
        _hasDscCapability = source.readBoolean( );
        _band = source.readBoolean( );
        _canAcceptMessage22 = source.readBoolean( );
        _assigned = source.readBoolean( );
        _raim = source.readInt32( );
        _radioStatus = source.readInt32( );
    }

}
