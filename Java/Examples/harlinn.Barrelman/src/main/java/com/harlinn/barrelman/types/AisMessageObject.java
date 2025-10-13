package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class AisMessageObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _aisDevice;
    private DateTime _receivedTimestamp;
    private long _messageSequenceNumber = 0;
    private int _repeat = 0;
    private Guid _mmsi;


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getAisDevice( ) {
        return _aisDevice;
    }
    public void setAisDevice( Guid value ) {
        if( _aisDevice != value ) {
            this._aisDevice = value;
            onPropertyChanged( );
        }
    }

    public DateTime getReceivedTimestamp( ) {
        return _receivedTimestamp;
    }
    public void setReceivedTimestamp( DateTime value ) {
        if( _receivedTimestamp != value ) {
            this._receivedTimestamp = value;
            onPropertyChanged( );
        }
    }

    public long getMessageSequenceNumber( ) {
        return _messageSequenceNumber;
    }
    public void setMessageSequenceNumber( long value ) {
        if( _messageSequenceNumber != value ) {
            this._messageSequenceNumber = value;
            onPropertyChanged( );
        }
    }

    public int getRepeat( ) {
        return _repeat;
    }
    public void setRepeat( int value ) {
        if( _repeat != value ) {
            this._repeat = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi( ) {
        return _mmsi;
    }
    public void setMmsi( Guid value ) {
        if( _mmsi != value ) {
            this._mmsi = value;
            onPropertyChanged( );
        }
    }


}
