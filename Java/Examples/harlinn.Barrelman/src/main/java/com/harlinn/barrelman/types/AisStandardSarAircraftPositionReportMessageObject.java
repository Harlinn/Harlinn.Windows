package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStandardSarAircraftPositionReportMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisStandardSarAircraftPositionReportMessage;

    private int _altitude = 0;
    private int _speedOverGround = 0;
    private int _positionAccuracy = PositionAccuracy.Low;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private double _courseOverGround = 0.0;
    private int _timestamp = 0;
    private int _reserved = 0;
    private boolean _dataTerminalReady = false;
    private int _spare = 0;
    private boolean _assigned = false;
    private int _raim = Raim.NotInUse;
    private int _radioStatus = 0;

    public AisStandardSarAircraftPositionReportMessageObject( ) {
    }
    public AisStandardSarAircraftPositionReportMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int altitude, int speedOverGround, int positionAccuracy, double longitude, double latitude, double courseOverGround, int timestamp, int reserved, boolean dataTerminalReady, int spare, boolean assigned, int raim, int radioStatus ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._altitude = altitude;
        this._speedOverGround = speedOverGround;
        this._positionAccuracy = positionAccuracy;
        this._longitude = longitude;
        this._latitude = latitude;
        this._courseOverGround = courseOverGround;
        this._timestamp = timestamp;
        this._reserved = reserved;
        this._dataTerminalReady = dataTerminalReady;
        this._spare = spare;
        this._assigned = assigned;
        this._raim = raim;
        this._radioStatus = radioStatus;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisStandardSarAircraftPositionReportMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisStandardSarAircraftPositionReportMessageObject( );
    }

    public int getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( int value ) {
        if( !Comparer.equalsInt32( _altitude, value ) ) {
            _altitude = value;
            onPropertyChanged( );
        }
    }

    public int getSpeedOverGround( ) {
        return _speedOverGround;
    }
    public void setSpeedOverGround( int value ) {
        if( !Comparer.equalsInt32( _speedOverGround, value ) ) {
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

    public int getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( int value ) {
        if( !Comparer.equalsInt32( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
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

    public boolean getDataTerminalReady( ) {
        return _dataTerminalReady;
    }
    public void setDataTerminalReady( boolean value ) {
        if( !Comparer.equalsBoolean( _dataTerminalReady, value ) ) {
            _dataTerminalReady = value;
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
        var targetObject = ( AisStandardSarAircraftPositionReportMessageObject )target;
        targetObject._altitude = this._altitude;
        targetObject._speedOverGround = this._speedOverGround;
        targetObject._positionAccuracy = this._positionAccuracy;
        targetObject._longitude = this._longitude;
        targetObject._latitude = this._latitude;
        targetObject._courseOverGround = this._courseOverGround;
        targetObject._timestamp = this._timestamp;
        targetObject._reserved = this._reserved;
        targetObject._dataTerminalReady = this._dataTerminalReady;
        targetObject._spare = this._spare;
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
        var other = (AisStandardSarAircraftPositionReportMessageObject)obj;
        if( !Comparer.equalsInt32( this._altitude, other._altitude ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._speedOverGround, other._speedOverGround ) ) {
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
        if( !Comparer.equalsInt32( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._reserved, other._reserved ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._dataTerminalReady, other._dataTerminalReady ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
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
        destination.writeInt32( _altitude );
        destination.writeInt32( _speedOverGround );
        destination.writeInt32( _positionAccuracy );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeDouble( _courseOverGround );
        destination.writeInt32( _timestamp );
        destination.writeInt32( _reserved );
        destination.writeBoolean( _dataTerminalReady );
        destination.writeInt32( _spare );
        destination.writeBoolean( _assigned );
        destination.writeInt32( _raim );
        destination.writeInt32( _radioStatus );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _altitude = source.readInt32( );
        _speedOverGround = source.readInt32( );
        _positionAccuracy = source.readInt32( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _courseOverGround = source.readDouble( );
        _timestamp = source.readInt32( );
        _reserved = source.readInt32( );
        _dataTerminalReady = source.readBoolean( );
        _spare = source.readInt32( );
        _assigned = source.readBoolean( );
        _raim = source.readInt32( );
        _radioStatus = source.readInt32( );
    }

}
