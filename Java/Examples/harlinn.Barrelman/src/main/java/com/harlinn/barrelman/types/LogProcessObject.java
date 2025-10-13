package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogProcessObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _application;
    private Guid _host;
    private DateTime _started;
    private DateTime _stopped;
    private long _processId = 0;
    private String _path = "";
    private String _identity = "";

    @Override
    public int getObjectType( ) {
        return Kind.LogProcess;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogProcessObject( );
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

    public Guid getApplication( ) {
        return _application;
    }
    public void setApplication( Guid value ) {
        if( _application != value ) {
            this._application = value;
            onPropertyChanged( );
        }
    }

    public Guid getHost( ) {
        return _host;
    }
    public void setHost( Guid value ) {
        if( _host != value ) {
            this._host = value;
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

    public long getProcessId( ) {
        return _processId;
    }
    public void setProcessId( long value ) {
        if( _processId != value ) {
            this._processId = value;
            onPropertyChanged( );
        }
    }

    public String getPath( ) {
        return _path;
    }
    public void setPath( String value ) {
        if( _path != value ) {
            this._path = value;
            onPropertyChanged( );
        }
    }

    public String getIdentity( ) {
        return _identity;
    }
    public void setIdentity( String value ) {
        if( _identity != value ) {
            this._identity = value;
            onPropertyChanged( );
        }
    }


}
