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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getThread( ) {
        return _thread;
    }
    public void setThread( Guid value ) {
        if( !Comparer.equalsGuid( _thread, value ) ) {
            _thread = value;
            onPropertyChanged( );
        }
    }

    public long getSequenceNumber( ) {
        return _sequenceNumber;
    }
    public void setSequenceNumber( long value ) {
        if( !Comparer.equalsInt64( _sequenceNumber, value ) ) {
            _sequenceNumber = value;
            onPropertyChanged( );
        }
    }

    public int getLevel( ) {
        return _level;
    }
    public void setLevel( int value ) {
        if( !Comparer.equalsInt32( _level, value ) ) {
            _level = value;
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

    public int getDepth( ) {
        return _depth;
    }
    public void setDepth( int value ) {
        if( !Comparer.equalsInt32( _depth, value ) ) {
            _depth = value;
            onPropertyChanged( );
        }
    }

    public Guid getLocation( ) {
        return _location;
    }
    public void setLocation( Guid value ) {
        if( !Comparer.equalsGuid( _location, value ) ) {
            _location = value;
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

    public String getExceptionString( ) {
        return _exceptionString;
    }
    public void setExceptionString( String value ) {
        if( !Comparer.equalsString( _exceptionString, value ) ) {
            _exceptionString = value;
            onPropertyChanged( );
        }
    }

    public byte[] getPropertiesData( ) {
        return _propertiesData;
    }
    public void setPropertiesData( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _propertiesData, value ) ) {
            _propertiesData = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( LogRecordObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._thread = this._thread;
        targetObject._sequenceNumber = this._sequenceNumber;
        targetObject._level = this._level;
        targetObject._timestamp = this._timestamp;
        targetObject._depth = this._depth;
        targetObject._location = this._location;
        targetObject._message = this._message;
        targetObject._exceptionString = this._exceptionString;
        targetObject._propertiesData = this._propertiesData != null ? this._propertiesData.clone() : this._propertiesData;;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (LogRecordObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._thread, other._thread ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._sequenceNumber, other._sequenceNumber ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._level, other._level ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._depth, other._depth ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._location, other._location ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._message, other._message ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._exceptionString, other._exceptionString ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8Array( this._propertiesData, other._propertiesData ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _thread );
        destination.writeInt64( _sequenceNumber );
        destination.writeInt32( _level );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _depth );
        destination.writeGuid( _location );
        destination.writeStringUtf8( _message );
        destination.writeStringUtf8( _exceptionString );
        destination.writeUInt8Array( _propertiesData );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _thread = source.readGuid( );
        _sequenceNumber = source.readInt64( );
        _level = source.readInt32( );
        _timestamp = source.readDateTime( );
        _depth = source.readInt32( );
        _location = source.readGuid( );
        _message = source.readString( );
        _exceptionString = source.readString( );
        _propertiesData = source.readUInt8Array( );
    }

}
