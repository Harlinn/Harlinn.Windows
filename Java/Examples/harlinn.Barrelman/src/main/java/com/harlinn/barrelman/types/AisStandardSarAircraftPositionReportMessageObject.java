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
        if( _altitude != value ) {
            this._altitude = value;
            onPropertyChanged( );
        }
    }

    public int getSpeedOverGround( ) {
        return _speedOverGround;
    }
    public void setSpeedOverGround( int value ) {
        if( _speedOverGround != value ) {
            this._speedOverGround = value;
            onPropertyChanged( );
        }
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

    public double getCourseOverGround( ) {
        return _courseOverGround;
    }
    public void setCourseOverGround( double value ) {
        if( _courseOverGround != value ) {
            this._courseOverGround = value;
            onPropertyChanged( );
        }
    }

    public int getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( int value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getReserved( ) {
        return _reserved;
    }
    public void setReserved( int value ) {
        if( _reserved != value ) {
            this._reserved = value;
            onPropertyChanged( );
        }
    }

    public boolean getDataTerminalReady( ) {
        return _dataTerminalReady;
    }
    public void setDataTerminalReady( boolean value ) {
        if( _dataTerminalReady != value ) {
            this._dataTerminalReady = value;
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

    public boolean getAssigned( ) {
        return _assigned;
    }
    public void setAssigned( boolean value ) {
        if( _assigned != value ) {
            this._assigned = value;
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

    public int getRadioStatus( ) {
        return _radioStatus;
    }
    public void setRadioStatus( int value ) {
        if( _radioStatus != value ) {
            this._radioStatus = value;
            onPropertyChanged( );
        }
    }


}
