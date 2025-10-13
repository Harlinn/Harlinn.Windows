package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class TrackBaseObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _tracker;
    private long _trackNumber = 0;
    private DateTime _timestamp;


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getTracker( ) {
        return _tracker;
    }
    public void setTracker( Guid value ) {
        if( _tracker != value ) {
            this._tracker = value;
            onPropertyChanged( );
        }
    }

    public long getTrackNumber( ) {
        return _trackNumber;
    }
    public void setTrackNumber( long value ) {
        if( _trackNumber != value ) {
            this._trackNumber = value;
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


}
