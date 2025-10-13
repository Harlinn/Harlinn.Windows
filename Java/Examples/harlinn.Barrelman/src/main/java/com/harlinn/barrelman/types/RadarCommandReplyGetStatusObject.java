package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarCommandReplyGetStatusObject extends RadarCommandReplyObject {

    private int _azimuthCount = 0;
    private int _triggerCount = 0;
    private TimeSpan _rotationCount;
    private int _pulse = RadarPulse.Short;
    private boolean _tx = false;

    @Override
    public int getObjectType( ) {
        return Kind.RadarCommandReplyGetStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarCommandReplyGetStatusObject( );
    }

    public int getAzimuthCount( ) {
        return _azimuthCount;
    }
    public void setAzimuthCount( int value ) {
        if( _azimuthCount != value ) {
            this._azimuthCount = value;
            onPropertyChanged( );
        }
    }

    public int getTriggerCount( ) {
        return _triggerCount;
    }
    public void setTriggerCount( int value ) {
        if( _triggerCount != value ) {
            this._triggerCount = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getRotationCount( ) {
        return _rotationCount;
    }
    public void setRotationCount( TimeSpan value ) {
        if( _rotationCount != value ) {
            this._rotationCount = value;
            onPropertyChanged( );
        }
    }

    public int getPulse( ) {
        return _pulse;
    }
    public void setPulse( int value ) {
        if( _pulse != value ) {
            this._pulse = value;
            onPropertyChanged( );
        }
    }

    public boolean getTx( ) {
        return _tx;
    }
    public void setTx( boolean value ) {
        if( _tx != value ) {
            this._tx = value;
            onPropertyChanged( );
        }
    }


}
