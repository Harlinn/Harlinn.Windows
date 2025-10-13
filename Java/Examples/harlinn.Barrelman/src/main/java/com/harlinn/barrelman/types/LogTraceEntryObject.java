package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogTraceEntryObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _thread;
    private long _sequenceNumber = 0;
    private Guid _location;
    private int _depth = 0;
    private DateTime _entered;
    private DateTime _ended;

    @Override
    public int getObjectType( ) {
        return Kind.LogTraceEntry;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogTraceEntryObject( );
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

    public Guid getThread( ) {
        return _thread;
    }
    public void setThread( Guid value ) {
        if( _thread != value ) {
            this._thread = value;
            onPropertyChanged( );
        }
    }

    public long getSequenceNumber( ) {
        return _sequenceNumber;
    }
    public void setSequenceNumber( long value ) {
        if( _sequenceNumber != value ) {
            this._sequenceNumber = value;
            onPropertyChanged( );
        }
    }

    public Guid getLocation( ) {
        return _location;
    }
    public void setLocation( Guid value ) {
        if( _location != value ) {
            this._location = value;
            onPropertyChanged( );
        }
    }

    public int getDepth( ) {
        return _depth;
    }
    public void setDepth( int value ) {
        if( _depth != value ) {
            this._depth = value;
            onPropertyChanged( );
        }
    }

    public DateTime getEntered( ) {
        return _entered;
    }
    public void setEntered( DateTime value ) {
        if( _entered != value ) {
            this._entered = value;
            onPropertyChanged( );
        }
    }

    public DateTime getEnded( ) {
        return _ended;
    }
    public void setEnded( DateTime value ) {
        if( _ended != value ) {
            this._ended = value;
            onPropertyChanged( );
        }
    }


}
