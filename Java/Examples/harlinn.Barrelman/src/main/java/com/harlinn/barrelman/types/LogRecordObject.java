package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogRecordObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _thread;
    private long _sequenceNumber = 0;
    private int _level = LogLevel.Unknown;
    private DateTime _timestamp;
    private int _depth = 0;
    private Guid _location;
    private String _message = "";
    private String _exceptionString = "";
    private byte[] _propertiesData = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.LogRecord;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogRecordObject( );
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

    public int getLevel( ) {
        return _level;
    }
    public void setLevel( int value ) {
        if( _level != value ) {
            this._level = value;
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

    public int getDepth( ) {
        return _depth;
    }
    public void setDepth( int value ) {
        if( _depth != value ) {
            this._depth = value;
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

    public String getMessage( ) {
        return _message;
    }
    public void setMessage( String value ) {
        if( _message != value ) {
            this._message = value;
            onPropertyChanged( );
        }
    }

    public String getExceptionString( ) {
        return _exceptionString;
    }
    public void setExceptionString( String value ) {
        if( _exceptionString != value ) {
            this._exceptionString = value;
            onPropertyChanged( );
        }
    }

    public byte[] getPropertiesData( ) {
        return _propertiesData;
    }
    public void setPropertiesData( byte[] value ) {
        if( _propertiesData != value ) {
            this._propertiesData = value;
            onPropertyChanged( );
        }
    }


}
