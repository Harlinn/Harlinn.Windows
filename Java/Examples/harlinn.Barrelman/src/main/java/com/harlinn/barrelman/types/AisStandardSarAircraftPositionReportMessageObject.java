package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStandardSarAircraftPositionReportMessageObject extends AisMessageObject {

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
