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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getApplication( ) {
        return _application;
    }
    public void setApplication( Guid value ) {
        if( !Comparer.equalsGuid( _application, value ) ) {
            _application = value;
            onPropertyChanged( );
        }
    }

    public Guid getHost( ) {
        return _host;
    }
    public void setHost( Guid value ) {
        if( !Comparer.equalsNullableGuid( _host, value ) ) {
            _host = value;
            onPropertyChanged( );
        }
    }

    public DateTime getStarted( ) {
        return _started;
    }
    public void setStarted( DateTime value ) {
        if( !Comparer.equalsDateTime( _started, value ) ) {
            _started = value;
            onPropertyChanged( );
        }
    }

    public DateTime getStopped( ) {
        return _stopped;
    }
    public void setStopped( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _stopped, value ) ) {
            _stopped = value;
            onPropertyChanged( );
        }
    }

    public long getProcessId( ) {
        return _processId;
    }
    public void setProcessId( long value ) {
        if( !Comparer.equalsInt64( _processId, value ) ) {
            _processId = value;
            onPropertyChanged( );
        }
    }

    public String getPath( ) {
        return _path;
    }
    public void setPath( String value ) {
        if( !Comparer.equalsString( _path, value ) ) {
            _path = value;
            onPropertyChanged( );
        }
    }

    public String getIdentity( ) {
        return _identity;
    }
    public void setIdentity( String value ) {
        if( !Comparer.equalsString( _identity, value ) ) {
            _identity = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( LogProcessObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._application = this._application;
        targetObject._host = this._host;
        targetObject._started = this._started;
        targetObject._stopped = this._stopped;
        targetObject._processId = this._processId;
        targetObject._path = this._path;
        targetObject._identity = this._identity;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (LogProcessObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._application, other._application ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._host, other._host ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._started, other._started ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._stopped, other._stopped ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._processId, other._processId ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._path, other._path ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._identity, other._identity ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _application );
        destination.writeNullableGuid( _host );
        destination.writeDateTime( _started );
        destination.writeNullableDateTime( _stopped );
        destination.writeInt64( _processId );
        destination.writeStringUtf8( _path );
        destination.writeStringUtf8( _identity );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _application = source.readGuid( );
        _host = source.readNullableGuid( );
        _started = source.readDateTime( );
        _stopped = source.readNullableDateTime( );
        _processId = source.readInt64( );
        _path = source.readString( );
        _identity = source.readString( );
    }

}
