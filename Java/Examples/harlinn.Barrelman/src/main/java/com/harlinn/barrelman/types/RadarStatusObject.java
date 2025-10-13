package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarStatusObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _azimuthCount = 0;
    private int _triggerCount = 0;
    private TimeSpan _rotationTime;
    private int _pulse = RadarPulse.Short;
    private boolean _tx = false;
    private boolean _tracking = false;

    @Override
    public int getObjectType( ) {
        return Kind.RadarStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarStatusObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( _radar != value ) {
            this._radar = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
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

    public TimeSpan getRotationTime( ) {
        return _rotationTime;
    }
    public void setRotationTime( TimeSpan value ) {
        if( _rotationTime != value ) {
            this._rotationTime = value;
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

    public boolean getTracking( ) {
        return _tracking;
    }
    public void setTracking( boolean value ) {
        if( _tracking != value ) {
            this._tracking = value;
            onPropertyChanged( );
        }
    }


}
