package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadioCommandReplyObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radio;
    private DateTime _timestamp;
    private Guid _command;
    private int _status = DeviceCommandReplyStatus.Unknown;
    private String _message = "";

    @Override
    public int getObjectType( ) {
        return Kind.RadioCommandReply;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadioCommandReplyObject( );
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

    public Guid getRadio( ) {
        return _radio;
    }
    public void setRadio( Guid value ) {
        if( !Comparer.equalsGuid( _radio, value ) ) {
            _radio = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public Guid getCommand( ) {
        return _command;
    }
    public void setCommand( Guid value ) {
        if( !Comparer.equalsNullableGuid( _command, value ) ) {
            _command = value;
            onPropertyChanged( );
        }
    }

    public int getStatus( ) {
        return _status;
    }
    public void setStatus( int value ) {
        if( !Comparer.equalsInt32( _status, value ) ) {
            _status = value;
            onPropertyChanged( );
        }
    }

    public String getMessage( ) {
        return _message;
    }
    public void setMessage( String value ) {
        if( !Comparer.equalsString( _message, value ) ) {
            _message = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadioCommandReplyObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._radio = this._radio;
        targetObject._timestamp = this._timestamp;
        targetObject._command = this._command;
        targetObject._status = this._status;
        targetObject._message = this._message;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadioCommandReplyObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._radio, other._radio ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._command, other._command ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._status, other._status ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._message, other._message ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radio );
        destination.writeDateTime( _timestamp );
        destination.writeNullableGuid( _command );
        destination.writeInt32( _status );
        destination.writeStringUtf8( _message );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radio = source.readGuid( );
        _timestamp = source.readDateTime( );
        _command = source.readNullableGuid( );
        _status = source.readInt32( );
        _message = source.readString( );
    }

}
