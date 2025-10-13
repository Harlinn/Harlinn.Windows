package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogThreadObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _process;
    private DateTime _started;
    private DateTime _stopped;
    private long _threadId = 0;
    private String _name = "";

    @Override
    public int getObjectType( ) {
        return Kind.LogThread;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogThreadObject( );
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

    public Guid getProcess( ) {
        return _process;
    }
    public void setProcess( Guid value ) {
        if( _process != value ) {
            this._process = value;
            onPropertyChanged( );
        }
    }

    public DateTime getStarted( ) {
        return _started;
    }
    public void setStarted( DateTime value ) {
        if( _started != value ) {
            this._started = value;
            onPropertyChanged( );
        }
    }

    public DateTime getStopped( ) {
        return _stopped;
    }
    public void setStopped( DateTime value ) {
        if( _stopped != value ) {
            this._stopped = value;
            onPropertyChanged( );
        }
    }

    public long getThreadId( ) {
        return _threadId;
    }
    public void setThreadId( long value ) {
        if( _threadId != value ) {
            this._threadId = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( _name != value ) {
            this._name = value;
            onPropertyChanged( );
        }
    }


}
