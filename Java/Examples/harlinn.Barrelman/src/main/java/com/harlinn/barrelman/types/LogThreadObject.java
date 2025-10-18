package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogThreadObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.LogThread;

    private long _rowVersion = 0;
    private Guid _process;
    private DateTime _started;
    private DateTime _stopped;
    private long _threadId = 0;
    private String _name = "";

    public LogThreadObject( ) {
    }
    public LogThreadObject( byte objectState, Guid id, long rowVersion, Guid process, DateTime started, DateTime stopped, long threadId, String name ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._process = process;
        this._started = started;
        this._stopped = stopped;
        this._threadId = threadId;
        this._name = name;
    }

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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getProcess( ) {
        return _process;
    }
    public void setProcess( Guid value ) {
        if( !Comparer.equalsGuid( _process, value ) ) {
            _process = value;
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

    public long getThreadId( ) {
        return _threadId;
    }
    public void setThreadId( long value ) {
        if( !Comparer.equalsInt64( _threadId, value ) ) {
            _threadId = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( LogThreadObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._process = this._process;
        targetObject._started = this._started;
        targetObject._stopped = this._stopped;
        targetObject._threadId = this._threadId;
        targetObject._name = this._name;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (LogThreadObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._process, other._process ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._started, other._started ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._stopped, other._stopped ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._threadId, other._threadId ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _process );
        destination.writeDateTime( _started );
        destination.writeNullableDateTime( _stopped );
        destination.writeInt64( _threadId );
        destination.writeStringUtf8( _name );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _process = source.readGuid( );
        _started = source.readDateTime( );
        _stopped = source.readNullableDateTime( );
        _threadId = source.readInt64( );
        _name = source.readString( );
    }

}
