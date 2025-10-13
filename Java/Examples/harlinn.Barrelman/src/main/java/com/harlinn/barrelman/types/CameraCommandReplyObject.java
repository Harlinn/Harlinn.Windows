package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandReplyObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _camera;
    private DateTime _timestamp;
    private Guid _command;
    private int _status = DeviceCommandReplyStatus.Unknown;
    private String _message = "";
    private double _panAngle = 0.0;
    private double _tiltAngle = 0.0;
    private double _focalLength = 0.0;

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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getCamera( ) {
        return _camera;
    }
    public void setCamera( Guid value ) {
        if( _camera != value ) {
            this._camera = value;
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

    public Guid getCommand( ) {
        return _command;
    }
    public void setCommand( Guid value ) {
        if( _command != value ) {
            this._command = value;
            onPropertyChanged( );
        }
    }

    public int getStatus( ) {
        return _status;
    }
    public void setStatus( int value ) {
        if( _status != value ) {
            this._status = value;
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

    public double getPanAngle( ) {
        return _panAngle;
    }
    public void setPanAngle( double value ) {
        if( _panAngle != value ) {
            this._panAngle = value;
            onPropertyChanged( );
        }
    }

    public double getTiltAngle( ) {
        return _tiltAngle;
    }
    public void setTiltAngle( double value ) {
        if( _tiltAngle != value ) {
            this._tiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( double value ) {
        if( _focalLength != value ) {
            this._focalLength = value;
            onPropertyChanged( );
        }
    }


}
