package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStandardClassBCsPositionReportMessageObject extends AisMessageObject {

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
        if( _reserved != value ) {
            this._reserved = value;
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

    public Integer getTrueHeading( ) {
        return _trueHeading;
    }
    public void setTrueHeading( Integer value ) {
        if( _trueHeading != value ) {
            this._trueHeading = value;
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

    public int getRegionalReserved( ) {
        return _regionalReserved;
    }
    public void setRegionalReserved( int value ) {
        if( _regionalReserved != value ) {
            this._regionalReserved = value;
            onPropertyChanged( );
        }
    }

    public boolean getIsCsUnit( ) {
        return _isCsUnit;
    }
    public void setIsCsUnit( boolean value ) {
        if( _isCsUnit != value ) {
            this._isCsUnit = value;
            onPropertyChanged( );
        }
    }

    public boolean getHasDisplay( ) {
        return _hasDisplay;
    }
    public void setHasDisplay( boolean value ) {
        if( _hasDisplay != value ) {
            this._hasDisplay = value;
            onPropertyChanged( );
        }
    }

    public boolean getHasDscCapability( ) {
        return _hasDscCapability;
    }
    public void setHasDscCapability( boolean value ) {
        if( _hasDscCapability != value ) {
            this._hasDscCapability = value;
            onPropertyChanged( );
        }
    }

    public boolean getBand( ) {
        return _band;
    }
    public void setBand( boolean value ) {
        if( _band != value ) {
            this._band = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanAcceptMessage22( ) {
        return _canAcceptMessage22;
    }
    public void setCanAcceptMessage22( boolean value ) {
        if( _canAcceptMessage22 != value ) {
            this._canAcceptMessage22 = value;
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
