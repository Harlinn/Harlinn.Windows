package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandReplyObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.CameraCommandReply;

    private long _rowVersion = 0;
    private Guid _camera;
    private DateTime _timestamp;
    private Guid _command;
    private int _status = DeviceCommandReplyStatus.Unknown;
    private String _message = "";
    private double _panAngle = 0.0;
    private double _tiltAngle = 0.0;
    private double _focalLength = 0.0;

    public CameraCommandReplyObject( ) {
    }
    public CameraCommandReplyObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, Guid command, int status, String message, double panAngle, double tiltAngle, double focalLength ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._camera = camera;
        this._timestamp = timestamp;
        this._command = command;
        this._status = status;
        this._message = message;
        this._panAngle = panAngle;
        this._tiltAngle = tiltAngle;
        this._focalLength = focalLength;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandReply;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandReplyObject( );
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

    public Guid getCamera( ) {
        return _camera;
    }
    public void setCamera( Guid value ) {
        if( !Comparer.equalsGuid( _camera, value ) ) {
            _camera = value;
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

    public double getPanAngle( ) {
        return _panAngle;
    }
    public void setPanAngle( double value ) {
        if( !Comparer.equalsDouble( _panAngle, value ) ) {
            _panAngle = value;
            onPropertyChanged( );
        }
    }

    public double getTiltAngle( ) {
        return _tiltAngle;
    }
    public void setTiltAngle( double value ) {
        if( !Comparer.equalsDouble( _tiltAngle, value ) ) {
            _tiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( double value ) {
        if( !Comparer.equalsDouble( _focalLength, value ) ) {
            _focalLength = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandReplyObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._camera = this._camera;
        targetObject._timestamp = this._timestamp;
        targetObject._command = this._command;
        targetObject._status = this._status;
        targetObject._message = this._message;
        targetObject._panAngle = this._panAngle;
        targetObject._tiltAngle = this._tiltAngle;
        targetObject._focalLength = this._focalLength;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandReplyObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._camera, other._camera ) ) {
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
        if( !Comparer.equalsDouble( this._panAngle, other._panAngle ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._tiltAngle, other._tiltAngle ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._focalLength, other._focalLength ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _camera );
        destination.writeDateTime( _timestamp );
        destination.writeNullableGuid( _command );
        destination.writeInt32( _status );
        destination.writeStringUtf8( _message );
        destination.writeDouble( _panAngle );
        destination.writeDouble( _tiltAngle );
        destination.writeDouble( _focalLength );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _camera = source.readGuid( );
        _timestamp = source.readDateTime( );
        _command = source.readNullableGuid( );
        _status = source.readInt32( );
        _message = source.readString( );
        _panAngle = source.readDouble( );
        _tiltAngle = source.readDouble( );
        _focalLength = source.readDouble( );
    }

}
