package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AlarmStateChangeObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _alarm;
    private DateTime _timestamp;
    private int _state = AlarmState.Unknown;

    @Override
    public int getObjectType( ) {
        return Kind.AlarmStateChange;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AlarmStateChangeObject( );
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

    public Guid getAlarm( ) {
        return _alarm;
    }
    public void setAlarm( Guid value ) {
        if( _alarm != value ) {
            this._alarm = value;
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

    public int getState( ) {
        return _state;
    }
    public void setState( int value ) {
        if( _state != value ) {
            this._state = value;
            onPropertyChanged( );
        }
    }


}
